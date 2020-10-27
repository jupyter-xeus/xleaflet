/******************************************************************************
* Copyright (c) 2018, Sylvain Corlay and Johan Mabille, Wolf Vollprecht and   *
* Martin Renou                                                                *
*                                                                             *
* Distributed under the terms of the BSD 3-Clause License.                    *
*                                                                             *
* The full license is in the file LICENSE, distributed with this software.    *
*******************************************************************************/

#ifndef XLEAFLET_LAYERS_CONTROL_HPP
#define XLEAFLET_LAYERS_CONTROL_HPP

#include "xwidgets/xmaterialize.hpp"
#include "xwidgets/xwidget.hpp"

#include "xcontrol.hpp"
#include "xleaflet_config.hpp"

namespace xlf
{
    /******************************
     * layers_control declaration *
     ******************************/

    template <class D>
    class xlayers_control : public xcontrol<D>
    {
    public:

        using base_type = xcontrol<D>;
        using derived_type = D;

    protected:

        xlayers_control();
        using base_type::base_type;

    private:

        void set_defaults();
    };

    using layers_control = xw::xmaterialize<xlayers_control>;

    /**********************************
     * xlayers_control implementation *
     **********************************/

    template <class D>
    inline xlayers_control<D>::xlayers_control()
        : base_type()
    {
        set_defaults();
    }

    template <class D>
    inline void xlayers_control<D>::set_defaults()
    {
        this->_model_name() = "LeafletLayersControlModel";
        this->_view_name() = "LeafletLayersControlView";
    }

}

/*********************
 * precompiled types *
 *********************/

    extern template class xw::xmaterialize<xlf::xlayers_control>;
    extern template class xw::xtransport<xw::xmaterialize<xlf::xlayers_control>>;

#endif
