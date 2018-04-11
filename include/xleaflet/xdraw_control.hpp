/******************************************************************************
* Copyright (c) 2018, Sylvain Corlay and Johan Mabille, Wolf Vollprecht and   *
* Martin Renou                                                                *
*                                                                             *
* Distributed under the terms of the BSD 3-Clause License.                    *
*                                                                             *
* The full license is in the file LICENSE, distributed with this software.    *
*******************************************************************************/

#ifndef XLEAFLET_DRAW_CONTROL_HPP
#define XLEAFLET_DRAW_CONTROL_HPP

#include <string>
#include <vector>

#include "xwidgets/xmaterialize.hpp"
#include "xwidgets/xholder.hpp"
#include "xwidgets/xwidget.hpp"

#include "xleaflet_config.hpp"
#include "xfeature_group.hpp"
#include "xcontrol.hpp"

namespace xleaflet
{
    /****************************
     * draw_control declaration *
     ****************************/

    template <class D>
    class xdraw_control : public xcontrol<D>
    {
    public:

        using base_type = xcontrol<D>;
        using derived_type = D;

        using feature_group_type = xw::xholder<xfeature_group>;

        xeus::xjson get_state() const;
        void apply_patch(const xeus::xjson&);

        XPROPERTY(feature_group_type, derived_type, layer);
        XPROPERTY(xeus::xjson, derived_type, polyline);
        XPROPERTY(xeus::xjson, derived_type, polygon);
        XPROPERTY(xeus::xjson, derived_type, circle);
        XPROPERTY(xeus::xjson, derived_type, rectangle);
        XPROPERTY(xeus::xjson, derived_type, marker);
        XPROPERTY(bool, derived_type, edit, true);
        XPROPERTY(bool, derived_type, remove, true);

    protected:

        xdraw_control();
        using base_type::base_type;

    private:

        void set_defaults();
    };

    using draw_control = xw::xmaterialize<xdraw_control>;

    using draw_control_generator = xw::xgenerator<xdraw_control>;

    /********************************
     * xdraw_control implementation *
     ********************************/

     template <class D>
     inline xeus::xjson xdraw_control<D>::get_state() const
     {
         xeus::xjson state = base_type::get_state();

         XOBJECT_SET_PATCH_FROM_PROPERTY(layer, state);
         XOBJECT_SET_PATCH_FROM_PROPERTY(polyline, state);
         XOBJECT_SET_PATCH_FROM_PROPERTY(polygon, state);
         XOBJECT_SET_PATCH_FROM_PROPERTY(circle, state);
         XOBJECT_SET_PATCH_FROM_PROPERTY(rectangle, state);
         XOBJECT_SET_PATCH_FROM_PROPERTY(marker, state);
         XOBJECT_SET_PATCH_FROM_PROPERTY(edit, state);
         XOBJECT_SET_PATCH_FROM_PROPERTY(remove, state);

         return state;
     }

     template <class D>
     inline void xdraw_control<D>::apply_patch(const xeus::xjson& patch)
     {
         base_type::apply_patch(patch);

         XOBJECT_SET_PROPERTY_FROM_PATCH(layer, patch);
     }

    template <class D>
    inline xdraw_control<D>::xdraw_control()
        : base_type()
    {
        set_defaults();
    }

    template <class D>
    inline void xdraw_control<D>::set_defaults()
    {
        this->_model_name() = "LeafletDrawControlModel";
        this->_view_name() = "LeafletDrawControlView";

        this->layer() = feature_group();
        this->polyline() = {"shapeOptions", {}};
        this->polygon() = {"shapeOptions", {}};
    }

}

#endif
