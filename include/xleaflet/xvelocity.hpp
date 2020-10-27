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

#include "xwidgets/xcolor.hpp"
#include "xwidgets/xmaterialize.hpp"
#include "xwidgets/xwidget.hpp"

#include "xlayer.hpp"
#include "xleaflet_config.hpp"

namespace nl = nlohmann;

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

        void serialize_state(nl::json&, xeus::buffer_sequence&) const;
        void apply_patch(const nl::json&, const xeus::buffer_sequence&);

        XPROPERTY(nl::json, derived_type, data);
        XPROPERTY(std::string, derived_type, units);
        XPROPERTY(bool, derived_type, display_values, true);
        XPROPERTY(nl::json, derived_type, display_options, R"({
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

    /***************************
     * velocity implementation *
     ***************************/

    template <class D>
    inline void xvelocity<D>::serialize_state(nl::json& state,
                                              xeus::buffer_sequence& buffers) const
    {
        base_type::serialize_state(state, buffers);

        using xw::xwidgets_serialize;

        xwidgets_serialize(data(), state["data"], buffers);
        xwidgets_serialize(units(), state["units"], buffers);
        xwidgets_serialize(display_values(), state["display_values"], buffers);
        xwidgets_serialize(display_options(), state["display_options"], buffers);
        xwidgets_serialize(min_velocity(), state["min_velocity"], buffers);
        xwidgets_serialize(max_velocity(), state["max_velocity"], buffers);
        xwidgets_serialize(velocity_scale(), state["velocity_scale"], buffers);
        xwidgets_serialize(color_scale(), state["color_scale"], buffers);
    }

    template <class D>
    inline void xvelocity<D>::apply_patch(const nl::json& patch,
                                          const xeus::buffer_sequence& buffers)
    {
        base_type::apply_patch(patch, buffers);

        using xw::set_property_from_patch;

        set_property_from_patch(data, patch, buffers);
        set_property_from_patch(units, patch, buffers);
        set_property_from_patch(display_values, patch, buffers);
        set_property_from_patch(display_options, patch, buffers);
        set_property_from_patch(min_velocity, patch, buffers);
        set_property_from_patch(max_velocity, patch, buffers);
        set_property_from_patch(velocity_scale, patch, buffers);
        set_property_from_patch(color_scale, patch, buffers);
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

    extern template class xw::xmaterialize<xlf::xvelocity>;
    extern template class xw::xtransport<xw::xmaterialize<xlf::xvelocity>>;

#endif
