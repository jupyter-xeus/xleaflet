#include "xleaflet/xrectangle.hpp"

template class XLEAFLET_API xw::xmaterialize<xleaflet::xrectangle>;
template xw::xmaterialize<xleaflet::xrectangle>::xmaterialize();
template class XLEAFLET_API xw::xtransport<xw::xmaterialize<xleaflet::xrectangle>>;
template class XLEAFLET_API xw::xgenerator<xleaflet::xrectangle>;
template xw::xgenerator<xleaflet::xrectangle>::xgenerator();
template class XLEAFLET_API xw::xtransport<xw::xgenerator<xleaflet::xrectangle>>;
