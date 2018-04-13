#include "xleaflet/xgeo_json.hpp"

template class XLEAFLET_API xw::xmaterialize<xlf::xgeo_json>;
template xw::xmaterialize<xlf::xgeo_json>::xmaterialize();
template class XLEAFLET_API xw::xtransport<xw::xmaterialize<xlf::xgeo_json>>;
template class XLEAFLET_API xw::xgenerator<xlf::xgeo_json>;
template xw::xgenerator<xlf::xgeo_json>::xgenerator();
template class XLEAFLET_API xw::xtransport<xw::xgenerator<xlf::xgeo_json>>;
