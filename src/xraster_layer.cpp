#include "xleaflet/xraster_layer.hpp"

template class XLEAFLET_API xw::xmaterialize<xleaflet::xraster_layer>;
template xw::xmaterialize<xleaflet::xraster_layer>::xmaterialize();
template class XLEAFLET_API xw::xtransport<xw::xmaterialize<xleaflet::xraster_layer>>;
template class XLEAFLET_API xw::xgenerator<xleaflet::xraster_layer>;
template xw::xgenerator<xleaflet::xraster_layer>::xgenerator();
template class XLEAFLET_API xw::xtransport<xw::xgenerator<xleaflet::xraster_layer>>;
