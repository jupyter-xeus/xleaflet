#include "xleaflet/xlayer_group.hpp"

template class XLEAFLET_API xw::xmaterialize<xleaflet::xlayer_group>;
template xw::xmaterialize<xleaflet::xlayer_group>::xmaterialize();
template class XLEAFLET_API xw::xtransport<xw::xmaterialize<xleaflet::xlayer_group>>;
template class XLEAFLET_API xw::xgenerator<xleaflet::xlayer_group>;
template xw::xgenerator<xleaflet::xlayer_group>::xgenerator();
template class XLEAFLET_API xw::xtransport<xw::xgenerator<xleaflet::xlayer_group>>;
