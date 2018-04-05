#include "xleaflet/xmap.hpp"
#include "xleaflet/xlayer.hpp"
#include "xleaflet/xraster_layer.hpp"
#include "xleaflet/xtile_layer.hpp"
#include "xleaflet/xui_layer.hpp"
#include "xleaflet/xmarker.hpp"
#include "xleaflet/ximage_overlay.hpp"
#include "xleaflet/xvideo_overlay.hpp"

template class XLEAFLET_API xw::xmaterialize<xleaflet::xmap>;
template xw::xmaterialize<xleaflet::xmap>::xmaterialize();
template class XLEAFLET_API xw::xtransport<xw::xmaterialize<xleaflet::xmap>>;
template class XLEAFLET_API xw::xgenerator<xleaflet::xmap>;
template xw::xgenerator<xleaflet::xmap>::xgenerator();
template class XLEAFLET_API xw::xtransport<xw::xgenerator<xleaflet::xmap>>;
