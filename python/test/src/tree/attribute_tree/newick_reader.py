import sys

sys.path.append('./bin')

from yoyo.genesis.utils import *
from yoyo.genesis.tree import *

def count_attribute_tree_data( tree: Tree):
	node_attr_cnt = 0
	for node in tree.nodes():
		data = node.data()
		node_attr_cnt = node_attr_cnt + len(data.attributes)

	edge_attr_cnt = 0
	for edge in tree.edges():
		data = edge.data()
		edge_attr_cnt = edge_attr_cnt + len(data.attributes)

	return (node_attr_cnt, edge_attr_cnt)

def print_attribute_tree_data( tree: Tree):
	#LOG_DBG << "Nodes";
	for node in tree.nodes():
		data = node.data()
		#LOG_DBG1 << "node " << data.name;
		for m in data.attributes:
			True
			#LOG_DBG2 << m.first << " --> " << m.second;

	#LOG_DBG << "Edges";
	for edge in tree.edges():
		data = edge.data();
		#LOG_DBG1 << "edge";
		for m in data.attributes:
			True
			#LOG_DBG2 << m.first << " --> " << m.second;

###################################################
########## INDEXED_NEWICK_READER_INDEX ############

#Read and process tree.
infile = "test/data/tree/indexed_attributes_0.newick"

reader = IndexedAttributeTreeNewickReader()
reader.add_attribute( IndexedAttributeTreeNewickReader.Source.kComment, 0, IndexedAttributeTreeNewickReader.Target.kEdge, "bootstrap")

tree = reader.read( from_file( infile ))

counts = count_attribute_tree_data( tree )
if 0 != counts[0]:
	print("Error at INDEXED_NEWICK_READER_INDEX-1")
if 3 != counts[1]:
	print("Error at INDEXED_NEWICK_READER_INDEX-2")

#print_attribute_tree_data( tree );

###################################################
######## INDEXED_NEWICK_READER_CATCH_ALL ##########

# Read and process tree.
infile = "test/data/tree/indexed_attributes_1.newick"

reader = IndexedAttributeTreeNewickReader()
reader.add_catch_all( IndexedAttributeTreeNewickReader.Source.kComment, IndexedAttributeTreeNewickReader.Target.kEdge, "comment_")

tree = reader.read( from_file( infile ))

node_attr_cnt = 0
for node in tree.nodes():
	data = node.data();
	node_attr_cnt = node_attr_cnt + len(data.attributes)
if 0 != node_attr_cnt:
	print("Error at INDEXED_NEWICK_READER_CATCH_ALL-1")

edge_attr_cnt = 0
for edge in tree.edges():
	data = edge.data()
	edge_attr_cnt += len(data.attributes)
if 12 != edge_attr_cnt:
	print("Error at INDEXED_NEWICK_READER_CATCH_ALL-2")

counts = count_attribute_tree_data( tree )
if  0 != counts[0]:
	print("Error at INDEXED_NEWICK_READER_CATCH_ALL-3")
if 12 != counts[1]:
	print("Error at INDEXED_NEWICK_READER_CATCH_ALL-4")

###################################################
############# KEYED_NEWICK_READER_KEYS ############

#Read and process tree.
infile = "test/data/tree/keyed_attributes_0.newick"

reader = KeyedAttributeTreeNewickReader()
reader.add_attribute( "bs",     KeyedAttributeTreeNewickReader.Target.kEdge )
reader.add_attribute( "!color", KeyedAttributeTreeNewickReader.Target.kEdge, "color" )

tree = reader.read( from_file( infile ))

counts = count_attribute_tree_data( tree )
if 0 != counts[0]:
	print("Error at KEYED_NEWICK_READER_KEYS-1")
if 4 != counts[1]:
	print("Error at KEYED_NEWICK_READER_KEYS-2")

###################################################
########### KEYED_NEWICK_READER_CATCH_ALL #########

# Read and process tree.
Infile = "test/data/tree/keyed_attributes_0.newick"

reader = KeyedAttributeTreeNewickReader()
reader.add_catch_all( KeyedAttributeTreeNewickReader.Target.kEdge )

tree = reader.read( from_file( infile ))

counts = count_attribute_tree_data( tree )
if 0 != counts[0]:
	print("Error at KEYED_NEWICK_READER_CATCH_ALL-1")
if 4 != counts[1]:
	print("Error at KEYED_NEWICK_READER_CATCH_ALL-2")

# print_attribute_tree_data( tree );

###################################################
############## KEYED_NEWICK_READER_NHX ############

# Read and process tree.
infile = "test/data/tree/keyed_attributes_1.newick"

reader = KeyedAttributeTreeNewickReader()
reader.add_nhx_attributes()
# reader.add_catch_all( KeyedAttributeTreeNewickReader::Target::kNode );

tree = reader.read( from_file( infile ))

counts = count_attribute_tree_data( tree )
if 25 != counts[0]:
	print("Error at KEYED_NEWICK_READER_NHX-1")
if  1 != counts[1]:
	print("Error at KEYED_NEWICK_READER_NHX-2")

# print_attribute_tree_data( tree );

###################################################

print("\nDone")
