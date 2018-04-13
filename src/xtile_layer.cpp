#include "xleaflet/xtile_layer.hpp"

template class XLEAFLET_API xw::xmaterialize<xlf::xtile_layer>;
template xw::xmaterialize<xlf::xtile_layer>::xmaterialize();
template class XLEAFLET_API xw::xtransport<xw::xmaterialize<xlf::xtile_layer>>;
template class XLEAFLET_API xw::xgenerator<xlf::xtile_layer>;
template xw::xgenerator<xlf::xtile_layer>::xgenerator();
template class XLEAFLET_API xw::xtransport<xw::xgenerator<xlf::xtile_layer>>;
