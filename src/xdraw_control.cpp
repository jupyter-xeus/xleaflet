#include "xleaflet/xdraw_control.hpp"

template class XLEAFLET_API xw::xmaterialize<xlf::xdraw_control>;
template xw::xmaterialize<xlf::xdraw_control>::xmaterialize();
template class XLEAFLET_API xw::xtransport<xw::xmaterialize<xlf::xdraw_control>>;
template class XLEAFLET_API xw::xgenerator<xlf::xdraw_control>;
template xw::xgenerator<xlf::xdraw_control>::xgenerator();
template class XLEAFLET_API xw::xtransport<xw::xgenerator<xlf::xdraw_control>>;
