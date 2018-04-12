#include "xleaflet/xtile_layer.hpp"

template class XLEAFLET_API xw::xmaterialize<xleaflet::xtile_layer>;
template xw::xmaterialize<xleaflet::xtile_layer>::xmaterialize();
template class XLEAFLET_API xw::xtransport<xw::xmaterialize<xleaflet::xtile_layer>>;
template class XLEAFLET_API xw::xgenerator<xleaflet::xtile_layer>;
template xw::xgenerator<xleaflet::xtile_layer>::xgenerator();
template class XLEAFLET_API xw::xtransport<xw::xgenerator<xleaflet::xtile_layer>>;
