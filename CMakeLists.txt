############################################################################
# Copyright (c) 2017, Sylvain Corlay, Johan Mabille and Wolf Vollprecht    #
#                                                                          #
# Distributed under the terms of the BSD 3-Clause License.                 #
#                                                                          #
# The full license is in the file LICENSE, distributed with this software. #
############################################################################

cmake_minimum_required(VERSION 3.8)
project(xleaflet)

message(STATUS "Forcing tests build type to Release")
set(CMAKE_BUILD_TYPE Release CACHE STRING "Choose the type of build." FORCE)

set(XLEAFLET_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)
set(XLEAFLET_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)

# Configuration
# =============

include(GNUInstallDirs)
include(CMakePackageConfigHelpers)

set(XLEAFLET_INSTALL_LIBRARY_DIR "\"${CMAKE_INSTALL_PREFIX}/${CMAKE_INSTALL_LIBDIR}\"")

configure_file (
    "${XLEAFLET_INCLUDE_DIR}/xleaflet/xleaflet_config_cling.hpp.in"
    "${XLEAFLET_INCLUDE_DIR}/xleaflet/xleaflet_config_cling.hpp"
)

# Versionning
# ===========

file(STRINGS "${XLEAFLET_INCLUDE_DIR}/xleaflet/xleaflet_config.hpp" xleaflet_version_defines
     REGEX "#define XLEAFLET_VERSION_(MAJOR|MINOR|PATCH)")
foreach(ver ${xleaflet_version_defines})
    if(ver MATCHES "#define XLEAFLET_VERSION_(MAJOR|MINOR|PATCH) +([^ ]+)$")
        set(XLEAFLET_VERSION_${CMAKE_MATCH_1} "${CMAKE_MATCH_2}" CACHE INTERNAL "")
    endif()
endforeach()
set(XLEAFLET_VERSION
    ${XLEAFLET_VERSION_MAJOR}.${XLEAFLET_VERSION_MINOR}.${XLEAFLET_VERSION_PATCH})
message(STATUS "xleaflet version: v${XLEAFLET_VERSION}")

# Binary version
# See the following URL for explanations about the binary versionning
# https://www.gnu.org/software/libtool/manual/html_node/Updating-version-info.html#Updating-version-info
file(STRINGS "${XLEAFLET_INCLUDE_DIR}/xleaflet/xleaflet_config.hpp" xleaflet_version_defines
    REGEX "#define XLEAFLET_BINARY_(CURRENT|REVISION|AGE)")
foreach(ver ${xleaflet_version_defines})
    if(ver MATCHES "#define XLEAFLET_BINARY_(CURRENT|REVISION|AGE) +([^ ]+)$")
        set(XLEAFLET_BINARY_${CMAKE_MATCH_1} "${CMAKE_MATCH_2}" CACHE INTERNAL "")
    endif()
endforeach()
set(XLEAFLET_BINARY_VERSION
    ${XLEAFLET_BINARY_CURRENT}.${XLEAFLET_BINARY_REVISION}.${XLEAFLET_BINARY_AGE})
message(STATUS "xleaflet binary version: v${XLEAFLET_BINARY_VERSION}")

# Dependencies
# ============

find_package(cppzmq 4.2.3 REQUIRED)
find_package(xtl 0.4 REQUIRED)
find_package(xeus 0.11.0 REQUIRED)
find_package(xwidgets 0.8.2 REQUIRED)

# Source files
# ============

set(XLEAFLET_HEADERS
    ${XLEAFLET_INCLUDE_DIR}/xleaflet/xcircle_marker.hpp
    ${XLEAFLET_INCLUDE_DIR}/xleaflet/xcircle.hpp
    ${XLEAFLET_INCLUDE_DIR}/xleaflet/xfeature_group.hpp
    ${XLEAFLET_INCLUDE_DIR}/xleaflet/xgeo_json.hpp
    ${XLEAFLET_INCLUDE_DIR}/xleaflet/ximage_overlay.hpp
    ${XLEAFLET_INCLUDE_DIR}/xleaflet/xlayer_group.hpp
    ${XLEAFLET_INCLUDE_DIR}/xleaflet/xlayer.hpp
    ${XLEAFLET_INCLUDE_DIR}/xleaflet/xleaflet_config_cling.hpp
    ${XLEAFLET_INCLUDE_DIR}/xleaflet/xleaflet_config.hpp
    ${XLEAFLET_INCLUDE_DIR}/xleaflet/xmap.hpp
    ${XLEAFLET_INCLUDE_DIR}/xleaflet/xmarker_cluster.hpp
    ${XLEAFLET_INCLUDE_DIR}/xleaflet/xmarker.hpp
    ${XLEAFLET_INCLUDE_DIR}/xleaflet/xpath.hpp
    ${XLEAFLET_INCLUDE_DIR}/xleaflet/xpolygon.hpp
    ${XLEAFLET_INCLUDE_DIR}/xleaflet/xpolyline.hpp
    ${XLEAFLET_INCLUDE_DIR}/xleaflet/xraster_layer.hpp
    ${XLEAFLET_INCLUDE_DIR}/xleaflet/xrectangle.hpp
    ${XLEAFLET_INCLUDE_DIR}/xleaflet/xtile_layer.hpp
    ${XLEAFLET_INCLUDE_DIR}/xleaflet/xui_layer.hpp
    ${XLEAFLET_INCLUDE_DIR}/xleaflet/xvector_layer.hpp
    ${XLEAFLET_INCLUDE_DIR}/xleaflet/xvideo_overlay.hpp
    ${XLEAFLET_INCLUDE_DIR}/xleaflet/xwms_layer.hpp
)

