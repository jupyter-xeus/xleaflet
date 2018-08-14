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

#include <string>
#include <vector>

#include "xwidgets/xholder.hpp"
#include "xwidgets/xmaterialize.hpp"
#include "xwidgets/xwidget.hpp"

#include "xcontrol.hpp"
#include "xfeature_group.hpp"
#include "xleaflet_config.hpp"

namespace xlf
{
    /****************************
     * draw_control declaration *
     ****************************/

    template <class D>
    class xdraw_control : public xcontrol<D>
    {
    public:

        using draw_callback_type = std::function<void(const std::string&, const xeus::xjson&)>;

        using base_type = xcontrol<D>;
        using derived_type = D;

        using feature_group_type = xw::xholder<xfeature_group>;

        void serialize_state(xeus::xjson&, xeus::buffer_sequence&) const;
        void apply_patch(const xeus::xjson&, const xeus::buffer_sequence&);

        void on_draw(draw_callback_type);

        void handle_custom_message(const xeus::xjson&);

        XPROPERTY(feature_group_type, derived_type, layer);
        XPROPERTY(xeus::xjson, derived_type, polyline);
        XPROPERTY(xeus::xjson, derived_type, polygon);
        XPROPERTY(xeus::xjson, derived_type, circle);
        XPROPERTY(xeus::xjson, derived_type, rectangle);
        XPROPERTY(xeus::xjson, derived_type, marker);
        XPROPERTY(bool, derived_type, edit, true);
        XPROPERTY(bool, derived_type, remove, true);
        XPROPERTY(xeus::xjson, derived_type, last_draw, {});
        XPROPERTY(std::string, derived_type, last_action, "");

    protected:

        xdraw_control();
        using base_type::base_type;

    private:

        void set_defaults();

        std::list<draw_callback_type> m_draw_callbacks;
    };

    using draw_control = xw::xmaterialize<xdraw_control>;

    using draw_control_generator = xw::xgenerator<xdraw_control>;

    /********************************
     * xdraw_control implementation *
     ********************************/

    template <class D>
    inline void xdraw_control<D>::serialize_state(xeus::xjson& state,
                                                  xeus::buffer_sequence& buffers) const
    {
        base_type::serialize_state(state, buffers);

        using xw::set_patch_from_property;

        set_patch_from_property(layer, state, buffers);
        set_patch_from_property(polyline, state, buffers);
        set_patch_from_property(polygon, state, buffers);
        set_patch_from_property(circle, state, buffers);
        set_patch_from_property(rectangle, state, buffers);
        set_patch_from_property(marker, state, buffers);
        set_patch_from_property(edit, state, buffers);
        set_patch_from_property(remove, state, buffers);
        set_patch_from_property(last_draw, state, buffers);
        set_patch_from_property(last_action, state, buffers);
    }

    template <class D>
    inline void xdraw_control<D>::apply_patch(const xeus::xjson& patch,
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
    inline void xdraw_control<D>::handle_custom_message(const xeus::xjson& content)
    {
        auto it = content.find("event");
        if (it != content.end() && it.value().get<std::string>().find("draw") == 0)
        {
            std::string value = it.value().get<std::string>();
            std::string action = value.substr(value.find(":") + 1, std::string::npos);
            xeus::xjson geo_json_content = content["geo_json"];

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
    extern template class xw::xgenerator<xlf::xdraw_control>;
    extern template xw::xgenerator<xlf::xdraw_control>::xgenerator();
    extern template class xw::xtransport<xw::xgenerator<xlf::xdraw_control>>;
#endif

#endif
