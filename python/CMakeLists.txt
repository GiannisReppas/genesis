<<<<<<< HEAD
project(mylibgenesis)
cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)
include_directories(/home/giannis/Desktop/binder/source)
include_directories(./../lib)
include_directories(/usr/include/pybind11)
include_directories(/usr/include/python3.10)
set_property(GLOBAL PROPERTY POSITION_INDEPENDENT_CODE ON)
add_definitions(-DNDEBUG)
add_library(mylibgenesis SHARED
	mylibgenesis.cpp
	std/type_traits.cpp
	std/stl_iterator_base_types.cpp
	std/exception.cpp
	bits/types/struct_FILE.cpp
	std/stdexcept.cpp
	std/locale_classes.cpp
	std/basic_ios_tcc.cpp
	std/istream_tcc.cpp
	std/fstream_tcc.cpp
	std/random.cpp
	genesis/utils/math/bitvector.cpp
	std/genesis/utils/math/bitvector.cpp
	genesis/utils/math/bitvector/helper.cpp
	genesis/utils/color/functions.cpp
	genesis/utils/containers/range.cpp
	genesis/utils/containers/matrix.cpp
	genesis/utils/containers/matrix_1.cpp
	genesis/utils/containers/matrix_2.cpp
	genesis/utils/tools/char_lookup.cpp
	genesis/utils/core/logging.cpp
	genesis/utils/core/fs.cpp
	genesis/utils/io/input_source.cpp
	genesis/utils/text/string.cpp
	genesis/utils/text/string_1.cpp
	genesis/utils/io/base_output_target.cpp
	genesis/utils/io/gzip_output_target.cpp
	genesis/utils/math/common.cpp
	genesis/utils/color/names.cpp
	genesis/utils/tools/tickmarks.cpp
	genesis/utils/formats/svg/helper.cpp
	genesis/utils/formats/svg/attributes.cpp
	genesis/utils/formats/svg/group.cpp
	genesis/utils/formats/svg/color_bar.cpp
	genesis/utils/formats/svg/shapes.cpp
	genesis/utils/formats/svg/shapes_1.cpp
	genesis/utils/formats/nexus/writer.cpp
	genesis/utils/math/statistics.cpp
	genesis/utils/math/statistics_1.cpp
	genesis/utils/math/matrix.cpp
	genesis/utils/containers/interval_tree.cpp
	genesis/utils/containers/interval_tree/node.cpp
	genesis/utils/containers/interval_tree/iterator.cpp
	genesis/utils/containers/interval_tree/node_1.cpp
	__/python/custom_bindings/template_instances/matrix.cpp
	genesis/utils/containers/lambda_iterator.cpp
	genesis/sequence/functions/codes.cpp
	genesis/sequence/counts.cpp
	genesis/sequence/formats/phylip_reader.cpp
	genesis/sequence/functions/consensus.cpp
	genesis/sequence/functions/consensus_1.cpp
	genesis/sequence/reference_genome.cpp
	genesis/sequence/functions/dict.cpp
	genesis/sequence/functions/functions.cpp
	genesis/sequence/functions/functions_1.cpp
	genesis/sequence/functions/quality.cpp
	genesis/sequence/formats/fastq_writer.cpp
	genesis/sequence/functions/stats.cpp
	genesis/sequence/functions/labels.cpp
	genesis/sequence/functions/signatures.cpp
	genesis/sequence/functions/signatures_1.cpp
	genesis/taxonomy/formats/taxopath_parser.cpp
	genesis/taxonomy/taxonomy.cpp
	genesis/taxonomy/functions/taxonomy.cpp
	std/genesis/taxonomy/taxopath.cpp
	genesis/taxonomy/printers/nested.cpp
	genesis/taxonomy/iterator/preorder.cpp
	genesis/tree/tree/link.cpp
	genesis/tree/tree.cpp
	genesis/tree/common_tree/tree.cpp
	genesis/tree/common_tree/newick_reader.cpp
	genesis/tree/function/functions.cpp
	genesis/taxonomy/functions/tree.cpp
	genesis/tree/drawing/layout_tree.cpp
	genesis/tree/drawing/heat_tree.cpp
	genesis/tree/common_tree/functions.cpp
	genesis/tree/function/manipulation.cpp
	genesis/tree/function/operators.cpp
	genesis/tree/mass_tree/balances.cpp
	genesis/tree/mass_tree/phylo_ilr.cpp
	genesis/tree/common_tree/newick_writer.cpp
	genesis/tree/formats/newick/input_iterator.cpp
	genesis/tree/attribute_tree/tree.cpp
	genesis/tree/attribute_tree/keyed_newick_reader.cpp
	genesis/tree/bipartition/rf.cpp
	genesis/tree/iterator/path.cpp
	__/python/custom_bindings/template_instances/path.cpp
	genesis/tree/iterator/path_set.cpp
	__/python/custom_bindings/template_instances/path_set.cpp
	genesis/placement/formats/jplace_reader.cpp
	genesis/placement/sample.cpp
	genesis/placement/function/functions.cpp
	genesis/placement/function/functions_1.cpp
	genesis/placement/pquery/plain.cpp
	__/python/custom_bindings/template_instances/range.cpp
	genesis/placement/formats/jplace_writer.cpp
	genesis/placement/function/nhd.cpp
	genesis/placement/function/epca.cpp
	genesis/placement/function/operators.cpp
	genesis/placement/simulator/distributions.cpp
	genesis/population/genome_region.cpp
	genesis/population/genome_locus_set.cpp
	genesis/population/base_counts.cpp
	genesis/population/formats/simple_pileup_input_iterator.cpp
	genesis/population/formats/sync_reader.cpp
	genesis/population/formats/variant_input_iterator.cpp
	genesis/population/window/base_window.cpp
	genesis/population/window/chromosome_iterator.cpp
	genesis/population/window/chromosome_iterator_1.cpp
	genesis/population/functions/functions.cpp
	__/python/custom_bindings/template_instances/lambda_iterator.cpp
)
target_link_libraries(mylibgenesis PUBLIC /home/giannis/Desktop/genesis/bin/libgenesis.so )
set_target_properties(mylibgenesis PROPERTIES PREFIX "")
set_target_properties(mylibgenesis PROPERTIES SUFFIX ".so")
=======
# Genesis - A toolkit for working with phylogenetic data.
# Copyright (C) 2014-2024 Lucas Czech
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.
#
# Contact:
# Lucas Czech <lucas.czech@h-its.org>
# Exelixis Lab, Heidelberg Institute for Theoretical Studies
# Schloss-Wolfsbrunnenweg 35, D-69118 Heidelberg, Germany

