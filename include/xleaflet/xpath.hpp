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

        XPROPERTY(bool, derived_type, stroke, true);
        XPROPERTY(xw::html_color, derived_type, color, "#0033FF");
        XPROPERTY(int, derived_type, weight, 5);
        XPROPERTY(bool, derived_type, fill, true);
        XPROPERTY(xw::html_color, derived_type, fill_color, "#0033FF");
        XPROPERTY(double, derived_type, fill_opacity, 0.2);
        XPROPERTY(std::string, derived_type, dash_array, "");
        XPROPERTY(std::string, derived_type, line_cap, "");
        XPROPERTY(std::string, derived_type, line_join, "");
        XPROPERTY(std::string, derived_type, pointer_events, "");
        XPROPERTY(std::string, derived_type, class_name, "");
        XPROPERTY(double, derived_type, opacity, 1.0);

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

        using xw::set_property_from_patch;

        set_property_from_patch(stroke, patch, buffers);
        set_property_from_patch(color, patch, buffers);
        set_property_from_patch(weight, patch, buffers);
        set_property_from_patch(fill, patch, buffers);
        set_property_from_patch(fill_color, patch, buffers);
        set_property_from_patch(fill_opacity, patch, buffers);
        set_property_from_patch(dash_array, patch, buffers);
        set_property_from_patch(line_cap, patch, buffers);
        set_property_from_patch(line_join, patch, buffers);
        set_property_from_patch(pointer_events, patch, buffers);
        set_property_from_patch(class_name, patch, buffers);
        set_property_from_patch(opacity, patch, buffers);
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
