#include "xleaflet/xmap.hpp"

template class XLEAFLET_API xw::xmaterialize<xlf::xmap>;
template xw::xmaterialize<xlf::xmap>::xmaterialize();
template class XLEAFLET_API xw::xtransport<xw::xmaterialize<xlf::xmap>>;
template class XLEAFLET_API xw::xgenerator<xlf::xmap>;
template xw::xgenerator<xlf::xmap>::xgenerator();
template class XLEAFLET_API xw::xtransport<xw::xgenerator<xlf::xmap>>;
