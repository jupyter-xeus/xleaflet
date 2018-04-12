/******************************************************************************
* Copyright (c) 2018, Sylvain Corlay and Johan Mabille, Wolf Vollprecht and   *
* Martin Renou                                                                *
*                                                                             *
* Distributed under the terms of the BSD 3-Clause License.                    *
*                                                                             *
* The full license is in the file LICENSE, distributed with this software.    *
*******************************************************************************/

#ifndef XLEAFLET_CONTROL_HPP
#define XLEAFLET_CONTROL_HPP

#include <string>
#include <vector>

#include "xwidgets/xmaterialize.hpp"
#include "xwidgets/xwidget.hpp"

#include "xleaflet_config.hpp"

namespace xleaflet
{
    /*********************
     * control declaration *
     *********************/

    template <class D>
    class xcontrol : public xw::xwidget<D>
    {
    public:

        using base_type = xw::xwidget<D>;
        using derived_type = D;

        xeus::xjson get_state() const;
        void apply_patch(const xeus::xjson&);

        XPROPERTY(std::vector<std::string>, derived_type, options);

    protected:

        xcontrol();
        using base_type::base_type;

    private:

        void set_defaults();
    };

    using control = xw::xmaterialize<xcontrol>;

    using control_generator = xw::xgenerator<xcontrol>;

    /***************************
     * xcontrol implementation *
     ***************************/

    template <class D>
    inline xeus::xjson xcontrol<D>::get_state() const
    {
        xeus::xjson state = base_type::get_state();

        XOBJECT_SET_PATCH_FROM_PROPERTY(options, state);

        return state;
    }

    template <class D>
    inline void xcontrol<D>::apply_patch(const xeus::xjson& patch)
    {
        base_type::apply_patch(patch);

        XOBJECT_SET_PROPERTY_FROM_PATCH(options, patch);
    }

    template <class D>
    inline xcontrol<D>::xcontrol()
        : base_type()
    {
        set_defaults();
    }

    template <class D>
    inline void xcontrol<D>::set_defaults()
    {
        this->_model_module() = "jupyter-leaflet";
        this->_view_module() = "jupyter-leaflet";
        this->_model_name() = "LeafletControlModel";
        this->_view_name() = "LeafletControlView";
        this->_model_module_version() = XJUPYTER_LEAFLET_VERSION;
        this->_view_module_version() = XJUPYTER_LEAFLET_VERSION;

        this->options() = std::vector<std::string>();
    }

}

/*********************
 * precompiled types *
 *********************/

#ifndef _WIN32
    extern template class xw::xmaterialize<xleaflet::xcontrol>;
    extern template xw::xmaterialize<xleaflet::xcontrol>::xmaterialize();
    extern template class xw::xtransport<xw::xmaterialize<xleaflet::xcontrol>>;
    extern template class xw::xgenerator<xleaflet::xcontrol>;
    extern template xw::xgenerator<xleaflet::xcontrol>::xgenerator();
    extern template class xw::xtransport<xw::xgenerator<xleaflet::xcontrol>>;
#endif

#endif
