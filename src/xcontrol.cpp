#include "xleaflet/xcontrol.hpp"

template class XLEAFLET_API xw::xmaterialize<xleaflet::xcontrol>;
template xw::xmaterialize<xleaflet::xcontrol>::xmaterialize();
template class XLEAFLET_API xw::xtransport<xw::xmaterialize<xleaflet::xcontrol>>;
template class XLEAFLET_API xw::xgenerator<xleaflet::xcontrol>;
template xw::xgenerator<xleaflet::xcontrol>::xgenerator();
template class XLEAFLET_API xw::xtransport<xw::xgenerator<xleaflet::xcontrol>>;
