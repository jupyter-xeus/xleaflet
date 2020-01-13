.. Copyright (c) 2018, Johan Mabille, Sylvain Corlay, Wolf Vollprecht and Martin Renou

   Distributed under the terms of the BSD 3-Clause License.

   The full license is in the file LICENSE, distributed with this software.

Polygon
=======

Example
-------

.. code::

    #include "xleaflet/xmap.hpp"
    #include "xleaflet/xpolygon.hpp"

    auto polygon = xlf::polygon::initialize()
        .locations({{{42, -49}, {43, -49}, {43, -48}}})
        .color("green")
        .fill_color("green")
        .finalize();

    auto map = xlf::map::initialize()
        .center({42.5531, -48.6914})
        .zoom(6)
        .finalize();
    map.add_layer(polygon);

    map

Attributes
----------

=====================   ======================================    ================   ===
Attribute               Type                                      Default Value      Doc
=====================   ======================================    ================   ===
locations               ``std::vector<std::array<double, 2>>``    {}                 List of points of the polygon
stroke                  ``bool``                                  true               Set it to `false` to disable borders
color                   ``std::string``                           "#0033FF"          Color of the stroke
opacity                 ``float``                                 1.0                Opacity of the stroke
weight                  ``int``                                   5                  Width of the stroke in pixels
fill                    ``bool``                                  true               Whether to fill the polygon or not
fill_color              ``std::string``                           "#0033FF"
fill_opacity            ``float``                                 0.2
dash_array              ``std::string``
line_cap                ``std::string``                           "round"
line_join               ``std::string``                           "round"
=====================   ======================================    ================   ===
