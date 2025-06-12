/******************************************************************************
* Copyright (c) 2018, Sylvain Corlay and Johan Mabille, Wolf Vollprecht and   *
* Martin Renou                                                                *
*                                                                             *
* Distributed under the terms of the BSD 3-Clause License.                    *
*                                                                             *
* The full license is in the file LICENSE, distributed with this software.    *
*******************************************************************************/

#ifndef XLEAFLET_POLYLINE_HPP
#define XLEAFLET_POLYLINE_HPP

#include "xtensor/misc/xexpression_holder.hpp"

#include "xwidgets/xmaterialize.hpp"
#include "xwidgets/xwidget.hpp"

#include "xpath.hpp"

namespace nl = nlohmann;

namespace xlf
{
    /************************
     * polyline declaration *
     ************************/

    template <class D>
    class xpolyline : public xpath<D>
    {
    public:

        using locations_type = xt::xexpression_holder;

        using base_type = xpath<D>;
        using derived_type = D;

        void serialize_state(nl::json&, xeus::buffer_sequence&) const;
        void apply_patch(const nl::json&, const xeus::buffer_sequence&);

        XPROPERTY(locations_type, derived_type, locations);
        XPROPERTY(double, derived_type, smooth_factor, 1.0);
        XPROPERTY(bool, derived_type, no_clip, false);

    protected:

        xpolyline();
        using base_type::base_type;

    private:

        void set_defaults();
    };

    using polyline = xw::xmaterialize<xpolyline>;

    /****************************
     * xpolyline implementation *
     ****************************/

    template <class D>
    inline void xpolyline<D>::serialize_state(nl::json& state,
                                              xeus::buffer_sequence& buffers) const
    {
        base_type::serialize_state(state, buffers);

        using xw::xwidgets_serialize;

        xwidgets_serialize(locations(), state["locations"], buffers);
        xwidgets_serialize(smooth_factor(), state["smooth_factor"], buffers);
        xwidgets_serialize(no_clip(), state["no_clip"], buffers);
    }

    template <class D>
    inline void xpolyline<D>::apply_patch(const nl::json& patch,
                                          const xeus::buffer_sequence& buffers)
    {
        base_type::apply_patch(patch, buffers);

        using xw::set_property_from_patch;

        set_property_from_patch(locations, patch, buffers);
        set_property_from_patch(smooth_factor, patch, buffers);
        set_property_from_patch(no_clip, patch, buffers);
    }

    template <class D>
    inline xpolyline<D>::xpolyline()
        : base_type()
    {
        set_defaults();
    }

    template <class D>
    inline void xpolyline<D>::set_defaults()
    {
        this->_model_name() = "LeafletPolylineModel";
        this->_view_name() = "LeafletPolylineView";

        this->locations() = xt::xexpression_holder();

        this->options().insert(
            this->options().end(),
            {
                "smooth_factor",
                "no_clip"
            }
        );
    }
}

/*********************
 * precompiled types *
 *********************/

    extern template class xw::xmaterialize<xlf::xpolyline>;
    extern template class xw::xtransport<xw::xmaterialize<xlf::xpolyline>>;

#endif
