.. Copyright (c) 2018, Johan Mabille, Sylvain Corlay, Wolf Vollprecht and Martin Renou

   Distributed under the terms of the BSD 3-Clause License.

   The full license is in the file LICENSE, distributed with this software.

.. raw:: html
    :file: embed_widgets/tile_layer.html

Tile layer
==========

Example
-------

.. code::

    #include "xleaflet/xmap.hpp"
    #include "xleaflet/xbasemaps.hpp"

    auto map = xlf::map_generator()
        .center({52.204793, 360.121558})
        .zoom(9)
        .finalize();

    auto dark_matter_layer = xlf::basemap({"CartoDB", "DarkMatter"});
    map.add_layer(dark_matter_layer);
    map

.. raw:: html

    <script type="application/vnd.jupyter.widget-view+json">
    {
        "model_id": "9a95fa8590fc4911a0145cfa5111b2d2",
        "version_major": 2,
        "version_minor": 0
    }
    </script>

Usage
-----

Creating a ``tile_layer`` is straightforward, a list of basic tile layers is provided.
This list of layers can be accessed using the ``basemaps`` function:

.. code::

    #include <iostream>

    #include "xleaflet/xbasemaps.hpp"

    std::cout << xlf::basemaps().dump(6) << std::endl;

A ``tile_layer`` instance can be created using the ``basemap`` function, specifying the wanted map
(e.g. ``{"CartoDB", "DarkMatter"}``, ``{"Strava", "Winter"}``, ``{"NASAGIBS", "ModisTerraTrueColorCR"}``, ...).

Sometimes one could want to specify the date of the given images, for instance with NASA images:

.. code::

    auto nasa_layer = xlf::basemap({"NASAGIBS", "ModisTerraTrueColorCR"}, "2018-04-08");
    map.add_layer(nasa_layer);

Attributes
----------

=====================   ===============    ===================================================================================
Attribute               Type               Default Value
=====================   ===============    ===================================================================================
url                     ``std::string``    "https://{s}.tile.openstreetmap.org/{z}/{x}/{y}.png"
min_zoom                ``int``            0
max_zoom                ``int``            18
tile_size               ``int``            256
attribution             ``std::string``    "Map data (c) <a href=\'https://openstreetmap.org\'>OpenStreetMap</a> contributors"
detect_retina           ``bool``           false
opacity                 ``float``          1.0
visible                 ``bool``           true
=====================   ===============    ===================================================================================
