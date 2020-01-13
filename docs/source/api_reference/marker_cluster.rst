.. Copyright (c) 2018, Johan Mabille, Sylvain Corlay, Wolf Vollprecht and Martin Renou

   Distributed under the terms of the BSD 3-Clause License.

   The full license is in the file LICENSE, distributed with this software.

Marker Cluster
==============

Example
-------

.. code::

    #include "xleaflet/xmap.hpp"
    #include "xleaflet/xbasemaps.hpp"
    #include "xleaflet/xmarker.hpp"
    #include "xleaflet/xmarker_cluster.hpp"

    auto map = xlf::map::initialize()
        .center({50, 354})
        .zoom(5)
        .finalize();

    auto marker1 = xlf::marker::initialize()
        .location({50, 354})
        .finalize();
    auto marker2 = xlf::marker::initialize()
        .location({52, 356})
        .finalize();
    auto marker3 = xlf::marker::initialize()
        .location({48, 352})
        .finalize();

    auto marker_cluster = xlf::marker_cluster::initialize()
        .markers({marker1, marker2, marker3})
        .finalize();

    map.add_layer(marker_cluster);

    map

Attributes
----------

=====================   ========================================    ================   ===
Attribute               Type                                        Default Value      Doc
=====================   ========================================    ================   ===
markers                 ``std::vector<xlf::marker>``                {}                 Array of markers
=====================   ========================================    ================   ===
