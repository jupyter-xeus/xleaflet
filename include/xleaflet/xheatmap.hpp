/******************************************************************************
* Copyright (c) 2018, Sylvain Corlay and Johan Mabille, Wolf Vollprecht and   *
* Martin Renou                                                                *
*                                                                             *
* Distributed under the terms of the BSD 3-Clause License.                    *
*                                                                             *
* The full license is in the file LICENSE, distributed with this software.    *
*******************************************************************************/

#ifndef XLEAFLET_HEATMAP_HPP
#define XLEAFLET_HEATMAP_HPP

#include "xtensor/xexpression_holder.hpp"

#include "xwidgets/xmaterialize.hpp"
#include "xwidgets/xwidget.hpp"

#include "xleaflet_config.hpp"
#include "xraster_layer.hpp"

namespace nl = nlohmann;

namespace xlf
{
    /***********************
     * heatmap declaration *
     ***********************/

    template <class D>
    class xheatmap : public xraster_layer<D>
    {
    public:

        // Lat, lng, intensity
        using locations_type = xt::xexpression_holder;

        using base_type = xraster_layer<D>;
        using derived_type = D;

        void serialize_state(nl::json&, xeus::buffer_sequence&) const;
        void apply_patch(const nl::json&, const xeus::buffer_sequence&);

        XPROPERTY(locations_type, derived_type, locations);
        XPROPERTY(double, derived_type, min_opacity, 0.05);
        XPROPERTY(int, derived_type, max_zoom, 18);
        XPROPERTY(double, derived_type, max, 1.0);
        XPROPERTY(double, derived_type, radius, 25.0);
        XPROPERTY(double, derived_type, blur, 15.0);
        XPROPERTY(nl::json, derived_type, gradient);

    protected:

        xheatmap();
        using base_type::base_type;

    private:

        void set_defaults();
    };

    using heatmap = xw::xmaterialize<xheatmap>;

    /**************************
     * heatmap implementation *
     **************************/

    template <class D>
    inline void xheatmap<D>::serialize_state(nl::json& state,
                                             xeus::buffer_sequence& buffers) const
    {
        base_type::serialize_state(state, buffers);

        using xw::xwidgets_serialize;

        xwidgets_serialize(locations(), state["locations"], buffers);
        xwidgets_serialize(min_opacity(), state["min_opacity"], buffers);
        xwidgets_serialize(max_zoom(), state["max_zoom"], buffers);
        xwidgets_serialize(max(), state["max"], buffers);
        xwidgets_serialize(radius(), state["radius"], buffers);
        xwidgets_serialize(blur(), state["blur"], buffers);
        xwidgets_serialize(gradient(), state["gradient"], buffers);
    }

    template <class D>
    inline void xheatmap<D>::apply_patch(const nl::json& patch,
                                         const xeus::buffer_sequence& buffers)
    {
        base_type::apply_patch(patch, buffers);

        using xw::set_property_from_patch;

        set_property_from_patch(locations, patch, buffers);
        set_property_from_patch(min_opacity, patch, buffers);
        set_property_from_patch(max_zoom, patch, buffers);
        set_property_from_patch(max, patch, buffers);
        set_property_from_patch(radius, patch, buffers);
        set_property_from_patch(blur, patch, buffers);
        set_property_from_patch(gradient, patch, buffers);
    }

    template <class D>
    inline xheatmap<D>::xheatmap()
        : base_type()
    {
        set_defaults();
    }

    template <class D>
    inline void xheatmap<D>::set_defaults()
    {
        this->_model_name() = "LeafletHeatmapModel";
        this->_view_name() = "LeafletHeatmapView";

        this->gradient() = {
            {"0.4", "blue"},
            {"0.6", "cyan"},
            {"0.7", "lime"},
            {"0.8", "yellow"},
            {"1.0", "red"}
        };

        this->options().insert(
            this->options().end(),
            {
                "min_opacity",
                "max_zoom",
                "max",
                "radius",
                "blur",
                "gradient"
            }
        );

        this->locations() = xt::xexpression_holder();
    }
}

/*********************
 * precompiled types *
 *********************/

#ifndef _WIN32
    extern template class xw::xmaterialize<xlf::xheatmap>;
    extern template xw::xmaterialize<xlf::xheatmap>::xmaterialize();
    extern template class xw::xtransport<xw::xmaterialize<xlf::xheatmap>>;
#endif

#endif