# ------------------------------------------------------------------------------
#   Setup Python
# ------------------------------------------------------------------------------

# Check for Python libs. Pybind does not check for the python dev packages, so we need to do this.
message (STATUS "Looking for PythonLibs")
find_package (PythonLibs 2.7)

if( NOT PYTHONLIBS_FOUND )
    message (STATUS "PythonLibs not found")
    message (STATUS "${ColorRed}Cannot build Python module${ColorEnd}")
    message (STATUS "${ColorYellow}Try installing the 'python-dev' or 'python2.7-dev' packages "
    "first.${ColorEnd}")
    return()
endif()

message (STATUS "Found PythonLibs: ${PYTHONLIBS_VERSION_STRING}")

# ------------------------------------------------------------------------------
#   Setup Pybind11
# ------------------------------------------------------------------------------

# CMake version check first.
if( ${CMAKE_VERSION} VERSION_LESS 2.8.12 )
    message (STATUS "Pybind11 requires at least CMake version 2.8.12")
    message (STATUS "${ColorRed}Cannot build Python module${ColorEnd}")
    return()
endif()

# As Pybind11 is a header-only library, we simply check for its existence.
message (STATUS "Looking for Pybind11")

IF( NOT EXISTS ${PROJECT_SOURCE_DIR}/tools/pybind11/include/pybind11/pybind11.h )
    message (STATUS "Pybind11 not found")
    message (STATUS "Will now download Pybind11")

    # If Pybind11 was not found, we download and unpack it (at configure time). This roughly follows
    # https://github.com/google/googletest/tree/master/googletest#incorporating-into-an-existing-cmake-project
    # See also the CMakeLists.txt file for the tests - there we use this technique for GTest.

    configure_file(
        ${PROJECT_SOURCE_DIR}/tools/cmake/Pybind11Download.cmake
        ${CMAKE_BINARY_DIR}/pybind11-download/CMakeLists.txt
    )

    execute_process( COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
        RESULT_VARIABLE result
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/pybind11-download
    )

    if(result)
        message (STATUS "Cannot configure Pybind11: ${result}")
        message (STATUS "${ColorRed}Cannot build Python module${ColorEnd}")
        return()
    endif()

    execute_process( COMMAND ${CMAKE_COMMAND} --build .
        RESULT_VARIABLE result
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/pybind11-download
    )

    if(result)
        message (STATUS "Cannot build Pybind11: ${result}")
        message (STATUS "${ColorRed}Cannot build Python module${ColorEnd}")
        return()
    endif()

    # If the header still does not exists, something went wrong.
    IF( NOT EXISTS ${PROJECT_SOURCE_DIR}/tools/pybind11/include/pybind11/pybind11.h )
        message (STATUS "Pybind11 not found")
        message (STATUS "${ColorRed}Cannot build Python module${ColorEnd}")
        return()
    ENDIF()

    message (STATUS "Finished downloading Pybind11")
