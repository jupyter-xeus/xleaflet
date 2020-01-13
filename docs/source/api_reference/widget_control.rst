.. Copyright (c) 2018, Johan Mabille, Sylvain Corlay, Wolf Vollprecht and Martin Renou

   Distributed under the terms of the BSD 3-Clause License.

   The full license is in the file LICENSE, distributed with this software.

.. raw:: html
    :file: embed_widgets/widget_control.html

Widget control
==============

Example
-------

.. code::

    #include "xleaflet/xmap.hpp"
    #include "xleaflet/xbasemaps.hpp"
    #include "xwidgets/xslider.hpp"
    #include "xwidgets/xnumeral.hpp"
    #include "xwidgets/xlink.hpp"
    #include "xleaflet/xwidget_control.hpp"

    std::array<double, 2> center = {52.204793, 360.121558};

    auto map = xlf::map::initialize()
        .center(center)
        .zoom(4)
        .close_popup_on_click(false)
        .finalize();
    map.display();

    auto button1 = xw::slider<double>::initialize()
        .min(1.0)
        .max(9.0)
        .value(4.0)
        .orientation("horizontal")
        .finalize();

    auto popup2 = xlf::widget_control::initialize()
        .widget(button1)
        .position("bottomright")
        .finalize();
    map.add_control(popup2);

    xw::numeral<double> numeral;
    auto popup4 = xlf::widget_control::initialize()
        .widget(numeral)
        .position("topright")
        .finalize();
    map.add_control(popup4);


    auto l = xw::link(numeral, "value", map, "zoom");
    auto m = xw::link(button1, "value", map, "zoom");
    <div style ="height:30px;"> </div>

.. raw:: html

    <script type="application/vnd.jupyter.widget-view+json">
    {
        "model_id": "2bb1b0a9cf0a4070945929030bc25053",
        "version_major": 2,
        "version_minor": 0
    }
    </script>
    <div style ="height:30px;"> </div>

Attributes
----------

=====================   =========================    =====================   ===
Attribute               Type                         Default Value           Doc
=====================   =========================    =====================   ===
widget                  ``xwidget``                                          Content of the widget
position                ``string``                                           Position of the widget
=====================   =========================    =====================   ===
