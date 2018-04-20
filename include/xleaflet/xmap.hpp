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
#include "xbasemaps.hpp"

namespace xlf
{
    /*******************
     * map declaration *
     *******************/

    template <class D>
    class xmap : public xw::xwidget<D>
    {
    public:

        using callback_type = std::function<void(const xeus::xjson&)>;

        using point_type = std::array<double, 2>;
        using bounds_type = std::array<point_type, 2>;
        using bounds_polygon_type = std::array<point_type, 4>;

        using base_type = xw::xwidget<D>;
        using derived_type = D;

        using layer_list_type = std::vector<xw::xholder<xlayer>>;
        using control_list_type = std::vector<xw::xholder<xcontrol>>;

        void serialize_state(xeus::xjson&, xeus::buffer_sequence&) const;
        void apply_patch(const xeus::xjson&, const xeus::buffer_sequence&);

        void on_interaction(callback_type);

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

        std::list<callback_type> m_interaction_callbacks;
    };

    using map = xw::xmaterialize<xmap>;

    using map_generator = xw::xgenerator<xmap>;

    /***********************
     * xmap implementation *
     ***********************/

    template <class D>
    inline void xmap<D>::serialize_state(xeus::xjson& state, xeus::buffer_sequence& buffers) const
    {
        base_type::serialize_state(state, buffers);

        xw::set_patch_from_property(center, state, buffers);
        xw::set_patch_from_property(zoom_start, state, buffers);
        xw::set_patch_from_property(zoom, state, buffers);
        xw::set_patch_from_property(max_zoom, state, buffers);
        xw::set_patch_from_property(min_zoom, state, buffers);
        xw::set_patch_from_property(dragging, state, buffers);
        xw::set_patch_from_property(touch_zoom, state, buffers);
        xw::set_patch_from_property(scroll_wheel_zoom, state, buffers);
        xw::set_patch_from_property(double_click_zoom, state, buffers);
        xw::set_patch_from_property(box_zoom, state, buffers);
        xw::set_patch_from_property(tap, state, buffers);
        xw::set_patch_from_property(tap_tolerance, state, buffers);
        xw::set_patch_from_property(world_copy_jump, state, buffers);
        xw::set_patch_from_property(close_popup_on_click, state, buffers);
        xw::set_patch_from_property(keyboard, state, buffers);
        xw::set_patch_from_property(keyboard_pan_offset, state, buffers);
        xw::set_patch_from_property(keyboard_zoom_offset, state, buffers);
        xw::set_patch_from_property(inertia, state, buffers);
        xw::set_patch_from_property(inertia_deceleration, state, buffers);
        xw::set_patch_from_property(inertia_max_speed, state, buffers);
        xw::set_patch_from_property(zoom_control, state, buffers);
        xw::set_patch_from_property(attribution_control, state, buffers);
        xw::set_patch_from_property(zoom_animation_threshold, state, buffers);
        xw::set_patch_from_property(options, state, buffers);
        xw::set_patch_from_property(bounds, state, buffers);
        xw::set_patch_from_property(bounds_polygon, state, buffers);
        xw::set_patch_from_property(layers, state, buffers);
        xw::set_patch_from_property(controls, state, buffers);
    }

    template <class D>
    inline void xmap<D>::apply_patch(const xeus::xjson& patch, const xeus::buffer_sequence& buffers)
    {
        base_type::apply_patch(patch, buffers);

        xw::set_property_from_patch(center, patch, buffers);
        xw::set_property_from_patch(zoom_start, patch, buffers);
        xw::set_property_from_patch(zoom, patch, buffers);
        xw::set_property_from_patch(max_zoom, patch, buffers);
        xw::set_property_from_patch(min_zoom, patch, buffers);
        xw::set_property_from_patch(dragging, patch, buffers);
        xw::set_property_from_patch(touch_zoom, patch, buffers);
        xw::set_property_from_patch(scroll_wheel_zoom, patch, buffers);
        xw::set_property_from_patch(double_click_zoom, patch, buffers);
        xw::set_property_from_patch(box_zoom, patch, buffers);
        xw::set_property_from_patch(tap, patch, buffers);
        xw::set_property_from_patch(tap_tolerance, patch, buffers);
        xw::set_property_from_patch(world_copy_jump, patch, buffers);
        xw::set_property_from_patch(close_popup_on_click, patch, buffers);
        xw::set_property_from_patch(keyboard, patch, buffers);
        xw::set_property_from_patch(keyboard_pan_offset, patch, buffers);
        xw::set_property_from_patch(keyboard_zoom_offset, patch, buffers);
        xw::set_property_from_patch(inertia, patch, buffers);
        xw::set_property_from_patch(inertia_deceleration, patch, buffers);
        xw::set_property_from_patch(inertia_max_speed, patch, buffers);
        xw::set_property_from_patch(zoom_control, patch, buffers);
        xw::set_property_from_patch(attribution_control, patch, buffers);
        xw::set_property_from_patch(zoom_animation_threshold, patch, buffers);
        xw::set_property_from_patch(options, patch, buffers);
        xw::set_property_from_patch(bounds, patch, buffers);
        xw::set_property_from_patch(bounds_polygon, patch, buffers);
        xw::set_property_from_patch(layers, patch, buffers);
        xw::set_property_from_patch(controls, patch, buffers);
    }

