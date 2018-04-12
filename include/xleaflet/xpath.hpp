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

namespace xleaflet
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

        xeus::xjson get_state() const;
        void apply_patch(const xeus::xjson&);

        XPROPERTY(bool, derived_type, stroke, true);
        XPROPERTY(xw::html_color, derived_type, color, "#0033FF");
        XPROPERTY(int, derived_type, weight, 5);
        XPROPERTY(bool, derived_type, fill, true);
        XPROPERTY(xw::html_color, derived_type, fill_color, "#0033FF");
        XPROPERTY(float, derived_type, fill_opacity, 0.2);
        XPROPERTY(std::string, derived_type, dash_array, "");
        XPROPERTY(std::string, derived_type, line_cap, "");
        XPROPERTY(std::string, derived_type, line_join, "");
        XPROPERTY(bool, derived_type, clickable, true);
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
    inline xeus::xjson xpath<D>::get_state() const
    {
        xeus::xjson state = base_type::get_state();

        XOBJECT_SET_PATCH_FROM_PROPERTY(stroke, state);
        XOBJECT_SET_PATCH_FROM_PROPERTY(color, state);
        XOBJECT_SET_PATCH_FROM_PROPERTY(weight, state);
        XOBJECT_SET_PATCH_FROM_PROPERTY(fill, state);
        XOBJECT_SET_PATCH_FROM_PROPERTY(fill_color, state);
        XOBJECT_SET_PATCH_FROM_PROPERTY(fill_opacity, state);
        XOBJECT_SET_PATCH_FROM_PROPERTY(dash_array, state);
        XOBJECT_SET_PATCH_FROM_PROPERTY(line_cap, state);
        XOBJECT_SET_PATCH_FROM_PROPERTY(line_join, state);
        XOBJECT_SET_PATCH_FROM_PROPERTY(clickable, state);
        XOBJECT_SET_PATCH_FROM_PROPERTY(pointer_events, state);
        XOBJECT_SET_PATCH_FROM_PROPERTY(class_name, state);
        XOBJECT_SET_PATCH_FROM_PROPERTY(opacity, state);

        return state;
    }

    template <class D>
    inline void xpath<D>::apply_patch(const xeus::xjson& patch)
    {
        base_type::apply_patch(patch);

        XOBJECT_SET_PROPERTY_FROM_PATCH(stroke, patch);
        XOBJECT_SET_PROPERTY_FROM_PATCH(color, patch);
        XOBJECT_SET_PROPERTY_FROM_PATCH(weight, patch);
        XOBJECT_SET_PROPERTY_FROM_PATCH(fill, patch);
        XOBJECT_SET_PROPERTY_FROM_PATCH(fill_color, patch);
        XOBJECT_SET_PROPERTY_FROM_PATCH(fill_opacity, patch);
        XOBJECT_SET_PROPERTY_FROM_PATCH(dash_array, patch);
        XOBJECT_SET_PROPERTY_FROM_PATCH(line_cap, patch);
        XOBJECT_SET_PROPERTY_FROM_PATCH(line_join, patch);
        XOBJECT_SET_PROPERTY_FROM_PATCH(clickable, patch);
        XOBJECT_SET_PROPERTY_FROM_PATCH(pointer_events, patch);
        XOBJECT_SET_PROPERTY_FROM_PATCH(class_name, patch);
        XOBJECT_SET_PROPERTY_FROM_PATCH(opacity, patch);
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
                "clickable",
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
    extern template class xw::xmaterialize<xleaflet::xpath>;
    extern template xw::xmaterialize<xleaflet::xpath>::xmaterialize();
    extern template class xw::xtransport<xw::xmaterialize<xleaflet::xpath>>;
    extern template class xw::xgenerator<xleaflet::xpath>;
    extern template xw::xgenerator<xleaflet::xpath>::xgenerator();
    extern template class xw::xtransport<xw::xgenerator<xleaflet::xpath>>;
#endif

#endif
