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

namespace xlf
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

        void serialize_state(xeus::xjson&, xeus::buffer_sequence&) const;
        void apply_patch(const xeus::xjson&, const xeus::buffer_sequence&);

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
    inline void xwms_layer<D>::serialize_state(xeus::xjson& state,
                                               xeus::buffer_sequence& buffers) const
    {
        base_type::serialize_state(state, buffers);

        using xw::set_patch_from_property;

        set_patch_from_property(service, state, buffers);
        set_patch_from_property(request, state, buffers);
        set_patch_from_property(layers, state, buffers);
        set_patch_from_property(styles, state, buffers);
        set_patch_from_property(format, state, buffers);
        set_patch_from_property(transparent, state, buffers);
        set_patch_from_property(version, state, buffers);
        set_patch_from_property(crs, state, buffers);
        set_patch_from_property(uppercase, state, buffers);
    }

    template <class D>
    inline void xwms_layer<D>::apply_patch(const xeus::xjson& patch,
                                           const xeus::buffer_sequence& buffers)
    {
        base_type::apply_patch(patch, buffers);

        using xw::set_property_from_patch;

        set_property_from_patch(service, patch, buffers);
        set_property_from_patch(request, patch, buffers);
        set_property_from_patch(layers, patch, buffers);
        set_property_from_patch(styles, patch, buffers);
        set_property_from_patch(format, patch, buffers);
        set_property_from_patch(transparent, patch, buffers);
        set_property_from_patch(version, patch, buffers);
        set_property_from_patch(crs, patch, buffers);
        set_property_from_patch(uppercase, patch, buffers);
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

/*********************
 * precompiled types *
 *********************/

#ifndef _WIN32
    extern template class xw::xmaterialize<xlf::xwms_layer>;
    extern template xw::xmaterialize<xlf::xwms_layer>::xmaterialize();
    extern template class xw::xtransport<xw::xmaterialize<xlf::xwms_layer>>;
    extern template class xw::xgenerator<xlf::xwms_layer>;
    extern template xw::xgenerator<xlf::xwms_layer>::xgenerator();
    extern template class xw::xtransport<xw::xgenerator<xlf::xwms_layer>>;
#endif

#endif
