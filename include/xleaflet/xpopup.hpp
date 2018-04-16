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

#include <string>

#include "xwidgets/xmaterialize.hpp"
#include "xwidgets/xwidget.hpp"
#include "xwidgets/xholder.hpp"

#include "xui_layer.hpp"

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

        xeus::xjson get_state() const;
        void apply_patch(const xeus::xjson&);

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

    using popup_generator = xw::xgenerator<xpopup>;

    /*************************
     * xpopup implementation *
     *************************/

    template <class D>
    inline xeus::xjson xpopup<D>::get_state() const
    {
        xeus::xjson state = base_type::get_state();

        XOBJECT_SET_PATCH_FROM_PROPERTY(location, state);
        XOBJECT_SET_PATCH_FROM_PROPERTY(child, state);
        XOBJECT_SET_PATCH_FROM_PROPERTY(max_width, state);
        XOBJECT_SET_PATCH_FROM_PROPERTY(min_width, state);
        XOBJECT_SET_PATCH_FROM_PROPERTY(max_height, state);
        XOBJECT_SET_PATCH_FROM_PROPERTY(auto_pan, state);
        XOBJECT_SET_PATCH_FROM_PROPERTY(auto_pan_padding_top_left, state);
        XOBJECT_SET_PATCH_FROM_PROPERTY(auto_pan_padding_bottom_right, state);
        XOBJECT_SET_PATCH_FROM_PROPERTY(auto_pan_padding, state);
        XOBJECT_SET_PATCH_FROM_PROPERTY(keep_in_view, state);
        XOBJECT_SET_PATCH_FROM_PROPERTY(close_button, state);
        XOBJECT_SET_PATCH_FROM_PROPERTY(auto_close, state);
        XOBJECT_SET_PATCH_FROM_PROPERTY(close_on_escape_key, state);
        XOBJECT_SET_PATCH_FROM_PROPERTY(class_name, state);

        return state;
    }

    template <class D>
    inline void xpopup<D>::apply_patch(const xeus::xjson& patch)
    {
        base_type::apply_patch(patch);

        XOBJECT_SET_PROPERTY_FROM_PATCH(location, patch);
        XOBJECT_SET_PROPERTY_FROM_PATCH(child, patch);
        XOBJECT_SET_PROPERTY_FROM_PATCH(max_width, patch);
        XOBJECT_SET_PROPERTY_FROM_PATCH(min_width, patch);
        XOBJECT_SET_PROPERTY_FROM_PATCH(max_height, patch);
        XOBJECT_SET_PROPERTY_FROM_PATCH(auto_pan, patch);
        XOBJECT_SET_PROPERTY_FROM_PATCH(auto_pan_padding_top_left, patch);
        XOBJECT_SET_PROPERTY_FROM_PATCH(auto_pan_padding_bottom_right, patch);
        XOBJECT_SET_PROPERTY_FROM_PATCH(auto_pan_padding, patch);
        XOBJECT_SET_PROPERTY_FROM_PATCH(keep_in_view, patch);
        XOBJECT_SET_PROPERTY_FROM_PATCH(close_button, patch);
        XOBJECT_SET_PROPERTY_FROM_PATCH(auto_close, patch);
        XOBJECT_SET_PROPERTY_FROM_PATCH(close_on_escape_key, patch);
        XOBJECT_SET_PROPERTY_FROM_PATCH(class_name, patch);
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

#ifndef _WIN32
    extern template class xw::xmaterialize<xlf::xpopup>;
    extern template xw::xmaterialize<xlf::xpopup>::xmaterialize();
    extern template class xw::xtransport<xw::xmaterialize<xlf::xpopup>>;
    extern template class xw::xgenerator<xlf::xpopup>;
    extern template xw::xgenerator<xlf::xpopup>::xgenerator();
    extern template class xw::xtransport<xw::xgenerator<xlf::xpopup>>;
#endif

#endif
