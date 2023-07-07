import sys

sys.path.append('./bin')

from yoyo.genesis.utils import *
from yoyo.genesis.tree import *

###################################################
####### EDGE_COLOR_BRANCH_LENGTH_GRADIENT #########

infile = "./test/data/tree/distances.newick"
tree = CommonTreeNewickReader().read( from_file( infile ))

# Colorize the branches according to their length.
colors = edge_color_branch_length_gradient(tree)

# We expect at least one branch to have max color (red) and one to have min color (green).
count = 0
for i in colors:
	if (i.r() == 1) and (i.g() == 0) and (i.b() == 0):
		count = count + 1
if 1 > count:
	print("Error at EDGE_COLOR_BRANCH_LENGTH_GRADIENT-1")
count = 0
for i in colors:
	if (i.r() == 0) and (i.g() == 1) and (i.b() == 0):
		count = count + 1
if 1 > count:
	print("Error at EDGE_COLOR_BRANCH_LENGTH_GRADIENT-2")

###################################################
################## NODE_NAMES #####################

tree = Tree()

# Using a tree with all names set to some value.
input = "((A,(B,C)D)E,((F,(G,H)I)J,K)L)R;"
#tree = CommonTreeNewickReader().read( from_string( input ))
tree = CommonTreeNewickReader().read( from_file( './test/src/tree/common_tree/common_tree_py1.txt' ))

if 13 != tree.node_count():
	print("Error at NODE_NAMES-1")
if  7 != leaf_node_count(tree):
	print("Error at NODE_NAMES-2")

names_all    = node_names(tree)
names_leaves = node_names(tree, True)

if 13 != len(names_all):
	print("Error at NODE_NAMES-3")
if  7 != len(names_leaves):
	print("Error at NODE_NAMES-4")

# Using a tree where some names are empty.
input = "((A,(B,))E,((,(G,H))J,)L);"
#tree = CommonTreeNewickReader().read( from_string( input ))
tree = CommonTreeNewickReader().read( from_file( './test/src/tree/common_tree/common_tree_py2.txt' ))

if 13 != tree.node_count():
	print("Error at NODE_NAMES-5")
if  7 != leaf_node_count(tree):
	print("Error at NODE_NAMES-6")

names_all    = node_names(tree)
names_leaves = node_names(tree, True)

if 7 != len(names_all):
	print("Error at NODE_NAMES-7")
if 4 != len(names_leaves):
	print("Error at NODE_NAMES-8")

###################################################

print("\nDone")