#include "xleaflet/xpath.hpp"

template class XLEAFLET_API xw::xmaterialize<xlf::xpath>;
template xw::xmaterialize<xlf::xpath>::xmaterialize();
template class XLEAFLET_API xw::xtransport<xw::xmaterialize<xlf::xpath>>;
template class XLEAFLET_API xw::xgenerator<xlf::xpath>;
template xw::xgenerator<xlf::xpath>::xgenerator();
template class XLEAFLET_API xw::xtransport<xw::xgenerator<xlf::xpath>>;
