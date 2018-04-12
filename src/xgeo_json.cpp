#include "xleaflet/xgeo_json.hpp"

template class XLEAFLET_API xw::xmaterialize<xleaflet::xgeo_json>;
template xw::xmaterialize<xleaflet::xgeo_json>::xmaterialize();
template class XLEAFLET_API xw::xtransport<xw::xmaterialize<xleaflet::xgeo_json>>;
template class XLEAFLET_API xw::xgenerator<xleaflet::xgeo_json>;
template xw::xgenerator<xleaflet::xgeo_json>::xgenerator();
template class XLEAFLET_API xw::xtransport<xw::xgenerator<xleaflet::xgeo_json>>;
