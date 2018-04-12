#include "xleaflet/xmarker.hpp"

template class XLEAFLET_API xw::xmaterialize<xleaflet::xmarker>;
template xw::xmaterialize<xleaflet::xmarker>::xmaterialize();
template class XLEAFLET_API xw::xtransport<xw::xmaterialize<xleaflet::xmarker>>;
template class XLEAFLET_API xw::xgenerator<xleaflet::xmarker>;
template xw::xgenerator<xleaflet::xmarker>::xgenerator();
template class XLEAFLET_API xw::xtransport<xw::xgenerator<xleaflet::xmarker>>;
