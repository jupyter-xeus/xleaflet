.. Copyright (c) 2018, Johan Mabille and Sylvain Corlay, and Wolf Vollprecht

   Distributed under the terms of the BSD 3-Clause License.

   The full license is in the file LICENSE, distributed with this software.

Map
===

.. code::

    #include "xleaflet/xmap.hpp"

    auto map = xlf::map_generator()
        .layers({layer1, layer2, layer3...})
        .controls({control1, control2, control3...})
        .center({52.204793, 360.121558}) // Initial geographic center of the map
        .zoom(15)                    // Initial map zoom level
        .max_zoom(18)
        .min_zoom(1)
        .dragging(true)              // Whether the map be draggable with mouse/touch or not
        .touch_zoom(true)            // Whether the map can be zoomed by touch-dragging with two fingers on mobile
        .scroll_wheel_zoom(false)    // Whether the map can be zoomed by using the mouse wheel
        .double_click_zoom(true)     // Whether the map can be zoomed in by double clicking on it and zoomed out by double clicking while holding shift
        .box_zoom(true)              // Whether the map can be zoomed to a rectangular area
                                     // specified by dragging the mouse while pressing the shift key
        .tap(true)                   // Enables mobile hacks for supporting instant taps
        .tap_tolerance(15)           // The max number of pixels a user can shift his finger during touch for it to be considered a valid tap
        .world_copy_jump(false)      // With this option enabled, the map tracks when you pan to another "copy" of the world and seamlessly jumps to
                                     // the original one so that all overlays like markers and vector layers are still visible
        .close_popup_on_click(true)  // Set it to false if you don't want popups to close when user clicks the map
        .bounce_at_zoom_limits(true) // Set it to false if you don't want the map to zoom beyond min/max zoom and then bounce back when pinch-zooming
        .keyboard(true)              // Makes the map focusable and allows users to navigate the map with keyboard arrows and +/- keys
        .keyboard_pan_offset(80)
        .keyboard_zoom_offset(1)
        .inertia(true)               // If enabled, panning of the map will have an inertia effect
        .inertia_deceleration(3000)  // The rate with which the inertial movement slows down, in pixels/second²
        .inertia_max_speed(1500)     // Max speed of the inertial movement, in pixels/second
        .zoom_control(true)
        .attribution_control(true)
        .zoom_animation_threshold(4)
        .finalize();

    map.display();

One could want to react on special map events like ``mousemove``, this can be achieved by using the ``on_interaction`` method of map:

.. code::

    #include <iostream>

    #include "xleaflet/xmap.hpp"

    void print_mouse_position(xeus::xjson event)
    {
        if (event["type"] == "mousemove")
        {
            std::cout << "Mouse position: " << event["coordinates"].dump() << std::endl;
        }

        if (event["type"] == "mouseout")
        {
            std::cout << "Mouse out" << std::endl;;
        }
    }

    xlf::map map;

    map.on_interaction(print_mouse_position);
    map.display();

The list of possible events accessible from ``event["type"]`` is the following:
    - ``click``
    - ``dblclick``
    - ``mousedown``
    - ``mouseup``
    - ``mouseover``
    - ``mouseout``
    - ``mousemove``
    - ``contextmenu``
    - ``preclick``

The map widget works with a list of layers. Layers are instances of ``tile_layer``, ``marker``, ``popup``, ``wms_layer``, ``image_overlay``,
``video_overlay``, ``polygon``, ``rectangle``, ``circle_marker``, ``circle``, ``marker_cluster``, ``layer_group`` or ``geo_json``.

.. code::

    #include "xleaflet/xmap.hpp"

    xlf::map map;

    map.add_layer(marker);
    map.add_layer(circle);
    map.add_layer(layer_group);

    map.remove_layer(circle);

    map.clear_layers();

It is also possible to have a list of controls on the map. Controls are instances of ``layers_control``, ``split_map_control`` or ``draw_control``.

