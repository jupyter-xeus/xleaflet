#include "xleaflet/xsplit_map_control.hpp"

template class XLEAFLET_API xw::xmaterialize<xlf::xsplit_map_control>;
template xw::xmaterialize<xlf::xsplit_map_control>::xmaterialize();
template class XLEAFLET_API xw::xtransport<xw::xmaterialize<xlf::xsplit_map_control>>;
template class XLEAFLET_API xw::xgenerator<xlf::xsplit_map_control>;
template xw::xgenerator<xlf::xsplit_map_control>::xgenerator();
template class XLEAFLET_API xw::xtransport<xw::xgenerator<xlf::xsplit_map_control>>;
