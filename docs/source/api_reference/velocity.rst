.. raw:: html
    :file: embed_widgets/velocity.html

Velocity
========

Example
-------

.. code::

    #include <fstream>

    #include "nlohmann/json.hpp"

    #include "xleaflet/xmap.hpp"
    #include "xleaflet/xvelocity.hpp"

    auto map = xlf::map_generator()
        .center({0, 0})
        .zoom(1)
        .finalize();

    auto base_layer = xlf::basemap({"CartoDB", "DarkMatter"});
    map.add_layer(base_layer);

    std::ifstream file("velocity_data.json");
    nlohmann::json data;
    file >> data;

    auto velocity = xlf::velocity_generator()
        .data(data)
        .velocity_scale(0.01)
        .max_velocity(20)
        .display_options(R"({
            "velocityType": "Global Wind",
            "displayPosition": "bottomleft",
            "displayEmptyString": "No wind data"
        })")
        .finalize();

    map.add_layer(velocity);

    map

.. raw:: html

    <script type="application/vnd.jupyter.widget-view+json">
    {
        "version_major": 2,
        "version_minor": 0,
        "model_id": "af27d37e7ba1467aa55ad523f5f5032e"
    }
    </script>

Attributes
----------


======================    ===================================================================    ====
Attribute                 Default Value                                                          Doc
======================    ===================================================================    ====
data                      Null JSON objectdataset                                                Underlying dataset
units                     None                                                                   Units
display_values            True                                                                   Display velocity data on mouse hover
display_options           {}                                                                     Display options
min_velocity              0.0                                                                    Used to align color scale
max_velocity              10.0                                                                   Used to align color scale
velocity_scale            0.005                                                                  Modifier for particle animations
color_scale               Empty std::vector of html colors                                       Array of hex/rgb colors for user-specified color scale.
======================    ===================================================================    ====
