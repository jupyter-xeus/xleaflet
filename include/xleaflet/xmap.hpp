/******************************************************************************
* Copyright (c) 2018, Sylvain Corlay and Johan Mabille, and Wolf Vollprecht   *
*                                                                             *
* Distributed under the terms of the BSD 3-Clause License.                    *
*                                                                             *
* The full license is in the file LICENSE, distributed with this software.    *
*******************************************************************************/

#ifndef XLEAFLET_MAP_HPP
#define XLEAFLET_MAP_HPP

#include <array>
#include <functional>
#include <list>
#include <string>
#include <utility>
#include <vector>

#include "xtl/xoptional.hpp"

#include "xwidgets/xcolor.hpp"
#include "xwidgets/xeither.hpp"
#include "xwidgets/xmaterialize.hpp"
#include "xwidgets/xstyle.hpp"
#include "xwidgets/xobject.hpp"
#include "xwidgets/xholder.hpp"
#include "xwidgets/xwidget.hpp"

#include "xleaflet_config.hpp"
#include "xlayer.hpp"
#include "xtile_layer.hpp"
#include "xcontrol.hpp"

namespace xleaflet
{
    /*******************
     * map declaration *
     *******************/

    template <class D>
    class xmap : public xw::xwidget<D>
    {
    public:

        using click_callback_type = std::function<void()>;

        using point_type = std::array<double, 2>;
        using bounds_type = std::array<point_type, 2>;
        using bounds_polygon_type = std::array<point_type, 4>;

        using base_type = xw::xwidget<D>;
        using derived_type = D;

        using layer_list_type = std::vector<xw::xholder<xlayer>>;
        using control_list_type = std::vector<xw::xholder<xcontrol>>;

        xeus::xjson get_state() const;
        void apply_patch(const xeus::xjson&);

        void on_click(click_callback_type);

        template <class T>
        void add_layer(const xlayer<T>& l);

        template <class T>
        void add_layer(xlayer<T>&& l);

        template <class T>
        void remove_layer(const xlayer<T>& l);

        void clear_layers();

        template <class T>
        void add_control(const xcontrol<T>& l);

        template <class T>
        void add_control(xcontrol<T>&& l);

        template <class T>
        void remove_control(const xcontrol<T>& l);

        void clear_controls();

        void handle_custom_message(const xeus::xjson&);

        XPROPERTY(point_type, derived_type, center);
        XPROPERTY(int, derived_type, zoom_start, 12);
        XPROPERTY(int, derived_type, zoom, 12);
        XPROPERTY(int, derived_type, max_zoom, 18);
        XPROPERTY(int, derived_type, min_zoom, 1);
        XPROPERTY(xeus::xjson, derived_type, basemap);
        XPROPERTY(std::string, derived_type, modistate, "yesterday");
        XPROPERTY(bool, derived_type, dragging, true);
        XPROPERTY(bool, derived_type, touch_zoom, true);
        XPROPERTY(bool, derived_type, scroll_wheel_zoom, false);
        XPROPERTY(bool, derived_type, double_click_zoom, true);
        XPROPERTY(bool, derived_type, box_zoom, true);
        XPROPERTY(bool, derived_type, tap, true);
        XPROPERTY(int, derived_type, tap_tolerance, 15);
        XPROPERTY(bool, derived_type, world_copy_jump, false);
        XPROPERTY(bool, derived_type, close_popup_on_click, true);
        XPROPERTY(bool, derived_type, bounce_at_zoom_limits, true);
        XPROPERTY(bool, derived_type, keyboard, true);
        XPROPERTY(int, derived_type, keyboard_pan_offset, 80);
        XPROPERTY(int, derived_type, keyboard_zoom_offset, 1);
        XPROPERTY(bool, derived_type, inertia, true);
        XPROPERTY(int, derived_type, inertia_deceleration, 3000);
        XPROPERTY(int, derived_type, inertia_max_speed, 1500);
        XPROPERTY(bool, derived_type, zoom_control, true);
        XPROPERTY(bool, derived_type, attribution_control, true);
        XPROPERTY(int, derived_type, zoom_animation_threshold, 4);

