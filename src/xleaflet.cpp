#include "xleaflet/xcircle.hpp"
#include "xleaflet/xcircle_marker.hpp"
#include "xleaflet/ximage_overlay.hpp"
#include "xleaflet/xlayer.hpp"
#include "xleaflet/xmap.hpp"
#include "xleaflet/xmarker_cluster.hpp"
#include "xleaflet/xmarker.hpp"
#include "xleaflet/xpath.hpp"
#include "xleaflet/xpolygon.hpp"
#include "xleaflet/xpolyline.hpp"
#include "xleaflet/xraster_layer.hpp"
#include "xleaflet/xrectangle.hpp"
#include "xleaflet/xtile_layer.hpp"
#include "xleaflet/xui_layer.hpp"
#include "xleaflet/xvector_layer.hpp"
#include "xleaflet/xvideo_overlay.hpp"
#include "xleaflet/xwms_layer.hpp"

template class XLEAFLET_API xw::xmaterialize<xleaflet::xmap>;
template xw::xmaterialize<xleaflet::xmap>::xmaterialize();
template class XLEAFLET_API xw::xtransport<xw::xmaterialize<xleaflet::xmap>>;
template class XLEAFLET_API xw::xgenerator<xleaflet::xmap>;
template xw::xgenerator<xleaflet::xmap>::xgenerator();
template class XLEAFLET_API xw::xtransport<xw::xgenerator<xleaflet::xmap>>;
