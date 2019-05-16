.. Copyright (c) 2018, Johan Mabille, Sylvain Corlay, Wolf Vollprecht and Martin Renou

   Distributed under the terms of the BSD 3-Clause License.

   The full license is in the file LICENSE, distributed with this software.

.. raw:: html
   :file: embed_widgets/draw_control.html

Draw Control
============

The ``draw_control`` allows one to draw shapes on the map such as ``rectangle`` ``circle`` or lines.

.. code::

    #include "xleaflet/xmap.hpp"
    #include "xleaflet/xdraw_control.hpp"
    #include "xleaflet/xbasemaps.hpp"

    auto water_color = xlf::basemap({"Stamen", "Watercolor"});

    auto map = xlf::map_generator()
        .layers({water_color})
        .center({50, 354})
        .zoom(5)
        .finalize();

        xeus::xjson polyline_options = {
        {"shapeOptions", {
            {"color", "#6bc2e5"},
            {"weight", 8},
            {"opacity", 1.0}
        }}
    };

    // Set some options for draw control
    xeus::xjson polygon_options = {
        {"shapeOptions", {
            {"fillColor", "#6be5c3"},
            {"color", "#6be5c3"},
            {"fillOpacity", 1.0}
        }},
        {"drawError", {
            {"color", "#dd253b"},
            {"message", "Oups!"}
        }},
        {"allowIntersection", false}
    };

    xeus::xjson circle_options = {
        {"shapeOptions", {
            {"fillColor", "#efed69"},
            {"fillOpacity", 1.0},
            {"color", "#efed69"}
        }}
    };

    xeus::xjson rectangle_options = {
        {"shapeOptions", {
            {"fillColor", "#fca45d"},
            {"fillOpacity", 1.0},
            {"color", "#fca45d"}
        }}
    };

    auto draw_control = xlf::draw_control_generator()
        .polyline(polyline_options)
        .polygon(polygon_options)
        .circle(circle_options)
        .rectangle(rectangle_options)
        .finalize();
    map.add_control(draw_control);

    map

.. raw:: html

    <script type="application/vnd.jupyter.widget-view+json">
    {
    "model_id": "1cc6a5ba697b40e99ebecebc0737c901",
    "version_major": 2,
    "version_minor": 0
    }
    </script>
