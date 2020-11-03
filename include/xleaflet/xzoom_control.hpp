/******************************************************************************
* Copyright (c) 2018, Sylvain Corlay and Johan Mabille, Wolf Vollprecht and   *
* Martin Renou                                                                *
*                                                                             *
* Distributed under the terms of the BSD 3-Clause License.                    *
*                                                                             *
* The full license is in the file LICENSE, distributed with this software.    *
*******************************************************************************/

#ifndef XLEAFLET_ZOOM_CONTROL_HPP
#define XLEAFLET_ZOOM_CONTROL_HPP

#include <string>

#include "xwidgets/xcolor.hpp"
#include "xwidgets/xmaterialize.hpp"
#include "xwidgets/xwidget.hpp"

#include "xcontrol.hpp"
#include "xfeature_group.hpp"
#include "xleaflet_config.hpp"

namespace nl = nlohmann;

namespace xlf
{
    /*******************************
     * zoom_control declaration *
     *******************************/

    template <class D>
    class xzoom_control : public xcontrol<D>
    {
    public:

        using base_type = xcontrol<D>;
        using derived_type = D;

        void serialize_state(nl::json&, xeus::buffer_sequence&) const;
        void apply_patch(const nl::json&, const xeus::buffer_sequence&);

        XPROPERTY(std::string, derived_type, zoom_in_text, "+");
        XPROPERTY(std::string, derived_type, zoom_in_title, "Zoom in");
        XPROPERTY(xtl::xoptional<std::string>, derived_type, zoom_out_text, "-");
        XPROPERTY(std::string, derived_type, zoom_out_title, "Zoom out");

    protected:

        xzoom_control();
        using base_type::base_type;

    private:

        void set_defaults();
    };

    using zoom_control = xw::xmaterialize<xzoom_control>;

    /********************************
     * xzoom_control implementation *
     ********************************/

    template <class D>
    inline void xzoom_control<D>::serialize_state(nl::json& state,
                                                  xeus::buffer_sequence& buffers) const
    {
        base_type::serialize_state(state, buffers);

        using xw::xwidgets_serialize;

        xwidgets_serialize(zoom_in_text(), state["zoom_in_text"], buffers);
        xwidgets_serialize(zoom_in_title(), state["zoom_in_title"], buffers);
        xwidgets_serialize(zoom_out_text(), state["zoom_out_text"], buffers);
        xwidgets_serialize(zoom_out_title(), state["zoom_out_title"], buffers);
    }

    template <class D>
    inline void xzoom_control<D>::apply_patch(const nl::json& patch,
                                              const xeus::buffer_sequence& buffers)
    {
        base_type::apply_patch(patch, buffers);

        using xw::set_property_from_patch;

        set_property_from_patch(zoom_in_text, patch, buffers);
        set_property_from_patch(zoom_in_title, patch, buffers);
        set_property_from_patch(zoom_out_text, patch, buffers);
        set_property_from_patch(zoom_out_title, patch, buffers);
    }

    template <class D>
    inline xzoom_control<D>::xzoom_control()
        : base_type()
    {
        set_defaults();
    }

    template <class D>
    inline void xzoom_control<D>::set_defaults()
    {
        this->_model_name() = "LeafletZoomControlModel";
        this->_view_name() = "LeafletZoomControlView";
    }
}

/*********************
 * precompiled types *
 *********************/

    extern template class xw::xmaterialize<xlf::xzoom_control>;
    extern template class xw::xtransport<xw::xmaterialize<xlf::xzoom_control>>;

#endif
