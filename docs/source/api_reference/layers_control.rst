.. Copyright (c) 2018, Johan Mabille, Sylvain Corlay, Wolf Vollprecht and Martin Renou

   Distributed under the terms of the BSD 3-Clause License.

   The full license is in the file LICENSE, distributed with this software.

.. raw:: html
    :file: embed_widgets/layers_control.html

Layers Control
==============

The ``layers_control`` allows one to display a selector on the top right of the map in order to select which tile layer to display on the map.

.. code::

    #include "xleaflet/xmap.hpp"
    #include "xleaflet/xbasemaps.hpp"
    #include "xleaflet/xtile_layer.hpp"
    #include "xleaflet/xwms_layer.hpp"
    #include "xleaflet/xlayers_control.hpp"

    auto map = xlf::map::initialize();
    map.center = xlf::map::point_type{50, 354};
    map.zoom = 4;
    map.finalize();

    auto nasa_layer = xlf::basemap({"NASAGIBS", "ModisTerraTrueColorCR"}, "2018-03-30");
    map.add_layer(nasa_layer);

    auto wms = xlf::wms_layer::initialize();
    wms.url = "https://demo.boundlessgeo.com/geoserver/ows?";
    wms.layers = "nasa:bluemarble";
    wms.name = "nasa:bluemarble";
    wms.finalize();
    map.add_layer(wms);

    map.add_control(xlf::layers_control());

    map

.. raw:: html

    <script type="application/vnd.jupyter.widget-view+json">
    {
        "model_id": "edc6adbca10a49b89effc9c6e1d0ebc7",
        "version_major": 2,
        "version_minor": 0
    }
    </script>
