#include "xleaflet/xraster_layer.hpp"

template class XLEAFLET_API xw::xmaterialize<xlf::xraster_layer>;
template xw::xmaterialize<xlf::xraster_layer>::xmaterialize();
template class XLEAFLET_API xw::xtransport<xw::xmaterialize<xlf::xraster_layer>>;
template class XLEAFLET_API xw::xgenerator<xlf::xraster_layer>;
template xw::xgenerator<xlf::xraster_layer>::xgenerator();
template class XLEAFLET_API xw::xtransport<xw::xgenerator<xlf::xraster_layer>>;
