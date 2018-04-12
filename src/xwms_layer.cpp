#include "xleaflet/xwms_layer.hpp"

template class XLEAFLET_API xw::xmaterialize<xleaflet::xwms_layer>;
template xw::xmaterialize<xleaflet::xwms_layer>::xmaterialize();
template class XLEAFLET_API xw::xtransport<xw::xmaterialize<xleaflet::xwms_layer>>;
template class XLEAFLET_API xw::xgenerator<xleaflet::xwms_layer>;
template xw::xgenerator<xleaflet::xwms_layer>::xgenerator();
template class XLEAFLET_API xw::xtransport<xw::xgenerator<xleaflet::xwms_layer>>;