.. code::

    #include "xleaflet/xmap.hpp"

    xlf::map map;

    map.add_control(control1);
    map.add_control(control2);

    map.remove_control(control1);

    map.clear_controls();

Tile layer
==========

Creating a ``tile_layer`` is straightforward, a list of basic tile layers is provided.
This list of layers can be accessed using the ``basemaps`` function:

.. code::

    #include <iostream>

    #include "xleaflet/xbasemaps.hpp"

    std::cout << xlf::basemaps().dump(6) << std::endl;

A ``tile_layer`` instance can be created using the ``basemap`` function, specifying the wanted map
(e.g. ``{"CartoDB", "DarkMatter"}``, ``{"Strava", "Winter"}``, ``{"NASAGIBS", "ModisTerraTrueColorCR"}``, ...):

.. code::

    #include "xleaflet/xmap.hpp"
    #include "xleaflet/xbasemaps.hpp"

    auto map = xlf::map_generator()
        .center({52.204793, 360.121558})
        .zoom(9)
        .finalize();
    map.display();

    auto dark_matter_layer = xlf::basemap({"CartoDB", "DarkMatter"});
    map.add_layer(dark_matter_layer);

Sometimes one could want to specify the date of the given images, for instance with NASA images:

.. code::

    auto nasa_layer = xlf::basemap({"NASAGIBS", "ModisTerraTrueColorCR"}, "2018-04-08");
    map.add_layer(nasa_layer);

It is also possible to change the opacity of the ``tile_layer``:

.. code::

    nasa_layer.opacity = 0.5;

And make it visible or not:

.. code::

    nasa_layer.visible = false;

If the user knows the url to his map, he can create a ``tile_layer`` with the following:

.. code::

    #include "xleaflet/xtile_layer.hpp"

    auto nasa_layer = xlf::tile_layer_generator()
        .url("https://map1.vis.earthdata.nasa.gov/wmts-webmerc/MODIS_Terra_CorrectedReflectance_TrueColor/default/2018-02-25/GoogleMapsCompatible_Level9/{z}/{y}/{x}.jpg")
        .attribution("Imagery provided by services from the Global Imagery Browse Services (GIBS), operated by the NASA/GSFC/Earth Science Data and Information System (<a href='https://earthdata.nasa.gov'>ESDIS</a>) with funding provided by NASA/HQ.")
        .name("NASAGIBS.ModisTerraTrueColorCR")
        .max_zoom(9)
        .opacity(0.5)
        .visible(true)
        .finalize();

Marker
======

.. code::

    #include "xleaflet/xmarker.hpp"

    auto marker = xlf::marker_generator()
        .location({52.204793, 360.121558})
        .draggable(true)     // Whether the marker is draggable with mouse/touch or not
        .keyboard(true)      // Whether the marker can be tabbed to with a keyboard and clicked by pressing enter
        .title("My marker")  // Text for the browser tooltip that appear on marker hover (no tooltip by default)
        .alt("marker")       // Text for the `alt` attribute of the icon image (useful for accessibility)
        .rise_on_hover(true) // If `true`, the marker will get on top of others when you hover the mouse over it
        .rise_offset(250)    // The z-index offset used for the `rise_on_hover` feature
        .opacity(0.8)
        .visible(true)
        .z_index_offset(0)   // By default, marker images z_index is set automatically based on its latitude.
                             // Use this option if you want to put the marker on top of all others (or below),
                             // specifying a high value like `1000` (or high negative value, respectively)
        .finalize();

If the marker is draggable, it can be useful to have an ``on_move`` event callback:

.. code::

    void on_move_callback(xeus::xjson event)
    {
        float latitude = event.find("location").value().at(0);
        float longitude = event.find("location").value().at(1);

        // Do something useful with latitude and longitude
    }

    marker.on_move(on_move_callback);

Popup
=====

