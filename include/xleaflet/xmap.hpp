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

#ifdef _MSC_VER
        template <class T>
        using layer_type = xlayer<T>;

        using layer_list_type = std::vector<xw::xholder<layer_type>>;
#else
        using layer_list_type = std::vector<xw::xholder<xlayer>>;
#endif

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

        void handle_custom_message(const xeus::xjson&);

        XPROPERTY(xeus::xjson, derived_type, basemap);
        XPROPERTY(point_type, derived_type, center);
        XPROPERTY(int, derived_type, zoom, 12);
        XPROPERTY(int, derived_type, zoom_start, 12);
        XPROPERTY(bounds_type, derived_type, bounds)
        XPROPERTY(bounds_polygon_type, derived_type, bounds_polygon)
        XPROPERTY(std::vector<std::string>, derived_type, options);
        XPROPERTY(std::vector<xw::xholder<xlayer>>, derived_type, layers);

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
        XOBJECT_SET_PATCH_FROM_PROPERTY(zoom, state);
        XOBJECT_SET_PATCH_FROM_PROPERTY(basemap, state);
        XOBJECT_SET_PATCH_FROM_PROPERTY(bounds, state);
        XOBJECT_SET_PATCH_FROM_PROPERTY(bounds_polygon, state);
        XOBJECT_SET_PATCH_FROM_PROPERTY(options, state);
        XOBJECT_SET_PATCH_FROM_PROPERTY(layers, state);

        return state;
    }

    template <class D>
    inline void xmap<D>::apply_patch(const xeus::xjson& patch)
    {
        base_type::apply_patch(patch);

        XOBJECT_SET_PROPERTY_FROM_PATCH(center, patch);
        XOBJECT_SET_PROPERTY_FROM_PATCH(zoom, patch);
        XOBJECT_SET_PROPERTY_FROM_PATCH(basemap, patch);
        XOBJECT_SET_PROPERTY_FROM_PATCH(bounds, patch);
        XOBJECT_SET_PROPERTY_FROM_PATCH(bounds_polygon, patch);
        XOBJECT_SET_PROPERTY_FROM_PATCH(options, patch);
        XOBJECT_SET_PROPERTY_FROM_PATCH(layers, patch);
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
#ifdef _MSC_VER
        this->layers().emplace_back(xw::make_id_holder<layer_type>(l.id()));
#else
        this->layers().emplace_back(xw::make_id_holder<xlayer>(l.id()));
#endif
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
#ifdef _MSC_VER
        template <class T>
        using layer_type = xlayer<T>;

        this->layers().erase(
            std::remove_if(
                this->layers().begin(), this->layers().end(),
                [&l](xw::xholder<layer_type> _l){return _l.id() == l.id();}
            ),
            this->layers().end()
        );
#else
        this->layers().erase(
            std::remove_if(
                this->layers().begin(), this->layers().end(),
                [&l](xw::xholder<xlayer> _l){return _l.id() == l.id();}
            ),
            this->layers().end()
        );
#endif
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
            "attribution_control",
            "basemap",
            "bounce_at_zoom_limits",
            "box_zoom",
            "center",
            "close_popup_on_click",
            "double_click_zoom",
            "dragging",
            "inertia",
            "inertia_deceleration",
            "inertia_max_speed",
            "keyboard",
            "keyboard_pan_offset",
            "keyboard_zoom_offset",
            "max_zoom",
            "min_zoom",
            "scroll_wheel_zoom",
            "tap",
            "tap_tolerance",
            "touch_zoom",
            "world_copy_jump",
            "zoom",
            "zoom_animation_threshold",
            "zoom_control",
            "zoom_start"
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
