#include "xleaflet/xpath.hpp"

template class XLEAFLET_API xw::xmaterialize<xleaflet::xpath>;
template xw::xmaterialize<xleaflet::xpath>::xmaterialize();
template class XLEAFLET_API xw::xtransport<xw::xmaterialize<xleaflet::xpath>>;
template class XLEAFLET_API xw::xgenerator<xleaflet::xpath>;
template xw::xgenerator<xleaflet::xpath>::xgenerator();
template class XLEAFLET_API xw::xtransport<xw::xgenerator<xleaflet::xpath>>;
