#include "xleaflet/xcircle.hpp"

template class XLEAFLET_API xw::xmaterialize<xleaflet::xcircle>;
template xw::xmaterialize<xleaflet::xcircle>::xmaterialize();
template class XLEAFLET_API xw::xtransport<xw::xmaterialize<xleaflet::xcircle>>;
template class XLEAFLET_API xw::xgenerator<xleaflet::xcircle>;
template xw::xgenerator<xleaflet::xcircle>::xgenerator();
template class XLEAFLET_API xw::xtransport<xw::xgenerator<xleaflet::xcircle>>;
