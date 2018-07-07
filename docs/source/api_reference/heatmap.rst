Heatmap
=======

Example
-------

.. code::

    #include <random>
    #include <array>
    #include <vector>

    #include "xleaflet/xmap.hpp"
    #include "xleaflet/xheatmap.hpp"

    auto map = xlf::map_generator()
        .center({37.58, 261.65})
        .zoom(5)
        .finalize();

    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_real_distribution<double> rd_latitude(34.0, 40.0);
    std::uniform_real_distribution<double> rd_longitude(255.0, 265.0);
    std::uniform_real_distribution<double> rd_intensity(0.0, 1000.0);

    std::vector<std::array<double, 3>> heatmap_points;

    for (std::size_t i = 0; i < 100; ++i)
    {
        heatmap_points.push_back({rd_latitude(mt), rd_longitude(mt), rd_intensity(mt)});
    }

    auto heatmap = xlf::heatmap_generator()
        .locations(heatmap_points)
        .finalize();

    map.add_layer(heatmap);

    map

.. raw:: html

    <script type="application/vnd.jupyter.widget-view+json">
    {
        "version_major": 2,
        "version_minor": 0,
        "model_id": "f2ea9daf01fd4bf59c32ac98672caba0"
    }
    </script>

Attributes
----------

==============    ===================================================================    ====
Attribute         Default Value                                                          Doc
==============    ===================================================================    ====
locations         []                                                                     List of center locations
min_opacity       0.05                                                                   Minimum opacity the heat will start at
max_zoom          18                                                                     Zoom level where max intensity is reached
max               1.0                                                                    Maximum point intensity
radius            25.0                                                                   Radius of each "point" of the heatmap
blur              15.0                                                                   Amount of blur
gradient          {0.4: 'blue', 0.6: 'cyan', 0.7: 'lime', 0.8: 'yellow', 1.0: 'red'}     Color gradient config
==============    ===================================================================    ====
