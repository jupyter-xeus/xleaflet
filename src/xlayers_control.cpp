#include "xleaflet/xlayers_control.hpp"

template class XLEAFLET_API xw::xmaterialize<xleaflet::xlayers_control>;
template xw::xmaterialize<xleaflet::xlayers_control>::xmaterialize();
template class XLEAFLET_API xw::xtransport<xw::xmaterialize<xleaflet::xlayers_control>>;
template class XLEAFLET_API xw::xgenerator<xleaflet::xlayers_control>;
template xw::xgenerator<xleaflet::xlayers_control>::xgenerator();
template class XLEAFLET_API xw::xtransport<xw::xgenerator<xleaflet::xlayers_control>>;
