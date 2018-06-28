#include "xleaflet/xheatmap.hpp"

template class XLEAFLET_API xw::xmaterialize<xlf::xheatmap>;
template xw::xmaterialize<xlf::xheatmap>::xmaterialize();
template class XLEAFLET_API xw::xtransport<xw::xmaterialize<xlf::xheatmap>>;
template class XLEAFLET_API xw::xgenerator<xlf::xheatmap>;
template xw::xgenerator<xlf::xheatmap>::xgenerator();
template class XLEAFLET_API xw::xtransport<xw::xgenerator<xlf::xheatmap>>;
