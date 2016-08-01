/*
    Genesis - A toolkit for working with phylogenetic data.
    Copyright (C) 2014-2016 Lucas Czech

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
 * @brief Implementation of Default Tree functions.
 *
 * @file
 * @ingroup tree
 */

#include "tree/default/functions.hpp"

#include "tree/default/tree.hpp"
#include "utils/text/string.hpp"

namespace genesis {
namespace tree {

// =================================================================================================
//     Node Names
// =================================================================================================

/**
 * @brief Returns an unordered set of all node names of a Tree.
 *
 * If `leaves_only` is set to true, nodes names of inner nodes are not included.
 * Unnamed nodes (`node.data.name == ""`) are always excluded.
 * The only difference to node_names_sorted() is the type of container used for storing the result.
 */
std::unordered_set<std::string> node_names(
    Tree const& tree,
    bool leaves_only
) {
    std::unordered_set<std::string> ret;
    for( auto const& node : tree.nodes() ) {
        if( node->is_inner() && leaves_only ) {
            continue;
        }
        auto const name = node->data<DefaultNodeData>().name;
        if( name == "" ) {
            continue;
        }
        ret.insert( std::move( name ));
    }
    return ret;
}

/**
 * @brief Returns a set of all node names of a Tree.
 *
 * If `leaves_only` is set to true, nodes names of inner nodes are not included.
 * Unnamed nodes (`node.data.name == ""`) are always excluded.
 * The only difference to node_names() is the type of container used for storing the result.
 */
utils::SortedVector<std::string> node_names_sorted(
    Tree const& tree,
    bool leaves_only
) {
    utils::SortedVector<std::string> ret;
    for( auto const& node : tree.nodes() ) {
        if( node->is_inner() && leaves_only ) {
            continue;
        }
        auto const name = node->data<DefaultNodeData>().name;
        if( name == "" ) {
            continue;
        }
        ret.insert( std::move( name ));
    }
    return ret;
}

/**
 * @brief Finds a Node, given its name. If not found, nullptr is returned.
 */
TreeNode const* find_node(
    Tree const& tree,
    const std::string& name,
    bool replace_underscores
) {
    auto clean_name = name;
    if (replace_underscores) {
        clean_name = utils::replace_all(name, "_", " ");
    }

    for (auto it = tree.begin_nodes(); it != tree.end_nodes(); ++it) {
        if( it->get()->data<DefaultNodeData>().name == clean_name) {
            return it->get();
        }
    }

    return nullptr;
}

/**
 * @brief Finds a Node, given its name. If not found, nullptr is returned.
 */
TreeNode* find_node(
    Tree& tree,
    const std::string& name,
    bool replace_underscores
) {
    // Avoid code duplication according to Scott Meyers.
    auto const& ctree = static_cast< Tree const& >( tree );
    return const_cast< TreeNode* >(
        find_node( ctree, name, replace_underscores )
    );
}

// =================================================================================================
//     Branch Length
// =================================================================================================

/**
 * @brief Get a vector of all branch lengths of a Tree, index by the
 * @link TreeEdge::index() edge index@endlink.
 */
std::vector<double> branch_lengths(
    Tree const& tree
) {
    std::vector<double> result;
    result.reserve( tree.edge_count() );
    for( size_t i = 0; i < tree.edge_count(); ++i ) {
        result.push_back( tree.edge_at(i).data<DefaultEdgeData>().branch_length );
    }
    return result;
}

/**
 * @brief Set all branch lengths of a Tree to a given value.
 */
void set_all_branch_lengths(
    Tree& tree,
    double length
) {
    for( auto& edge : tree.edges() ) {
        edge->data<DefaultEdgeData>().branch_length = length;
    }
}

} // namespace tree
} // namespace genesis
