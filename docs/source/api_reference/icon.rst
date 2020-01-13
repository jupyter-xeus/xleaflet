.. Copyright (c) 2018, Johan Mabille, Sylvain Corlay, Wolf Vollprecht and Martin Renou

   Distributed under the terms of the BSD 3-Clause License.

   The full license is in the file LICENSE, distributed with this software.

.. raw:: html
    :file: embed_widgets/icon.html

Icon
====

Example
-------

.. code::

    #include <array>

    #include "xleaflet/xmap.hpp"
    #include "xleaflet/xmarker.hpp"
    #include "xleaflet/xicon.hpp"

    using size_type = std::array<int, 2>;

    std::array<double, 2> center({52.204793, 360.121558});

    auto map = xlf::map::initialize()
        .center(center)
        .zoom(10)
        .finalize();

    auto icon = xlf::icon::initialize()
        .icon_url("https://leafletjs.com/examples/custom-icons/leaf-red.png")
        .icon_size(size_type({38, 95}))
        .icon_anchor(size_type({22, 94}))
        .finalize();

    auto marker = xlf::marker::initialize()
        .location(center)
        .icon(icon)
        .rotation_angle(0)
        .rotation_origin("22px 94px")
        .finalize();

    map.add_layer(marker);

    map

.. raw:: html

    <script type="application/vnd.jupyter.widget-view+json">
    {
        "model_id": "b98f79b010574f8d96fc5b76ed78a844",
        "version_major": 2,
        "version_minor": 0
    }
    </script>

Attributes
----------

=====================   =========================    =====================   ===
Attribute               Type                         Default Value           Doc
=====================   =========================    =====================   ===
icon_url                ``std::string``              ""                      url for icon image
shadow_url              ``std::string``              ""                      url for icon shadow image
icon_size               ``std::array<int, 2>``       {10, 10}                size of the icon, in pixels
shadow_size             ``std::array<int, 2>``       {10, 10}                size of the icon shadow, in pixels
icon_anchor             ``std::array<int, 2>``       {0, 0}                  anchor point for the icon
shadow_anchor           ``std::array<int, 2>``       {0, 0}                  anchor point for the icon shadow
popup_anchor            ``std::array<int, 2>``       {0, 0}                  anchor point for the popup
=====================   =========================    =====================   ===
