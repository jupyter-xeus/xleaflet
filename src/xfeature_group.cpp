#include "xleaflet/xfeature_group.hpp"

template class XLEAFLET_API xw::xmaterialize<xleaflet::xfeature_group>;
template xw::xmaterialize<xleaflet::xfeature_group>::xmaterialize();
template class XLEAFLET_API xw::xtransport<xw::xmaterialize<xleaflet::xfeature_group>>;
template class XLEAFLET_API xw::xgenerator<xleaflet::xfeature_group>;
template xw::xgenerator<xleaflet::xfeature_group>::xgenerator();
template class XLEAFLET_API xw::xtransport<xw::xgenerator<xleaflet::xfeature_group>>;
