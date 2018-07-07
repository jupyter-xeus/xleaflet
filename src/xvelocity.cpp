#include "xleaflet/xvelocity.hpp"

template class XLEAFLET_API xw::xmaterialize<xlf::xvelocity>;
template xw::xmaterialize<xlf::xvelocity>::xmaterialize();
template class XLEAFLET_API xw::xtransport<xw::xmaterialize<xlf::xvelocity>>;
template class XLEAFLET_API xw::xgenerator<xlf::xvelocity>;
template xw::xgenerator<xlf::xvelocity>::xgenerator();
template class XLEAFLET_API xw::xtransport<xw::xgenerator<xlf::xvelocity>>;
