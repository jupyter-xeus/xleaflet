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

#include "xwidgets/xcolor.hpp"
#include "xwidgets/xeither.hpp"
#include "xwidgets/xholder.hpp"
#include "xwidgets/xmaterialize.hpp"
#include "xwidgets/xobject.hpp"
#include "xwidgets/xstyle.hpp"
#include "xwidgets/xwidget.hpp"

#include "xbasemaps.hpp"
#include "xcontrol.hpp"
#include "xlayer.hpp"
#include "xleaflet_config.hpp"
#include "xtile_layer.hpp"
#include "xzoom_control.hpp"

namespace nl = nlohmann;

namespace xlf
{
    /*******************
     * map declaration *
     *******************/

    template <class D>
    class xmap : public xw::xwidget<D>
    {
    public:

        using callback_type = std::function<void(const nl::json&)>;

        using point_type = std::array<double, 2>;
        using bounds_type = std::array<point_type, 2>;
        using bounds_polygon_type = std::array<point_type, 4>;

        using base_type = xw::xwidget<D>;
        using derived_type = D;

        using layer_list_type = std::vector<xw::xholder>;
        using control_list_type = std::vector<xw::xholder>;

        void serialize_state(nl::json&, xeus::buffer_sequence&) const;
        void apply_patch(const nl::json&, const xeus::buffer_sequence&);

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

        void handle_custom_message(const nl::json&);

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

    /***********************
     * xmap implementation *
     ***********************/

    template <class D>
    inline void xmap<D>::serialize_state(nl::json& state, xeus::buffer_sequence& buffers) const
    {
        base_type::serialize_state(state, buffers);

        using xw::xwidgets_serialize;

        xwidgets_serialize(center(), state["center"], buffers);
        xwidgets_serialize(zoom_start(), state["zoom_start"], buffers);
        xwidgets_serialize(zoom(), state["zoom"], buffers);
        xwidgets_serialize(max_zoom(), state["max_zoom"], buffers);        
        xwidgets_serialize(min_zoom(), state["min_zoom"], buffers);
        xwidgets_serialize(dragging(), state["dragging"], buffers);
        xwidgets_serialize(touch_zoom(), state["touch_zoom"], buffers);
        xwidgets_serialize(scroll_wheel_zoom(), state["scroll_wheel_zoom"], buffers); 
        xwidgets_serialize(double_click_zoom(), state["double_click_zoom"], buffers);
        xwidgets_serialize(box_zoom(), state["box_zoom"], buffers);
        xwidgets_serialize(tap(), state["tap"], buffers);
        xwidgets_serialize(tap_tolerance(), state["tap_tolerance"], buffers); 
        xwidgets_serialize(world_copy_jump(), state["world_copy_jump"], buffers);
        xwidgets_serialize(close_popup_on_click(), state["close_popup_on_click"], buffers); 
        xwidgets_serialize(keyboard(), state["keyboard"], buffers);
        xwidgets_serialize(keyboard_pan_offset(), state["keyboard_pan_offset"], buffers); 
        xwidgets_serialize(keyboard_zoom_offset(), state["keyboard_zoom_offset"], buffers);
        xwidgets_serialize(inertia(), state["inertia"], buffers); 
        xwidgets_serialize(inertia_deceleration(), state["inertia_deceleration"], buffers); 
        xwidgets_serialize(inertia_max_speed(), state["inertia_max_speed"], buffers); 
        xwidgets_serialize(zoom_control(), state["zoom_control"], buffers); 
        xwidgets_serialize(attribution_control(), state["attribution_control"], buffers); 
        xwidgets_serialize(zoom_animation_threshold(), state["zoom_animation_threshold"], buffers); 
        xwidgets_serialize(options(), state["options"], buffers); 
        xwidgets_serialize(bounds(), state["bounds"], buffers); 
        xwidgets_serialize(bounds_polygon(), state["bounds_polygon"], buffers); 
        xwidgets_serialize(layers(), state["layers"], buffers); 
        xwidgets_serialize(controls(), state["controls"], buffers); 
    }

