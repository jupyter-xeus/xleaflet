.. Copyright (c) 2018, Johan Mabille, Sylvain Corlay, Wolf Vollprecht and Martin Renou

   Distributed under the terms of the BSD 3-Clause License.

   The full license is in the file LICENSE, distributed with this software.


.. raw:: html
   :file: embed_widgets/fullscreen_control.html


Fullscreen Control
==================

The ``fullscreen_control`` allows one to display a selector on the top left of the map in order to display the map in fullscreen.

.. code::

    #include "xleaflet/xmap.hpp"
    #include "xleaflet/xbasemaps.hpp"
    #include "xleaflet/xtile_layer.hpp"
    #include "xleaflet/xwms_layer.hpp"
    #include "xleaflet/xlayers_control.hpp"
    #include "xleaflet/xfullscreen_control.hpp"

    auto map = xlf::map_generator()
    .center({51.64, -76.52})
    .zoom(5)
    .finalize();

    map.add_control(xlf::fullscreen_control());

    map

.. raw:: html

    <script type="application/vnd.jupyter.widget-view+json">
    {
        "version_major": 2,
        "version_minor": 0,
        "model_id": "9c4473d2196f432eb47be766b13916e6"
    }
    </script>
    <div style ="height:30px;"> </div>
