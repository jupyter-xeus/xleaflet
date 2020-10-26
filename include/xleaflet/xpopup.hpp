/******************************************************************************
* Copyright (c) 2018, Sylvain Corlay and Johan Mabille, Wolf Vollprecht and   *
* Martin Renou                                                                *
*                                                                             *
* Distributed under the terms of the BSD 3-Clause License.                    *
*                                                                             *
* The full license is in the file LICENSE, distributed with this software.    *
*******************************************************************************/

#ifndef XLEAFLET_POPUP_HPP
#define XLEAFLET_POPUP_HPP

#include <array>
#include <string>

#include "xwidgets/xholder.hpp"
#include "xwidgets/xmaterialize.hpp"
#include "xwidgets/xwidget.hpp"

#include "xui_layer.hpp"

namespace nl = nlohmann;

namespace xlf
{
    /*********************
     * popup declaration *
     *********************/

    template <class D>
    class xpopup : public xui_layer<D>
    {
    public:

        using point_type = std::array<double, 2>;

        using base_type = xui_layer<D>;
        using derived_type = D;

        using widget_type = xw::xholder<xw::xwidget>;

        void serialize_state(nl::json&, xeus::buffer_sequence&) const;
        void apply_patch(const nl::json&, const xeus::buffer_sequence&);

        XPROPERTY(point_type, derived_type, location);
        XPROPERTY(xtl::xoptional<widget_type>, derived_type, child);
        XPROPERTY(int, derived_type, max_width, 300);
        XPROPERTY(int, derived_type, min_width, 50);
        XPROPERTY(int, derived_type, max_height);
        XPROPERTY(bool, derived_type, auto_pan, true);
        XPROPERTY(point_type, derived_type, auto_pan_padding_top_left);
        XPROPERTY(point_type, derived_type, auto_pan_padding_bottom_right);
        XPROPERTY(point_type, derived_type, auto_pan_padding);
        XPROPERTY(bool, derived_type, keep_in_view, false);
        XPROPERTY(bool, derived_type, close_button, true);
        XPROPERTY(bool, derived_type, auto_close, true);
        XPROPERTY(bool, derived_type, close_on_escape_key, true);
        XPROPERTY(std::string, derived_type, class_name, "");

    protected:

        xpopup();
        using base_type::base_type;

    private:

        void set_defaults();
    };

    using popup = xw::xmaterialize<xpopup>;

    /*************************
     * xpopup implementation *
     *************************/

    template <class D>
    inline void xpopup<D>::serialize_state(nl::json& state,
                                           xeus::buffer_sequence& buffers) const
    {
        base_type::serialize_state(state, buffers);

        using xw::xwidgets_serialize;

        xwidgets_serialize(location(), state["location"], buffers);
        xwidgets_serialize(child(), state["child"], buffers);
        xwidgets_serialize(max_width(), state["max_width"], buffers);
        xwidgets_serialize(min_width(), state["min_width"], buffers);
        xwidgets_serialize(max_height(), state["max_height"], buffers);
        xwidgets_serialize(auto_pan(), state["auto_pan"], buffers);
        xwidgets_serialize(auto_pan_padding_top_left(), state["auto_pan_padding_top_left"], buffers);
        xwidgets_serialize(auto_pan_padding_bottom_right(), state["auto_pan_padding_bottom_right"], buffers);
        xwidgets_serialize(auto_pan_padding(), state["auto_pan_padding"], buffers);
        xwidgets_serialize(keep_in_view(), state["keep_in_view"], buffers);
        xwidgets_serialize(close_button(), state["close_button"], buffers);
        xwidgets_serialize(auto_close(), state["auto_close"], buffers);
        xwidgets_serialize(close_on_escape_key(), state["close_on_escape_key"], buffers);
        xwidgets_serialize(class_name(), state["class_name"], buffers);
    }

    template <class D>
    inline void xpopup<D>::apply_patch(const nl::json& patch,
                                       const xeus::buffer_sequence& buffers)
    {
        base_type::apply_patch(patch, buffers);

        using xw::set_property_from_patch;

        set_property_from_patch(location, patch, buffers);
        set_property_from_patch(child, patch, buffers);
        set_property_from_patch(max_width, patch, buffers);
        set_property_from_patch(min_width, patch, buffers);
        set_property_from_patch(max_height, patch, buffers);
        set_property_from_patch(auto_pan, patch, buffers);
        set_property_from_patch(auto_pan_padding_top_left, patch, buffers);
        set_property_from_patch(auto_pan_padding_bottom_right, patch, buffers);
        set_property_from_patch(auto_pan_padding, patch, buffers);
        set_property_from_patch(keep_in_view, patch, buffers);
        set_property_from_patch(close_button, patch, buffers);
        set_property_from_patch(auto_close, patch, buffers);
        set_property_from_patch(close_on_escape_key, patch, buffers);
        set_property_from_patch(class_name, patch, buffers);
    }

    template <class D>
    inline xpopup<D>::xpopup()
        : base_type()
    {
        set_defaults();
    }

    template <class D>
    inline void xpopup<D>::set_defaults()
    {
        this->_model_name() = "LeafletPopupModel";
        this->_view_name() = "LeafletPopupView";

        this->location() = {0, 0};
        this->auto_pan_padding() = {5, 5};

        this->options().insert(
            this->options().end(),
            {
                "max_width",
                "min_width",
                "max_height",
                "auto_pan",
                "auto_pan_padding_top_left",
                "auto_pan_padding_bottom_right",
                "auto_pan_padding",
                "keep_in_view",
                "close_button",
                "auto_close",
                "close_on_escape_key",
                "class_name"
            }
        );
    }
}

/*********************
 * precompiled types *
 *********************/

    extern template class xw::xmaterialize<xlf::xpopup>;
    extern template class xw::xtransport<xw::xmaterialize<xlf::xpopup>>;

#endif
