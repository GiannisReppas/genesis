#ifndef GENESIS_POPULATION_WINDOW_VARIANT_WINDOW_ITERATOR_H_
#define GENESIS_POPULATION_WINDOW_VARIANT_WINDOW_ITERATOR_H_

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
 * @ingroup population
 */

#include "genesis/population/streams/variant_input_stream.hpp"
#include "genesis/population/window/base_window_iterator.hpp"
#include "genesis/population/window/window_view_iterator.hpp"
#include "genesis/population/window/window_view.hpp"
#include "genesis/population/window/window.hpp"

#include <type_traits>

namespace genesis {
namespace population {

// =================================================================================================
//     Generic Variant Window Iterator
// =================================================================================================

// Quick check to avoid future bugs if we ever change that definition.
static_assert(
    std::is_same<VariantInputStream::value_type, Variant>::value,
    "VariantInputStream::value_type != Variant"
);

/**
 * @brief Typedef for a uniform Window iterator type.
 *
 * This typedef is used for any Window iterator over an VariantInputStream. It's simply a more
 * convenient name that the full template specialization.
 */
using VariantWindowIterator = BaseWindowIterator<
    VariantInputStream::Iterator,
    VariantInputStream::value_type,
    Window<VariantInputStream::value_type>
>;

/**
 * @brief Typedef for our uniform WindowView iterator type.
 *
 * This typedef is used for any WindowView iterator over an VariantInputStream. It's simply a more
 * convenient name that the full template specialization.
 *
 * In particular, we use this type as an abstraction that captures iterators over both Window and
 * WindowView, for instance when using make_window_view_iterator() to wrap a WindowIterator into
 * a WindowViewIterator. as Because we want to model different types of window iterators, some of
 * which use Window, some of which use WindowView, this abstraction allows us to have a single type.
 */
using VariantWindowViewIterator = BaseWindowIterator<
    VariantInputStream::Iterator,
    VariantInputStream::value_type,
    WindowView<VariantInputStream::value_type>
>;

} // namespace population
} // namespace genesis

#endif // include guard
