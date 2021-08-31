/******************************************************************************
* Copyright (c) 2018, Sylvain Corlay and Johan Mabille, and Wolf Vollprecht   *
*                                                                             *
* Distributed under the terms of the BSD 3-Clause License.                    *
*                                                                             *
* The full license is in the file LICENSE, distributed with this software.    *
*******************************************************************************/

#ifndef XLEAFLET_CONFIG_HPP
#define XLEAFLET_CONFIG_HPP

#include <string>

// Visual C++ declspec macros
#ifdef _WIN32
    #ifdef XLEAFLET_EXPORTS
        #define XLEAFLET_API __declspec(dllexport)
    #else
        #define XLEAFLET_API __declspec(dllimport)
    #endif
#else
    #define XLEAFLET_API
#endif

// Project version
#define XLEAFLET_VERSION_MAJOR 0
#define XLEAFLET_VERSION_MINOR 15
#define XLEAFLET_VERSION_PATCH 0

// Binary version
#define XLEAFLET_BINARY_CURRENT 1
#define XLEAFLET_BINARY_REVISION 0
#define XLEAFLET_BINARY_AGE 1

// Semver requirement for jupyter-leaflet
#define XJUPYTER_LEAFLET_VERSION_MAJOR 0
#define XJUPYTER_LEAFLET_VERSION_MINOR 14
#define XJUPYTER_LEAFLET_VERSION_PATCH 0

// Composing the version strings from major, minor and patch
#define XLEAFLET_CONCATENATE(A, B) XLEAFLET_CONCATENATE_IMPL(A, B)
#define XLEAFLET_CONCATENATE_IMPL(A, B) A##B
#define XLEAFLET_STRINGIFY(a) XLEAFLET_STRINGIFY_IMPL(a)
#define XLEAFLET_STRINGIFY_IMPL(a) #a

#define XJUPYTER_LEAFLET_VERSION XLEAFLET_STRINGIFY(XLEAFLET_CONCATENATE(XJUPYTER_LEAFLET_VERSION_MAJOR,   \
                             XLEAFLET_CONCATENATE(.,XLEAFLET_CONCATENATE(XJUPYTER_LEAFLET_VERSION_MINOR,   \
                                                  XLEAFLET_CONCATENATE(.,XJUPYTER_LEAFLET_VERSION_PATCH)))))

inline std::string jupyter_leaflet_semver()
{
    return std::string("^") + XJUPYTER_LEAFLET_VERSION;
}

#ifdef __CLING__
#include "xleaflet_config_cling.hpp"
#endif

#endif
