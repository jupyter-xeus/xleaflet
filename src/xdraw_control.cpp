#include "xleaflet/xdraw_control.hpp"

template class XLEAFLET_API xw::xmaterialize<xleaflet::xdraw_control>;
template xw::xmaterialize<xleaflet::xdraw_control>::xmaterialize();
template class XLEAFLET_API xw::xtransport<xw::xmaterialize<xleaflet::xdraw_control>>;
template class XLEAFLET_API xw::xgenerator<xleaflet::xdraw_control>;
template xw::xgenerator<xleaflet::xdraw_control>::xgenerator();
template class XLEAFLET_API xw::xtransport<xw::xgenerator<xleaflet::xdraw_control>>;
