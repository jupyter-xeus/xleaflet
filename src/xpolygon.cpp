#include "xleaflet/xpolygon.hpp"

template class XLEAFLET_API xw::xmaterialize<xlf::xpolygon>;
template xw::xmaterialize<xlf::xpolygon>::xmaterialize();
template class XLEAFLET_API xw::xtransport<xw::xmaterialize<xlf::xpolygon>>;
template class XLEAFLET_API xw::xgenerator<xlf::xpolygon>;
template xw::xgenerator<xlf::xpolygon>::xgenerator();
template class XLEAFLET_API xw::xtransport<xw::xgenerator<xlf::xpolygon>>;
