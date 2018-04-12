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

#include "xwidgets/xmaterialize.hpp"
#include "xwidgets/xholder.hpp"
#include "xwidgets/xwidget.hpp"

#include "xleaflet_config.hpp"
#include "xfeature_group.hpp"
#include "xcontrol.hpp"

namespace xleaflet
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

        xeus::xjson get_state() const;
        void apply_patch(const xeus::xjson&);

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
     inline xeus::xjson xdraw_control<D>::get_state() const
     {
         xeus::xjson state = base_type::get_state();

         XOBJECT_SET_PATCH_FROM_PROPERTY(layer, state);
         XOBJECT_SET_PATCH_FROM_PROPERTY(polyline, state);
         XOBJECT_SET_PATCH_FROM_PROPERTY(polygon, state);
         XOBJECT_SET_PATCH_FROM_PROPERTY(circle, state);
         XOBJECT_SET_PATCH_FROM_PROPERTY(rectangle, state);
         XOBJECT_SET_PATCH_FROM_PROPERTY(marker, state);
         XOBJECT_SET_PATCH_FROM_PROPERTY(edit, state);
         XOBJECT_SET_PATCH_FROM_PROPERTY(remove, state);
         XOBJECT_SET_PATCH_FROM_PROPERTY(last_draw, state);
         XOBJECT_SET_PATCH_FROM_PROPERTY(last_action, state);

         return state;
     }

     template <class D>
     inline void xdraw_control<D>::apply_patch(const xeus::xjson& patch)
     {
         base_type::apply_patch(patch);

         XOBJECT_SET_PROPERTY_FROM_PATCH(layer, patch);
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
            std::string action = value.substr(
                value.find(":") + 1,
                std::string::npos
            );
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
    extern template class xw::xmaterialize<xleaflet::xdraw_control>;
    extern template xw::xmaterialize<xleaflet::xdraw_control>::xmaterialize();
    extern template class xw::xtransport<xw::xmaterialize<xleaflet::xdraw_control>>;
    extern template class xw::xgenerator<xleaflet::xdraw_control>;
    extern template xw::xgenerator<xleaflet::xdraw_control>::xgenerator();
    extern template class xw::xtransport<xw::xgenerator<xleaflet::xdraw_control>>;
#endif

#endif
