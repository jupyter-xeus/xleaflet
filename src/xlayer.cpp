#include "xleaflet/xlayer.hpp"

template class XLEAFLET_API xw::xmaterialize<xleaflet::xlayer>;
template xw::xmaterialize<xleaflet::xlayer>::xmaterialize();
template class XLEAFLET_API xw::xtransport<xw::xmaterialize<xleaflet::xlayer>>;
template class XLEAFLET_API xw::xgenerator<xleaflet::xlayer>;
template xw::xgenerator<xleaflet::xlayer>::xgenerator();
template class XLEAFLET_API xw::xtransport<xw::xgenerator<xleaflet::xlayer>>;
