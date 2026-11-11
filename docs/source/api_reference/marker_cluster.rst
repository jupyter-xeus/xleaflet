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

    auto map = xlf::map::initialize();
    map.center = xlf::map::point_type{50, 354};
    map.zoom = 5;
    map.finalize();

    auto marker1 = xlf::marker::initialize();
    marker1.location = xlf::marker::point_type{50, 354};
    marker1.finalize();
    auto marker2 = xlf::marker::initialize();
    marker2.location = xlf::marker::point_type{52, 356};
    marker2.finalize();
    auto marker3 = xlf::marker::initialize();
    marker3.location = xlf::marker::point_type{48, 352};
    marker3.finalize();

    auto marker_cluster = xlf::marker_cluster::initialize();
    marker_cluster.markers = xlf::marker_cluster::marker_list_type{marker1, marker2, marker3};
    marker_cluster.finalize();

    map.add_layer(marker_cluster);

    map

Attributes
----------

=====================   ========================================    ================   ===
Attribute               Type                                        Default Value      Doc
=====================   ========================================    ================   ===
markers                 ``std::vector<xlf::marker>``                {}                 Array of markers
=====================   ========================================    ================   ===
