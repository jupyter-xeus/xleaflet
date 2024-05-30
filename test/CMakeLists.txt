############################################################################
# Copyright (c) 2018, Sylvain Corlay, Johan Mabille, and Wolf Vollprecht   #
#                                                                          #
# Distributed under the terms of the BSD 3-Clause License.                 #
#                                                                          #
# The full license is in the file LICENSE, distributed with this software. #
############################################################################

cmake_minimum_required(VERSION 3.8)

find_package(pybind11 REQUIRED)

message(STATUS "Forcing tests build type to Release")
set(CMAKE_BUILD_TYPE Release CACHE STRING "Choose the type of build." FORCE)

if (CMAKE_CURRENT_SOURCE_DIR STREQUAL CMAKE_SOURCE_DIR)
    project(xleaflet-test)

    find_package(xleaflet REQUIRED CONFIG)
    set(XWIDGETS_INCLUDE_DIR ${xwidgets_INCLUDE_DIRS})
    set(XLEAFLET_INCLUDE_DIR ${xleaflet_INCLUDE_DIRS})
endif ()

# Dependencies
# ============

find_package(doctest)
find_package(Threads)

# Source files
# ============

include_directories(${XLEAFLET_INCLUDE_DIR})

set(XLEAFLET_TESTS
    main.cpp
    test_xleaflet.cpp
)

# Output
# ======

add_executable(test_xleaflet ${XLEAFLET_TESTS} ${XLEAFLET_HEADERS})
include_directories(${pybind11_INCLUDE_DIRS})
target_compile_features(test_xleaflet PRIVATE cxx_std_14)

target_link_libraries(test_xleaflet
                      PUBLIC xtl
                      PUBLIC xeus
                      PUBLIC xwidgets
                      PUBLIC xleaflet
                      PRIVATE doctest::doctest
                      PRIVATE ${CMAKE_THREAD_LIBS_INIT}
                      PRIVATE ${PYTHON_LIBRARIES} pybind11::embed    )
target_include_directories(test_xleaflet PRIVATE ${XLEAFLET_INCLUDE_DIR} ${XWIDGETS_INCLUDE_DIR})
