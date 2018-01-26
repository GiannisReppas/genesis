#ifndef GENESIS_TREE_BIPARTITION_BIPARTITION_FUNCTIONS_H_
#define GENESIS_TREE_BIPARTITION_BIPARTITION_FUNCTIONS_H_

/*
    Genesis - A toolkit for working with phylogenetic data.
    Copyright (C) 2014-2018 Lucas Czech and HITS gGmbH

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
    Lucas Czech <lucas.czech@h-its.org>
    Exelixis Lab, Heidelberg Institute for Theoretical Studies
    Schloss-Wolfsbrunnenweg 35, D-69118 Heidelberg, Germany
*/

/**
 * @brief
 *
 * @file
 * @ingroup tree
 */

#include "genesis/tree/tree.hpp"

#include <string>
#include <unordered_set>
#include <vector>

namespace genesis {
namespace tree {

// =================================================================================================
//     Bipartition Functions
// =================================================================================================

std::unordered_set<size_t> get_clade_edges( Tree const& tree, std::vector< tree::TreeNode const* > const& nodes );

std::unordered_set<size_t> get_clade_edges( Tree const& tree, std::vector< std::string > const& node_names );

} // namespace tree
} // namespace genesis

#endif // include guard
