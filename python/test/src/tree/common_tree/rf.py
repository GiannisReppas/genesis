import sys

sys.path.append('./bin')

from yoyo.genesis.utils import *
from yoyo.genesis.tree import *

###################################################
#################### RFDISTANCE ####################

trees = TreeSet()
infile = "./test/data/tree/random-trees.newick";
CommonTreeNewickReader().read( from_file( infile ), trees );
if 10 != trees.size():
	print("Error at RFDISTANCE-1")

rf_mat = rf_distance_absolute( trees )

rf_mat_exp = Matrix_unsigned_long_t( 10, 10, [
	0, 14, 14, 12, 14, 14, 14, 10, 14, 10,
	14, 0, 14, 14, 14, 14, 14, 14, 14, 14,
	14, 14, 0, 14, 12, 14, 10, 14, 14, 14,
	12, 14, 14, 0, 14, 14, 12, 12, 14, 14,
	14, 14, 12, 14, 0, 14, 14, 14, 12, 14,
	14, 14, 14, 14, 14, 0, 14, 12, 12, 14,
	14, 14, 10, 12, 14, 14, 0, 12, 14, 14,
	10, 14, 14, 12, 14, 12, 12, 0, 14, 12,
	14, 14, 14, 14, 12, 12, 14, 14, 0, 14,
	10, 14, 14, 14, 14, 14, 14, 12, 14, 0
]);
if rf_mat_exp != rf_mat:
	print("Error at RFDISTANCE-2")

rf_vec = rf_distance_absolute( trees[0], trees )

rf_vec_exp = [0, 14, 14, 12, 14, 14, 14, 10, 14, 10]
if rf_vec_exp != rf_vec:
	print("Error at RFDISTANCE-3")

###################################################

print("\nDone")