#ifndef GENESIS_UTILS_CORE_THREAD_FUNCTIONS_H_
#define GENESIS_UTILS_CORE_THREAD_FUNCTIONS_H_

/*
    Genesis - A toolkit for working with phylogenetic data.
    Copyright (C) 2014-2024 Lucas Czech

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.

    Contact:
    Lucas Czech <lczech@carnegiescience.edu>
    Department of Plant Biology, Carnegie Institution For Science
    260 Panama Street, Stanford, CA 94305, USA
*/

/**
 * @brief
 *
 * @file
 * @ingroup utils
 */

#include <atomic>
#include <cassert>
#include <condition_variable>
#include <functional>
#include <future>
#include <memory>
#include <mutex>
#include <stdexcept>
#include <thread>
#include <utility>
#include <vector>

#include "genesis/utils/core/multi_future.hpp"
#include "genesis/utils/core/options.hpp"
#include "genesis/utils/core/thread_pool.hpp"

namespace genesis {
namespace utils {

// =================================================================================================
//     Parallel Loop
// =================================================================================================

/**
 * @brief Parallel block over a range of elements, breaking the range into blocks for which
 * the @p body function is executed individually.
 *
 * The function takes a @p begin index and an @p end (past-the-end) index, and executes
 * the @p body in @p num_blocks many blocks, by submitting tasks to the @p thread_pool,
 * aiming to equally distribute the work across the range @p begin to @p end.
 * In other words, it is equivalent to `for( T i = begin; i < end; ++i )`.
 *
 * The @p body function to loop through is called once per block. It should take two arguments:
 * the first index in the block and the index after the last index in the block, e.g.:
 *
 * ```
 * []( size_t begin, size_t end ) {
 *     for( size_t i = begin; i < end; ++i ) {
 *         // ...
 *     }
 * }
 * ```
 *
 * The @p thread_pool defaults to using the Options::get().global_thread_pool(). This requires to
 * call Options::get().init_global_thread_pool() first.
 *
 * The @p num_blocks determines the number of blocks to split the loop body into. Default is
 * to use the number of threads in the pool.
 *
 * The function returns a MultiFuture that can be used to wait for all the blocks to finish.
 * If the loop body returns a value, the MultiFuture can also be used to obtain the values
 * returned by each block, for example:
 *
 * ```
 * []( size_t begin, size_t end ) {
 *     size_t block_sum = 0;
 *     for( size_t i = begin; i < end; ++i ) {
 *         // ...
 *         block_sum += ...
 *     }
 *     return block_sum;
 * }
 * ```
 *
 * This is useful for example for aggregating values, such as a parallel sum.
 */
template<
    typename F,
    typename T1, typename T2, typename T = typename std::common_type<T1, T2>::type,
    typename R = typename std::result_of<typename std::decay<F>::type(T, T)>::type
>
MultiFuture<R> parallel_block(
    T1 begin, T2 end, F&& body,
    std::shared_ptr<ThreadPool> thread_pool = nullptr,
    size_t num_blocks = 0
) {
    // If no thread pool was provided, we use the global one.
    if( !thread_pool ) {
        thread_pool = Options::get().global_thread_pool();
    }

    // Get the total range and number of tasks.
    // Casting, so that we work with a common type... bit of a relic, but sure, why not.
    auto begin_t = static_cast<T>( begin );
    auto end_t = static_cast<T>( end );
    if( begin_t > end_t ) {
        std::swap( begin_t, end_t );
    }
    size_t const total_size = end_t - begin_t;

    // Edge case. Nothing to do.
    if( total_size == 0 ) {
        assert( begin_t == end_t );
        return MultiFuture<R>();
    }

    // Default block size is the number of threads, unless there are not even that many tasks,
    // in which case we can use fewer blocks.
    if( num_blocks == 0 ) {
        assert( thread_pool->size() > 0 );
        num_blocks = thread_pool->size();
    }
    if( num_blocks > total_size ) {
        num_blocks = total_size;
    }
    assert( num_blocks > 0 );
    assert( num_blocks <= total_size );

    // Compute the needed sizes. We do _not_ follow BS::thread_pool here, as they currently
    // do not distribute work optimally, see https://github.com/bshoshany/thread-pool/issues/96
    // Instead, we use blocks of minimal size, and add the remainder to the first few blocks,
    // so that the blocks that are one larger than the others run first, minimizing our wait
    // time at the end. See e.g., https://stackoverflow.com/a/36689107
    size_t const block_size = total_size / num_blocks;
    size_t const remainder  = total_size % num_blocks;
    assert( block_size > 0 );
    assert( remainder < num_blocks );

    // Enqueue all blocks.
    size_t current_start = 0;
    MultiFuture<R> result( num_blocks );
    for( size_t i = 0; i < num_blocks; ++i ) {
        // We get the length of the current block, and in the beginning also add one to their
        // length to distribute the remainder elements that did not fit evently into the blocks.
        // Use that length to get the begin and end points, and submit the block.
        auto const l = block_size + ( i < remainder ? 1 : 0 );
        auto const b = begin_t + static_cast<T>( current_start );
        auto const e = begin_t + static_cast<T>( current_start + l );
        assert( l > 0 );
        assert( b < e );
        result[i] = thread_pool->enqueue( std::forward<F>( body ), b, e );

        // Our next block will start where this one ended.
        current_start += l;
        assert( current_start <= total_size );
    }

    // Now we should have processed everything exactly.
    // Check this, then return the future.
    assert( current_start == total_size );
    assert( begin_t + static_cast<T>( current_start ) == end_t );
    return result;
}

/**
 * @brief Parallel `for` over a range of positions, breaking the range into blocks for which
 * the @p body function is executed individually.
 *
 * This is almost the same as parallel_block(), but intended to be used with `for` loops that
 * do not need to compute per-block return values. The function signature of `F` is hence simply
 * expected to be `void F( size_t i )`, and is called for every position in the processed range.
 *
 * ```
 * std::vector<int> numbers( 100 );
 * auto futures = pool->parallel_for(
 *     0, numbers.size(),
 *     [&numbers]( size_t i )
 *     {
 *         numbers[i] *= 2;
 *     }
 * );
 * futures.get();
 * ```
 *
 * This makes it a convenience function; see also parallel_for_each() for container-based data.
 */
template<
    typename F,
    typename T1, typename T2, typename T = typename std::common_type<T1, T2>::type
>
MultiFuture<void> parallel_for(
    T1 begin, T2 end, F&& body,
    std::shared_ptr<ThreadPool> thread_pool = nullptr,
    size_t num_blocks = 0
) {
    return parallel_block(
        begin, end,
        [body]( T b, T e ){
            for( size_t i = b; i < e; ++i ) {
                body(i);
            }
        },
        thread_pool,
        num_blocks
    );
}

/**
 * @brief Parallel `for each` over a container, processing it in blocks for which
 * the @p body function is executed individually.
 *
 * This is almost the same as parallel_for(), but intended to be used with containers.
 * The function signature of `F` is hence simply expected to be `void F( T& element )` or
 * `void F( T const& element )`, and is called for every element in the container.
 *
 * ```
 * std::vector<int> numbers( 100 );
 * auto futures = pool->parallel_for_each(
 *     numbers.begin(), numbers.end(),
 *     []( int& element )
 *     {
 *         element *= 2;
 *     }
 * );
 * futures.get();
 * ```
 *
 * This makes it a convenience function.
 */
template<typename F, typename T>
MultiFuture<void> parallel_for_each(
    T const begin, T const end, F&& body,
    std::shared_ptr<ThreadPool> thread_pool = nullptr,
    size_t num_blocks = 0
) {
    // Boundary checks.
    auto const total = std::distance( begin, end );
    if( total < 0 ) {
        throw std::invalid_argument( "Cannot use parallel_for_each() with a reverse range." );
    }
    if( total == 0 ) {
        return MultiFuture<void>();
    }

    // Run the loop over elements in parallel blocks.
    // For some reason, we need to take `begin` by const copy in the signature above,
    // and copy it again here for the lambda. Otherwise, we run into some weird iterator
    // invalidity issues, that might come from the threading or something... it's weird.
    // The iterator itself is never advanced here, so that should not lead to this error...
    return parallel_block(
        0, total,
        [begin, body]( size_t b, size_t e ){
            for( size_t i = b; i < e; ++i ) {
                body( *(begin + i) );
            }
        },
        thread_pool,
        num_blocks
    );
}

/**
 * @brief Parallel `for each` over a container, processing it in blocks for which
 * the @p body function is executed individually.
 *
 * Expects a random access container that supports `size()` as well as `operator[]` to access
 * individual elements, and a @p body that takes one element of that container to process.
 *
 * ```
 * std::vector<int> numbers( 100 );
 * auto futures = pool->parallel_for_each(
 *     numbers,
 *     []( int& element )
 *     {
 *         element *= 2;
 *     }
 * );
 * futures.get();
 * ```
 *
 * This makes it a convenience function.
 */
template<typename F, typename T>
MultiFuture<void> parallel_for_each(
    T& container, F&& body,
    std::shared_ptr<ThreadPool> thread_pool = nullptr,
    size_t num_blocks = 0
) {
    // Boundary checks.
    if( container.size() == 0 ) {
        return MultiFuture<void>();
    }

    // Run the loop over elements in parallel blocks.
    return parallel_block(
        0, container.size(),
        [&container, body]( size_t b, size_t e ) {
            for( size_t i = b; i < e; ++i ) {
                body( container[ i ] );
            }
        },
        thread_pool,
        num_blocks
    );
}

// =================================================================================================
//     Critical Section
// =================================================================================================

/**
 * @brief Helper class to define a critical section.
 *
 * This is similar to `#pragma omp critical`, in order to synchronize access to a criticla section
 * across multiple threads. The class internally uses a `std::mutex` to guarantee exclusive access
 * for each thread.
 *
 * The class is templated with a `Tag`, so that mutiple independent sections can be defined, each
 * getting their own mutex. The usage for this class is hence to first define the access tag, and
 * then use it as follows:
 *
 *     // Define section tag
 *     struct MyThreadCriticalSection{};
 *
 *     // Start a critical section
 *     {
 *     ThreadCriticalSection<MyThreadCriticalSection> cs;
 *
 *     // Critical section code for MyThreadCriticalSection
 *     std::cout << "Task " << id << " is running in MyThreadCriticalSection." << std::endl;
 *     std::this_thread::sleep_for(std::chrono::milliseconds(100));
 *
 *     } // MyThreadCriticalSection mutex is automatically released here
 *
 * To simplify this, instead of having to define the tag struct each time, we also provide a
 * macro `GENESIS_THREAD_CRITICAL_SECTION(TagName)` to this end:
 *
 *     // Start a critical section
 *     {
 *     GENESIS_THREAD_CRITICAL_SECTION(MyThreadCriticalSection)
 *     //...
 *     }
 *
 * This can however not be used if multiple sections need to be synchronized with the same tag,
 * as the macro would define the same struct multiple times; depending on the scope, this leads
 * either to a multiple definition error, or to structs that are local to their scope, and hence
 * lead to sections that do not synchronize with each other. In that case, use the above instead,
 * with a tag struct that is defined in a fitting scope that is visible to all sections that need
 * to be protected by it.
 */
template<typename Tag>
class ThreadCriticalSection
{
public:

    ThreadCriticalSection()
    {
        get_static_mutex_().lock();
    }

    ~ThreadCriticalSection()
    {
        get_static_mutex_().unlock();
    }

private:

    static std::mutex& get_static_mutex_()
    {
        static std::mutex mutex_;
        return mutex_;
    }
};

// Macro to define a tag and create a ThreadCriticalSection instance
#define GENESIS_THREAD_CRITICAL_SECTION(TagName) \
    struct TagName {}; \
    ThreadCriticalSection<TagName> genesis_critical_section_##TagName;

} // namespace utils
} // namespace genesis

#endif // include guard
