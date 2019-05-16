/******************************************************************************
* Copyright (c) 2018, Sylvain Corlay and Johan Mabille, Wolf Vollprecht and   *
* Martin Renou                                                                *
*                                                                             *
* Distributed under the terms of the BSD 3-Clause License.                    *
*                                                                             *
* The full license is in the file LICENSE, distributed with this software.    *
*******************************************************************************/

#ifndef XLEAFLET_WIDGET_CONTROL_HPP
#define XLEAFLET_WIDGET_CONTROL_HPP

#include <string>

#include "xwidgets/xholder.hpp"
#include "xwidgets/xmaterialize.hpp"
#include "xwidgets/xwidget.hpp"

#include "xcontrol.hpp"

namespace xlf
{
    /*********************
     * widget_control declaration *
     *********************/

    template <class D>
    class xwidget_control : public xcontrol<D>
    {
    public:

        using point_type = std::array<double, 2>;

        using base_type = xcontrol<D>;
        using derived_type = D;

        using widget_type = xw::xholder<xw::xwidget>;

        void serialize_state(xeus::xjson&, xeus::buffer_sequence&) const;
        void apply_patch(const xeus::xjson&, const xeus::buffer_sequence&);

        XPROPERTY(xtl::xoptional<widget_type>, derived_type, widget);
        XPROPERTY(int, derived_type, max_width, 300);
        XPROPERTY(int, derived_type, min_width, 50);
        XPROPERTY(int, derived_type, max_height);
        XPROPERTY(int, derived_type, min_height);

    protected:

        xwidget_control();
        using base_type::base_type;

    private:

        void set_defaults();
    };

    using widget_control = xw::xmaterialize<xwidget_control>;

    using widget_control_generator = xw::xgenerator<xwidget_control>;

    /*************************
     * xwidget_control implementation *
     *************************/

    template <class D>
    inline void xwidget_control<D>::serialize_state(xeus::xjson& state,
                                           xeus::buffer_sequence& buffers) const
    {
        base_type::serialize_state(state, buffers);

        using xw::set_patch_from_property;

        set_patch_from_property(widget, state, buffers);
        set_patch_from_property(max_width, state, buffers);
        set_patch_from_property(min_width, state, buffers);
        set_patch_from_property(max_height, state, buffers);
        set_patch_from_property(min_height, state, buffers);
    }

    template <class D>
    inline void xwidget_control<D>::apply_patch(const xeus::xjson& patch,
                                       const xeus::buffer_sequence& buffers)
    {
        base_type::apply_patch(patch, buffers);

        using xw::set_property_from_patch;

        set_property_from_patch(widget, patch, buffers);
        set_property_from_patch(max_width, patch, buffers);
        set_property_from_patch(min_width, patch, buffers);
        set_property_from_patch(max_height, patch, buffers);
        set_property_from_patch(min_height, patch, buffers);
    }

    template <class D>
    inline xwidget_control<D>::xwidget_control()
        : base_type()
    {
        set_defaults();
    }

    template <class D>
    inline void xwidget_control<D>::set_defaults()
    {
        this->_model_name() = "LeafletWidgetControlModel";
        this->_view_name() = "LeafletWidgetControlView";

        this->options().insert(
            this->options().end(),
            {
                "max_width",
                "min_width",
                "max_height",
                "min_height"
            }
        );
    }
}

/*********************
 * precompiled types *
 *********************/

#ifndef _WIN32
    extern template class xw::xmaterialize<xlf::xwidget_control>;
    extern template xw::xmaterialize<xlf::xwidget_control>::xmaterialize();
    extern template class xw::xtransport<xw::xmaterialize<xlf::xwidget_control>>;
    extern template class xw::xgenerator<xlf::xwidget_control>;
    extern template xw::xgenerator<xlf::xwidget_control>::xgenerator();
    extern template class xw::xtransport<xw::xgenerator<xlf::xwidget_control>>;
#endif

#endif
