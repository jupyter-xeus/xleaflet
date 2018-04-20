.. Copyright (c) 2018, Johan Mabille, Sylvain Corlay, Wolf Vollprecht and Martin Renou

   Distributed under the terms of the BSD 3-Clause License.

   The full license is in the file LICENSE, distributed with this software.

.. raw:: html
    :file: embed_widgets/map.html

Map
===

Example
-------

.. code::

    #include "xleaflet/xmap.hpp"
    #include "xleaflet/xbasemaps.hpp"

    auto map = xlf::map_generator()
        .layers({xlf::basemap({"NASAGIBS", "ModisTerraTrueColorCR"}, "2017-04-08")})
        .center({52.204793, 360.121558})
        .zoom(4)
        .finalize();
    map

.. raw:: html

    <script type="application/vnd.jupyter.widget-view+json">
    {
    "model_id": "ab2369332a024dda83800361d0a1343e",
    "version_major": 2,
    "version_minor": 0
    }
    </script>

Attributes
----------

========================   =============================    ===============                     ===
Attribute                  Type                             Default Value                       Doc
========================   =============================    ===============                     ===
layers                     ``std::vector<xlf::layer>``      {default_layer}                     Vector of layers
controls                   ``std::vector<xlf::control>``    {}                                  Vector of controls
center                     ``std::array<double, 2>``        {0.0, 0.0}                          Initial geographic center of the map
zoom                       ``int``                          12                                  Initial map zoom level
max_zoom                   ``int``                          18
min_zoom                   ``int``                          1
dragging                   ``bool``                         true                                Whether the map be draggable with mouse/touch or not
touch_zoom                 ``bool``                         true                                Whether the map can be zoomed by touch-dragging with two fingers on mobile
scroll_wheel_zoom          ``bool``                         false                               Whether the map can be zoomed by using the mouse wheel
double_click_zoom          ``bool``                         true                                Whether the map can be zoomed in by double clicking on it and zoomed out by double clicking while holding shift
box_zoom                   ``bool``                         true                                Whether the map can be zoomed to a rectangular area specified by dragging the mouse while pressing the shift key
tap                        ``bool``                         true                                Enables mobile hacks for supporting instant taps
tap_tolerance              ``int``                          15                                  The max number of pixels a user can shift his finger during touch for it to be considered a valid tap
world_copy_jump            ``bool``                         false                               With this option enabled, the map tracks when you pan to another "copy" of the world and seamlessly jumps to
close_popup_on_click       ``bool``                         true                                Set it to false if you don't want popups to close when user clicks the map
bounce_at_zoom_limits      ``bool``                         true                                Set it to false if you don't want the map to zoom beyond min/max zoom and then bounce back when pinch-zooming
keyboard                   ``bool``                         true                                Makes the map focusable and allows users to navigate the map with keyboard arrows and +/- keys
keyboard_pan_offset        ``int``                          80
keyboard_zoom_offset       ``int``                          1
inertia                    ``bool``                         true                                If enabled, panning of the map will have an inertia effect
inertia_deceleration       ``int``                          3000                                The rate with which the inertial movement slows down, in pixels/second²
inertia_max_speed          ``int``                          1500                                Max speed of the inertial movement, in pixels/second
zoom_control               ``bool``                         true
attribution_control        ``bool``                         true
zoom_animation_threshold   ``int``                          4
========================   =============================    ===============                     ===

Methods
-------

=====================   ===========    =====================================     ===
Method                  Return type    Arguments                                 Doc
=====================   ===========    =====================================     ===
add_layer               ``void``       ``xlf::layer``                            Add a new layer to the map
remove_layer            ``void``       ``xlf::layer``                            Remove a layer from the map
clear_layers            ``void``                                                 Remove all layers from the map
add_control             ``void``       ``xlf::control``                          Add a new control to the map
remove_control          ``void``       ``xlf::control``                          Remove a control from the map
clear_controls          ``void``                                                 Remove all controls from the map
on_interaction          ``void``       ``std::function<void(xeus::xjson)>``      Add a callback on interaction
=====================   ===========    =====================================     ===
