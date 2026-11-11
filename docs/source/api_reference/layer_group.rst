.. Copyright (c) 2018, Johan Mabille, Sylvain Corlay, Wolf Vollprecht and Martin Renou

   Distributed under the terms of the BSD 3-Clause License.

   The full license is in the file LICENSE, distributed with this software.

Layer Group
===========

Example
-------

.. code::

    #include "xleaflet/xmap.hpp"
    #include "xleaflet/xbasemaps.hpp"
    #include "xleaflet/xlayer_group.hpp"
    #include "xleaflet/xcircle.hpp"
    #include "xleaflet/xmarker.hpp"
    #include "xleaflet/xrectangle.hpp"

    auto toner = xlf::basemap({"Stamen", "Toner"});

    auto map = xlf::map::initialize();
    map.layers = xlf::map::layer_list_type{toner};
    map.center = xlf::map::point_type{50, 354};
    map.zoom = 5;
    map.finalize();

    // Create some layers
    auto marker = xlf::marker::initialize();
    marker.location = xlf::marker::point_type{50, 354};
    marker.finalize();
    auto circle = xlf::circle::initialize();
    circle.location = xlf::circle::point_type{50, 370};
    circle.radius = 50000;
    circle.color = "yellow";
    circle.fill_color = "yellow";
    circle.finalize();
    auto rectangle = xlf::rectangle::initialize();
    rectangle.bounds = xlf::rectangle::bounds_type{{{54, 354}, {55, 360}}};
    rectangle.color = "orange";
    rectangle.fill_color = "orange";
    rectangle.finalize();

    // Create layer group
    auto layer_group = xlf::layer_group::initialize();
    layer_group.layers = xlf::layer_group::layer_list_type{marker, circle};
    layer_group.finalize();

    map.add_layer(layer_group);

    layer_group.add_layer(rectangle);

    layer_group.remove_layer(circle);

    map

Attributes
----------

=====================   ========================================    ================   ===
Attribute               Type                                        Default Value      Doc
=====================   ========================================    ================   ===
layers                  ``std::vector<xlf::layer>``                 {}                 Array of layers
=====================   ========================================    ================   ===

Methods
-------

=====================   ===========    =====================================     ===
Method                  Return type    Arguments                                 Doc
=====================   ===========    =====================================     ===
add_layer               ``void``       ``xlf::layer``                            Add a new layer to the group
remove_layer            ``void``       ``xlf::layer``                            Remove a layer from the group
clear_layers            ``void``                                                 Remove all layers from the group
=====================   ===========    =====================================     ===
