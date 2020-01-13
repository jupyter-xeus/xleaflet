/******************************************************************************
* Copyright (c) 2018, Sylvain Corlay and Johan Mabille, Wolf Vollprecht and   *
* Martin Renou                                                                *
*                                                                             *
* Distributed under the terms of the BSD 3-Clause License.                    *
*                                                                             *
* The full license is in the file LICENSE, distributed with this software.    *
*******************************************************************************/

#ifndef XLEAFLET_FULLSCREEN_CONTROL_HPP
#define XLEAFLET_FULLSCREEN_CONTROL_HPP

#include "xwidgets/xmaterialize.hpp"
#include "xwidgets/xwidget.hpp"

#include "xcontrol.hpp"
#include "xleaflet_config.hpp"

namespace xlf
{
    /******************************
     * fullscreen_control declaration *
     ******************************/

    template <class D>
    class xfullscreen_control : public xcontrol<D>
    {
    public:

        using base_type = xcontrol<D>;
        using derived_type = D;

    protected:

        xfullscreen_control();
        using base_type::base_type;

    private:

        void set_defaults();
    };

    using fullscreen_control = xw::xmaterialize<xfullscreen_control>;

    /**********************************
     * xfullscreen_control implementation *
     **********************************/

    template <class D>
    inline xfullscreen_control<D>::xfullscreen_control()
        : base_type()
    {
        set_defaults();
    }

    template <class D>
    inline void xfullscreen_control<D>::set_defaults()
    {
        this->_model_name() = "LeafletFullScreenControlModel";
        this->_view_name() = "LeafletFullScreenControlView";
    }
}

/*********************
 * precompiled types *
 *********************/

#ifndef _WIN32
    extern template class xw::xmaterialize<xlf::xfullscreen_control>;
    extern template xw::xmaterialize<xlf::xfullscreen_control>::xmaterialize();
    extern template class xw::xtransport<xw::xmaterialize<xlf::xfullscreen_control>>;
#endif

#endif
