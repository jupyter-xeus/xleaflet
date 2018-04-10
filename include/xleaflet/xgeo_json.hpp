/******************************************************************************
* Copyright (c) 2018, Sylvain Corlay and Johan Mabille, Wolf Vollprecht and   *
* Martin Renou                                                                *
*                                                                             *
* Distributed under the terms of the BSD 3-Clause License.                    *
*                                                                             *
* The full license is in the file LICENSE, distributed with this software.    *
*******************************************************************************/

#ifndef XLEAFLET_GEO_JSON_HPP
#define XLEAFLET_GEO_JSON_HPP

#include "xwidgets/xmaterialize.hpp"
#include "xwidgets/xwidget.hpp"

#include "xleaflet_config.hpp"
#include "xfeature_group.hpp"

namespace xleaflet
{
    /************************
     * geo_json declaration *
     ************************/

    template <class D>
    class xgeo_json : public xfeature_group<D>
    {
    public:

        using base_type = xfeature_group<D>;
        using derived_type = D;

        xeus::xjson get_state() const;
        void apply_patch(const xeus::xjson&);

        XPROPERTY(xeus::xjson, derived_type, data);
        XPROPERTY(xeus::xjson, derived_type, style);
        XPROPERTY(xeus::xjson, derived_type, hover_style);

    protected:

        xgeo_json();
        using base_type::base_type;

    private:

        void set_defaults();
    };

    using geo_json = xw::xmaterialize<xgeo_json>;

    using geo_json_generator = xw::xgenerator<xgeo_json>;

    /****************************
     * xgeo_json implementation *
     ****************************/

     template <class D>
     inline xeus::xjson xgeo_json<D>::get_state() const
     {
         xeus::xjson state = base_type::get_state();

         XOBJECT_SET_PATCH_FROM_PROPERTY(data, state);
         XOBJECT_SET_PATCH_FROM_PROPERTY(style, state);
         XOBJECT_SET_PATCH_FROM_PROPERTY(hover_style, state);

         return state;
     }

     template <class D>
     inline void xgeo_json<D>::apply_patch(const xeus::xjson& patch)
     {
         base_type::apply_patch(patch);

         XOBJECT_SET_PROPERTY_FROM_PATCH(data, patch);
         XOBJECT_SET_PROPERTY_FROM_PATCH(style, patch);
         XOBJECT_SET_PROPERTY_FROM_PATCH(hover_style, patch);
     }

    template <class D>
    inline xgeo_json<D>::xgeo_json()
        : base_type()
    {
        set_defaults();
    }

    template <class D>
    inline void xgeo_json<D>::set_defaults()
    {
        this->_model_name() = "LeafletGeoJSONModel";
        this->_view_name() = "LeafletGeoJSONView";
    }
}

#endif
