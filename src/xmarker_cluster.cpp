#include "xleaflet/xmarker_cluster.hpp"

template class XLEAFLET_API xw::xmaterialize<xlf::xmarker_cluster>;
template xw::xmaterialize<xlf::xmarker_cluster>::xmaterialize();
template class XLEAFLET_API xw::xtransport<xw::xmaterialize<xlf::xmarker_cluster>>;
template class XLEAFLET_API xw::xgenerator<xlf::xmarker_cluster>;
template xw::xgenerator<xlf::xmarker_cluster>::xgenerator();
template class XLEAFLET_API xw::xtransport<xw::xgenerator<xlf::xmarker_cluster>>;
