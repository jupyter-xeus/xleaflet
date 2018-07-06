#include "xleaflet/xmeasure_control.hpp"

template class XLEAFLET_API xw::xmaterialize<xlf::xmeasure_control>;
template xw::xmaterialize<xlf::xmeasure_control>::xmaterialize();
template class XLEAFLET_API xw::xtransport<xw::xmaterialize<xlf::xmeasure_control>>;
template class XLEAFLET_API xw::xgenerator<xlf::xmeasure_control>;
template xw::xgenerator<xlf::xmeasure_control>::xgenerator();
template class XLEAFLET_API xw::xtransport<xw::xgenerator<xlf::xmeasure_control>>;
