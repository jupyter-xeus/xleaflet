.. Copyright (c) 2018, Johan Mabille, Sylvain Corlay, Wolf Vollprecht and Martin Renou

   Distributed under the terms of the BSD 3-Clause License.

   The full license is in the file LICENSE, distributed with this software.

.. raw:: html
    :file: embed_widgets/popup.html

Popup
=====

Example
-------

.. code::

    #include "xwidgets/xhtml.hpp"

    #include "xleaflet/xmap.hpp"
    #include "xleaflet/xbasemaps.hpp"
    #include "xleaflet/xmarker.hpp"
    #include "xleaflet/xpopup.hpp"

    std::array<double, 2> center = {52.204793, 360.121558};

    auto map = xlf::map_generator()
        .center(center)
        .zoom(9)
        .close_popup_on_click(false)
        .finalize();
    map.display();

    auto marker = xlf::marker_generator()
        .location({52.1, 359.9})
        .finalize();
    map.add_layer(marker);

    xw::html message1, message2;
    message1.value = "Try clicking the marker!";
    message2.value = "Hello <b>World</b>";
    message2.placeholder = "Some HTML";
    message2.description = "Some HTML";

    // Popup with a given location on the map:
    auto popup = xlf::popup_generator()
        .location(center)
        .child(message1)
        .close_button(false)
        .auto_close(false)
        .close_on_escape_key(false)
        .finalize();
    map.add_layer(popup);

    // Popup associated to a layer
    marker.popup = message2;

.. raw:: html

    <script type="application/vnd.jupyter.widget-view+json">
    {
    "model_id": "4786c6b0f48743f18ace18fa903ff2ed",
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
child                   ``xwidget``                                          Content of the popup
max_width               ``int``                      300                     Max width of the popup, in pixels
min_width               ``int``                      50                      Min width of the popup, in pixels
max_height              ``int``                                              If set, creates a scrollable container of the given height inside a popup if its content exceeds it
auto_pan                ``bool``                     true                    Set it to `false` if you don't want the map to do panning animation to fit the opened popup
auto_pan_padding        ``std::array<double, 2>``    {5, 5}
keep_in_view            ``bool``                     false                   Set it to `true` if you want to prevent users from panning the popup off of the screen while it is open
close_button            ``bool``                     true                    Controls the presence of a close button in the popup
close_on_escape_key     ``bool``                     true                    Set it to `false` if you want to override the default behavior of the ESC key for closing of the popup
class_name              ``std::string``              ""                      A custom CSS class name to assign to the popup
=====================   =========================    =====================   ===
