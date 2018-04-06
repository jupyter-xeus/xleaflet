/******************************************************************************
* Copyright (c) 2018, Sylvain Corlay and Johan Mabille, Wolf Vollprecht and   *
* Martin Renou                                                                *
*                                                                             *
* Distributed under the terms of the BSD 3-Clause License.                    *
*                                                                             *
* The full license is in the file LICENSE, distributed with this software.    *
*******************************************************************************/

#ifndef XLEAFLET_WMS_LAYER_HPP
#define XLEAFLET_WMS_LAYER_HPP

#include <string>

#include "xwidgets/xmaterialize.hpp"
#include "xwidgets/xwidget.hpp"

#include "xtile_layer.hpp"

namespace xleaflet
{
    /*************************
     * wms_layer declaration *
     *************************/

    template <class D>
    class xwms_layer : public xtile_layer<D>
    {
    public:

        using base_type = xtile_layer<D>;
        using derived_type = D;

        xeus::xjson get_state() const;
        void apply_patch(const xeus::xjson&);

        XPROPERTY(std::string, derived_type, service, "WMS");
        XPROPERTY(std::string, derived_type, request, "GetMap");
        XPROPERTY(std::string, derived_type, layers, "");
        XPROPERTY(std::string, derived_type, styles, "");
        XPROPERTY(std::string, derived_type, format, "image/jpeg");
        XPROPERTY(bool, derived_type, transparent);
        XPROPERTY(std::string, derived_type, version, "1.1.1");
        XPROPERTY(std::string, derived_type, crs, "");
        XPROPERTY(bool, derived_type, uppercase);

    protected:

        xwms_layer();
        using base_type::base_type;

    private:

        void set_defaults();
    };

    using wms_layer = xw::xmaterialize<xwms_layer>;

    using wms_layer_generator = xw::xgenerator<xwms_layer>;

    /*****************************
     * xwms_layer implementation *
     *****************************/

    template <class D>
    inline xeus::xjson xwms_layer<D>::get_state() const
    {
        xeus::xjson state = base_type::get_state();

        XOBJECT_SET_PATCH_FROM_PROPERTY(service, state);
        XOBJECT_SET_PATCH_FROM_PROPERTY(request, state);
        XOBJECT_SET_PATCH_FROM_PROPERTY(layers, state);
        XOBJECT_SET_PATCH_FROM_PROPERTY(styles, state);
        XOBJECT_SET_PATCH_FROM_PROPERTY(format, state);
        XOBJECT_SET_PATCH_FROM_PROPERTY(transparent, state);
        XOBJECT_SET_PATCH_FROM_PROPERTY(version, state);
        XOBJECT_SET_PATCH_FROM_PROPERTY(crs, state);
        XOBJECT_SET_PATCH_FROM_PROPERTY(uppercase, state);

        return state;
    }

    template <class D>
    inline void xwms_layer<D>::apply_patch(const xeus::xjson& patch)
    {
        base_type::apply_patch(patch);

        XOBJECT_SET_PROPERTY_FROM_PATCH(service, patch);
        XOBJECT_SET_PROPERTY_FROM_PATCH(request, patch);
        XOBJECT_SET_PROPERTY_FROM_PATCH(layers, patch);
        XOBJECT_SET_PROPERTY_FROM_PATCH(styles, patch);
        XOBJECT_SET_PROPERTY_FROM_PATCH(format, patch);
        XOBJECT_SET_PROPERTY_FROM_PATCH(transparent, patch);
        XOBJECT_SET_PROPERTY_FROM_PATCH(version, patch);
        XOBJECT_SET_PROPERTY_FROM_PATCH(crs, patch);
        XOBJECT_SET_PROPERTY_FROM_PATCH(uppercase, patch);
    }

    template <class D>
    inline xwms_layer<D>::xwms_layer()
        : base_type()
    {
        set_defaults();
    }

    template <class D>
    inline void xwms_layer<D>::set_defaults()
    {
        this->_model_name() = "LeafletWMSLayerModel";
        this->_view_name() = "LeafletWMSLayerView";

        this->options().insert(
            this->options().end(),
            {
                "layers",
                "styles",
                "format",
                "transparent",
                "crs",
                "uppercase"
            }
        );
    }
}

#endif
