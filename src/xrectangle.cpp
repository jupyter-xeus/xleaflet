#include "xleaflet/xrectangle.hpp"

template class XLEAFLET_API xw::xmaterialize<xlf::xrectangle>;
template xw::xmaterialize<xlf::xrectangle>::xmaterialize();
template class XLEAFLET_API xw::xtransport<xw::xmaterialize<xlf::xrectangle>>;
template class XLEAFLET_API xw::xgenerator<xlf::xrectangle>;
template xw::xgenerator<xlf::xrectangle>::xgenerator();
template class XLEAFLET_API xw::xtransport<xw::xgenerator<xlf::xrectangle>>;
