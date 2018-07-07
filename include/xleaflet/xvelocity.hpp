/******************************************************************************
* Copyright (c) 2018, Sylvain Corlay and Johan Mabille, Wolf Vollprecht and   *
* Martin Renou                                                                *
*                                                                             *
* Distributed under the terms of the BSD 3-Clause License.                    *
*                                                                             *
* The full license is in the file LICENSE, distributed with this software.    *
*******************************************************************************/

#ifndef XLEAFLET_VELOCITY_HPP
#define XLEAFLET_VELOCITY_HPP

#include <string>
#include <vector>

#include "xwidgets/xmaterialize.hpp"
#include "xwidgets/xcolor.hpp"
#include "xwidgets/xwidget.hpp"

#include "xleaflet_config.hpp"
#include "xlayer.hpp"

namespace xlf
{
    /************************
     * velocity declaration *
     ************************/

    template <class D>
    class xvelocity : public xlayer<D>
    {
    public:

        using base_type = xlayer<D>;
        using derived_type = D;

        void serialize_state(xeus::xjson&, xeus::buffer_sequence&) const;
        void apply_patch(const xeus::xjson&, const xeus::buffer_sequence&);

        XPROPERTY(xeus::xjson, derived_type, data);
        XPROPERTY(std::string, derived_type, units);
        XPROPERTY(bool, derived_type, display_values, true);
        XPROPERTY(xeus::xjson, derived_type, display_options, R"({
            "velocityType": "Global Wind",
            "position": "bottomleft",
            "emptyString": "No velocity data",
            "angleConvention": "bearingCW",
            "displayPosition": "bottomleft",
            "displayEmptyString": "No velocity data",
            "speedUnit": "kt"
        })"_json);
        XPROPERTY(double, derived_type, min_velocity, 0);
        XPROPERTY(double, derived_type, max_velocity, 10);
        XPROPERTY(double, derived_type, velocity_scale, 0.005);
        XPROPERTY(std::vector<xw::html_color>, derived_type, color_scale);

    protected:

        xvelocity();
        using base_type::base_type;

    private:

        void set_defaults();
    };

    using velocity = xw::xmaterialize<xvelocity>;

    using velocity_generator = xw::xgenerator<xvelocity>;

    /***************************
     * velocity implementation *
     ***************************/

    template <class D>
    inline void xvelocity<D>::serialize_state(xeus::xjson& state, xeus::buffer_sequence& buffers) const
    {
        base_type::serialize_state(state, buffers);

        xw::set_patch_from_property(data, state, buffers);
        xw::set_patch_from_property(units, state, buffers);
        xw::set_patch_from_property(display_values, state, buffers);
        xw::set_patch_from_property(display_options, state, buffers);
        xw::set_patch_from_property(min_velocity, state, buffers);
        xw::set_patch_from_property(max_velocity, state, buffers);
        xw::set_patch_from_property(velocity_scale, state, buffers);
        xw::set_patch_from_property(color_scale, state, buffers);
    }

    template <class D>
    inline void xvelocity<D>::apply_patch(const xeus::xjson& patch, const xeus::buffer_sequence& buffers)
    {
        base_type::apply_patch(patch, buffers);

        xw::set_property_from_patch(data, patch, buffers);
        xw::set_property_from_patch(units, patch, buffers);
        xw::set_property_from_patch(display_values, patch, buffers);
        xw::set_property_from_patch(display_options, patch, buffers);
        xw::set_property_from_patch(min_velocity, patch, buffers);
        xw::set_property_from_patch(max_velocity, patch, buffers);
        xw::set_property_from_patch(velocity_scale, patch, buffers);
        xw::set_property_from_patch(color_scale, patch, buffers);
    }

    template <class D>
    inline xvelocity<D>::xvelocity()
        : base_type()
    {
        set_defaults();
    }

    template <class D>
    inline void xvelocity<D>::set_defaults()
    {
        this->_model_name() = "LeafletVelocityModel";
        this->_view_name() = "LeafletVelocityView";

        this->color_scale() = {
            "rgb(36,104, 180)",
            "rgb(60,157, 194)",
            "rgb(128,205,193)",
            "rgb(151,218,168)",
            "rgb(198,231,181)",
            "rgb(238,247,217)",
            "rgb(255,238,159)",
            "rgb(252,217,125)",
            "rgb(255,182,100)",
            "rgb(252,150,75)",
            "rgb(250,112,52)",
            "rgb(245,64,32)",
            "rgb(237,45,28)",
            "rgb(220,24,32)",
            "rgb(180,0,35)"
        };

        this->options().insert(
            this->options().end(),
            {
                "data",
                "units",
                "display_values",
                "display_options",
                "min_velocity",
                "max_velocity",
                "velocity_scale",
                "color_scale"
            }
        );
    }
}

/*********************
 * precompiled types *
 *********************/

#ifndef _WIN32
    extern template class xw::xmaterialize<xlf::xvelocity>;
    extern template xw::xmaterialize<xlf::xvelocity>::xmaterialize();
    extern template class xw::xtransport<xw::xmaterialize<xlf::xvelocity>>;
    extern template class xw::xgenerator<xlf::xvelocity>;
    extern template xw::xgenerator<xlf::xvelocity>::xgenerator();
    extern template class xw::xtransport<xw::xgenerator<xlf::xvelocity>>;
#endif

#endif
