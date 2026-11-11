.. Copyright (c) 2018, Johan Mabille, Sylvain Corlay, Wolf Vollprecht and Martin Renou

   Distributed under the terms of the BSD 3-Clause License.

   The full license is in the file LICENSE, distributed with this software.

GeoJSON
=======

Example
-------

.. code::

    #include <fstream>

    #include "xleaflet/xmap.hpp"
    #include "xleaflet/xbasemaps.hpp"
    #include "xleaflet/xgeo_json.hpp"

    auto black_and_white = xlf::basemap({"OpenStreetMap", "BlackAndWhite"});

    auto map = xlf::map::initialize();
    map.layers = xlf::map::layer_list_type{black_and_white};
    map.center = xlf::map::point_type{34.6252978589571, -77.34580993652344};
    map.zoom = 10;
    map.finalize();

    // Load a local file
    std::ifstream file("geo.json");
    xeus::xjson geo_data;
    file >> geo_data;

    auto geo_json = xlf::geo_json::initialize();
    geo_json.data = geo_data;
    geo_json.finalize();
    map.add_layer(geo_json);

    map

Attributes
----------

=====================   ========================================    ================   ===
Attribute               Type                                        Default Value      Doc
=====================   ========================================    ================   ===
data                    ``xeus::xjson``                                                Data dictionary
style                   ``xeus::xjson``                                                Style dictionary
hover_style             ``xeus::xjson``                                                Hover style dictionary
=====================   ========================================    ================   ===

Methods
-------

=====================   ===========    =====================================     ===
Method                  Return type    Arguments                                 Doc
=====================   ===========    =====================================     ===
on_click                ``void``       ``std::function<void(xeus::xjson)>``      Adds a callback on click event
on_hover                ``void``       ``std::function<void(xeus::xjson)>``      Adds a callback on hover event
=====================   ===========    =====================================     ===
