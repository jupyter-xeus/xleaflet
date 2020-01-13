.. Copyright (c) 2018, Johan Mabille, Sylvain Corlay, Wolf Vollprecht and Martin Renou

   Distributed under the terms of the BSD 3-Clause License.

   The full license is in the file LICENSE, distributed with this software.

.. raw:: html
    :file: embed_widgets/split_map_control.html

Split Map Control
=================

Example
-------

.. code::

    #include "xleaflet/xmap.hpp"
    #include "xleaflet/xbasemaps.hpp"
    #include "xleaflet/xsplit_map_control.hpp"

    auto map = xlf::map::initialize()
        .center({42.6824, 365.581})
        .zoom(5)
        .finalize();

    auto right_layer = xlf::basemap({"NASAGIBS", "ModisTerraTrueColorCR"}, "2017-11-11");
    auto left_layer = xlf::basemap({"NASAGIBS", "ModisAquaBands721CR"}, "2017-11-11");

    auto control = xlf::split_map_control::initialize()
        .left_layer(left_layer)
        .right_layer(right_layer)
        .finalize();
    map.add_control(control);

    map

.. raw:: html

    <script type="application/vnd.jupyter.widget-view+json">
    {
    "model_id": "09e886eadb98445bb73a4ae67ea618b4",
    "version_major": 2,
    "version_minor": 0
    }
    </script>

Attributes
----------

=====================   ========================================    ================   ===
Attribute               Type                                        Default Value      Doc
=====================   ========================================    ================   ===
left_layer              ``xlf::layer``                                                 Left layer
right_layer             ``xlf::layer``                                                 Right layer
=====================   ========================================    ================   ===