    template <class D>
    inline void xmap<D>::on_interaction(callback_type cb)
    {
        m_interaction_callbacks.emplace_back(std::move(cb));
    }

    template <class D>
    template <class T>
    inline void xmap<D>::add_layer(const xlayer<T>& l)
    {
        this->layers().emplace_back(xw::make_id_holder<xlayer>(l.id()));
        xeus::xjson state;
        xeus::buffer_sequence buffers;
        xw::set_patch_from_property(layers, state, buffers);
        this->send_patch(std::move(state), std::move(buffers));
    }

    template <class D>
    template <class T>
    inline void xmap<D>::add_layer(xlayer<T>&& l)
    {
        this->layers().emplace_back(xw::make_owning_holder(std::move(l)));
        xeus::xjson state;
        xeus::buffer_sequence buffers;
        xw::set_patch_from_property(layers, state, buffers);
        this->send_patch(std::move(state), std::move(buffers));
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
        xeus::buffer_sequence buffers;
        xw::set_patch_from_property(layers, state, buffers);
        this->send_patch(std::move(state), std::move(buffers));
    }

    template <class D>
    inline void xmap<D>::clear_layers()
    {
        this->layers() = {};
        xeus::xjson state;
        xeus::buffer_sequence buffers;
        xw::set_patch_from_property(layers, state, buffers);
        this->send_patch(std::move(state), std::move(buffers));
    }

    template <class D>
    template <class T>
    inline void xmap<D>::add_control(const xcontrol<T>& c)
    {
        this->controls().emplace_back(xw::make_id_holder<xcontrol>(c.id()));
        xeus::xjson state;
        xeus::buffer_sequence buffers;
        xw::set_patch_from_property(controls, state, buffers);
        this->send_patch(std::move(state), std::move(buffers));
    }

    template <class D>
    template <class T>
    inline void xmap<D>::add_control(xcontrol<T>&& c)
    {
        this->controls().emplace_back(xw::make_owning_holder(std::move(c)));
        xeus::xjson state;
        xeus::buffer_sequence buffers;
        xw::set_patch_from_property(controls, state, buffers);
        this->send_patch(std::move(state), std::move(buffers));
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
        xeus::buffer_sequence buffers;
        xw::set_patch_from_property(controls, state, buffers);
        this->send_patch(std::move(state), std::move(buffers));
    }

    template <class D>
    inline void xmap<D>::clear_controls()
    {
        this->controls() = {};
        xeus::xjson state;
        xeus::buffer_sequence buffers;
        xw::set_patch_from_property(controls, state, buffers);
        this->send_patch(std::move(state), std::move(buffers));
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
        this->center() = {0, 0};
        this->bounds() = {{{0, 0}, {0, 0}}};
        this->bounds_polygon() = {{{0, 0}, {0, 0}, {0, 0}, {0, 0}}};

        // Set default layer
        auto default_layer = xlf::basemap({"OpenStreetMap", "Mapnik"});
        this->add_layer(std::move(default_layer));
    }

    template <class D>
    inline void xmap<D>::handle_custom_message(const xeus::xjson& content)
    {
        auto it = content.find("event");
        if (it != content.end() && it.value() == "interaction")
        {
            for (auto it = m_interaction_callbacks.begin(); it != m_interaction_callbacks.end(); ++it)
            {
                it->operator()(content);
            }
        }
    }
}

/*********************
 * precompiled types *
 *********************/

#ifndef _WIN32
    extern template class xw::xmaterialize<xlf::xmap>;
    extern template xw::xmaterialize<xlf::xmap>::xmaterialize();
    extern template class xw::xtransport<xw::xmaterialize<xlf::xmap>>;
    extern template class xw::xgenerator<xlf::xmap>;
    extern template xw::xgenerator<xlf::xmap>::xgenerator();
    extern template class xw::xtransport<xw::xgenerator<xlf::xmap>>;
#endif

#endif
