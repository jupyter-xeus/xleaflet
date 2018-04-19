.. Copyright (c) 2018, Johan Mabille, Sylvain Corlay, Wolf Vollprecht and Martin Renou

   Distributed under the terms of the BSD 3-Clause License.

   The full license is in the file LICENSE, distributed with this software.

.. raw:: html
    :file: embed_widgets/wms_layer.html

WMS layer
=========

Example
-------

.. code::

    #include "xleaflet/xmap.hpp"
    #include "xleaflet/xwms_layer.hpp"

    auto wms = xlf::wms_layer_generator()
        .url("https://demo.boundlessgeo.com/geoserver/ows?")
        .layers("nasa:bluemarble")
        .finalize();

    auto map = xlf::map_generator()
        .layers({wms})
        .center({42.5531, -48.6914})
        .zoom(3)
        .finalize();

    map

.. raw:: html

    <script type="application/vnd.jupyter.widget-view+json">
    {
        "model_id": "768133089a2b4e56bb9a751b4a0ae077",
        "version_major": 2,
        "version_minor": 0
    }
    </script>

Attributes
----------

=====================   =========================    ===================================================================================   ===
Attribute               Type                         Default Value                                                                         Doc
=====================   =========================    ===================================================================================   ===
url                     ``std::string``              "https://{s}.tile.openstreetmap.org/{z}/{x}/{y}.png"
min_zoom                ``int``                      0
max_zoom                ``int``                      18
tile_size               ``int``                      256
attribution             ``std::string``              "Map data (c) <a href=\'https://openstreetmap.org\'>OpenStreetMap</a> contributors"
detect_retina           ``bool``                     false
opacity                 ``float``                    1.0
visible                 ``bool``                     true
service                 ``std::string``              "WMS"
request                 ``std::string``              "GetMap"
layers                  ``std::string``              ""                                                                                    Comma-separated list of WMS layers to show
styles                  ``std::string``              ""                                                                                    Comma-separated list of WMS styles
format                  ``std::string``              "image/jpeg"                                                                          WMS image format (use `'image/png'` for layers with transparency)
transparent             ``bool``                     false                                                                                 If `true`, the WMS service will return images with transparency
version                 ``std::string``              "1.1.1"                                                                               Version of the WMS service to use
crs                     ``std::string``              ""
=====================   =========================    ===================================================================================   ===