        XPROPERTY(std::vector<std::string>, derived_type, options);

        XPROPERTY(bounds_type, derived_type, bounds)
        XPROPERTY(bounds_polygon_type, derived_type, bounds_polygon)
        XPROPERTY(layer_list_type, derived_type, layers);
        XPROPERTY(control_list_type, derived_type, controls);

    protected:

        xmap();
        using base_type::base_type;

    private:

        void set_defaults();

        std::list<click_callback_type> m_click_callbacks;
    };

    using map = xw::xmaterialize<xmap>;

    using map_generator = xw::xgenerator<xmap>;

    /***********************
     * xmap implementation *
     ***********************/

    template <class D>
    inline xeus::xjson xmap<D>::get_state() const
    {
        xeus::xjson state = base_type::get_state();

        XOBJECT_SET_PATCH_FROM_PROPERTY(center, state);
        XOBJECT_SET_PATCH_FROM_PROPERTY(zoom_start, state);
        XOBJECT_SET_PATCH_FROM_PROPERTY(zoom, state);
        XOBJECT_SET_PATCH_FROM_PROPERTY(max_zoom, state);
        XOBJECT_SET_PATCH_FROM_PROPERTY(min_zoom, state);
        XOBJECT_SET_PATCH_FROM_PROPERTY(basemap, state);
        XOBJECT_SET_PATCH_FROM_PROPERTY(modistate, state);
        XOBJECT_SET_PATCH_FROM_PROPERTY(dragging, state);
        XOBJECT_SET_PATCH_FROM_PROPERTY(touch_zoom, state);
        XOBJECT_SET_PATCH_FROM_PROPERTY(scroll_wheel_zoom, state);
        XOBJECT_SET_PATCH_FROM_PROPERTY(double_click_zoom, state);
        XOBJECT_SET_PATCH_FROM_PROPERTY(box_zoom, state);
        XOBJECT_SET_PATCH_FROM_PROPERTY(tap, state);
        XOBJECT_SET_PATCH_FROM_PROPERTY(tap_tolerance, state);
        XOBJECT_SET_PATCH_FROM_PROPERTY(world_copy_jump, state);
        XOBJECT_SET_PATCH_FROM_PROPERTY(close_popup_on_click, state);
        XOBJECT_SET_PATCH_FROM_PROPERTY(keyboard, state);
        XOBJECT_SET_PATCH_FROM_PROPERTY(keyboard_pan_offset, state);
        XOBJECT_SET_PATCH_FROM_PROPERTY(keyboard_zoom_offset, state);
        XOBJECT_SET_PATCH_FROM_PROPERTY(inertia, state);
        XOBJECT_SET_PATCH_FROM_PROPERTY(inertia_deceleration, state);
        XOBJECT_SET_PATCH_FROM_PROPERTY(inertia_max_speed, state);
        XOBJECT_SET_PATCH_FROM_PROPERTY(zoom_control, state);
        XOBJECT_SET_PATCH_FROM_PROPERTY(attribution_control, state);
        XOBJECT_SET_PATCH_FROM_PROPERTY(zoom_animation_threshold, state);
        XOBJECT_SET_PATCH_FROM_PROPERTY(options, state);
        XOBJECT_SET_PATCH_FROM_PROPERTY(bounds, state);
        XOBJECT_SET_PATCH_FROM_PROPERTY(bounds_polygon, state);
        XOBJECT_SET_PATCH_FROM_PROPERTY(layers, state);
        XOBJECT_SET_PATCH_FROM_PROPERTY(controls, state);

        return state;
    }

