#include "xleaflet/xvector_layer.hpp"

template class XLEAFLET_API xw::xmaterialize<xlf::xvector_layer>;
template xw::xmaterialize<xlf::xvector_layer>::xmaterialize();
template class XLEAFLET_API xw::xtransport<xw::xmaterialize<xlf::xvector_layer>>;
template class XLEAFLET_API xw::xgenerator<xlf::xvector_layer>;
template xw::xgenerator<xlf::xvector_layer>::xgenerator();
template class XLEAFLET_API xw::xtransport<xw::xgenerator<xlf::xvector_layer>>;
