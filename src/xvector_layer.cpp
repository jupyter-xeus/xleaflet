#include "xleaflet/xvector_layer.hpp"

template class XLEAFLET_API xw::xmaterialize<xleaflet::xvector_layer>;
template xw::xmaterialize<xleaflet::xvector_layer>::xmaterialize();
template class XLEAFLET_API xw::xtransport<xw::xmaterialize<xleaflet::xvector_layer>>;
template class XLEAFLET_API xw::xgenerator<xleaflet::xvector_layer>;
template xw::xgenerator<xleaflet::xvector_layer>::xgenerator();
template class XLEAFLET_API xw::xtransport<xw::xgenerator<xleaflet::xvector_layer>>;
