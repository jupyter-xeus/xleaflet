.. raw:: html
    :file: embed_widgets/measure_control.html

Measure Control
===============

Example
-------

.. code::

	#include <iostream>
	#include <string>

	#include "xleaflet/xmap.hpp"
	#include "xleaflet/xmeasure_control.hpp"
	#include "xleaflet/xbasemaps.hpp"

	auto water_color = xlf::basemap({"Stamen", "Watercolor"});

	auto map = xlf::map_generator()
	    .layers({water_color})
	    .center({50, 354})
	    .zoom(5)
	    .finalize();

	auto measure_control = xlf::measure_control_generator()
	    .finalize();

	map.add_control(measure_control);

	map

.. raw:: html

	<script type="application/vnd.jupyter.widget-view+json">
	{
	    "version_major": 2,
	    "version_minor": 0,
	    "model_id": "1c722d8fa5cd448ea28daa77c09d8179"
	}
	</script>

Attributes
----------

=====================    ==========================================================================   ===
Attribute                Default Value                                                                Doc
=====================    ==========================================================================   ===
position                 "topright"                                                                   Position of the control on the Map, possible values are topleft, topright, bottomleft or bottomright
primary_length_unit      "feet"                                                                       Primary length unit, possible values are feet, meters, miles, kilometers or any user defined length unit
secondary_length_unit    None                                                                         Secondary length unit, possible values are None, feet, meters, miles, kilometers or any user defined length unit
primary_area_unit        "acres"                                                                      Primary area unit, possible values are acres, hectares, sqfeet, sqmeters, sqmiles or any user defined area unit
secondary_area_unit      None                                                                         Secondary area unit, possible values are None, acres, hectares, sqfeet, sqmeters, sqmiles or any user defined area unit
active_color             "#ABE67E"                                                                    Color of the currently drawn area
completed_color          "#C8F2BE"                                                                    Color of the completed areas
popup_options            {"className": "leaflet-measure-resultpopup", "autoPanPadding": [10, 10]}
capture_z_index          10000                                                                        Z-index of the marker used to capture measure clicks. Set this value higher than the z-index of all other map layers to disable click events on other layers while a measurement is active.
=====================    ==========================================================================   ===
