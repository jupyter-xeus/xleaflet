#include "xleaflet/xui_layer.hpp"

template class XLEAFLET_API xw::xmaterialize<xleaflet::xui_layer>;
template xw::xmaterialize<xleaflet::xui_layer>::xmaterialize();
template class XLEAFLET_API xw::xtransport<xw::xmaterialize<xleaflet::xui_layer>>;
template class XLEAFLET_API xw::xgenerator<xleaflet::xui_layer>;
template xw::xgenerator<xleaflet::xui_layer>::xgenerator();
template class XLEAFLET_API xw::xtransport<xw::xgenerator<xleaflet::xui_layer>>;
