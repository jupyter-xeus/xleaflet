#include "xleaflet/xmarker.hpp"

template class XLEAFLET_API xw::xmaterialize<xlf::xmarker>;
template xw::xmaterialize<xlf::xmarker>::xmaterialize();
template class XLEAFLET_API xw::xtransport<xw::xmaterialize<xlf::xmarker>>;
template class XLEAFLET_API xw::xgenerator<xlf::xmarker>;
template xw::xgenerator<xlf::xmarker>::xgenerator();
template class XLEAFLET_API xw::xtransport<xw::xgenerator<xlf::xmarker>>;
