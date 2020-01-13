/******************************************************************************
* Copyright (c) 2018, Sylvain Corlay and Johan Mabille, Wolf Vollprecht and   *
* Martin Renou                                                                *
*                                                                             *
* Distributed under the terms of the BSD 3-Clause License.                    *
*                                                                             *
* The full license is in the file LICENSE, distributed with this software.    *
*******************************************************************************/

#ifndef XLEAFLET_GEO_JSON_HPP
#define XLEAFLET_GEO_JSON_HPP

#include <functional>
#include <list>

#include "nlohmann/json.hpp"

#include "xwidgets/xmaterialize.hpp"
#include "xwidgets/xwidget.hpp"

#include "xfeature_group.hpp"
#include "xleaflet_config.hpp"

namespace nl = nlohmann;

namespace xlf
{
    /************************
     * geo_json declaration *
     ************************/

    template <class D>
    class xgeo_json : public xfeature_group<D>
    {
    public:

        using callback_type = std::function<void(const nl::json&)>;

        using base_type = xfeature_group<D>;
        using derived_type = D;

        void serialize_state(nl::json&, xeus::buffer_sequence&) const;
        void apply_patch(const nl::json&, const xeus::buffer_sequence&);

        void on_click(callback_type);
        void on_hover(callback_type);

        void handle_custom_message(const nl::json&);

        XPROPERTY(nl::json, derived_type, data);
        XPROPERTY(nl::json, derived_type, style);
        XPROPERTY(nl::json, derived_type, hover_style);

    protected:

        xgeo_json();
        using base_type::base_type;

    private:

        void set_defaults();
        std::list<callback_type> m_click_callbacks;
        std::list<callback_type> m_hover_callbacks;
    };

    using geo_json = xw::xmaterialize<xgeo_json>;

    /****************************
     * xgeo_json implementation *
     ****************************/

    template <class D>
    inline void xgeo_json<D>::serialize_state(nl::json& state,
                                              xeus::buffer_sequence& buffers) const
    {
        base_type::serialize_state(state, buffers);

        using xw::xwidgets_serialize;

        xwidgets_serialize(data(), state["data"], buffers);
        xwidgets_serialize(style(), state["style"], buffers);
        xwidgets_serialize(hover_style(), state["hover_style"], buffers);
    }

    template <class D>
    inline void xgeo_json<D>::apply_patch(const nl::json& patch,
                                          const xeus::buffer_sequence& buffers)
    {
        base_type::apply_patch(patch, buffers);

        using xw::set_property_from_patch;

        set_property_from_patch(data, patch, buffers);
        set_property_from_patch(style, patch, buffers);
        set_property_from_patch(hover_style, patch, buffers);
    }

    template <class D>
    inline void xgeo_json<D>::on_click(callback_type callback)
    {
        m_click_callbacks.emplace_back(std::move(callback));
    }

    template <class D>
    inline void xgeo_json<D>::on_hover(callback_type callback)
    {
        m_hover_callbacks.emplace_back(std::move(callback));
    }

    template <class D>
    inline xgeo_json<D>::xgeo_json()
        : base_type()
    {
        set_defaults();
    }

    template <class D>
    inline void xgeo_json<D>::set_defaults()
    {
        this->_model_name() = "LeafletGeoJSONModel";
        this->_view_name() = "LeafletGeoJSONView";
    }

    template <class D>
    inline void xgeo_json<D>::handle_custom_message(const nl::json& content)
    {
        auto it = content.find("event");
        if (it != content.end() && it.value() == "click")
        {
            for (auto it = m_click_callbacks.begin(); it != m_click_callbacks.end(); ++it)
            {
                it->operator()(content);
            }
        }

        if (it != content.end() && it.value() == "mouseover")
        {
            for (auto it = m_hover_callbacks.begin(); it != m_hover_callbacks.end(); ++it)
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
    extern template class xw::xmaterialize<xlf::xgeo_json>;
    extern template xw::xmaterialize<xlf::xgeo_json>::xmaterialize();
    extern template class xw::xtransport<xw::xmaterialize<xlf::xgeo_json>>;
#endif

#endif