    template <class D>
    inline void xmap<D>::apply_patch(const xeus::xjson& patch)
    {
        base_type::apply_patch(patch);

        XOBJECT_SET_PROPERTY_FROM_PATCH(center, patch);
        XOBJECT_SET_PROPERTY_FROM_PATCH(zoom_start, patch);
        XOBJECT_SET_PROPERTY_FROM_PATCH(zoom, patch);
        XOBJECT_SET_PROPERTY_FROM_PATCH(max_zoom, patch);
        XOBJECT_SET_PROPERTY_FROM_PATCH(min_zoom, patch);
        XOBJECT_SET_PROPERTY_FROM_PATCH(basemap, patch);
        XOBJECT_SET_PROPERTY_FROM_PATCH(modistate, patch);
        XOBJECT_SET_PROPERTY_FROM_PATCH(dragging, patch);
        XOBJECT_SET_PROPERTY_FROM_PATCH(touch_zoom, patch);
        XOBJECT_SET_PROPERTY_FROM_PATCH(scroll_wheel_zoom, patch);
        XOBJECT_SET_PROPERTY_FROM_PATCH(double_click_zoom, patch);
        XOBJECT_SET_PROPERTY_FROM_PATCH(box_zoom, patch);
        XOBJECT_SET_PROPERTY_FROM_PATCH(tap, patch);
        XOBJECT_SET_PROPERTY_FROM_PATCH(tap_tolerance, patch);
        XOBJECT_SET_PROPERTY_FROM_PATCH(world_copy_jump, patch);
        XOBJECT_SET_PROPERTY_FROM_PATCH(close_popup_on_click, patch);
        XOBJECT_SET_PROPERTY_FROM_PATCH(keyboard, patch);
        XOBJECT_SET_PROPERTY_FROM_PATCH(keyboard_pan_offset, patch);
        XOBJECT_SET_PROPERTY_FROM_PATCH(keyboard_zoom_offset, patch);
        XOBJECT_SET_PROPERTY_FROM_PATCH(inertia, patch);
        XOBJECT_SET_PROPERTY_FROM_PATCH(inertia_deceleration, patch);
        XOBJECT_SET_PROPERTY_FROM_PATCH(inertia_max_speed, patch);
        XOBJECT_SET_PROPERTY_FROM_PATCH(zoom_control, patch);
        XOBJECT_SET_PROPERTY_FROM_PATCH(attribution_control, patch);
        XOBJECT_SET_PROPERTY_FROM_PATCH(zoom_animation_threshold, patch);
        XOBJECT_SET_PROPERTY_FROM_PATCH(options, patch);
        XOBJECT_SET_PROPERTY_FROM_PATCH(bounds, patch);
        XOBJECT_SET_PROPERTY_FROM_PATCH(bounds_polygon, patch);
        XOBJECT_SET_PROPERTY_FROM_PATCH(layers, patch);
        XOBJECT_SET_PROPERTY_FROM_PATCH(controls, patch);
    }

    template <class D>
    inline void xmap<D>::on_click(click_callback_type cb)
    {
        m_click_callbacks.emplace_back(std::move(cb));
    }

    template <class D>
    template <class T>
    inline void xmap<D>::add_layer(const xlayer<T>& l)
    {
        this->layers().emplace_back(xw::make_id_holder<xlayer>(l.id()));
        xeus::xjson state;
        XOBJECT_SET_PATCH_FROM_PROPERTY(layers, state);
        this->send_patch(std::move(state));
    }

    template <class D>
    template <class T>
    inline void xmap<D>::add_layer(xlayer<T>&& l)
    {
        this->layers().emplace_back(xw::make_owning_holder(std::move(l)));
        xeus::xjson state;
        XOBJECT_SET_PATCH_FROM_PROPERTY(layers, state);
        this->send_patch(std::move(state));
    }

    template <class D>
    template <class T>
    inline void xmap<D>::remove_layer(const xlayer<T>& l)
    {
        this->layers().erase(
            std::remove_if(
                this->layers().begin(), this->layers().end(),
                [&l](const xw::xholder<xlayer>& element) {
                    return element.id() == l.id();
                }
            ),
            this->layers().end()
        );
        xeus::xjson state;
        XOBJECT_SET_PATCH_FROM_PROPERTY(layers, state);
        this->send_patch(std::move(state));
    }

    template <class D>
    inline void xmap<D>::clear_layers()
    {
        this->layers() = {};
        xeus::xjson state;
        XOBJECT_SET_PATCH_FROM_PROPERTY(layers, state);
        this->send_patch(std::move(state));
    }

