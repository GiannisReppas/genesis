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
 * @brief
 *
 * @file
 * @ingroup placement
 */

#include "placement/function/operators.hpp"

#include "placement/function/functions.hpp"
#include "placement/function/helper.hpp"
#include "placement/placement_tree.hpp"
#include "placement/sample.hpp"

#include "tree/default/tree.hpp"
#include "tree/function/operators.hpp"
#include "tree/printer/compact.hpp"
#include "tree/tree.hpp"

#include "utils/text/table.hpp"

#include <ostream>
#include <sstream>
#include <unordered_map>

namespace genesis {
namespace placement {

// =================================================================================================
//     Comparision and Equality
// =================================================================================================

/**
 * @brief Return whether two PlacementTree%s are compatible.
 *
 * This is the case iff:
 *
 *   * they have the same topology,
 *   * they have the same internal structure (e.g., node indices),
 *   * they have the same node names at corresponding nodes,
 *   * they have the same edge nums at corresponding edges,
 *   * the data types of all nodes and edges are those of a ::PlacementTree
 *
 * In all other cases, `false` is returned.
 */
bool compatible_trees( PlacementTree const& lhs, PlacementTree const& rhs )
{
    auto node_comparator = [] (
        PlacementTreeNode const& node_l,
        PlacementTreeNode const& node_r
    ) {
        auto l_ptr = dynamic_cast< PlacementNodeData const* >( node_l.data.get() );
        auto r_ptr = dynamic_cast< PlacementNodeData const* >( node_r.data.get() );
        if( l_ptr == nullptr || r_ptr == nullptr ) {
            return false;
        }
        return l_ptr->name    == r_ptr->name &&
               node_l.index() == node_r.index();
    };

    auto edge_comparator = [] (
        PlacementTreeEdge const& edge_l,
        PlacementTreeEdge const& edge_r
    ) {
        auto l_ptr = dynamic_cast< PlacementEdgeData const* >( edge_l.data.get() );
        auto r_ptr = dynamic_cast< PlacementEdgeData const* >( edge_r.data.get() );
        if( l_ptr == nullptr || r_ptr == nullptr ) {
            return false;
        }
        return l_ptr->edge_num()               == r_ptr->edge_num()               &&
               edge_l.primary_node().index()   == edge_r.primary_node().index()   &&
               edge_l.secondary_node().index() == edge_r.secondary_node().index();
    };

    return tree::equal(
        lhs, rhs, node_comparator, edge_comparator
    );
}

/**
 * @brief Return whether the PlacementTree%s of two Sample%s are compatible.
 *
 * See
 * @link compatible_trees( PlacementTree const& lhs, PlacementTree const& rhs ) this version @endlink
 * of the function for details.
 */
bool compatible_trees( Sample const& lhs, Sample const& rhs )
{
    return compatible_trees( lhs.tree(), rhs.tree() );
}

// =================================================================================================
//     Conversion
// =================================================================================================

/**
 * @brief Convert a @link tree::DefaultTree DefaultTree @endlink into a ::PlacementTree.
 *
 * This function returns a new tree with the same topology as the source tree, and the same
 * node names and branch lengths. In addition, the `edge_num` property of the PlacementTree is
 * established, as it is not part of the DefaultTree data.
 */
PlacementTree convert_to_placement_tree( tree::DefaultTree const& source_tree )
{
    // TODO those converters need to do double copies of the node and edge data. wasteful!
    auto node_data_converter = [] ( tree::BaseNodeData const& source_node ) {
        auto node_data   = PlacementNodeData();
        auto source_data = dynamic_cast< tree::DefaultNodeData const& >( source_node );
        node_data.name = source_data.name;
        return std::unique_ptr< tree::BaseNodeData >( new PlacementNodeData( node_data ));
    };

    auto edge_data_converter = [] ( tree::BaseEdgeData const& source_edge ) {
        auto edge_data   = PlacementEdgeData();
        auto source_data = dynamic_cast< tree::DefaultEdgeData const& >( source_edge );
        edge_data.branch_length = source_data.branch_length;
        return std::unique_ptr< tree::BaseEdgeData >( new PlacementEdgeData( edge_data ));
    };

    auto result = tree::convert(
        source_tree,
        node_data_converter,
        edge_data_converter
    );

    // Need to set the edge nums accordingly, as those are not part of Default Tree Edge Data.
    reset_edge_nums( result );
    return result;
}

// =================================================================================================
//     Output
// =================================================================================================

/**
 * @brief Print a table of all Pqueries with their Placements and Names to the stream.
 */
std::ostream& operator << (std::ostream& out, Sample const& smp)
{
    auto table = utils::Table();
    auto const kRight = utils::Table::Column::Justification::kRight;

    table.add_column("#").justify(kRight);
    table.add_column("name");
    table.add_column("edge_num").justify(kRight);
    table.add_column("likelihood").justify(kRight);
    table.add_column("like_weight_ratio").justify(kRight);
    table.add_column("proximal_length").justify(kRight);
    table.add_column("pendant_length").justify(kRight);

    size_t i = 0;
    for( auto const& pqry : smp.pqueries() ) {
        std::string name = pqry.name_size() > 0 ? pqry.name_at(0).name : "";
        if( pqry.name_size() > 1 ) {
            name += " (+" + std::to_string( pqry.name_size() - 1 ) + ")";
        }

        for( auto const& p : pqry.placements() ) {
            table << std::to_string(i);
            table << name;
            table << std::to_string( p.edge_num() );
            table << std::to_string( p.likelihood );
            table << std::to_string( p.like_weight_ratio );
            table << std::to_string( p.proximal_length );
            table << std::to_string( p.pendant_length );
        }

        ++i;
    }

    out << utils::simple_layout()(table);
    return out;
}

/**
 * @brief Return a simple view of the Tree of a Sample with information about the
 * @link Pquery Pqueries @endlink on it.
 */
std::string print_tree( Sample const& smp )
{
    auto place_map = placements_per_edge( smp );

    auto print_line = [ &place_map ]( PlacementTreeNode const& node, PlacementTreeEdge const& edge )
    {
        return placement_node_data( node ).name
            + " [" + std::to_string( placement_edge_data( edge ).edge_num() ) + "]" ": "
            + std::to_string( place_map[ edge.index() ].size() ) + " placements";
    };
    return tree::PrinterCompact().print( smp.tree(), print_line );
}

} // namespace placement
} // namespace genesis