ENDIF()

# Include Pybind11, as documented in http://pybind11.readthedocs.io/en/master/compiling.html#building-with-cmake
# We use the two-args version of add_subdirectory here, because it is not an actual subdirectory.
add_subdirectory( ${PROJECT_SOURCE_DIR}/tools/pybind11 ${CMAKE_CURRENT_BINARY_DIR}/pybind11 )

# Get the Pybind version, which is currently not exported directly...
SET(PYBIND11_VERSION ${PYBIND11_VERSION_MAJOR}.${PYBIND11_VERSION_MINOR}.${PYBIND11_VERSION_PATCH})

message (STATUS "Found Pybind11: ${PYBIND11_VERSION}")
message (STATUS "${ColorBlue}Building Python module${ColorEnd}")

# ------------------------------------------------------------------------------
#   Build Options
# ------------------------------------------------------------------------------

# Path to store the Python module.
set (LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin/python)

# Set rpath for all targets, so that they work out of the box (libgenesis.so in parent directory),
# as well as when relocating with the lib being in the same directory.
# Also, we need to set two versions of ORIGIN here (one and two dollar signs).
# This is because on some systems it seems to be escaped, on some not...
# See https://cmake.org/pipermail/cmake/2008-January/019290.html
# and https://cmake.org/Wiki/CMake_RPATH_handling for details.
# Tipp: Use `ldd binary` and `readelf -d binary` to check RPATH settings.
set( CMAKE_INSTALL_RPATH "$ORIGIN/..:$$ORIGIN/..:$ORIGIN:$$ORIGIN" )
set( CMAKE_BUILD_WITH_INSTALL_RPATH TRUE )

# No need to link to Python - this is done by Pybind. We keep it here for reference.
# include_directories   (${PYTHON_INCLUDE_DIRS})
# link_directories      (${PYTHON_LIBRARIES})

# ------------------------------------------------------------------------------
#   Sources
# ------------------------------------------------------------------------------

IF( GENESIS_UNITY_BUILD )
    # See main CMake file for the monolith macro.
    ASSEMBLE_MONOLITH( ${PROJECT_SOURCE_DIR}/python/src "${GENESIS_UNITY_BUILD}" "python" genesis_python_sources )
ELSE()
    file (GLOB_RECURSE genesis_python_sources ${PROJECT_SOURCE_DIR}/python/src/*.cpp)
ENDIF()

include_directories (${PROJECT_SOURCE_DIR}/python)
include_directories (${PROJECT_SOURCE_DIR}/lib)

# ------------------------------------------------------------------------------
#   Build Python Module
# ------------------------------------------------------------------------------

# Add the Pybind module, which is the equivalent of add_library(...).
pybind11_add_module( genesis_python_module MODULE ${genesis_python_sources} )

# Make sure that all Pybind things are processed before.
add_dependencies( genesis_python_module pybind11 )

# Link against our library.
target_link_libraries (genesis_python_module PRIVATE genesis_lib_shared)

# No need to do this manually, Pybind takes care of this. Keep it for reference.
# target_link_libraries (genesis_python_module ${PYTHON_LIBRARIES})

# Make sure that the module file is named according to Python standards
# (that is, no leading "lib", but don't change automatic suffix for shared libraries, e.g., ".so").
set_target_properties (genesis_python_module PROPERTIES OUTPUT_NAME genesis)
set_target_properties (genesis_python_module PROPERTIES PREFIX "")
set_target_properties (genesis_python_module PROPERTIES SUFFIX "${PYTHON_MODULE_EXTENSION}")

# add_custom_command (OUTPUT python_init COMMAND
#     touch ${PROJECT_SOURCE_DIR}/bin/python/__init__.py
# )

# Link against any external libraries.
target_link_libraries (genesis_python_module PRIVATE ${GENESIS_INTERNAL_LINK_LIBRARIES})
>>>>>>> dev
