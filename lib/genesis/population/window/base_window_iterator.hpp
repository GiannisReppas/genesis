#ifndef GENESIS_POPULATION_WINDOW_BASE_WINDOW_ITERATOR_H_
#define GENESIS_POPULATION_WINDOW_BASE_WINDOW_ITERATOR_H_

/*
    Genesis - A toolkit for working with phylogenetic data.
    Copyright (C) 2014-2022 Lucas Czech

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
 * @ingroup population
 */

#include "genesis/population/window/window.hpp"
#include "genesis/utils/containers/range.hpp"
#include "genesis/utils/core/std.hpp"

#include <cassert>
#include <functional>
#include <memory>
#include <stdexcept>
#include <string>
#include <type_traits>
#include <utility>

namespace genesis {
namespace population {

// =================================================================================================
//     Base Window Iterator
// =================================================================================================

/**
 * @brief Base iterator class for Window%s over the chromosomes of a genome.
 *
 * This base class serves for sliding windows, windows over regions of a genome, etc.
 *
 * The template parameters are:
 *  * `ForwardIterator`: The type of the underlying iterator over the genome data (that is, the input
 *     iterator from which the windows take their data). Needs to have a member type
 *     `value_type` that specifies the actual input type that the iterator produces, which we here
 *     call the `InputType` (and typedef it as that).
 *  * `DataType`: The data type of the Window::Data that is stored in Window::Entry. The functor
 *    #entry_input_function needs to be provided to convert from `InputType` to this `DataType`.
 *    By default, we take this to be the same as the `InputType`, meaning that the Window contains
 *    the same data type as the underlying iterator that we get our data from.
 *
 * The three functors
 *
 *  * #entry_input_function,
 *  * #chromosome_function, and
 *  * #position_function
 *
 * have to be set in the class prior to starting the iteration.
 *
 * The general usage of the derived classes that actually implement this iterator is as follows,
 * on the example of the SlidingIntervalWindowIterator:
 *
 *     // Make an iterator using some underlying data iterator
 *     // that yields data for one position in the genome at a time.
 *     auto win_it = SlidingIntervalWindowIterator<ForwardIterator>( data_begin, data_end );
 *
 *     // Set functors to access the underlying data.
 *     win_it.entry_input_function = []( DataType const& variant ) {
 *         return variant;
 *     };
 *     win_it.chromosome_function = []( DataType const& variant ) {
 *         return variant.chromosome;
 *     };
 *     win_it.position_function = []( DataType const& variant ) {
 *         return variant.position;
 *     };
 *
 *     // Set properties specific to the derived class.
 *     win_it.width( width );
 *     win_it.stride( stride );
 *
 *     // Iterate over Windows.
 *     for( auto it = win_it.begin(); it != win_it.end(); ++it ) {
 *         ...
 *     }
 *
 * Other derived classes work accordingly.
 */
template<class ForwardIterator, class DataType = typename ForwardIterator::value_type>
class BaseWindowIterator
{
public:

    // -------------------------------------------------------------------------
    //     Typedefs and Enums
    // -------------------------------------------------------------------------

    using self_type         = BaseWindowIterator<ForwardIterator, DataType>;

    using Window            = ::genesis::population::Window<DataType>;
    using Entry             = typename Window::Entry;
    using InputType         = typename ForwardIterator::value_type;

    using iterator_category = std::input_iterator_tag;
    using value_type        = Window;
    using pointer           = value_type*;
    using reference         = value_type&;
    using const_reference   = value_type const&;

    // -------------------------------------------------------------------------
    //     Public Functors
    // -------------------------------------------------------------------------

    /**
     * @brief Functor to convert from the underlying input iterator that provides the data
     * to fill the windows to the data that is stored per window.
     */
    std::function<DataType( InputType const& )> entry_input_function;

    /**
     * @brief Functor that yields the current chromosome, given the input iterator data.
     */
    std::function<std::string( InputType const& )> chromosome_function;

    /**
     * @brief Functor that yields the current position on the chromosome,
     * given the input iterator data.
     */
    std::function<size_t( InputType const& )> position_function;

    // ======================================================================================
    //      Internal Public Iterator
    // ======================================================================================

protected:

    // Forward Declaration.
    class BaseIterator;

public:

    /**
     * @brief Internal public iterator that produces Window%s.
     *
     * This is the iterator that is exposed to the user when calling begin() and end()
     * on the main class. Using this interface ensures that all types of window iterators
     * (sliding window, regions, etc) expose the same type of iterator (at least for the same
     * template parameters), making it easier to re-use code across different types of window
     * iterators.
     *
     * We internally use a PIMPL-like setup to abstract away from this and allow the actual
     * iterator implementations to run their own code. However, we here don't use PIMPL to hide
     * our implementation, but rather to simply abstract from it, so that the public interface
     * stays stable. See BaseIterator below for the class that needs to be derived from to implement
     * the actual window iteration code.
     */
    class Iterator
    {
    public:

