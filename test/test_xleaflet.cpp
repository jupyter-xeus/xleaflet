#include "gtest/gtest.h"
#include <fstream>
#include <iostream>
#include "xleaflet/xcircle.hpp"
#include "xleaflet/xcircle_marker.hpp"
#include "xleaflet/xdraw_control.hpp"
#include "xleaflet/xcontrol.hpp"
#include "xleaflet/xgeo_json.hpp"
#include "xleaflet/xheatmap.hpp"
#include "xleaflet/xicon.hpp"
#include "xleaflet/ximage_overlay.hpp"
#include "xleaflet/xlayer_group.hpp"
#include "xleaflet/xlayer.hpp"
#include "xleaflet/xlayers_control.hpp"
#include "xleaflet/xmap.hpp"
#include "xleaflet/xmarker_cluster.hpp"
#include "xleaflet/xmarker.hpp"
#include "xleaflet/xmeasure_control.hpp"
#include "xleaflet/xpath.hpp"
#include "xleaflet/xpolygon.hpp"
#include "xleaflet/xpolyline.hpp"
#include "xleaflet/xpopup.hpp"
#include "xleaflet/xrectangle.hpp"
#include "xleaflet/xsplit_map_control.hpp"
#include "xleaflet/xtile_layer.hpp"
#include "xleaflet/xui_layer.hpp"
#include "xleaflet/xvelocity.hpp"
#include "xleaflet/xvideo_overlay.hpp"
#include "xleaflet/xwms_layer.hpp"
#include "xleaflet/xfeature_group.hpp"
#include "xleaflet/test_xleaflet.hpp"

//MISSING WIDGET IN XLEAFLET
//chloropleth
//feature_group
//fullscreencotnrol
//localtilelayer

TEST(power, test)
{
    py::scoped_interpreter guard{};

    xlf::test_xleaflet<xlf::circle_marker>("Circle");
    xlf::test_xleaflet<xlf::draw_control>("DrawControl");
    xlf::test_xleaflet<xlf::circle_marker>("CircleMarker");
    xlf::test_xleaflet<xlf::control>("Control");
    xlf::test_xleaflet<xlf::geo_json>("GeoJSON");
    xlf::test_xleaflet<xlf::icon>("Icon");
    xlf::test_xleaflet<xlf::image_overlay>("ImageOverlay");
    xlf::test_xleaflet<xlf::layer>("Layer");
    xlf::test_xleaflet<xlf::layer_group>("LayerGroup");
    xlf::test_xleaflet<xlf::map>("Map");
    xlf::test_xleaflet<xlf::marker>("Marker");
    xlf::test_xleaflet<xlf::marker_cluster>("MarkerCluster");
    xlf::test_xleaflet<xlf::measure_control>("MeasureControl");
    xlf::test_xleaflet<xlf::path>("Path");
    xlf::test_xleaflet<xlf::popup>("Popup");
    xlf::test_xleaflet<xlf::raster_layer>("RasterLayer");
    xlf::test_xleaflet<xlf::tile_layer>("TileLayer");
    xlf::test_xleaflet<xlf::ui_layer>("UILayer");
    xlf::test_xleaflet<xlf::vector_layer>("VectorLayer");
    xlf::test_xleaflet<xlf::video_overlay>("VideoOverlay");
    xlf::test_xleaflet<xlf::wms_layer>("WMSLayer");
    xlf::test_xleaflet<xlf::rectangle>("Rectangle");
    xlf::test_xleaflet<xlf::polygon>("Polygon");
    xlf::test_xleaflet<xlf::polyline>("Polyline");
    xlf::test_xleaflet<xlf::split_map_control>("SplitMapControl");
    xlf::test_xleaflet<xlf::heatmap>("Heatmap");

}
