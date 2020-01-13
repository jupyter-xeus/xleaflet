#include "xleaflet/xtile_layer.hpp"

template class XLEAFLET_API xw::xmaterialize<xlf::xtile_layer>;
template xw::xmaterialize<xlf::xtile_layer>::xmaterialize();
template class XLEAFLET_API xw::xtransport<xw::xmaterialize<xlf::xtile_layer>>;