        // -------------------------------------------------------------------------
        //     Constructors and Rule of Five
        // -------------------------------------------------------------------------

        using self_type         = BaseWindowIterator<ForwardIterator, DataType>::Iterator;

        using Window            = ::genesis::population::Window<DataType>;
        using Entry             = typename Window::Entry;
        using InputType         = typename ForwardIterator::value_type;

        using iterator_category = std::input_iterator_tag;
        using value_type        = Window;
        using pointer           = value_type*;
        using reference         = value_type&;
        using const_reference   = value_type const&;

    protected:

        Iterator() = delete;

        Iterator( std::unique_ptr<BaseIterator> base_iterator )
            : pimpl_( std::move( base_iterator ))
        {}

    public:

        ~Iterator() = default;

        Iterator( self_type const& ) = default;
        Iterator( self_type&& )      = default;

        Iterator& operator= ( self_type const& ) = default;
        Iterator& operator= ( self_type&& )      = default;

        friend BaseWindowIterator;

        // -------------------------------------------------------------------------
        //     Properties
        // -------------------------------------------------------------------------

        /**
         * @brief Return whether the current iteration is the first of the current chromosome.
         *
         * When iterating over (e.g.) a VCF file with multiple chromosomes, this function is useful
         * to run some initialization per chromosome in the user code, such as preparing some output.
         *
         * See is_last_window() for the respective end-of-chromosome indicator, that can be used
         * to wrap up after a chromosome, such as writing the output that was producing during the
         * iterator.
         */
        bool is_first_window() const
        {
            assert( pimpl_ );
            return pimpl_->is_first_window_;
        }

        /**
         * @brief Return whether the current iteration is the last of the current chromosome.
         *
         * When iterating over (e.g.) a VCF file with multiple chromosomes, this function is useful
         * to wrap up after a chromosome in the user code, such as writing the output that was
         * producing during the iterator.
         *
         * See is_first_window() for the respective beginning-of-chromosome indicator, that can be
         * used to run some initialization per chromosome, such as preparing some output.
         */
        bool is_last_window() const
        {
            assert( pimpl_ );
            return pimpl_->is_last_window_;
        }

        // -------------------------------------------------------------------------
        //     Accessors
        // -------------------------------------------------------------------------

        value_type const & operator*() const
        {
            assert( pimpl_ );
            return pimpl_->get_current_window_();
        }

        value_type & operator*()
        {
            assert( pimpl_ );
            return pimpl_->get_current_window_();
        }

        value_type const * operator->() const
        {
            assert( pimpl_ );
            return &( pimpl_->get_current_window_() );
        }

        value_type * operator->()
        {
            assert( pimpl_ );
            return &( pimpl_->get_current_window_() );
        }

        // -------------------------------------------------------------------------
        //     Iteration
        // -------------------------------------------------------------------------

        self_type& operator ++()
        {
            assert( pimpl_ );
            pimpl_->increment_();
            return *this;
        }

        // self_type operator ++(int)
        // {
        //     auto cpy = *this;
        //     increment_();
        //     return cpy;
        // }

        /**
         * @brief Compare two iterators for equality.
         *
         * Any two iterators that are copies of each other or started from the same parent
         * will compare equal, as long as neither of them is past-the-end.
         * A valid (not past-the-end) iterator and an end() iterator will not compare equal,
         * no matter from which BaseWindowIterator they were created.
         * Two past-the-end iterators compare equal.
         */
        bool operator==( self_type const& other ) const
        {
            assert( pimpl_ );
            assert( other.pimpl_ );

            // We compare the parents as a baseline - two past-the-end iterator shall
            // always compare equal. If only one of them is past-the-end, they will compare false.
            return pimpl_->get_parent_() == other.pimpl_->get_parent_();
        }

        bool operator!=( self_type const& other ) const
        {
            return !(*this == other);
        }

        // -------------------------------------------------------------------------
        //     PIMPL-like Implementation Abstraction
        // -------------------------------------------------------------------------

    private:

        std::unique_ptr<BaseIterator> pimpl_;

    };

    // ======================================================================================
    //      Internal Base Iterator for PIMPL-like Abstraction
    // ======================================================================================

protected:

    /**
     * @brief Internal PIMPL-like implementation of the iterator that produces Window%s.
     *
     * This is the internal iterator class that the actual window iterator needs to derive from.
     * It declares the interface that we expect in the PIMPL-like setup in the above public
     * Iterator.
     */
    class BaseIterator
    {
    public:

        // -------------------------------------------------------------------------
        //     Constructors and Rule of Five
        // -------------------------------------------------------------------------

        using self_type         = BaseWindowIterator<ForwardIterator, DataType>::BaseIterator;

