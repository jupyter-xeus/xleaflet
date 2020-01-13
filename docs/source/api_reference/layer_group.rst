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

    auto map = xlf::map::initialize()
        .layers({toner})
        .center({50, 354})
        .zoom(5)
        .finalize();

    // Create some layers
    auto marker = xlf::marker::initialize()
        .location({50, 354})
        .finalize();
    auto circle = xlf::circle::initialize()
        .location({50, 370})
        .radius(50000)
        .color("yellow")
        .fill_color("yellow")
        .finalize();
    auto rectangle = xlf::rectangle::initialize()
        .bounds({{{54, 354}, {55, 360}}})
        .color("orange")
        .fill_color("orange")
        .finalize();

    // Create layer group
    auto layer_group = xlf::layer_group::initialize()
        .layers({marker, circle})
        .finalize();

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
