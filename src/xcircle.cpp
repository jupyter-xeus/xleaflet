#include "xleaflet/xcircle.hpp"

template class XLEAFLET_API xw::xmaterialize<xlf::xcircle>;
template xw::xmaterialize<xlf::xcircle>::xmaterialize();
template class XLEAFLET_API xw::xtransport<xw::xmaterialize<xlf::xcircle>>;
template class XLEAFLET_API xw::xgenerator<xlf::xcircle>;
template xw::xgenerator<xlf::xcircle>::xgenerator();
template class XLEAFLET_API xw::xtransport<xw::xgenerator<xlf::xcircle>>;
