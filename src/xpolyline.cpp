#include "xleaflet/xpolyline.hpp"

template class XLEAFLET_API xw::xmaterialize<xlf::xpolyline>;
template xw::xmaterialize<xlf::xpolyline>::xmaterialize();
template class XLEAFLET_API xw::xtransport<xw::xmaterialize<xlf::xpolyline>>;
template class XLEAFLET_API xw::xgenerator<xlf::xpolyline>;
template xw::xgenerator<xlf::xpolyline>::xgenerator();
template class XLEAFLET_API xw::xtransport<xw::xgenerator<xlf::xpolyline>>;
