#include "xleaflet/xwidget_control.hpp"

template class XLEAFLET_API xw::xmaterialize<xlf::xwidget_control>;
template xw::xmaterialize<xlf::xwidget_control>::xmaterialize();
template class XLEAFLET_API xw::xtransport<xw::xmaterialize<xlf::xwidget_control>>;
template class XLEAFLET_API xw::xgenerator<xlf::xwidget_control>;
template xw::xgenerator<xlf::xwidget_control>::xgenerator();
template class XLEAFLET_API xw::xtransport<xw::xgenerator<xlf::xwidget_control>>;
