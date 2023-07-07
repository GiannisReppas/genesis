import sys

sys.path.append('./bin')

from yoyo.genesis.utils import *
from yoyo.genesis.tree import *

##################################################
############# FROM_AND_TO_STRING #################

#LOL

##################################################
################ NEWICK_VARIANTS #################

tree = Tree()
newick_string = ""
writer = CommonTreeNewickWriter()

if not tree.empty():
	print("Error at NEWICK_VARIANTS-1")

# First, no branch lengths.
writer.enable_branch_lengths( False )
writer.trailing_new_line( False )

# Stupid tree.
newick_string = "();"
#tree = CommonTreeNewickReader().read( from_string( newick_string ))
tree = CommonTreeNewickReader().read( from_file( './test/src/tree/newick_py1.txt' ))
if not validate_topology(tree):
	print("Error at NEWICK_VARIANTS-2")
if 2 != tree.node_count():
	print("Error at NEWICK_VARIANTS-3")
if tree.empty():
	print("Error at NEWICK_VARIANTS-4")
if newick_string != writer.to_string( tree ):
	print("Error at NEWICK_VARIANTS-5")

# No nodes are named.
newick_string = "(,,(,));"
#tree = CommonTreeNewickReader().read( from_string( newick_string ))
tree = CommonTreeNewickReader().read( from_file( './test/src/tree/newick_py2.txt' ))
if not validate_topology(tree):
	print("Error at NEWICK_VARIANTS-6")
if newick_string != writer.to_string( tree ):
	print("Error at NEWICK_VARIANTS-7")

# Leaf nodes are named.
newick_string = "(A,B,(C,D));"
#tree = CommonTreeNewickReader().read( from_string( newick_string ))
tree = CommonTreeNewickReader().read( from_file( './test/src/tree/newick_py3.txt' ))
if not validate_topology(tree):
	print("Error at NEWICK_VARIANTS-8")
if newick_string != writer.to_string( tree ):
	print("Error at NEWICK_VARIANTS-9")

# All nodes are named.
newick_string = "(A,B,(C,D)E)F;"
#tree = CommonTreeNewickReader().read( from_string( newick_string ))
tree = CommonTreeNewickReader().read( from_file( './test/src/tree/newick_py4.txt' ))
if not validate_topology(tree):
	print("Error at NEWICK_VARIANTS-10")
if newick_string != writer.to_string( tree ):
	print("Error at NEWICK_VARIANTS-11")

# Now, test with branch lengths.
writer.enable_branch_lengths( True )

# All but root node have a distance to parent.
newick_string = "(:0.1,:0.2,(:0.3,:0.4):0.5);"
#tree = CommonTreeNewickReader().read( from_string( newick_string ))
tree = CommonTreeNewickReader().read( from_file( './test/src/tree/newick_py5.txt' ))
if not validate_topology(tree):
	print("Error at NEWICK_VARIANTS-12")
if newick_string != writer.to_string( tree ):
	print("Error at NEWICK_VARIANTS-13")

# All have a distance to parent.
# We never write out the root branch length, so this test is skipped.
newick_string = "(:0.1,:0.2,(:0.3,:0.4):0.5):0.0;"
#tree = CommonTreeNewickReader().read( from_string( newick_string ))
tree = CommonTreeNewickReader().read( from_file( './test/src/tree/newick_py6.txt' ))
if not validate_topology(tree):
	print("Error at NEWICK_VARIANTS-14")
# EXPECT_EQ( newick_string, writer.to_string( tree ));

# Distances and leaf names (popular).
newick_string = "(A:0.1,B:0.2,(C:0.3,D:0.4):0.5);"
#tree = CommonTreeNewickReader().read( from_string( newick_string ))
tree = CommonTreeNewickReader().read( from_file( './test/src/tree/newick_py7.txt' ))
if not validate_topology(tree):
	print("Error at NEWICK_VARIANTS-15")
if newick_string != writer.to_string( tree ):
	print("Error at NEWICK_VARIANTS-16")

# Distances and all names.
newick_string = "(A:0.1,B:0.2,(C:0.3,D:0.4)E:0.5)F;"
#tree = CommonTreeNewickReader().read( from_string( newick_string ))
tree = CommonTreeNewickReader().read( from_file( './test/src/tree/newick_py8.txt' ))
if not validate_topology(tree):
	print("Error at NEWICK_VARIANTS-17")
if newick_string != writer.to_string( tree ):
	print("Error at NEWICK_VARIANTS-18")

# A tree rooted on a leaf node (rare).
newick_string = "((B:0.2,(C:0.3,D:0.4)E:0.5)F:0.1)A;"
#tree = CommonTreeNewickReader().read( from_string( newick_string ))
tree = CommonTreeNewickReader().read( from_file( './test/src/tree/newick_py9.txt' ))
if not validate_topology(tree):
	print("Error at NEWICK_VARIANTS-19")
if newick_string != writer.to_string( tree ):
	print("Error at NEWICK_VARIANTS-20")

# All mixed, with comments and tags. Need to activate tags first.
# We here only test the reading, and check for a simple standard written output,
# instead of the hassle of using custom plugins to also write tags etc...
newick_string = "( ( Ant:0.2{0}, [a comment] 'Bee':0.09{1} )Inner:0.7{2}, Coyote:0.5{3} ){4};"
newick_string2 = "((Ant:0.2,Bee:0.09)Inner:0.7,Coyote:0.5);"
reader = CommonTreeNewickReader()
reader.enable_tags( True )
#tree = reader.read( from_string( newick_string ))
tree = reader.read( from_file( './test/src/tree/newick_py10.txt' ))
if not validate_topology(tree):
	print("Error at NEWICK_VARIANTS-21")
if newick_string2 != writer.to_string( tree ):
	print("Error at NEWICK_VARIANTS-22")

##################################################

print("\nDone")
