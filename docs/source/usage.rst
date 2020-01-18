.. Copyright (c) 2017, Johan Mabille and Sylvain Corlay

   Distributed under the terms of the BSD 3-Clause License.

   The full license is in the file LICENSE, distributed with this software.

Introduction
============

``xleaflet`` is the C++ backend for the leaflet_ maps visualization library. The
Python reference implementation is available in the ipyleaflet_ project.

``xleaflet`` depends on xwidgets_, each object that you can create in ``xleaflet``
is an xwidget instance which is synchronized with one or more views on the frontend.
See the ``xwidgets`` documentation_ for the usage of widgets.

Basic usage
===========

Default map
-----------

The default map can be displayed using Jupyter's display framework.

.. code::

    xlf::map map;
    map.display();

Changing widget attributes can be done from the model:

.. code::

    map.zoom = 15;

    // latitude 52.204793, longitude 360.121558
    map.center = std::array<double, 2>({52.204793, 360.121558});

Or by interacting directly with the view.

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

Generator classes
=================

Widgets such as ``map`` may have a large number of attributes that can be set by the user, such as ``center``, ``zoom``, ``min_zoom``, ``max_zoom``, ``scroll_wheel_zoom``, ``bounce_at_zoom_limits``, ``inertia``.

Providing a constructor for ``map`` with a large number of such attributes would make the use of ``xleaflet`` very cumbersome, because users would need to know all the positional arguments to modify only one value. Instead, we mimick a keyword argument initialization with a method-chaining mechanism.

.. code::

    #include "xleaflet/xmap.hpp"

    auto map = xlf::map::initialize()
        .center({52.204793, 360.121558})
        .zoom(15)
        .scroll_wheel_zoom(true)
        .inertia(false)
        .finalize();

Special Events
==============

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

XProperty Events
================

``xleaflet`` relies on the xproperty_ library, so that one could use the ``XOBSERVE`` function to react on model changes:

.. code::

    #include <iostream>

    #include "xleaflet/xmap.hpp"

    void print_lat_lng(xlf::map& map)
    {
        std::string lat = std::to_string(map.center().front());
        std::string lng = std::to_string(map.center().back());

        std::cout << "latitude: " << lat << ", longitude: " << lng << std::endl;
    }

    xlf::map map;

    XOBSERVE(map, center, print_lat_lng);
    map.display();


.. _xproperty: https://github.com/jupyter-xeus/xproperty
.. _documentation: https://github.com/jupyter-xeus/xwidgets/blob/master/docs/source/usage.rst
.. _xwidgets: https://github.com/jupyter-xeus/xwidgets
.. _leaflet: http://leafletjs.com/
.. _ipyleaflet: https://github.com/jupyter-widgets/ipyleaflet.git
