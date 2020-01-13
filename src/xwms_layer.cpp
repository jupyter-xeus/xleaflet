#include "xleaflet/xwms_layer.hpp"

template class XLEAFLET_API xw::xmaterialize<xlf::xwms_layer>;
template xw::xmaterialize<xlf::xwms_layer>::xmaterialize();
template class XLEAFLET_API xw::xtransport<xw::xmaterialize<xlf::xwms_layer>>;
