#ifndef GENESIS_H_
#define GENESIS_H_

/**
 * @brief This header includes all other genesis headers (*.hpp).
 * This makes it easy to integrate the code as a library, as all
 * symbols of genesis are available after including this header.
 *
 * You do not need to edit this file manually. Simply run the script
 * make_genesis_header.sh in ./tools to update this file.
 */

#include "placement/function/functions.hpp"
#include "placement/function/helper.hpp"
#include "placement/function/measures.hpp"
#include "placement/function/operators.hpp"
#include "placement/io/edge_color.hpp"
#include "placement/io/jplace_reader.hpp"
#include "placement/io/jplace_writer.hpp"
#include "placement/io/newick_processor.hpp"
#include "placement/io/phyloxml_processor.hpp"
#include "placement/io/serializer.hpp"
#include "placement/placement_tree.hpp"
#include "placement/pquery/distances.hpp"
#include "placement/pquery.hpp"
#include "placement/pquery/name.hpp"
#include "placement/pquery/placement.hpp"
#include "placement/pquery/plain.hpp"
#include "placement/sample.hpp"
#include "placement/sample_set.hpp"
#include "placement/simulator/simulator.hpp"
#include "placement/simulator/subtree.hpp"
#include "placement/simulator/twostep.hpp"

#include "sequence/codes.hpp"
#include "sequence/functions.hpp"
#include "sequence/io/fasta_reader.hpp"
#include "sequence/io/fasta_writer.hpp"
#include "sequence/io/phylip_reader.hpp"
#include "sequence/io/phylip_writer.hpp"
#include "sequence/sequence.hpp"
#include "sequence/sequence_set.hpp"

#include "tree/bipartition/bipartition.hpp"
#include "tree/bipartition/bipartition_set.hpp"
#include "tree/default/distances.hpp"
#include "tree/default/edge_color.hpp"
#include "tree/default/functions.hpp"
#include "tree/default/newick_mixin.hpp"
#include "tree/default/newick_processor.hpp"
#include "tree/default/phyloxml_mixin.hpp"
#include "tree/default/phyloxml_processor.hpp"
#include "tree/default/tree.hpp"
#include "tree/distances.hpp"
#include "tree/functions.hpp"
#include "tree/io/color_mixin.hpp"
#include "tree/io/newick/broker.hpp"
#include "tree/io/newick/color_mixin.hpp"
#include "tree/io/newick/element.hpp"
#include "tree/io/newick/lexer.hpp"
#include "tree/io/newick/parser.hpp"
#include "tree/io/newick/processor.hpp"
#include "tree/io/phyloxml/color_mixin.hpp"
#include "tree/io/phyloxml/processor.hpp"
#include "tree/iterator/eulertour.hpp"
#include "tree/iterator/inorder.hpp"
#include "tree/iterator/levelorder.hpp"
#include "tree/iterator/node_range.hpp"
#include "tree/iterator/nodes.hpp"
#include "tree/iterator/path.hpp"
#include "tree/iterator/postorder.hpp"
#include "tree/iterator/preorder.hpp"
#include "tree/operators.hpp"
#include "tree/printer/compact.hpp"
#include "tree/printer/detailed.hpp"
#include "tree/printer/table.hpp"
#include "tree/tree_edge.hpp"
#include "tree/tree.hpp"
#include "tree/tree_link.hpp"
#include "tree/tree_node.hpp"
#include "tree/tree_node_iterator.hpp"
#include "tree/tree_set.hpp"

#include "utils/core/fs.hpp"
#include "utils/core/genesis.hpp"
#include "utils/core/indexed_list.hpp"
#include "utils/core/logging.hpp"
#include "utils/core/options.hpp"
#include "utils/core/std.hpp"
#include "utils/io/counting_istream.hpp"
#include "utils/io/json/document.hpp"
#include "utils/io/json/lexer.hpp"
#include "utils/io/json/processor.hpp"
#include "utils/io/lexer.hpp"
#include "utils/io/lexer_iterator.hpp"
#include "utils/io/lexer/parser.hpp"
#include "utils/io/lexer/scanner.hpp"
#include "utils/io/lexer_token.hpp"
#include "utils/io/nexus/block.hpp"
#include "utils/io/nexus/document.hpp"
#include "utils/io/nexus/taxa.hpp"
#include "utils/io/nexus/trees.hpp"
#include "utils/io/nexus/writer.hpp"
#include "utils/io/serializer.hpp"
#include "utils/io/xml/document.hpp"
#include "utils/io/xml/processor.hpp"
#include "utils/math/bitvector.hpp"
#include "utils/math/histogram/accumulator.hpp"
#include "utils/math/histogram/distances.hpp"
#include "utils/math/histogram.hpp"
#include "utils/math/histogram/operations.hpp"
#include "utils/math/histogram/operators.hpp"
#include "utils/math/histogram/stats.hpp"
#include "utils/math/matrix.hpp"
#include "utils/math/matrix/operators.hpp"
#include "utils/text/char.hpp"
#include "utils/text/string.hpp"
#include "utils/text/style.hpp"
#include "utils/text/table.hpp"
#include "utils/tools/char_lookup.hpp"
#include "utils/tools/color/gradient.hpp"
#include "utils/tools/color.hpp"
#include "utils/tools/color/names.hpp"
#include "utils/tools/color/operators.hpp"
#include "utils/tools/date_time.hpp"

#endif // include guard
