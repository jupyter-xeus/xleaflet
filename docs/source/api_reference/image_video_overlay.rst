.. Copyright (c) 2018, Johan Mabille, Sylvain Corlay, Wolf Vollprecht and Martin Renou

   Distributed under the terms of the BSD 3-Clause License.

   The full license is in the file LICENSE, distributed with this software.

.. raw:: html
    :file: embed_widgets/image_video_overlay.html

Image overlay and Video overlay
===============================

Example
-------

.. code::

    #include "xleaflet/xmap.hpp"
    #include "xleaflet/xvideo_overlay.hpp"

    auto map = xlf::map_generator()
        .center({25, -115})
        .zoom(4)
        .finalize();

    auto video = xlf::video_overlay_generator()
        .url("https://www.mapbox.com/bites/00188/patricia_nasa.webm")
        .bounds({{{13, -130}, {32, -100}}})
        .finalize();

    map.add_layer(video);
    map

.. raw:: html

    <script type="application/vnd.jupyter.widget-view+json">
    {
    "model_id": "87d4292e2f214b97913a846cd527e8e5",
    "version_major": 2,
    "version_minor": 0
    }
    </script>

Attributes
----------

=====================   =========================================    ========================   ===
Attribute               Type                                         Default Value              Doc
=====================   =========================================    ========================   ===
url                     ``std::string``                              ""                         Url to the footage
bounds                  ``std::array<std::array<double, 2>, 2>``     {{0.0, 0.0}, {0.0, 0.0}}   SW and NE corners of the image
=====================   =========================================    ========================   ===
