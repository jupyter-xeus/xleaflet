#include "xleaflet/xmap.hpp"

template class XLEAFLET_API xw::xmaterialize<xlf::xmap>;
template xw::xmaterialize<xlf::xmap>::xmaterialize();
template class XLEAFLET_API xw::xtransport<xw::xmaterialize<xlf::xmap>>;
