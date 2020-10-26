/******************************************************************************
* Copyright (c) 2018, Sylvain Corlay and Johan Mabille, and Wolf Vollprecht   *
*                                                                             *
* Distributed under the terms of the BSD 3-Clause License.                    *
*                                                                             *
* The full license is in the file LICENSE, distributed with this software.    *
*******************************************************************************/

#ifndef XLEAFLET_MARKER_HPP
#define XLEAFLET_MARKER_HPP

#include <array>
#include <functional>
#include <list>
#include <string>

#include "xtl/xoptional.hpp"

#include "xwidgets/xmaterialize.hpp"
#include "xwidgets/xholder.hpp"
#include "xwidgets/xwidget.hpp"

#include "xui_layer.hpp"
#include "xicon.hpp"

namespace nl = nlohmann;

namespace xlf
{
    /**********************
     * marker declaration *
     **********************/

    template <class D>
    class xmarker : public xui_layer<D>
    {
    public:

        using move_callback_type = std::function<void(const nl::json&)>;

        using point_type = std::array<double, 2>;
        using icon_type = xw::xholder<xicon>;

        using base_type = xui_layer<D>;
        using derived_type = D;

        void serialize_state(nl::json&, xeus::buffer_sequence&) const;
        void apply_patch(const nl::json&, const xeus::buffer_sequence&);

        void on_move(move_callback_type);

        void handle_custom_message(const nl::json&);

        XPROPERTY(point_type, derived_type, location);
        XPROPERTY(int, derived_type, z_index_offset, 0.0);
        XPROPERTY(bool, derived_type, draggable, true);
        XPROPERTY(bool, derived_type, keyboard, true);
        XPROPERTY(std::string, derived_type, title, "");
        XPROPERTY(std::string, derived_type, alt, "");
        XPROPERTY(bool, derived_type, rise_on_hover, false);
        // TODO: bounded between 0.0 and 1.0
        XPROPERTY(double, derived_type, opacity, 1.0);
        XPROPERTY(bool, derived_type, visible, true);
        XPROPERTY(xtl::xoptional<icon_type>, derived_type, icon);
        XPROPERTY(double, derived_type, rotation_angle, 0.);
        XPROPERTY(std::string, derived_type, rotation_origin, "");
        XPROPERTY(int, derived_type, rise_offset, 250);

    protected:

        xmarker();
        using base_type::base_type;

    private:

        void set_defaults();

        std::list<move_callback_type> m_move_callbacks;
    };

    using marker = xw::xmaterialize<xmarker>;

    /******************************
     * xmarker implementation *
     ******************************/

    template <class D>
    inline void xmarker<D>::serialize_state(nl::json& state,
                                            xeus::buffer_sequence& buffers) const
    {
        base_type::serialize_state(state, buffers);

        using xw::xwidgets_serialize;

        xwidgets_serialize(location(), state["location"], buffers);
        xwidgets_serialize(z_index_offset(), state["z_index_offset"], buffers);
        xwidgets_serialize(draggable(), state["draggable"], buffers);
        xwidgets_serialize(keyboard(), state["keyboard"], buffers);
        xwidgets_serialize(title(), state["title"], buffers);
        xwidgets_serialize(alt(), state["alt"], buffers);
        xwidgets_serialize(rise_on_hover(), state["rise_on_hover"], buffers);
        xwidgets_serialize(opacity(), state["opacity"], buffers);
        xwidgets_serialize(visible(), state["visible"], buffers);
        xwidgets_serialize(icon(), state["icon"], buffers);
        xwidgets_serialize(rotation_angle(), state["rotation_angle"], buffers);
        xwidgets_serialize(rotation_origin(), state["rotation_origin"], buffers);
        xwidgets_serialize(rise_offset(), state["rise_offset"], buffers);
    }

    template <class D>
    inline void xmarker<D>::apply_patch(const nl::json& patch,
                                        const xeus::buffer_sequence& buffers)
    {
        base_type::apply_patch(patch, buffers);

        using xw::set_property_from_patch;

        set_property_from_patch(location, patch, buffers);
        set_property_from_patch(z_index_offset, patch, buffers);
        set_property_from_patch(draggable, patch, buffers);
        set_property_from_patch(keyboard, patch, buffers);
        set_property_from_patch(title, patch, buffers);
        set_property_from_patch(alt, patch, buffers);
        set_property_from_patch(rise_on_hover, patch, buffers);
        set_property_from_patch(opacity, patch, buffers);
        set_property_from_patch(visible, patch, buffers);
        set_property_from_patch(icon, patch, buffers);
        set_property_from_patch(rotation_angle, patch, buffers);
        set_property_from_patch(rotation_origin, patch, buffers);
        set_property_from_patch(rise_offset, patch, buffers);
    }

    template <class D>
    inline void xmarker<D>::on_move(move_callback_type callback)
    {
        m_move_callbacks.emplace_back(std::move(callback));
    }

    template <class D>
    inline xmarker<D>::xmarker()
        : base_type()
    {
        set_defaults();
    }

    template <class D>
    inline void xmarker<D>::set_defaults()
    {
        this->_model_name() = "LeafletMarkerModel";
        this->_view_name() = "LeafletMarkerView";

        this->location() = {0, 0};

        this->options().insert(
            this->options().end(),
            {
                "z_index_offset",
                "draggable",
                "keyboard",
                "title",
                "alt",
                "rise_on_hover",
                "rise_offset",
                "rotation_angle",
                "rotation_origin"
            }
        );
    }

    template <class D>
    inline void xmarker<D>::handle_custom_message(const nl::json& content)
    {
        auto it = content.find("event");
        if (it != content.end() && it.value() == "move")
        {
            for (auto it = m_move_callbacks.begin(); it != m_move_callbacks.end(); ++it)
            {
                it->operator()(content);
            }
        }
    }
}

/*********************
 * precompiled types *
 *********************/

    extern template class xw::xmaterialize<xlf::xmarker>;
    extern template class xw::xtransport<xw::xmaterialize<xlf::xmarker>>;

#endif
