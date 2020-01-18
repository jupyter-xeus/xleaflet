#include "gtest/gtest.h"

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

TEST(attributes, Circle)
{
    check_attributes<xlf::circle_marker>("ipyleaflet", "Circle");
}

TEST(attributes, DrawControl)
{
    check_attributes<xlf::draw_control>("ipyleaflet", "DrawControl");
}

TEST(attributes, CircleMarker)
{
    check_attributes<xlf::circle_marker>("ipyleaflet", "CircleMarker");
}

TEST(attributes, Control)
{
    check_attributes<xlf::control>("ipyleaflet", "Control");
}

TEST(attributes, GeoJSON)
{
    check_attributes<xlf::geo_json>("ipyleaflet", "GeoJSON");
}

TEST(attributes, Icon)
{
    check_attributes<xlf::icon>("ipyleaflet", "Icon");
}

TEST(attributes, ImageOverlay)
{
    check_attributes<xlf::image_overlay>("ipyleaflet", "ImageOverlay");
}

TEST(attributes, Layer)
{
    check_attributes<xlf::layer>("ipyleaflet", "Layer");
}

TEST(attributes, LayerGroup)
{
    check_attributes<xlf::layer_group>("ipyleaflet", "LayerGroup");
}

TEST(attributes, Map)
{
    check_attributes<xlf::map>("ipyleaflet", "Map");
}

TEST(attributes, Marker)
{
    check_attributes<xlf::marker>("ipyleaflet", "Marker");
}

TEST(attributes, MarkerCluster)
{
    check_attributes<xlf::marker_cluster>("ipyleaflet", "MarkerCluster");
}

TEST(attributes, MeasureControl)
{
    check_attributes<xlf::measure_control>("ipyleaflet", "MeasureControl");
}

TEST(attributes, Path)
{
    check_attributes<xlf::path>("ipyleaflet", "Path");
}

TEST(attributes, Popup)
{
    check_attributes<xlf::popup>("ipyleaflet", "Popup");
}

TEST(attributes, RasterLayer)
{
    check_attributes<xlf::raster_layer>("ipyleaflet", "RasterLayer");
}

TEST(attributes, TileLayer)
{
    check_attributes<xlf::tile_layer>("ipyleaflet", "TileLayer");
}

TEST(attributes, UILayer)
{
    check_attributes<xlf::ui_layer>("ipyleaflet", "UILayer");
}

TEST(attributes, VectorLayer)
{
    check_attributes<xlf::vector_layer>("ipyleaflet", "VectorLayer");
}

TEST(attributes, VideoOverlay)
{
    check_attributes<xlf::video_overlay>("ipyleaflet", "VideoOverlay");
}

TEST(attributes, WMSLayer)
{
    check_attributes<xlf::wms_layer>("ipyleaflet", "WMSLayer");
}

TEST(attributes, Rectangle)
{
    check_attributes<xlf::rectangle>("ipyleaflet", "Rectangle");
}

TEST(attributes, Polygon)
{
    check_attributes<xlf::polygon>("ipyleaflet", "Polygon");
}

TEST(attributes, Polyline)
{
    check_attributes<xlf::polyline>("ipyleaflet", "Polyline");
}

TEST(attributes, SplitMapControl)
{
    check_attributes<xlf::split_map_control>("ipyleaflet", "SplitMapControl");
}

TEST(attributes, Heatmap)
{
    check_attributes<xlf::heatmap>("ipyleaflet", "Heatmap");
}