set(XLEAFLET_SOURCES
    ${XLEAFLET_SOURCE_DIR}/xleaflet.cpp
)

# Output
# ======

add_library(xleaflet SHARED ${XLEAFLET_SOURCES} ${XLEAFLET_HEADERS})
target_include_directories(xleaflet PUBLIC $<BUILD_INTERFACE:${XLEAFLET_INCLUDE_DIR}>
                                           $<INSTALL_INTERFACE:include>)

target_link_libraries(xleaflet
    PUBLIC xtl
    PUBLIC xeus
    PUBLIC xwidgets)

set_target_properties(xleaflet PROPERTIES
                      PUBLIC_HEADER "${XLEAFLET_HEADERS}"
                      COMPILE_DEFINITIONS "XLEAFLET_EXPORTS"
                      PREFIX ""
                      VERSION ${XLEAFLET_BINARY_VERSION}
                      SOVERSION ${XLEAFLET_BINARY_CURRENT}
                      OUTPUT_NAME "libxleaflet")

# Compilation flags
# =================

include(CheckCXXCompilerFlag)
string(TOUPPER "${CMAKE_BUILD_TYPE}" U_CMAKE_BUILD_TYPE)
OPTION(DISABLE_ARCH_NATIVE "disable -march=native flag" OFF)

set_target_properties(xleaflet PROPERTIES
    CXX_EXTENSIONS OFF
    CXX_STANDARD_REQUIRED 14)

target_compile_features(xleaflet PRIVATE cxx_std_14)

if (CMAKE_CXX_COMPILER_ID MATCHES "Clang" OR CMAKE_CXX_COMPILER_ID MATCHES "GNU" OR CMAKE_CXX_COMPILER_ID MATCHES "Intel")
    target_compile_options(xleaflet PUBLIC -Wunused-parameter -Wextra -Wreorder)
    if (DISABLE_ARCH_NATIVE)
        target_compile_options(xleaflet PUBLIC -mtune=generic)
    else()
        target_compile_options(xleaflet PUBLIC -march=native)
    endif()

    # Enable link time optimization and set the default symbol
    # visibility to hidden (very important to obtain small binaries)
    if (NOT ${U_CMAKE_BUILD_TYPE} MATCHES DEBUG)
        # Check for Link Time Optimization support
        # (GCC/Clang)
        CHECK_CXX_COMPILER_FLAG("-flto" HAS_LTO_FLAG)
        if (HAS_LTO_FLAG)
            target_compile_options(xleaflet PUBLIC -flto)
        endif()

        # Intel equivalent to LTO is called IPO
        if (CMAKE_CXX_COMPILER_ID MATCHES "Intel")
            CHECK_CXX_COMPILER_FLAG("-ipo" HAS_IPO_FLAG)
            if (HAS_IPO_FLAG)
                target_compile_options(xleaflet PUBLIC -ipo)
            endif()
        endif()
    endif()
    message(STATUS "CMAKE_CXX_FLAGS: ${CMAKE_CXX_FLAGS}")
endif()

# if(MSVC)
#     target_compile_definitions(xleaflet PUBLIC -DNOMINMAX)
#     target_compile_options(xleaflet PUBLIC /DGUID_WINDOWS /MP /bigobj)
#     target_compile_options(xleaflet PUBLIC /wd4251 /wd 4996)
#     # Allows to compile in debug without requiring each dependencies to
#     # be compiled in debug
#     if(${U_CMAKE_BUILD_TYPE} MATCHES DEBUG)
#         set(CMAKE_CXX_FLAGS_DEBUG "/DNDEBUG /MD /Zi /Ob0 /Od /RTC1")
#         message(STATUS "Overriding CMAKE_CXX_FLAGS_DEBUG: ${CMAKE_CXX_FLAGS_DEBUG}")
#     endif()
# endif()

# Tests
# =====

OPTION(BUILD_TESTS "xleaflet test suite" OFF)
OPTION(DOWNLOAD_GTEST "build gtest from downloaded sources" OFF)

if(DOWNLOAD_GTEST OR GTEST_SRC_DIR)
    set(BUILD_TESTS ON)
endif()

if(BUILD_TESTS)
    add_subdirectory(test)
endif()

# Installation
# ============

set(XLEAFLET_CMAKECONFIG_INSTALL_DIR "${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}" CACHE STRING "install path for xleafletConfig.cmake")

install(TARGETS xleaflet
        EXPORT ${PROJECT_NAME}-targets
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
        PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/xleaflet)

# Makes the project importable from the build directory
export(EXPORT ${PROJECT_NAME}-targets
       FILE "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Targets.cmake")

configure_package_config_file(${PROJECT_NAME}Config.cmake.in
                              "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Config.cmake"
                              INSTALL_DESTINATION ${XLEAFLET_CMAKECONFIG_INSTALL_DIR})
write_basic_package_version_file(${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake
                                 VERSION ${XLEAFLET_VERSION}
                                 COMPATIBILITY AnyNewerVersion)
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Config.cmake
              ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake
              DESTINATION ${XLEAFLET_CMAKECONFIG_INSTALL_DIR})
install(EXPORT ${PROJECT_NAME}-targets
        FILE ${PROJECT_NAME}Targets.cmake
DESTINATION ${XLEAFLET_CMAKECONFIG_INSTALL_DIR})
