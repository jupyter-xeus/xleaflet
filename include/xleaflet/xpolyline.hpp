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

#include <array>

#include "xwidgets/xmaterialize.hpp"
#include "xwidgets/xwidget.hpp"

#include "xpath.hpp"

namespace xleaflet
{
    /************************
     * polyline declaration *
     ************************/

    template <class D>
    class xpolyline : public xpath<D>
    {
    public:

        using point_type = std::array<double, 2>;

        using base_type = xpath<D>;
        using derived_type = D;

        xeus::xjson get_state() const;
        void apply_patch(const xeus::xjson&);

        XPROPERTY(std::vector<point_type>, derived_type, locations);
        XPROPERTY(float, derived_type, smooth_factor, 1.0);
        XPROPERTY(bool, derived_type, no_clip, false);

    protected:

        xpolyline();
        using base_type::base_type;

    private:

        void set_defaults();
    };

    using polyline = xw::xmaterialize<xpolyline>;

    using polyline_generator = xw::xgenerator<xpolyline>;

    /****************************
     * xpolyline implementation *
     ****************************/

    template <class D>
    inline xeus::xjson xpolyline<D>::get_state() const
    {
        xeus::xjson state = base_type::get_state();

        XOBJECT_SET_PATCH_FROM_PROPERTY(locations, state);
        XOBJECT_SET_PATCH_FROM_PROPERTY(smooth_factor, state);
        XOBJECT_SET_PATCH_FROM_PROPERTY(no_clip, state);

        return state;
    }

    template <class D>
    inline void xpolyline<D>::apply_patch(const xeus::xjson& patch)
    {
        base_type::apply_patch(patch);

        XOBJECT_SET_PROPERTY_FROM_PATCH(locations, patch);
        XOBJECT_SET_PROPERTY_FROM_PATCH(smooth_factor, patch);
        XOBJECT_SET_PROPERTY_FROM_PATCH(no_clip, patch);
    }

    template <class D>
    inline xpolyline<D>::xpolyline()
        : base_type()
    {
        set_defaults();

        this->locations() = {};

        this->options().insert(
            this->options().end(),
            {
                "smooth_factor",
                "no_clip"
            }
        );
    }

    template <class D>
    inline void xpolyline<D>::set_defaults()
    {
        this->_model_name() = "LeafletPolylineModel";
        this->_view_name() = "LeafletPolylineView";
    }
}

#endif
