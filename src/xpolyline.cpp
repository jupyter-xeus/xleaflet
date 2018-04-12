#include "xleaflet/xpolyline.hpp"

template class XLEAFLET_API xw::xmaterialize<xleaflet::xpolyline>;
template xw::xmaterialize<xleaflet::xpolyline>::xmaterialize();
template class XLEAFLET_API xw::xtransport<xw::xmaterialize<xleaflet::xpolyline>>;
template class XLEAFLET_API xw::xgenerator<xleaflet::xpolyline>;
template xw::xgenerator<xleaflet::xpolyline>::xgenerator();
template class XLEAFLET_API xw::xtransport<xw::xgenerator<xleaflet::xpolyline>>;
