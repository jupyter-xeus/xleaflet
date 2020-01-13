#include "xleaflet/xvector_layer.hpp"

template class XLEAFLET_API xw::xmaterialize<xlf::xvector_layer>;
template xw::xmaterialize<xlf::xvector_layer>::xmaterialize();
template class XLEAFLET_API xw::xtransport<xw::xmaterialize<xlf::xvector_layer>>;
