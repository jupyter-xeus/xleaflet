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

namespace nl = nlohmann;

namespace xlf
{
    /******************************
     * widget_control declaration *
     ******************************/

    template <class D>
    class xwidget_control : public xcontrol<D>
    {
    public:

        using base_type = xcontrol<D>;
        using derived_type = D;

        using widget_type = xw::xholder;

        void serialize_state(nl::json&, xeus::buffer_sequence&) const;
        void apply_patch(const nl::json&, const xeus::buffer_sequence&);

        XPROPERTY(widget_type, derived_type, widget);
        XPROPERTY(xtl::xoptional<int>, derived_type, max_width);
        XPROPERTY(xtl::xoptional<int>, derived_type, min_width);
        XPROPERTY(xtl::xoptional<int>, derived_type, max_height);
        XPROPERTY(xtl::xoptional<int>, derived_type, min_height);

    protected:

        xwidget_control();
        using base_type::base_type;

    private:

        void set_defaults();
    };

    using widget_control = xw::xmaterialize<xwidget_control>;

    /**********************************
     * xwidget_control implementation *
     **********************************/

    template <class D>
    inline void xwidget_control<D>::serialize_state(nl::json& state,
                                                    xeus::buffer_sequence& buffers) const
    {
        base_type::serialize_state(state, buffers);

        using xw::xwidgets_serialize;

        xwidgets_serialize(widget(), state["widget"], buffers);
        xwidgets_serialize(max_width(), state["max_width"], buffers);
        xwidgets_serialize(min_width(), state["min_width"], buffers);
        xwidgets_serialize(max_height(), state["max_height"], buffers);
        xwidgets_serialize(min_height(), state["min_height"], buffers);
    }

    template <class D>
    inline void xwidget_control<D>::apply_patch(const nl::json& patch,
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

    extern template class xw::xmaterialize<xlf::xwidget_control>;
    extern template class xw::xtransport<xw::xmaterialize<xlf::xwidget_control>>;

#endif
