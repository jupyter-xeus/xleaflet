#include "xleaflet/ximage_overlay.hpp"

template class XLEAFLET_API xw::xmaterialize<xleaflet::ximage_overlay>;
template xw::xmaterialize<xleaflet::ximage_overlay>::xmaterialize();
template class XLEAFLET_API xw::xtransport<xw::xmaterialize<xleaflet::ximage_overlay>>;
template class XLEAFLET_API xw::xgenerator<xleaflet::ximage_overlay>;
template xw::xgenerator<xleaflet::ximage_overlay>::xgenerator();
template class XLEAFLET_API xw::xtransport<xw::xgenerator<xleaflet::ximage_overlay>>;
