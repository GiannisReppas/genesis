//ignoring tests in comments

////////// general
add pybind11 autodownload in CMake script
change make_genesis.py script to cmake file
have a .copy() method for some classes
bind ostream in python
stossc warning (error for c++ version > 11)


////////// utils
math/bitvector.py STREAMS - difficulties translating c++ to python code - __REPR__
interoperatability between numpy and matrix
why ::genesis::utils::operator<< won't compile for template parameter ::genesis::utils::Color


////////// sequence
from_string, to string errors


////////// taxonomy


////////// placement
edge_color.py - No way to test it until to_string() is fixed
manipulation.py - levelorder bug from tree waiting to be fixed


////////// tree
create a copy function for Node,EdgeData
OR
create a class only for python to keep a py::object in a CommonNodeData derived class
ONLY IF IT IS REALLY NEEDED IN PYTHON

tree/drawing.py - end of tests, find a way to bind ostream
tree/drawing.py - tests don't check anything, they just execute commands

tree/manipulation.py - levelorder convertion compilation error

tree/mass_tree.py - operators.hpp convert bug needs BaseNode/EdgeData (+add placement bindings)

tree/printer.py - check it with c++ tests


////////// population
utils/IntervalTree many bugs