        using Window            = ::genesis::population::Window<DataType>;
        using Entry             = typename Window::Entry;
        using InputType         = typename ForwardIterator::value_type;

        using iterator_category = std::input_iterator_tag;
        using value_type        = Window;
        using pointer           = value_type*;
        using reference         = value_type&;
        using const_reference   = value_type const&;

    protected:

        // BaseIterator() = default;

        /**
         * @brief Construct the base class, which does initialization checks on its member
         * variables to ensure that the user has set up the functors correctly.
         */
        BaseIterator( BaseWindowIterator const* parent )
        {
            init_( parent );
        }

    public:

        ~BaseIterator() = default;

        BaseIterator( self_type const& ) = default;
        BaseIterator( self_type&& )      = default;

        BaseIterator& operator= ( self_type const& ) = default;
        BaseIterator& operator= ( self_type&& )      = default;

        friend BaseWindowIterator;
        friend Iterator;

        // -------------------------------------------------------------------------
        //     Internal Members
        // -------------------------------------------------------------------------

    protected:

        /**
         * @brief Initialize the base iterator class and check that it is set up correctly.
         */
        void init_( BaseWindowIterator const* parent )
        {
            // We use the parent as a check if this Iterator is intended to be a begin()
            // or end() iterator. If its the former, init. If the latter, we are done here.
            // After we are done iterating the input (for which we do need _its_ begin and end
            // iterators), we then set the parent_ to nullptr, as a sign that we are done.
            // This allows us also to know if we reached end() (of the window iteration;
            // not of the underlying data iterator) without having to store the end() iterator
            // when using this class.
            if( ! parent ) {
                return;
            }

            // Check that the functors are set up.
            if( ! parent->entry_input_function ) {
                throw std::runtime_error(
                    "Need to set BaseWindowIterator::entry_input_function "
                    "before iterating over Windows with a Window Iterator."
                );
            }
            if( ! parent->chromosome_function ) {
                throw std::runtime_error(
                    "Need to set BaseWindowIterator::chromosome_function "
                    "before iterating over Windows with a Window Iterator."
                );
            }
            if( ! parent->position_function ) {
                throw std::runtime_error(
                    "Need to set BaseWindowIterator::position_function "
                    "before iterating over Windows with a Window Iterator."
                );
            }

            // Copy over the underlying data iterator.
            current_ = parent->begin_;
            end_     = parent->end_;
        }

        // -------------------------------------------------------------------------
        //     Virtual Members
        // -------------------------------------------------------------------------

    protected:

        /**
         * @brief Advance in the iteration. This function is called from operator++
         */
        virtual void increment_() = 0;

        /**
         * @brief Get the current window that the iterator shall return when dereferenced.
         */
        virtual value_type& get_current_window_() const = 0;

        /**
         * @brief Get a pointer to the base class parent.
         *
         * In the derived class implementation, this should be a pointer to the _derived_ parent
         * class, to make sure that it contains the correct settings etc needed for the iteration.
         */
        virtual BaseWindowIterator const* get_parent_() const = 0;

    protected:

        // Need to manually keep track of those...
        bool is_first_window_ = true;
        bool is_last_window_ = false;

        // Underlying iterator
        ForwardIterator current_;
        ForwardIterator end_;

    };

    // ======================================================================================
    //      Main Class
    // ======================================================================================

public:

    // -------------------------------------------------------------------------
    //     Constructors and Rule of Five
    // -------------------------------------------------------------------------

    BaseWindowIterator(
        ForwardIterator begin, ForwardIterator end
    )
        : begin_(begin)
        , end_(end)
    {}

    ~BaseWindowIterator() = default;

    BaseWindowIterator( BaseWindowIterator const& ) = default;
    BaseWindowIterator( BaseWindowIterator&& )      = default;

    BaseWindowIterator& operator= ( BaseWindowIterator const& ) = default;
    BaseWindowIterator& operator= ( BaseWindowIterator&& )      = default;

    friend Iterator;

    // -------------------------------------------------------------------------
    //     Iteration
    // -------------------------------------------------------------------------

    Iterator begin()
    {
        return Iterator( get_begin_iterator_() );
    }

    Iterator end()
    {
        return Iterator( get_end_iterator_() );
    }

    // -------------------------------------------------------------------------
    //     Virtual Members
    // -------------------------------------------------------------------------

protected:

    virtual std::unique_ptr<BaseIterator> get_begin_iterator_() = 0;
    virtual std::unique_ptr<BaseIterator> get_end_iterator_() = 0;

    // -------------------------------------------------------------------------
    //     Data Members
    // -------------------------------------------------------------------------

private:

    // Underlying iterator to the data that we want to put in windows.
    ForwardIterator begin_;
    ForwardIterator end_;

};

} // namespace population
} // namespace genesis

#endif // include guard
