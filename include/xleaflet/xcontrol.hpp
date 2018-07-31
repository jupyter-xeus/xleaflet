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
#include "xwidgets/xobject.hpp"

#include "xleaflet_config.hpp"

namespace xlf
{
    /*********************
     * control declaration *
     *********************/

    template <class D>
    class xcontrol : public xw::xobject<D>
    {
    public:

        using base_type = xw::xobject<D>;
        using derived_type = D;

        void serialize_state(xeus::xjson&, xeus::buffer_sequence&) const;
        void apply_patch(const xeus::xjson&, const xeus::buffer_sequence&);

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
    inline void xcontrol<D>::serialize_state(xeus::xjson& state, xeus::buffer_sequence& buffers) const
    {
        base_type::serialize_state(state, buffers);

        xw::set_patch_from_property(options, state, buffers);
    }

    template <class D>
    inline void xcontrol<D>::apply_patch(const xeus::xjson& patch, const xeus::buffer_sequence& buffers)
    {
        base_type::apply_patch(patch, buffers);

        xw::set_property_from_patch(options, patch, buffers);
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
    extern template class xw::xmaterialize<xlf::xcontrol>;
    extern template xw::xmaterialize<xlf::xcontrol>::xmaterialize();
    extern template class xw::xtransport<xw::xmaterialize<xlf::xcontrol>>;
    extern template class xw::xgenerator<xlf::xcontrol>;
    extern template xw::xgenerator<xlf::xcontrol>::xgenerator();
    extern template class xw::xtransport<xw::xgenerator<xlf::xcontrol>>;
#endif

#endif
