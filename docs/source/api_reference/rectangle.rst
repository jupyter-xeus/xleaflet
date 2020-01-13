.. Copyright (c) 2018, Johan Mabille, Sylvain Corlay, Wolf Vollprecht and Martin Renou

   Distributed under the terms of the BSD 3-Clause License.

   The full license is in the file LICENSE, distributed with this software.

Rectangle
=========

Example
-------

.. code::

    #include "xleaflet/xmap.hpp"
    #include "xleaflet/xbasemaps.hpp"
    #include "xleaflet/xrectangle.hpp"

    auto terrain = xlf::basemap({"Stamen", "Watercolor"});

    auto map = xlf::map::initialize()
        .layers({terrain})
        .center({53, 354})
        .zoom(5)
        .finalize();

    auto rectangle = xlf::rectangle::initialize()
        .bounds({{{52, 354}, {53, 360}}})
        .finalize();

    map.add_layer(rectangle);

    map

Attributes
----------

=====================   ========================================    ================   ===
Attribute               Type                                        Default Value      Doc
=====================   ========================================    ================   ===
bounds                  ``std::array<std::array<double, 2>, 2>``    {}                 SW and NE corners of the rectangle
stroke                  ``bool``                                    true               Set it to `false` to disable borders
color                   ``std::string``                             "#0033FF"          Color of the stroke
opacity                 ``float``                                   1.0                Opacity of the stroke
weight                  ``int``                                     5                  Width of the stroke in pixels
fill                    ``bool``                                    true               Whether to fill the polygon or not
fill_color              ``std::string``                             "#0033FF"
fill_opacity            ``float``                                   0.2
dash_array              ``std::string``
line_cap                ``std::string``                             "round"
line_join               ``std::string``                             "round"
=====================   ========================================    ================   ===
