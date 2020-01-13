.. Copyright (c) 2018, Johan Mabille, Sylvain Corlay, Wolf Vollprecht and Martin Renou

   Distributed under the terms of the BSD 3-Clause License.

   The full license is in the file LICENSE, distributed with this software.

.. raw:: html
    :file: embed_widgets/marker.html

Marker
======

Example
-------

.. code::

    #include "xleaflet/xmap.hpp"
    #include "xleaflet/xmarker.hpp"

    std::array<double, 2> center = {52.204793, 360.121558};

    auto map = xlf::map::initialize()
        .center(center)
        .zoom(15)
        .finalize();

    auto marker = xlf::marker::initialize()
        .location(center)
        .draggable(false)
        .finalize();
    map.add_layer(marker);

    map

.. raw:: html

    <script type="application/vnd.jupyter.widget-view+json">
    {
        "model_id": "218e8c0f43da4f0fa6616ee0ace2b2b6",
        "version_major": 2,
        "version_minor": 0
    }
    </script>

Attributes
----------

=====================   =========================    =====================   ===
Attribute               Type                         Default Value           Doc
=====================   =========================    =====================   ===
location                ``std::array<double, 2>``    {0.0, 0.0}
z_index_offset          ``int``                      0
draggable               ``bool``                     true                    Whether the marker is draggable with mouse/touch or not
keyboard                ``bool``                     true                    Whether the marker can be tabbed to with a keyboard and clicked by pressing enter
title                   ``std::string``              ""                      Text for the browser tooltip that appear on marker hover (no tooltip by default)
alt                     ``std::string``              ""                      Text for the `alt` attribute of the icon image (useful for accessibility)
rise_on_hover           ``bool``                     false                   The z-index offset used for the `rise_on_hover` feature
opacity                 ``float``                    1.0
visible                 ``bool``                     true
icon                    ``xlf::icon``                                        The icon for the marker
rotation_angle          ``int``                      0                       The rotation angle of the marker in degrees
rotation_origin         ``std::string``              ""                      The rotation origin of the marker
rise_offset             ``int``                      250                     The z-index offset used for the `rise_on_hover` feature
=====================   =========================    =====================   ===

Methods
-------

=====================   ===========    =====================================     ===
Method                  Return type    Arguments                                 Doc
=====================   ===========    =====================================     ===
on_move                 ``void``       ``std::function<void(xeus::xjson)>``      Adds a callback on move event
=====================   ===========    =====================================     ===
