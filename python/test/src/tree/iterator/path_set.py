import sys

sys.path.append('./bin')

from yoyo.genesis.utils import *
from yoyo.genesis.tree import *

def TestPathSet( start_node_name, finish_node_name, lca_node_name, out_nodes ):
	input = "((B,(D,E)C)A,F,(H,I)G)R;"
	nodes = ""

	#tree = CommonTreeNewickReader().read( from_string( input ))
	tree = CommonTreeNewickReader().read( from_file( './test/src/tree/iterator/path_set_py.txt' ))

	start_node  = find_node( tree, start_node_name  )
	finish_node = find_node( tree, finish_node_name )
	lca_node    = find_node( tree, lca_node_name )
	if None is start_node:
		print("Error at TestPathSet-1")
	if None is finish_node:
		print("Error at TestPathSet-2")
	if None is lca_node:
		print("Error at TestPathSet-3")

	for it in path_set( start_node, finish_node, lca_node ):
		nodes = nodes + it.node().data().name

	if out_nodes != nodes:
		print("Error at TestPathSet-4")
	# print(" with start node " + start_node_name + " and finish node " + finish_node_name)

###################################################
#################### PATH_SET #####################

TestPathSet( "A", "A", "A", "A" )
TestPathSet( "A", "B", "A", "BA" )
TestPathSet( "A", "C", "A", "CA" )
TestPathSet( "A", "D", "A", "DCA" )
TestPathSet( "A", "E", "A", "ECA" )
TestPathSet( "A", "F", "R", "AFR" )
TestPathSet( "A", "G", "R", "AGR" )
TestPathSet( "A", "H", "R", "AHGR" )
TestPathSet( "A", "I", "R", "AIGR" )
TestPathSet( "A", "R", "R", "AR" )

TestPathSet( "B", "A", "A", "BA" )
TestPathSet( "B", "B", "B", "B" )
TestPathSet( "B", "C", "A", "BCA" )
TestPathSet( "B", "D", "A", "BDCA" )
TestPathSet( "B", "E", "A", "BECA" )
TestPathSet( "B", "F", "R", "BAFR" )
TestPathSet( "B", "G", "R", "BAGR" )
TestPathSet( "B", "H", "R", "BAHGR" )
TestPathSet( "B", "I", "R", "BAIGR" )
TestPathSet( "B", "R", "R", "BAR" )

TestPathSet( "C", "A", "A", "CA" )
TestPathSet( "C", "B", "A", "CBA" )
TestPathSet( "C", "C", "C", "C" )
TestPathSet( "C", "D", "C", "DC" )
TestPathSet( "C", "E", "C", "EC" )
TestPathSet( "C", "F", "R", "CAFR" )
TestPathSet( "C", "G", "R", "CAGR" )
TestPathSet( "C", "H", "R", "CAHGR" )
TestPathSet( "C", "I", "R", "CAIGR" )
TestPathSet( "C", "R", "R", "CAR" )

TestPathSet( "D", "A", "A", "DCA" )
TestPathSet( "D", "B", "A", "DCBA" )
TestPathSet( "D", "C", "C", "DC" )
TestPathSet( "D", "D", "D", "D" )
TestPathSet( "D", "E", "C", "DEC" )
TestPathSet( "D", "F", "R", "DCAFR" )
TestPathSet( "D", "G", "R", "DCAGR" )
TestPathSet( "D", "H", "R", "DCAHGR" )
TestPathSet( "D", "I", "R", "DCAIGR" )
TestPathSet( "D", "R", "R", "DCAR" )

TestPathSet( "E", "A", "A", "ECA" )
TestPathSet( "E", "B", "A", "ECBA" )
TestPathSet( "E", "C", "C", "EC" )
TestPathSet( "E", "D", "C", "EDC" )
TestPathSet( "E", "E", "E", "E" )
TestPathSet( "E", "F", "R", "ECAFR" )
TestPathSet( "E", "G", "R", "ECAGR" )
TestPathSet( "E", "H", "R", "ECAHGR" )
TestPathSet( "E", "I", "R", "ECAIGR" )
TestPathSet( "E", "R", "R", "ECAR" )

TestPathSet( "F", "A", "R", "FAR" )
TestPathSet( "F", "B", "R", "FBAR" )
TestPathSet( "F", "C", "R", "FCAR" )
TestPathSet( "F", "D", "R", "FDCAR" )
TestPathSet( "F", "E", "R", "FECAR" )
TestPathSet( "F", "F", "F", "F" )
TestPathSet( "F", "G", "R", "FGR" )
TestPathSet( "F", "H", "R", "FHGR" )
TestPathSet( "F", "I", "R", "FIGR" )
TestPathSet( "F", "R", "R", "FR" )

TestPathSet( "G", "A", "R", "GAR" )
TestPathSet( "G", "B", "R", "GBAR" )
TestPathSet( "G", "C", "R", "GCAR" )
TestPathSet( "G", "D", "R", "GDCAR" )
TestPathSet( "G", "E", "R", "GECAR" )
TestPathSet( "G", "F", "R", "GFR" )
TestPathSet( "G", "G", "G", "G" )
TestPathSet( "G", "H", "G", "HG" )
TestPathSet( "G", "I", "G", "IG" )
TestPathSet( "G", "R", "R", "GR" )

TestPathSet( "H", "A", "R", "HGAR" )
TestPathSet( "H", "B", "R", "HGBAR" )
TestPathSet( "H", "C", "R", "HGCAR" )
TestPathSet( "H", "D", "R", "HGDCAR" )
TestPathSet( "H", "E", "R", "HGECAR" )
TestPathSet( "H", "F", "R", "HGFR" )
TestPathSet( "H", "G", "G", "HG" )
TestPathSet( "H", "H", "H", "H" )
TestPathSet( "H", "I", "G", "HIG" )
TestPathSet( "H", "R", "R", "HGR" )

TestPathSet( "I", "A", "R", "IGAR" )
TestPathSet( "I", "B", "R", "IGBAR" )
TestPathSet( "I", "C", "R", "IGCAR" )
TestPathSet( "I", "D", "R", "IGDCAR" )
TestPathSet( "I", "E", "R", "IGECAR" )
TestPathSet( "I", "F", "R", "IGFR" )
TestPathSet( "I", "G", "G", "IG" )
TestPathSet( "I", "H", "G", "IHG" )
TestPathSet( "I", "I", "I", "I" )
TestPathSet( "I", "R", "R", "IGR" )

TestPathSet( "R", "A", "R", "AR" )
TestPathSet( "R", "B", "R", "BAR" )
TestPathSet( "R", "C", "R", "CAR" )
TestPathSet( "R", "D", "R", "DCAR" )
TestPathSet( "R", "E", "R", "ECAR" )
TestPathSet( "R", "F", "R", "FR" )
TestPathSet( "R", "G", "R", "GR" )
TestPathSet( "R", "H", "R", "HGR" )
TestPathSet( "R", "I", "R", "IGR" )
TestPathSet( "R", "R", "R", "R" )

###################################################
############## PATH_SET_EXCEPTIONS ################

###################################################

print("\nDone")