    template <class D>
    inline void xmap<D>::apply_patch(const nl::json& patch, const xeus::buffer_sequence& buffers)
    {
        base_type::apply_patch(patch, buffers);

        using xw::set_property_from_patch;

        set_property_from_patch(center, patch, buffers);
        set_property_from_patch(zoom_start, patch, buffers);
        set_property_from_patch(zoom, patch, buffers);
        set_property_from_patch(max_zoom, patch, buffers);
        set_property_from_patch(min_zoom, patch, buffers);
        set_property_from_patch(dragging, patch, buffers);
        set_property_from_patch(touch_zoom, patch, buffers);
        set_property_from_patch(scroll_wheel_zoom, patch, buffers);
        set_property_from_patch(double_click_zoom, patch, buffers);
        set_property_from_patch(box_zoom, patch, buffers);
        set_property_from_patch(tap, patch, buffers);
        set_property_from_patch(tap_tolerance, patch, buffers);
        set_property_from_patch(world_copy_jump, patch, buffers);
        set_property_from_patch(close_popup_on_click, patch, buffers);
        set_property_from_patch(keyboard, patch, buffers);
        set_property_from_patch(keyboard_pan_offset, patch, buffers);
        set_property_from_patch(keyboard_zoom_offset, patch, buffers);
        set_property_from_patch(inertia, patch, buffers);
        set_property_from_patch(inertia_deceleration, patch, buffers);
        set_property_from_patch(inertia_max_speed, patch, buffers);
        set_property_from_patch(zoom_control, patch, buffers);
        set_property_from_patch(attribution_control, patch, buffers);
        set_property_from_patch(zoom_animation_threshold, patch, buffers);
        set_property_from_patch(options, patch, buffers);
        set_property_from_patch(bounds, patch, buffers);
        set_property_from_patch(bounds_polygon, patch, buffers);
        set_property_from_patch(layers, patch, buffers);
        set_property_from_patch(controls, patch, buffers);
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
        this->layers().emplace_back(xw::make_id_holder(l.id()));
        nl::json state;
        xeus::buffer_sequence buffers;
        using xw::xwidgets_serialize;
        xwidgets_serialize(layers(), state["layers"], buffers);
        this->send_patch(std::move(state), std::move(buffers));
    }

    template <class D>
    template <class T>
    inline void xmap<D>::add_layer(xlayer<T>&& l)
    {
        this->layers().emplace_back(xw::make_owning_holder(std::move(l)));
        nl::json state;
        xeus::buffer_sequence buffers;
        using xw::xwidgets_serialize;
        xwidgets_serialize(layers(), state["layers"], buffers);
        this->send_patch(std::move(state), std::move(buffers));
    }

    template <class D>
    template <class T>
    inline void xmap<D>::remove_layer(const xlayer<T>& l)
    {
        this->layers().erase(
            std::remove_if(
                this->layers().begin(), this->layers().end(),
                [&l](const xw::xholder& element) {
                    return element.id() == l.id();
                }
            ),
            this->layers().end()
        );
        nl::json state;
        xeus::buffer_sequence buffers;
        using xw::xwidgets_serialize;
        xwidgets_serialize(layers(), state["layers"], buffers);
        this->send_patch(std::move(state), std::move(buffers));
    }

    template <class D>
    inline void xmap<D>::clear_layers()
    {
        this->layers() = {};
        nl::json state;
        xeus::buffer_sequence buffers;
        using xw::xwidgets_serialize;
        xwidgets_serialize(layers(), state["layers"], buffers);
        this->send_patch(std::move(state), std::move(buffers));
    }

    template <class D>
    template <class T>
    inline void xmap<D>::add_control(const xcontrol<T>& c)
    {
        this->controls().emplace_back(xw::make_id_holder(c.id()));
        nl::json state;
        xeus::buffer_sequence buffers;
        using xw::xwidgets_serialize;
        xwidgets_serialize(controls(), state["controls"], buffers);
        this->send_patch(std::move(state), std::move(buffers));
    }

    template <class D>
    template <class T>
    inline void xmap<D>::add_control(xcontrol<T>&& c)
    {
        this->controls().emplace_back(xw::make_owning_holder(std::move(c)));
        nl::json state;
        xeus::buffer_sequence buffers;
        using xw::xwidgets_serialize;
        xwidgets_serialize(controls(), state["controls"], buffers);
        this->send_patch(std::move(state), std::move(buffers));
    }

    template <class D>
    template <class T>
    inline void xmap<D>::remove_control(const xcontrol<T>& c)
    {
        this->controls().erase(
            std::remove_if(
                this->controls().begin(), this->controls().end(),
                [&c](const xw::xholder& element) {
                    return element.id() == c.id();
                }
            ),
            this->controls().end()
        );
        nl::json state;
        xeus::buffer_sequence buffers;
        using xw::xwidgets_serialize;
        xwidgets_serialize(controls(), state["controls"], buffers);
        this->send_patch(std::move(state), std::move(buffers));
    }

    template <class D>
    inline void xmap<D>::clear_controls()
    {
        this->controls() = {};
        nl::json state;
        xeus::buffer_sequence buffers;
        using xw::xwidgets_serialize;
        xwidgets_serialize(controls(), state["controls"], buffers);
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
        this->_model_module_version() = jupyter_leaflet_semver();
        this->_view_module_version() = jupyter_leaflet_semver();

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
        this->bounds() = {{{{0, 0}}, {{0, 0}}}};
        this->bounds_polygon() = {{{{0, 0}}, {{0, 0}}, {{0, 0}}, {{0, 0}}}};
        // Set default layer
        auto base_layer = xlf::basemap({"OpenStreetMap", "Mapnik"});
        this->add_layer(std::move(base_layer));
        // Include zoom control
        if (this->zoom_control())
        {
            auto zoom = xlf::zoom_control();
            this->add_control(std::move(zoom));
        } 
    }

    template <class D>
    inline void xmap<D>::handle_custom_message(const nl::json& content)
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

    extern template class xw::xmaterialize<xlf::xmap>;
    extern template class xw::xtransport<xw::xmaterialize<xlf::xmap>>;

#endif
