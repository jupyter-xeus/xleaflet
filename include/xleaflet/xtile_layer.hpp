/******************************************************************************
* Copyright (c) 2018, Sylvain Corlay and Johan Mabille, and Wolf Vollprecht   *
*                                                                             *
* Distributed under the terms of the BSD 3-Clause License.                    *
*                                                                             *
* The full license is in the file LICENSE, distributed with this software.    *
*******************************************************************************/

#ifndef XLEAFLET_TILE_LAYER_HPP
#define XLEAFLET_TILE_LAYER_HPP

#include <functional>
#include <list>
#include <string>
#include <utility>

#include "xwidgets/xmaterialize.hpp"
#include "xwidgets/xwidget.hpp"

#include "xleaflet_config.hpp"
#include "xraster_layer.hpp"

namespace nl = nlohmann;

namespace xlf
{
    /**************************
     * tile_layer declaration *
     **************************/

    template <class D>
    class xtile_layer : public xraster_layer<D>
    {
    public:

        using load_callback_type = std::function<void(const nl::json&)>;

        using base_type = xraster_layer<D>;
        using derived_type = D;

        void serialize_state(nl::json&, xeus::buffer_sequence&) const;
        void apply_patch(const nl::json&, const xeus::buffer_sequence&);

        void on_load(load_callback_type);

        void handle_custom_message(const nl::json&);

        XPROPERTY(
            std::string, derived_type, url,
            "https://{s}.tile.openstreetmap.org/{z}/{x}/{y}.png");
        XPROPERTY(int, derived_type, min_zoom, 0);
        XPROPERTY(int, derived_type, max_zoom, 18);
        XPROPERTY(int, derived_type, tile_size, 256);
        XPROPERTY(
            std::string, derived_type, attribution,
            "Map data (c) <a href=\"https://openstreetmap.org\">OpenStreetMap</a> contributors");
        XPROPERTY(bool, derived_type, detect_retina, false);

    protected:

        xtile_layer();
        using base_type::base_type;

    private:

        void set_defaults();

        std::list<load_callback_type> m_load_callbacks;
    };

    using tile_layer = xw::xmaterialize<xtile_layer>;

    /******************************
     * xtile_layer implementation *
     ******************************/

    template <class D>
    inline void xtile_layer<D>::serialize_state(nl::json& state,
                                                xeus::buffer_sequence& buffers) const
    {
        base_type::serialize_state(state, buffers);

        using xw::xwidgets_serialize;

        xwidgets_serialize(url(), state["url"], buffers);
        xwidgets_serialize(min_zoom(), state["min_zoom"], buffers);
        xwidgets_serialize(max_zoom(), state["max_zoom"], buffers);
        xwidgets_serialize(tile_size(), state["tile_size"], buffers);
        xwidgets_serialize(attribution(), state["attribution"], buffers);
        xwidgets_serialize(detect_retina(), state["detect_retina"], buffers);
    }

    template <class D>
    inline void xtile_layer<D>::apply_patch(const nl::json& patch,
                                            const xeus::buffer_sequence& buffers)
    {
        base_type::apply_patch(patch, buffers);

        using xw::set_property_from_patch;

        set_property_from_patch(url, patch, buffers);
        set_property_from_patch(min_zoom, patch, buffers);
        set_property_from_patch(max_zoom, patch, buffers);
        set_property_from_patch(tile_size, patch, buffers);
        set_property_from_patch(attribution, patch, buffers);
        set_property_from_patch(detect_retina, patch, buffers);
    }

    template <class D>
    inline void xtile_layer<D>::on_load(load_callback_type callback)
    {
        m_load_callbacks.emplace_back(std::move(callback));
    }

    template <class D>
    inline xtile_layer<D>::xtile_layer()
        : base_type()
    {
        set_defaults();
    }

    template <class D>
    inline void xtile_layer<D>::set_defaults()
    {
        this->_model_name() = "LeafletTileLayerModel";
        this->_view_name() = "LeafletTileLayerView";

        this->bottom() = true;

        this->options().insert(
            this->options().end(),
            {
                "min_zoom",
                "max_zoom",
                "tile_size",
                "attribution",
                "detect_retina"
            }
        );
    }

    template <class D>
    inline void xtile_layer<D>::handle_custom_message(const nl::json& content)
    {
        auto it = content.find("event");
        if (it != content.end() && it.value() == "load")
        {
            for (auto it = m_load_callbacks.begin(); it != m_load_callbacks.end(); ++it)
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
    extern template class xw::xmaterialize<xlf::xtile_layer>;
    extern template xw::xmaterialize<xlf::xtile_layer>::xmaterialize();
    extern template class xw::xtransport<xw::xmaterialize<xlf::xtile_layer>>;
#endif

#endif
