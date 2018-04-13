#include "xleaflet/xwms_layer.hpp"

template class XLEAFLET_API xw::xmaterialize<xlf::xwms_layer>;
template xw::xmaterialize<xlf::xwms_layer>::xmaterialize();
template class XLEAFLET_API xw::xtransport<xw::xmaterialize<xlf::xwms_layer>>;
template class XLEAFLET_API xw::xgenerator<xlf::xwms_layer>;
template xw::xgenerator<xlf::xwms_layer>::xgenerator();
template class XLEAFLET_API xw::xtransport<xw::xgenerator<xlf::xwms_layer>>;
