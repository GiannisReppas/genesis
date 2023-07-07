import sys

sys.path.append('./bin')

from yoyo.genesis.utils import *
from yoyo.genesis.tree import *

##################################################
################### COMPACT ######################

input = "((A,(B,C)D)E,((F,(G,H)I)J,K)L)R;"

#tree = CommonTreeNewickReader().read( from_string( input ))
tree = CommonTreeNewickReader().read( from_file( './test/src/tree/printer_py.txt' ))

tp = PrinterCompact()
res = tp.print(tree)

##################################################
################### DETAILED #####################

input = "((A,(B,C)D)E,((F,(G,H)I)J,K)L)R;"

#tree = CommonTreeNewickReader().read( from_string( input ))
tree = CommonTreeNewickReader().read( from_file( './test/src/tree/printer_py.txt' ))

tp = PrinterDetailed()
res = tp.print(tree)

##################################################
##################### TABLE ######################

input = "((A,(B,C)D)E,((F,(G,H)I)J,K)L)R;";

#tree = CommonTreeNewickReader().read( from_string( input ))
tree = CommonTreeNewickReader().read( from_file( './test/src/tree/printer_py.txt' ))

tp = PrinterTable()
res = tp.print(tree)

##################################################

print("\nDone")