.. code::

    #include "xleaflet/xpopup.hpp"

    auto popup = xlf::popup_generator()
        .location({52.204793, 360.121558})
        .max_width(300)            // Max width of the popup, in pixels
        .min_width(50)             // Min width of the popup, in pixels
        .max_height(50)            // If set, creates a scrollable container of the given height inside a popup if its content exceeds it
        .auto_pan(true)            // Set it to `false` if you don't want the map to do panning animation to fit the opened popup
        .auto_pan_padding({5, 5})
        .keep_in_view(true)        // Set it to `true` if you want to prevent users from panning the popup off of the screen while it is open
        .close_button(true)        // Controls the presence of a close button in the popup
        .auto_close(true)          // Set it to `false` if you want to override the default behavior of the popup closing when another popup is opened
        .close_on_escape_key(true) // Set it to `false` if you want to override the default behavior of the ESC key for closing of the popup
        .class_name("")            // A custom CSS class name to assign to the popup
        .finalize();

There are two ways to create a ``popup``, the first one is to create a popup with a location and add it to the map.
The second one is to use the ``popup`` attribute of a layer, for example you could create a widget instance like a
button and bind it to the popup attribute of a marker:

.. code::

    #include "xwidgets/xbutton.hpp"

    #include "xleaflet/xmarker.hpp"
    #include "xleaflet/xpopup.hpp"

    xw::button button;
    button.description = "button";
    button.button_style = "success";

    xlf::marker marker;
    marker.popup = button;

Doing this will create a popup which will appear when clicking on the marker.

WMS layer
=========

.. code::

    #include "xleaflet/xwms_layer.hpp"

    auto wms_layer = xlf::wms_layer_generator()
        .url("https://demo.boundlessgeo.com/geoserver/ows?")
        .layers("nasa:bluemarble") // Comma-separated list of WMS layers to show
        .service("WMS")
        .request("GetMap")
        .styles("")                // Comma-separated list of WMS styles
        .format("image/jpeg")      // WMS image format (use `'image/png'` for layers with transparency)
        .transparent(false)        // If `true`, the WMS service will return images with transparency
        .version("1.1.1")          // Version of the WMS service to use
        .finalize();

Image overlay and Video overlay
===============================

.. code::

    #include "xleaflet/xvideo_overlay.hpp"

    auto video_overlay = xlf::video_overlay_generator()
        .url("https://www.mapbox.com/bites/00188/patricia_nasa.webm")
        .bounds({{{13, -130}, {32, -100}}}) // SW and NE corners of the image
        .attribution("mapbox")
        .finalize();

Polygon
=======

.. code::

    #include "xleaflet/xpolygon.hpp"

    auto polygon = xlf::polygon_generator()
        .locations({{{ , }, { , }, { , }}}) // Array of LatLng points
        .stroke(true)           // Whether to draw stroke along the path. Set it to `false` to disable borders on polygons or circles
        .color("#0033FF")
        .opacity(1.0)
        .weight(5)              // Stroke width in pixels
        .fill(true)
        .fill_color("#0033FF")
        .fill_opacity(0.2)
        .class_name("")
        .finalize();

Rectangle
=========

.. code::

    #include "xleaflet/xrectangle.hpp"

    auto rectangle = xlf::rectangle_generator()
        .bounds({{{50, 354}, {55, 360}}}) // SW and NE location tuples
        .stroke(true)                     // Whether to draw stroke along the path. Set it to `false` to disable borders on polygons or circles
        .color("#0033FF")
        .opacity(1.0)
        .weight(5)                        // Stroke width in pixels
        .fill(true)
        .fill_color("#0033FF")
        .fill_opacity(0.2)
        .class_name("")
        .smooth_factor(1.0)               // How much to simplify the polygon on each zoom level. More means
		                                  // better performance and smoother look, and less means more accurate representation
        .no_clip(false)                   // Disable polygon clipping

        .finalize();

Circle marker
=============

