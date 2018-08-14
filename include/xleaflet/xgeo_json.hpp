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

#include "xwidgets/xmaterialize.hpp"
#include "xwidgets/xwidget.hpp"

#include "xfeature_group.hpp"
#include "xleaflet_config.hpp"

namespace xlf
{
    /************************
     * geo_json declaration *
     ************************/

    template <class D>
    class xgeo_json : public xfeature_group<D>
    {
    public:

        using callback_type = std::function<void(const xeus::xjson&)>;

        using base_type = xfeature_group<D>;
        using derived_type = D;

        void serialize_state(xeus::xjson&, xeus::buffer_sequence&) const;
        void apply_patch(const xeus::xjson&, const xeus::buffer_sequence&);

        void on_click(callback_type);
        void on_hover(callback_type);

        void handle_custom_message(const xeus::xjson&);

        XPROPERTY(xeus::xjson, derived_type, data);
        XPROPERTY(xeus::xjson, derived_type, style);
        XPROPERTY(xeus::xjson, derived_type, hover_style);

    protected:

        xgeo_json();
        using base_type::base_type;

    private:

        void set_defaults();
        std::list<callback_type> m_click_callbacks;
        std::list<callback_type> m_hover_callbacks;
    };

    using geo_json = xw::xmaterialize<xgeo_json>;

    using geo_json_generator = xw::xgenerator<xgeo_json>;

    /****************************
     * xgeo_json implementation *
     ****************************/

    template <class D>
    inline void xgeo_json<D>::serialize_state(xeus::xjson& state,
                                              xeus::buffer_sequence& buffers) const
    {
        base_type::serialize_state(state, buffers);

        using xw::set_patch_from_property;

        set_patch_from_property(data, state, buffers);
        set_patch_from_property(style, state, buffers);
        set_patch_from_property(hover_style, state, buffers);
    }

    template <class D>
    inline void xgeo_json<D>::apply_patch(const xeus::xjson& patch,
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
    inline void xgeo_json<D>::handle_custom_message(const xeus::xjson& content)
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
    extern template class xw::xgenerator<xlf::xgeo_json>;
    extern template xw::xgenerator<xlf::xgeo_json>::xgenerator();
    extern template class xw::xtransport<xw::xgenerator<xlf::xgeo_json>>;
#endif

#endif
