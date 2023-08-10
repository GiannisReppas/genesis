//ignoring tests in comments

/* general */

add pybind11 autodownload in CMake script
change python script to cmake file
why -include-pybind11-stl for binder command and not in config file
have a .copy() method for some classes
bind ostream in python
from_string, to string errors


/* utils */


math/bitvector.py STREAMS - difficulties translating c++ to python code - __REPR__
interoperatability between numpy and matrix
stossc warning (error for c++ version > 11)
why ::genesis::utils::operator<< won't compile for template parameter ::genesis::utils::Color


/* sequence */


remove make_unique from bindings (if possible)


/* taxonomy */


taxonomy/iterator.py - error at last test


/* tree */

create a copy function for Node,EdgeData
OR
create a class only for python to keep a py::object in a CommonNodeData derived class
ONLY IF IT IS REALLY NEEDED IN PYTHON

tree/drawing.py - end of tests, find a way to bind ostream
tree/drawing.py - tests don't check anything, they just execute commands

tree/manipulation.py - levelorder convertion compilation error

tree/mass_tree.py - operators.hpp convert bug needs BaseNode/EdgeData (+add placement bindings)

tree/printer.py - check it with c++ tests


/* placement */


edge_color.py - No way to test it until to_string() is fixed
manipulation.py - levelorder bug from tree waiting to be fixed


/* population */


utils/IntervalTree many bugs
