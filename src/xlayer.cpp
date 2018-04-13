#include "xleaflet/xlayer.hpp"

template class XLEAFLET_API xw::xmaterialize<xlf::xlayer>;
template xw::xmaterialize<xlf::xlayer>::xmaterialize();
template class XLEAFLET_API xw::xtransport<xw::xmaterialize<xlf::xlayer>>;
template class XLEAFLET_API xw::xgenerator<xlf::xlayer>;
template xw::xgenerator<xlf::xlayer>::xgenerator();
template class XLEAFLET_API xw::xtransport<xw::xgenerator<xlf::xlayer>>;
