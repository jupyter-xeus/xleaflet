#include "xleaflet/xlayer.hpp"

template class XLEAFLET_API xw::xmaterialize<xlf::xlayer>;
template xw::xmaterialize<xlf::xlayer>::xmaterialize();
template class XLEAFLET_API xw::xtransport<xw::xmaterialize<xlf::xlayer>>;
