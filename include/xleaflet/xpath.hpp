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

#include "xwidgets/xmaterialize.hpp"
#include "xwidgets/xcolor.hpp"
#include "xwidgets/xwidget.hpp"

#include "xvector_layer.hpp"

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

        void serialize_state(xeus::xjson&, xeus::buffer_sequence&) const;
        void apply_patch(const xeus::xjson&, const xeus::buffer_sequence&);

        XPROPERTY(bool, derived_type, stroke, true);
        XPROPERTY(xw::html_color, derived_type, color, "#0033FF");
        XPROPERTY(int, derived_type, weight, 5);
        XPROPERTY(bool, derived_type, fill, true);
        XPROPERTY(xw::html_color, derived_type, fill_color, "#0033FF");
        XPROPERTY(float, derived_type, fill_opacity, 0.2);
        XPROPERTY(std::string, derived_type, dash_array, "");
        XPROPERTY(std::string, derived_type, line_cap, "");
        XPROPERTY(std::string, derived_type, line_join, "");
        XPROPERTY(std::string, derived_type, pointer_events, "");
        XPROPERTY(std::string, derived_type, class_name, "");
        XPROPERTY(float, derived_type, opacity, 1.0);

    protected:

        xpath();
        using base_type::base_type;

    private:

        void set_defaults();
    };

    using path = xw::xmaterialize<xpath>;

    using path_generator = xw::xgenerator<xpath>;

    /************************
     * xpath implementation *
     ************************/

    template <class D>
    inline void xpath<D>::serialize_state(xeus::xjson& state, xeus::buffer_sequence& buffers) const
    {
        base_type::serialize_state(state, buffers);

        xw::set_patch_from_property(stroke, state, buffers);
        xw::set_patch_from_property(color, state, buffers);
        xw::set_patch_from_property(weight, state, buffers);
        xw::set_patch_from_property(fill, state, buffers);
        xw::set_patch_from_property(fill_color, state, buffers);
        xw::set_patch_from_property(fill_opacity, state, buffers);
        xw::set_patch_from_property(dash_array, state, buffers);
        xw::set_patch_from_property(line_cap, state, buffers);
        xw::set_patch_from_property(line_join, state, buffers);
        xw::set_patch_from_property(pointer_events, state, buffers);
        xw::set_patch_from_property(class_name, state, buffers);
        xw::set_patch_from_property(opacity, state, buffers);
    }

    template <class D>
    inline void xpath<D>::apply_patch(const xeus::xjson& patch, const xeus::buffer_sequence& buffers)
    {
        base_type::apply_patch(patch, buffers);

        xw::set_property_from_patch(stroke, patch, buffers);
        xw::set_property_from_patch(color, patch, buffers);
        xw::set_property_from_patch(weight, patch, buffers);
        xw::set_property_from_patch(fill, patch, buffers);
        xw::set_property_from_patch(fill_color, patch, buffers);
        xw::set_property_from_patch(fill_opacity, patch, buffers);
        xw::set_property_from_patch(dash_array, patch, buffers);
        xw::set_property_from_patch(line_cap, patch, buffers);
        xw::set_property_from_patch(line_join, patch, buffers);
        xw::set_property_from_patch(pointer_events, patch, buffers);
        xw::set_property_from_patch(class_name, patch, buffers);
        xw::set_property_from_patch(opacity, patch, buffers);
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

#ifndef _WIN32
    extern template class xw::xmaterialize<xlf::xpath>;
    extern template xw::xmaterialize<xlf::xpath>::xmaterialize();
    extern template class xw::xtransport<xw::xmaterialize<xlf::xpath>>;
    extern template class xw::xgenerator<xlf::xpath>;
    extern template xw::xgenerator<xlf::xpath>::xgenerator();
    extern template class xw::xtransport<xw::xgenerator<xlf::xpath>>;
#endif

#endif
