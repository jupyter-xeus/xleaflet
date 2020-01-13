/******************************************************************************
* Copyright (c) 2018, Sylvain Corlay and Johan Mabille, Wolf Vollprecht and   *
* Martin Renou                                                                *
*                                                                             *
* Distributed under the terms of the BSD 3-Clause License.                    *
*                                                                             *
* The full license is in the file LICENSE, distributed with this software.    *
*******************************************************************************/

#ifndef XLEAFLET_DRAW_CONTROL_HPP
#define XLEAFLET_DRAW_CONTROL_HPP

#include <functional>
#include <list>
#include <string>
#include <utility>
#include <vector>

#include "nlohmann/json.hpp"

#include "xwidgets/xholder.hpp"
#include "xwidgets/xmaterialize.hpp"
#include "xwidgets/xwidget.hpp"

#include "xcontrol.hpp"
#include "xfeature_group.hpp"
#include "xleaflet_config.hpp"

namespace nl = nlohmann;

namespace xlf
{
    /****************************
     * draw_control declaration *
     ****************************/

    template <class D>
    class xdraw_control : public xcontrol<D>
    {
    public:

        using draw_callback_type = std::function<void(const std::string&, const nl::json&)>;

        using base_type = xcontrol<D>;
        using derived_type = D;

        using feature_group_type = xw::xholder<xfeature_group>;

        void serialize_state(nl::json&, xeus::buffer_sequence&) const;
        void apply_patch(const nl::json&, const xeus::buffer_sequence&);

        void on_draw(draw_callback_type);

        void handle_custom_message(const nl::json&);

        XPROPERTY(feature_group_type, derived_type, layer);
        XPROPERTY(nl::json, derived_type, polyline);
        XPROPERTY(nl::json, derived_type, polygon);
        XPROPERTY(nl::json, derived_type, circle);
        XPROPERTY(nl::json, derived_type, rectangle);
        XPROPERTY(nl::json, derived_type, marker);
        XPROPERTY(bool, derived_type, edit, true);
        XPROPERTY(bool, derived_type, remove, true);
        XPROPERTY(nl::json, derived_type, last_draw, {});
        XPROPERTY(std::string, derived_type, last_action, "");

    protected:

        xdraw_control();
        using base_type::base_type;

    private:

        void set_defaults();

        std::list<draw_callback_type> m_draw_callbacks;
    };

    using draw_control = xw::xmaterialize<xdraw_control>;

    /********************************
     * xdraw_control implementation *
     ********************************/

    template <class D>
    inline void xdraw_control<D>::serialize_state(nl::json& state,
                                                  xeus::buffer_sequence& buffers) const
    {
        base_type::serialize_state(state, buffers);

        using xw::xwidgets_serialize;

        xwidgets_serialize(layer(), state["layer"], buffers);
        xwidgets_serialize(polyline(), state["polyline"], buffers);
        xwidgets_serialize(polygon(), state["polygon"], buffers);
        xwidgets_serialize(circle(), state["circle"], buffers);
        xwidgets_serialize(rectangle(), state["rectangle"], buffers);
        xwidgets_serialize(marker(), state["marker"], buffers);
        xwidgets_serialize(edit(), state["edit"], buffers);
        xwidgets_serialize(remove(), state["remove"], buffers);
        xwidgets_serialize(last_draw(), state["last_draw"], buffers);
        xwidgets_serialize(last_action(), state["last_action"], buffers);
    }

    template <class D>
    inline void xdraw_control<D>::apply_patch(const nl::json& patch,
                                              const xeus::buffer_sequence& buffers)
    {
        base_type::apply_patch(patch, buffers);

        using xw::set_property_from_patch;

        set_property_from_patch(layer, patch, buffers);
        set_property_from_patch(polyline, patch, buffers);
        set_property_from_patch(polygon, patch, buffers);
        set_property_from_patch(circle, patch, buffers);
        set_property_from_patch(rectangle, patch, buffers);
        set_property_from_patch(marker, patch, buffers);
        set_property_from_patch(edit, patch, buffers);
        set_property_from_patch(remove, patch, buffers);
        set_property_from_patch(last_draw, patch, buffers);
        set_property_from_patch(last_action, patch, buffers);
    }

    template <class D>
    inline void xdraw_control<D>::on_draw(draw_callback_type callback)
    {
        m_draw_callbacks.emplace_back(std::move(callback));
    }

    template <class D>
    inline xdraw_control<D>::xdraw_control()
        : base_type()
    {
        set_defaults();
    }

    template <class D>
    inline void xdraw_control<D>::set_defaults()
    {
        this->_model_name() = "LeafletDrawControlModel";
        this->_view_name() = "LeafletDrawControlView";

        this->layer() = feature_group();
        this->polyline() = {"shapeOptions", {}};
        this->polygon() = {"shapeOptions", {}};
    }

    template <class D>
    inline void xdraw_control<D>::handle_custom_message(const nl::json& content)
    {
        auto it = content.find("event");
        if (it != content.end() && it.value().get<std::string>().find("draw") == 0)
        {
            std::string value = it.value().get<std::string>();
            std::string action = value.substr(value.find(":") + 1, std::string::npos);
            nl::json geo_json_content = content["geo_json"];

            this->last_action() = action;
            this->last_draw() = geo_json_content;

            for (auto it = m_draw_callbacks.begin(); it != m_draw_callbacks.end(); ++it)
            {
                it->operator()(std::move(action), std::move(geo_json_content));
            }
        }
    }
}

/*********************
 * precompiled types *
 *********************/

#ifndef _WIN32
    extern template class xw::xmaterialize<xlf::xdraw_control>;
    extern template xw::xmaterialize<xlf::xdraw_control>::xmaterialize();
    extern template class xw::xtransport<xw::xmaterialize<xlf::xdraw_control>>;
#endif

#endif
