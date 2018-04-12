#include "xleaflet/xmarker_cluster.hpp"

template class XLEAFLET_API xw::xmaterialize<xleaflet::xmarker_cluster>;
template xw::xmaterialize<xleaflet::xmarker_cluster>::xmaterialize();
template class XLEAFLET_API xw::xtransport<xw::xmaterialize<xleaflet::xmarker_cluster>>;
template class XLEAFLET_API xw::xgenerator<xleaflet::xmarker_cluster>;
template xw::xgenerator<xleaflet::xmarker_cluster>::xgenerator();
template class XLEAFLET_API xw::xtransport<xw::xgenerator<xleaflet::xmarker_cluster>>;
