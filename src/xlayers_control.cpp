#include "xleaflet/xlayers_control.hpp"

template class XLEAFLET_API xw::xmaterialize<xlf::xlayers_control>;
template xw::xmaterialize<xlf::xlayers_control>::xmaterialize();
template class XLEAFLET_API xw::xtransport<xw::xmaterialize<xlf::xlayers_control>>;
template class XLEAFLET_API xw::xgenerator<xlf::xlayers_control>;
template xw::xgenerator<xlf::xlayers_control>::xgenerator();
template class XLEAFLET_API xw::xtransport<xw::xgenerator<xlf::xlayers_control>>;
