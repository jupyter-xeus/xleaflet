#include "xleaflet/ximage_overlay.hpp"

template class XLEAFLET_API xw::xmaterialize<xlf::ximage_overlay>;
template xw::xmaterialize<xlf::ximage_overlay>::xmaterialize();
template class XLEAFLET_API xw::xtransport<xw::xmaterialize<xlf::ximage_overlay>>;
template class XLEAFLET_API xw::xgenerator<xlf::ximage_overlay>;
template xw::xgenerator<xlf::ximage_overlay>::xgenerator();
template class XLEAFLET_API xw::xtransport<xw::xgenerator<xlf::ximage_overlay>>;
