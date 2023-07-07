import sys

sys.path.append('./genesis_bindings')

from mylibgenesis.genesis.utils import *
from mylibgenesis.genesis.tree import *

def TestSubtreeSize( link_index, out_subtree_size ):
	input = "((B,(D,E)C)A,F,(H,I)G)R;"

	tree = CommonTreeNewickReader().read( from_file('./test/src/tree/functions_py.txt'))
	#tree = CommonTreeNewickReader().read( from_string( input ))

	st_size = subtree_size( tree, tree.link_at( link_index ))
	if out_subtree_size != st_size:
		print("Error at TestSubtreeSize-1")
	print("with link index " + str(link_index))

def TestSubtreeSizes( node_name, out_sizes ):
	input = "((B,(D,E)C)A,F,(H,I)G)R;"

	tree = CommonTreeNewickReader().read( from_file('./test/src/tree/functions_py.txt'))
	#tree = CommonTreeNewickReader().read( from_string( input ))

	node = find_node( tree, node_name )
	if not node:
		print("Error at TestSubtreeSizes-1")

	st_sizes = subtree_sizes( tree, node )
	if out_sizes != st_sizes:
		print("Error at TestSubtreeSizes-2")
	print(" with start node " + str(node_name))

def TestSubtreeMaxPathHeight( node_name, out_size ):
	input = "((B,(D,E)C)A,F,(H,I)G)R;"

	tree = CommonTreeNewickReader().read( from_file('./test/src/tree/functions_py.txt'))
	#tree = CommonTreeNewickReader().read( from_string( input ))

	node = find_node( tree, node_name )
	if not node:
		print("Error at TestSubtreeMaxPathHeight-1")

	#We are lazy and only evaluate the links towards the root.
	st_size = subtree_max_path_height( tree, node.link().outer() )
	if out_size != st_size:
		print("Error at TestSubtreeMaxPathHeight-2")
	print(" with start node " + str(node_name))

def TestTreeLCA( node_name_a, node_name_b, node_name_lca ):
	input = "((B,(D,E)C)A,F,(H,I)G)R;"

	tree = CommonTreeNewickReader().read( from_file('./test/src/tree/functions_py.txt'))
	#tree = CommonTreeNewickReader().read( from_string( input ))

	node_a = find_node( tree, node_name_a )
	node_b = find_node( tree, node_name_b )
	if not node_a:
		print("Error at TestTreeLCA-1")
	if not node_b:
		print("Error at TestTreeLCA-2")

	node_lca = lowest_common_ancestor( node_a, node_b )

	a = node_lca.data().clone()
	a.name = "giannis"
	print( node_lca.data().name )
	exit()

	if node_name_lca != node_lca.data().name:
		print("Error at TestTreeLCA-3")
	print(" with nodes " + str(node_name_a) + ", " + str(node_name_b) + " and LCA " + str(node_name_lca))

###################################################
################### EDGE_SIDES ####################

input = "((B,(D,E)C)A,F,(H,I)G)R;"
tree = CommonTreeNewickReader().read( from_file('./test/src/tree/functions_py.txt'))
#tree = CommonTreeNewickReader().read( from_string( input ))

edge_side_mat = edge_sides( tree )

exp = Matrix_signed_char_t( 9, 9, [
	0,  1,  1, -1, -1, -1, -1, -1, -1,
	-1,  0, -1, -1, -1, -1, -1, -1, -1,
	-1, -1,  0, -1, -1, -1, -1, -1, -1,
	-1, -1, -1,  0, -1, -1, -1, -1, -1,
	-1, -1, -1, -1,  0,  1,  1,  1,  1,
	-1, -1, -1, -1, -1,  0,  1,  1, -1,
	-1, -1, -1, -1, -1, -1,  0, -1, -1,
	-1, -1, -1, -1, -1, -1, -1,  0, -1,
	-1, -1, -1, -1, -1, -1, -1, -1,  0
])

if exp != edge_side_mat:
	print("Error at EDGE_SIDES-1")

###################################################
############## NODE_ROOT_DIRECTIONS ###############

input = "((B,(D,E)C)A,F,(H,I)G)R;"
tree = CommonTreeNewickReader().read( from_file('./test/src/tree/functions_py.txt'))
#tree = CommonTreeNewickReader().read( from_string( input ))

node_root_mat = node_root_direction_matrix( tree )

exp = Matrix_signed_char_t( 10, 10, [
	0, -1, -1, -1, -1, -1, -1, -1, -1, -1,
	1,  0, -1, -1,  1,  1,  1,  1,  1,  1,
	1,  1,  0,  1,  1,  1,  1,  1,  1,  1,
	1,  1,  1,  0,  1,  1,  1,  1,  1,  1,
	1,  1,  1,  1,  0,  1,  1,  1,  1,  1,
	1,  1,  1,  1,  1,  0, -1, -1, -1, -1,
	1,  1,  1,  1,  1,  1,  0, -1, -1,  1,
	1,  1,  1,  1,  1,  1,  1,  0,  1,  1,
	1,  1,  1,  1,  1,  1,  1,  1,  0,  1,
	1,  1,  1,  1,  1,  1,  1,  1,  1,  0,
])

if exp != node_root_mat:
	print("Error at NODE_ROOT_DIRECCTIONS-1")

###################################################
################## SUBTREE_SIZE ###################

TestSubtreeSize(  0, 5 )
TestSubtreeSize(  1, 1 )
TestSubtreeSize(  2, 3 )
TestSubtreeSize(  3, 7 )
TestSubtreeSize(  4, 1 )
TestSubtreeSize(  5, 1 )
TestSubtreeSize(  6, 9 )
TestSubtreeSize(  7, 9 )
TestSubtreeSize(  8, 9 )
TestSubtreeSize(  9, 5 )
TestSubtreeSize( 10, 1 )
TestSubtreeSize( 11, 3 )
TestSubtreeSize( 12, 7 )
TestSubtreeSize( 13, 1 )
TestSubtreeSize( 14, 1 )
TestSubtreeSize( 15, 9 )
TestSubtreeSize( 16, 9 )
TestSubtreeSize( 17, 9 )