    template <class D>
    template <class T>
    inline void xmap<D>::add_control(const xcontrol<T>& c)
    {
        this->controls().emplace_back(xw::make_id_holder<xcontrol>(c.id()));
        xeus::xjson state;
        XOBJECT_SET_PATCH_FROM_PROPERTY(controls, state);
        this->send_patch(std::move(state));
    }

    template <class D>
    template <class T>
    inline void xmap<D>::add_control(xcontrol<T>&& c)
    {
        this->controls().emplace_back(xw::make_owning_holder(std::move(c)));
        xeus::xjson state;
        XOBJECT_SET_PATCH_FROM_PROPERTY(controls, state);
        this->send_patch(std::move(state));
    }

    template <class D>
    template <class T>
    inline void xmap<D>::remove_control(const xcontrol<T>& c)
    {
        this->controls().erase(
            std::remove_if(
                this->controls().begin(), this->controls().end(),
                [&c](const xw::xholder<xcontrol>& element) {
                    return element.id() == c.id();
                }
            ),
            this->controls().end()
        );
        xeus::xjson state;
        XOBJECT_SET_PATCH_FROM_PROPERTY(controls, state);
        this->send_patch(std::move(state));
    }

    template <class D>
    inline void xmap<D>::clear_controls()
    {
        this->controls() = {};
        xeus::xjson state;
        XOBJECT_SET_PATCH_FROM_PROPERTY(controls, state);
        this->send_patch(std::move(state));
    }

    template <class D>
    inline xmap<D>::xmap()
        : base_type()
    {
        set_defaults();
    }

    template <class D>
    inline void xmap<D>::set_defaults()
    {
        this->_model_module() = "jupyter-leaflet";
        this->_view_module() = "jupyter-leaflet";
        this->_model_name() = "LeafletMapModel";
        this->_view_name() = "LeafletMapView";
        this->_model_module_version() = XJUPYTER_LEAFLET_VERSION;
        this->_view_module_version() = XJUPYTER_LEAFLET_VERSION;

        this->options() = std::vector<std::string>({
            "center",
            "zoom_start",
            "zoom",
            "max_zoom",
            "min_zoom",
            "basemap",
            "dragging",
            "touch_zoom",
            "scroll_wheel_zoom",
            "double_click_zoom",
            "box_zoom",
            "tap",
            "tap_tolerance",
            "world_copy_jump",
            "close_popup_on_click",
            "bounce_at_zoom_limits",
            "keyboard",
            "keyboard_pan_offset",
            "keyboard_zoom_offset",
            "inertia",
            "inertia_deceleration",
            "inertia_max_speed",
            "zoom_control",
            "attribution_control",
            "zoom_animation_threshold",
        });
        this->basemap() = {
            {"url", "https://{s}.tile.openstreetmap.org/{z}/{x}/{y}.png"},
            {"max_zoom", 19},
            {"attribution", "BLA"}
        };
        this->center() = {0, 0};
        this->bounds() = {{{0, 0}, {0, 0}}};
        this->bounds_polygon() = {{{0, 0}, {0, 0}, {0, 0}, {0, 0}}};

        // Set default layer
        auto default_layer = xleaflet::tile_layer();
        default_layer.send_patch(std::move(this->basemap()));
        this->add_layer(std::move(default_layer));
    }

    template <class D>
    inline void xmap<D>::handle_custom_message(const xeus::xjson& content)
    {
        auto it = content.find("event");
        if (it != content.end() && it.value() == "click")
        {
            for (auto it = m_click_callbacks.begin(); it != m_click_callbacks.end(); ++it)
            {
                it->operator()();
            }
        }
    }
}

/*********************
 * precompiled types *
 *********************/

#ifndef _WIN32
    extern template class xw::xmaterialize<xleaflet::xmap>;
    extern template xw::xmaterialize<xleaflet::xmap>::xmaterialize();
    extern template class xw::xtransport<xw::xmaterialize<xleaflet::xmap>>;
    extern template class xw::xgenerator<xleaflet::xmap>;
    extern template xw::xgenerator<xleaflet::xmap>::xgenerator();
    extern template class xw::xtransport<xw::xgenerator<xleaflet::xmap>>;
#endif

#endif
