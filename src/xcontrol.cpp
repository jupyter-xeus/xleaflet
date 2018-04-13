#include "xleaflet/xcontrol.hpp"

template class XLEAFLET_API xw::xmaterialize<xlf::xcontrol>;
template xw::xmaterialize<xlf::xcontrol>::xmaterialize();
template class XLEAFLET_API xw::xtransport<xw::xmaterialize<xlf::xcontrol>>;
template class XLEAFLET_API xw::xgenerator<xlf::xcontrol>;
template xw::xgenerator<xlf::xcontrol>::xgenerator();
template class XLEAFLET_API xw::xtransport<xw::xgenerator<xlf::xcontrol>>;
