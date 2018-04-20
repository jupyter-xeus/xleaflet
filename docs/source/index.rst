.. Copyright (c) 2018, Johan Mabille and Sylvain Corlay, and Wolf Vollprecht

   Distributed under the terms of the BSD 3-Clause License.

   The full license is in the file LICENSE, distributed with this software.

.. image:: xleaflet.svg

The C++ backend for ipyleaflet.

Introduction
------------

``xleaflet`` is a C++ backend for the ipyleaflet_ maps visualization library.

``xleaflet`` and its dependencies require a modern C++ compiler supporting C++14. The following C++ compilers are supported:

- On Windows platforms, Visual C++ 2015 Update 2, or more recent
- On Unix platforms, gcc 4.9 or a recent version of Clang

Licensing
---------

We use a shared copyright model that enables all contributors to maintain the
copyright on their contributions.

This software is licensed under the BSD-3-Clause license. See the LICENSE file for details.

.. toctree::
   :caption: Installation
   :maxdepth: 2

   installation

.. toctree::
   :caption: Usage
   :maxdepth: 2

   usage

.. toctree::
   :caption: Api Reference
   :maxdepth: 2

   api_reference/map
   api_reference/tile_layer
   api_reference/marker
   api_reference/popup
   api_reference/wms_layer
   api_reference/image_video_overlay
   api_reference/polygon
   api_reference/rectangle
   api_reference/circle
   api_reference/circle_marker
   api_reference/marker_cluster
   api_reference/layer_group
   api_reference/geo_json
   api_reference/layers_control
   api_reference/split_map_control
   api_reference/draw_control

.. toctree::
   :caption: Developer Zone

   releasing

.. _ipyleaflet: https://github.com/jupyter-widgets/ipyleaflet.git
