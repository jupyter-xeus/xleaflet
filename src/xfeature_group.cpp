#include "xleaflet/xfeature_group.hpp"

template class XLEAFLET_API xw::xmaterialize<xlf::xfeature_group>;
template xw::xmaterialize<xlf::xfeature_group>::xmaterialize();
template class XLEAFLET_API xw::xtransport<xw::xmaterialize<xlf::xfeature_group>>;
template class XLEAFLET_API xw::xgenerator<xlf::xfeature_group>;
template xw::xgenerator<xlf::xfeature_group>::xgenerator();
template class XLEAFLET_API xw::xtransport<xw::xgenerator<xlf::xfeature_group>>;
