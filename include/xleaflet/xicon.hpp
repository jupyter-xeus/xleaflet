/******************************************************************************
* Copyright (c) 2018, Sylvain Corlay and Johan Mabille, and Wolf Vollprecht   *
*                                                                             *
* Distributed under the terms of the BSD 3-Clause License.                    *
*                                                                             *
* The full license is in the file LICENSE, distributed with this software.    *
*******************************************************************************/

#ifndef XLEAFLET_ICON_HPP
#define XLEAFLET_ICON_HPP

#include <array>
#include <string>

#include "xtl/xoptional.hpp"

#include "xwidgets/xmaterialize.hpp"
#include "xwidgets/xwidget.hpp"

#include "xui_layer.hpp"

namespace nl = nlohmann;

namespace xlf
{
    /********************
     * icon declaration *
     ********************/

    template <class D>
    class xicon : public xui_layer<D>
    {
    public:

        using size_type = std::array<int, 2>;

        using base_type = xui_layer<D>;
        using derived_type = D;

        void serialize_state(nl::json&, xeus::buffer_sequence&) const;
        void apply_patch(const nl::json&, const xeus::buffer_sequence&);

        XPROPERTY(std::string, derived_type, icon_url, "");
        XPROPERTY(xtl::xoptional<std::string>, derived_type, shadow_url);
        XPROPERTY(xtl::xoptional<size_type>, derived_type, icon_size);
        XPROPERTY(xtl::xoptional<size_type>, derived_type, shadow_size);
        XPROPERTY(xtl::xoptional<size_type>, derived_type, icon_anchor);
        XPROPERTY(xtl::xoptional<size_type>, derived_type, shadow_anchor);
        XPROPERTY(xtl::xoptional<size_type>, derived_type, popup_anchor);

    protected:

        xicon();
        using base_type::base_type;

    private:

        void set_defaults();
    };

    using icon = xw::xmaterialize<xicon>;

    /************************
     * xicon implementation *
     ************************/

    template <class D>
    inline void xicon<D>::serialize_state(nl::json& state,
                                            xeus::buffer_sequence& buffers) const
    {
        base_type::serialize_state(state, buffers);

        using xw::xwidgets_serialize;

        xwidgets_serialize(icon_url(), state["icon_url"], buffers);
        xwidgets_serialize(shadow_url(), state["shadow_url"], buffers);
        xwidgets_serialize(icon_size(), state["icon_size"], buffers);
        xwidgets_serialize(shadow_size(), state["shadow_size"], buffers);
        xwidgets_serialize(icon_anchor(), state["icon_anchor"], buffers);
        xwidgets_serialize(shadow_anchor(), state["shadow_anchor"], buffers);
        xwidgets_serialize(popup_anchor(), state["popup_anchor"], buffers);
    }

    template <class D>
    inline void xicon<D>::apply_patch(const nl::json& patch,
                                        const xeus::buffer_sequence& buffers)
    {
        base_type::apply_patch(patch, buffers);

        using xw::set_property_from_patch;

        set_property_from_patch(icon_url, patch, buffers);
        set_property_from_patch(shadow_url, patch, buffers);
        set_property_from_patch(icon_size, patch, buffers);
        set_property_from_patch(shadow_size, patch, buffers);
        set_property_from_patch(icon_anchor, patch, buffers);
        set_property_from_patch(shadow_anchor, patch, buffers);
        set_property_from_patch(popup_anchor, patch, buffers);
    }

    template <class D>
    inline xicon<D>::xicon()
        : base_type()
    {
        set_defaults();
    }

    template <class D>
    inline void xicon<D>::set_defaults()
    {
        this->_model_name() = "LeafletIconModel";
        this->_view_name() = "LeafletIconView";

        this->icon_size() = size_type({10, 10});
        this->shadow_size() = size_type({10, 10});
        this->icon_anchor() = size_type({0, 0});
        this->shadow_anchor() = size_type({0, 0});
        this->popup_anchor() = size_type({0, 0});

        this->options().insert(
            this->options().end(),
            {
                "icon_url",
                "shadow_url",
                "icon_size",
                "shadow_size",
                "icon_anchor",
                "shadow_anchor",
                "popup_anchor"
            }
        );
    }
}

/*********************
 * precompiled types *
 *********************/

    extern template class xw::xmaterialize<xlf::xicon>;
    extern template class xw::xtransport<xw::xmaterialize<xlf::xicon>>;

#endif
