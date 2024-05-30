/***************************************************************************
* Copyright (c) 2016, Johan Mabille and Sylvain Corlay                     *
*                                                                          *
* Distributed under the terms of the BSD 3-Clause License.                 *
*                                                                          *
* The full license is in the file LICENSE, distributed with this software. *
****************************************************************************/

#include <doctest/doctest.h>

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

#include "check_attributes.hpp"

// MISSING WIDGETS IN XLEAFLET
// chloropleth
// feature_group
// fullscreencotnrol
// localtilelayer

TEST_SUITE("attributes")
{
    TEST_CASE("Circle")
    {
        check_attributes<xlf::circle_marker>("ipyleaflet", "Circle");
    }

    TEST_CASE("DrawControl")
    {
        check_attributes<xlf::draw_control>("ipyleaflet", "DrawControl");
    }

    TEST_CASE("CircleMarker")
    {
        check_attributes<xlf::circle_marker>("ipyleaflet", "CircleMarker");
    }

    TEST_CASE("Control")
    {
        check_attributes<xlf::control>("ipyleaflet", "Control");
    }

    TEST_CASE("GeoJSON")
    {
        check_attributes<xlf::geo_json>("ipyleaflet", "GeoJSON");
    }

    TEST_CASE("Icon")
    {
        check_attributes<xlf::icon>("ipyleaflet", "Icon");
    }

    TEST_CASE("ImageOverlay")
    {
        check_attributes<xlf::image_overlay>("ipyleaflet", "ImageOverlay");
    }

    TEST_CASE("Layer")
    {
        check_attributes<xlf::layer>("ipyleaflet", "Layer");
    }

    TEST_CASE("LayerGroup")
    {
        check_attributes<xlf::layer_group>("ipyleaflet", "LayerGroup");
    }

    // TODO: enable and fix this
    /*TEST_CASE("Map")
    {
        check_attributes<xlf::map>("ipyleaflet", "Map");
    }*/

    TEST_CASE("Marker")
    {
        check_attributes<xlf::marker>("ipyleaflet", "Marker");
    }

    TEST_CASE("MarkerCluster")
    {
        check_attributes<xlf::marker_cluster>("ipyleaflet", "MarkerCluster");
    }

    TEST_CASE("MeasureControl")
    {
        check_attributes<xlf::measure_control>("ipyleaflet", "MeasureControl");
    }

    TEST_CASE("Path")
    {
        check_attributes<xlf::path>("ipyleaflet", "Path");
    }

    TEST_CASE("Popup")
    {
        check_attributes<xlf::popup>("ipyleaflet", "Popup");
    }

    TEST_CASE("RasterLayer")
    {
        check_attributes<xlf::raster_layer>("ipyleaflet", "RasterLayer");
    }

    TEST_CASE("TileLayer")
    {
        check_attributes<xlf::tile_layer>("ipyleaflet", "TileLayer");
    }

    TEST_CASE("UILayer")
    {
        check_attributes<xlf::ui_layer>("ipyleaflet", "UILayer");
    }

    TEST_CASE("VectorLayer")
    {
        check_attributes<xlf::vector_layer>("ipyleaflet", "VectorLayer");
    }

    TEST_CASE("VideoOverlay")
    {
        check_attributes<xlf::video_overlay>("ipyleaflet", "VideoOverlay");
    }

    TEST_CASE("WMSLayer")
    {
        check_attributes<xlf::wms_layer>("ipyleaflet", "WMSLayer");
    }

    TEST_CASE("Rectangle")
    {
        check_attributes<xlf::rectangle>("ipyleaflet", "Rectangle");
    }

    TEST_CASE("Polygon")
    {
        check_attributes<xlf::polygon>("ipyleaflet", "Polygon");
    }

    TEST_CASE("Polyline")
    {
        check_attributes<xlf::polyline>("ipyleaflet", "Polyline");
    }

    TEST_CASE("SplitMapControl")
    {
        check_attributes<xlf::split_map_control>("ipyleaflet", "SplitMapControl");
    }

    TEST_CASE("Heatmap")
    {
        check_attributes<xlf::heatmap>("ipyleaflet", "Heatmap");
    }
}