.. code::

    #include "xleaflet/xcircle_marker.hpp"

    auto circle_marker = xlf::circle_marker_generator()
        .location({0.0, 0.0})
        .radius(10)           // Radius of circle in pixels
        .stroke(true)         // Whether to draw stroke along the path. Set it to `false` to disable borders on polygons or circles
        .color("#0033FF")
        .opacity(1.0)
        .weight(5)            // Stroke width in pixels
        .fill(true)
        .fill_color("#0033FF")
        .fill_opacity(0.2)
        .class_name("")
        .finalize();

Circle
======

.. code::

    #include "xleaflet/xcircle.hpp"

    auto circle = xlf::circle_generator()
        .location({0.0, 0.0})
        .radius(10)           // Radius of circle in meters
        .stroke(true)         // Whether to draw stroke along the path. Set it to `false` to disable borders on polygons or circles
        .color("#0033FF")
        .opacity(1.0)
        .weight(5)            // Stroke width in pixels
        .fill(true)
        .fill_color("#0033FF")
        .fill_opacity(0.2)
        .class_name("")
        .finalize();

Marker cluster
==============

.. code::

    #include "xleaflet/xmarker_cluster.hpp"

    auto marker_cluster = xlf::marker_cluster_generator()
        .markers({marker1, marker2, marker3 ...})
        .finalize();

Layer group
===========

.. code::

    #include "xleaflet/xlayer_group.hpp"

    auto layer_group = xlf::layer_group_generator()
        .layers({layer1, layer2, layer3 ...})
        .finalize();

It is possible to add new layers or remove layers using the following:

.. code::

    xlf::layer_group layer_group;

    layer_group.add_layer(marker);
    layer_group.add_layer(circle);
    layer_group.add_layer(video_overlay);

    // The layer group now contains {marker, circle, video_overlay}

    layer_group.remove_layer(circle);

    // The layer group now contains {marker, video_overlay}

    layer_group.clear_layers();

    // The layer group is now empty

Geo json
========

.. code::

    #include "xleaflet/xgeo_json.hpp"

    auto geo_json = xlf::geo_json_generator()
        .data(...)
        .style(...)
        .hover_style(...)
        .finalize();

It is possible to create a ``geo_json`` from a json file:

.. code::

    #include <fstream>
    #include "xleaflet/xgeo_json.hpp"

    std::ifstream file("geo.json");
    xeus::xjson geo_data;
    file >> geo_data;

    auto geo_json = xlf::geo_json_generator()
        .data(geo_data)
        .finalize();

The ``geo_json`` class comes with two events methods:

.. code::

    #include <iostream>

    void print_event_callback(xeus::xjson event)
    {
        std::cout << event.dump(4) << std::endl;
    }

    geo_json.on_hover(print_event_callback);
    geo_json.on_click(print_event_callback);

Layers control
==============

The ``layers_control`` allows one to display a selector on the top right of the map in order to select which tile layer to display on the map.

.. code::

    #include "xleaflet/xlayers_control.hpp"

    xlf::layers_control layers_control;

    map.add_control(layers_control);

Split map control
=================

The ``split_map_control`` allows one to display two tile layers at the same time on the map with a slider in the middle.

.. code::

    #include "xleaflet/xsplit_map_control.hpp"

    auto split_map_control = xlf::split_map_control_generator()
        .left_layer(tile_layer1)
        .right_layer(tile_layer2)
        .finalize();

    map.add_control(split_map_control);

Draw control
============

The ``draw_control`` allows one to draw shapes on the map such as ``rectangle`` ``circle`` or lines.

.. code::

    #include "xleaflet/xdraw_control.hpp"

    xlf::draw_control draw_control;

    map.add_control(draw_control);


.. _xproperty: https://github.com/QuantStack/xproperty
.. _documentation: https://github.com/QuantStack/xwidgets/blob/master/docs/source/usage.rst
.. _xwidgets: https://github.com/QuantStack/xwidgets
.. _leaflet: http://leafletjs.com/
.. _ipyleaflet: https://github.com/jupyter-widgets/ipyleaflet.git
