#include "xleaflet/xpolygon.hpp"

template class XLEAFLET_API xw::xmaterialize<xleaflet::xpolygon>;
template xw::xmaterialize<xleaflet::xpolygon>::xmaterialize();
template class XLEAFLET_API xw::xtransport<xw::xmaterialize<xleaflet::xpolygon>>;
template class XLEAFLET_API xw::xgenerator<xleaflet::xpolygon>;
template xw::xgenerator<xleaflet::xpolygon>::xgenerator();
template class XLEAFLET_API xw::xtransport<xw::xgenerator<xleaflet::xpolygon>>;
