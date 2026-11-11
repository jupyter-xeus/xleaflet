/******************************************************************************
* Copyright (c) 2018, Sylvain Corlay and Johan Mabille, Wolf Vollprecht and   *
* Martin Renou                                                                *
*                                                                             *
* Distributed under the terms of the BSD 3-Clause License.                    *
*                                                                             *
* The full license is in the file LICENSE, distributed with this software.    *
*******************************************************************************/

#ifndef XLEAFLET_PATH_HPP
#define XLEAFLET_PATH_HPP

#include <string>

#include "xwidgets/xcolor.hpp"
#include "xwidgets/xmaterialize.hpp"
#include "xwidgets/xwidget.hpp"

#include "xvector_layer.hpp"

namespace nl = nlohmann;

namespace xlf
{
    /********************
     * path declaration *
     ********************/

    template <class D>
    class xpath : public xvector_layer<D>
    {
    public:

        using base_type = xvector_layer<D>;
        using derived_type = D;

        void serialize_state(nl::json&, xeus::buffer_sequence&) const;
        void apply_patch(const nl::json&, const xeus::buffer_sequence&);

        XPROPERTY(bool, xw::xcommon, stroke, true);
        XPROPERTY(xw::html_color, xw::xcommon, color, "#0033FF");
        XPROPERTY(int, xw::xcommon, weight, 5);
        XPROPERTY(bool, xw::xcommon, fill, true);
        XPROPERTY(xw::html_color, xw::xcommon, fill_color, "#0033FF");
        XPROPERTY(double, xw::xcommon, fill_opacity, 0.2);
        XPROPERTY(std::string, xw::xcommon, dash_array, "");
        XPROPERTY(std::string, xw::xcommon, line_cap, "");
        XPROPERTY(std::string, xw::xcommon, line_join, "");
        XPROPERTY(std::string, xw::xcommon, pointer_events, "");
        XPROPERTY(std::string, xw::xcommon, class_name, "");
        XPROPERTY(double, xw::xcommon, opacity, 1.0);

    protected:

        xpath();
        using base_type::base_type;

    private:

        void set_defaults();
    };

    using path = xw::xmaterialize<xpath>;

    /************************
     * xpath implementation *
     ************************/

    template <class D>
    inline void xpath<D>::serialize_state(nl::json& state, xeus::buffer_sequence& buffers) const
    {
        base_type::serialize_state(state, buffers);

        using xw::xwidgets_serialize;

        xwidgets_serialize(stroke(), state["stroke"], buffers);
        xwidgets_serialize(color(), state["color"], buffers);
        xwidgets_serialize(weight(), state["weight"], buffers);
        xwidgets_serialize(fill(), state["fill"], buffers);
        xwidgets_serialize(fill_color(), state["fill_color"], buffers);
        xwidgets_serialize(fill_opacity(), state["fill_opacity"], buffers);
        xwidgets_serialize(dash_array(), state["dash_array"], buffers);
        xwidgets_serialize(line_cap(), state["line_cap"], buffers);
        xwidgets_serialize(line_join(), state["line_join"], buffers);
        xwidgets_serialize(pointer_events(), state["pointer_events"], buffers);
        xwidgets_serialize(class_name(), state["class_name"], buffers);
        xwidgets_serialize(opacity(), state["opacity"], buffers);
    }

    template <class D>
    inline void xpath<D>::apply_patch(const nl::json& patch,
                                      const xeus::buffer_sequence& buffers)
    {
        base_type::apply_patch(patch, buffers);
    }

    template <class D>
    inline xpath<D>::xpath()
        : base_type()
    {
        set_defaults();
    }

    template <class D>
    inline void xpath<D>::set_defaults()
    {
        this->_model_name() = "LeafletPathModel";
        this->_view_name() = "LeafletPathView";

        this->options().insert(
            this->options().end(),
            {
                "stroke",
                "color",
                "weight",
                "fill",
                "fill_color",
                "fill_opacity",
                "dash_array",
                "line_cap",
                "line_join",
                "pointer_events",
                "class_name",
                "opacity"
            }
        );
    }
}

/*********************
 * precompiled types *
 *********************/

    extern template class xw::xmaterialize<xlf::xpath>;
    extern template class xw::xtransport<xw::xmaterialize<xlf::xpath>>;

#endif