####################################################
################## SUBTREE_SIZES ###################

TestSubtreeSizes( "R", [ 9, 2, 0, 0, 0, 4, 2, 0, 0, 0 ] )
TestSubtreeSizes( "A", [ 4, 2, 0, 0, 0, 9, 2, 0, 0, 0 ] )
TestSubtreeSizes( "B", [ 4, 2, 0, 0, 0, 8, 2, 0, 0, 9 ] )
TestSubtreeSizes( "C", [ 4, 2, 0, 0, 0, 6, 9, 0, 0, 0 ] )
TestSubtreeSizes( "D", [ 4, 2, 0, 0, 0, 6, 8, 0, 9, 0 ] )
TestSubtreeSizes( "E", [ 4, 2, 0, 0, 0, 6, 8, 9, 0, 0 ] )
TestSubtreeSizes( "F", [ 8, 2, 0, 0, 9, 4, 2, 0, 0, 0 ] )
TestSubtreeSizes( "G", [ 6, 9, 0, 0, 0, 4, 2, 0, 0, 0 ] )
TestSubtreeSizes( "H", [ 6, 8, 0, 9, 0, 4, 2, 0, 0, 0 ] )
TestSubtreeSizes( "I", [ 6, 8, 9, 0, 0, 4, 2, 0, 0, 0 ] )

####################################################
############# SUBTREE_MAX_PATH_HEIGHT ##############

TestSubtreeMaxPathHeight( "A", 2 )
TestSubtreeMaxPathHeight( "B", 0 )
TestSubtreeMaxPathHeight( "C", 1 )
TestSubtreeMaxPathHeight( "D", 0 )
TestSubtreeMaxPathHeight( "E", 0 )
TestSubtreeMaxPathHeight( "F", 0 )
TestSubtreeMaxPathHeight( "G", 1 )
TestSubtreeMaxPathHeight( "H", 0 )
TestSubtreeMaxPathHeight( "I", 0 )

####################################################
############# SUBTREE_MAX_PATH_HEIGHTS #############

input = "((B,(D,E)C)A,F,(H,I)G)R;"

tree = CommonTreeNewickReader().read( from_file('./test/src/tree/functions_py.txt'))
#tree = CommonTreeNewickReader().read( from_string( input ))

heights = subtree_max_path_heights( tree )
exp_heights = [ 3, 1, 0, 0, 0, 2, 1, 0, 0, 0 ]
if exp_heights != heights:
	print("Error at SUBTREE_MAX_PATH_HEIGHTS-1")

####################################################
####################### LCA ########################

TestTreeLCA( "A", "A", "A" )
TestTreeLCA( "A", "B", "A" )
TestTreeLCA( "A", "F", "R" )
TestTreeLCA( "E", "C", "C" )
TestTreeLCA( "E", "H", "R" )
TestTreeLCA( "H", "I", "G" )

####################################################
####################### LCAs #######################

input = "((B,(D,E)C)A,F,(H,I)G)R;"
tree = CommonTreeNewickReader().read( from_file('./test/src/tree/functions_py.txt'))
#tree = CommonTreeNewickReader().read( from_string( input ))

lcas = lowest_common_ancestors( tree )
exp = Matrix_unsigned_long_t( 10, 10, [
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 1, 1, 1, 0, 0, 0, 0, 0, 0,
	0, 1, 2, 1, 0, 0, 0, 0, 0, 0,
	0, 1, 1, 3, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 4, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 5, 5, 5, 5, 5,
	0, 0, 0, 0, 0, 5, 6, 6, 6, 5,
	0, 0, 0, 0, 0, 5, 6, 7, 6, 5,
	0, 0, 0, 0, 0, 5, 6, 6, 8, 5,
	0, 0, 0, 0, 0, 5, 5, 5, 5, 9
])

if exp != lcas:
	print("Error at LCAs-1")

####################################################
################### SIGN_MATRIX ####################

infile = "test/data/tree/rooted.newick"
tree = CommonTreeNewickReader().read( from_file( infile ))

#Full sign matrix
exf = Matrix_signed_char_t( 9, 9, [
	0, -1, -1, -1, +1, +1, +1, +1, +1,
	0,  0, -1, +1,  0,  0,  0,  0,  0,
	0,  0,  0,  0,  0,  0,  0,  0,  0,
	0,  0,  0,  0,  0,  0,  0,  0,  0,
	0,  0,  0,  0,  0, -1, -1, -1, +1,
	0,  0,  0,  0,  0,  0, -1, +1,  0,
	0,  0,  0,  0,  0,  0,  0,  0,  0,
	0,  0,  0,  0,  0,  0,  0,  0,  0,
	0,  0,  0,  0,  0,  0,  0,  0,  0
])
smf = sign_matrix( tree )
if exf != smf:
	print("Error at SIGN_MATRIX-1")

#LOG_DBG << smf;
#LOG_DBG;
#LOG_DBG << exf;

#Compressed sign matrix
exc = Matrix_signed_char_t( 4, 5, [
	-1, -1, +1, +1, +1,
	-1, +1,  0,  0,  0,
	0,  0, -1, -1, +1,
	0,  0, -1, +1,  0
])
smc = sign_matrix( tree, True )
if exc != smc:
	print("Error at SIGN_MATRIX-2")

#LOG_DBG << smc;
#LOG_DBG;
#LOG_DBG << exc;

###################################################

print("\nDone")


