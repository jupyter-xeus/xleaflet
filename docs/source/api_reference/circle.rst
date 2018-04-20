.. Copyright (c) 2018, Johan Mabille, Sylvain Corlay, Wolf Vollprecht and Martin Renou

   Distributed under the terms of the BSD 3-Clause License.

   The full license is in the file LICENSE, distributed with this software.

Circle
======

Example
-------

.. code::

    #include "xleaflet/xmap.hpp"
    #include "xleaflet/xbasemaps.hpp"
    #include "xleaflet/xcircle.hpp"

    auto terrain = xlf::basemap({"Stamen", "Watercolor"});

    auto map = xlf::map_generator()
        .layers({terrain})
        .center({53, 354})
        .zoom(5)
        .finalize();

    auto circle = xlf::circle_generator()
        .location({50, 354})
        .radius(50000)
        .color("green")
        .fill_color("green")
        .finalize();

    map.add_layer(circle);

    map

Attributes
----------

=====================   ========================================    ================   ===
Attribute               Type                                        Default Value      Doc
=====================   ========================================    ================   ===
location                ``std::array<double, 2>``                   {0.0, 0.0}         Location of the circle
radius                  ``int``                                     1000               Radius of the circle, in meters
stroke                  ``bool``                                    true               Set it to `false` to disable borders
color                   ``std::string``                             "#0033FF"          Color of the stroke
opacity                 ``float``                                   1.0                Opacity of the stroke
weight                  ``int``                                     5                  Width of the stroke in pixels
fill                    ``bool``                                    true               Whether to fill the circle or not
fill_color              ``std::string``                             "#0033FF"
fill_opacity            ``float``                                   0.2
dash_array              ``std::string``
line_cap                ``std::string``                             "round"
line_join               ``std::string``                             "round"
=====================   ========================================    ================   ===
