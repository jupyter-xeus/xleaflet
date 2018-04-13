#include "xleaflet/xlayer_group.hpp"

template class XLEAFLET_API xw::xmaterialize<xlf::xlayer_group>;
template xw::xmaterialize<xlf::xlayer_group>::xmaterialize();
template class XLEAFLET_API xw::xtransport<xw::xmaterialize<xlf::xlayer_group>>;
template class XLEAFLET_API xw::xgenerator<xlf::xlayer_group>;
template xw::xgenerator<xlf::xlayer_group>::xgenerator();
template class XLEAFLET_API xw::xtransport<xw::xgenerator<xlf::xlayer_group>>;
