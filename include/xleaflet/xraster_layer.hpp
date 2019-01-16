/******************************************************************************
* Copyright (c) 2018, Sylvain Corlay and Johan Mabille, and Wolf Vollprecht   *
*                                                                             *
* Distributed under the terms of the BSD 3-Clause License.                    *
*                                                                             *
* The full license is in the file LICENSE, distributed with this software.    *
*******************************************************************************/

#ifndef XLEAFLET_RASTER_LAYER_HPP
#define XLEAFLET_RASTER_LAYER_HPP

#include <string>

#include "xwidgets/xmaterialize.hpp"
#include "xwidgets/xwidget.hpp"

#include "xlayer.hpp"
#include "xleaflet_config.hpp"

namespace xlf
{
    /****************************
     * raster_layer declaration *
     ****************************/

    template <class D>
    class xraster_layer : public xlayer<D>
    {
    public:

        using base_type = xlayer<D>;
        using derived_type = D;

        void serialize_state(xeus::xjson&, xeus::buffer_sequence&) const;
        void apply_patch(const xeus::xjson&, const xeus::buffer_sequence&);

        XPROPERTY(double, derived_type, opacity, 1.0);
        XPROPERTY(bool, derived_type, visible, true);

    protected:

        xraster_layer();
        using base_type::base_type;

    private:

        void set_defaults();

        void setup_properties();
    };

    using raster_layer = xw::xmaterialize<xraster_layer>;

    using raster_layer_generator = xw::xgenerator<xraster_layer>;

    /********************************
     * xraster_layer implementation *
     ********************************/

    template <class D>
    inline void xraster_layer<D>::serialize_state(xeus::xjson& state,
                                                  xeus::buffer_sequence& buffers) const
    {
        base_type::serialize_state(state, buffers);

        using xw::set_patch_from_property;

        set_patch_from_property(opacity, state, buffers);
        set_patch_from_property(visible, state, buffers);
    }

    template <class D>
    inline void xraster_layer<D>::apply_patch(const xeus::xjson& patch,
                                              const xeus::buffer_sequence& buffers)
    {
        base_type::apply_patch(patch, buffers);

        using xw::set_property_from_patch;

        set_property_from_patch(opacity, patch, buffers);
        set_property_from_patch(visible, patch, buffers);
    }

    template <class D>
    inline xraster_layer<D>::xraster_layer()
        : base_type()
    {
        set_defaults();

        this->setup_properties();
    }

    template <class D>
    inline void xraster_layer<D>::setup_properties()
    {
        // TODO: Create a class (in xproperty?) for bounded integer/float/double
        // instead of having a validator when needed

        // Opacity should be bounded between 0.0 and 1.0
    }

    template <class D>
    inline void xraster_layer<D>::set_defaults()
    {
        this->_model_name() = "LeafletRasterLayerModel";
        this->_view_name() = "LeafletRasterLayerView";
    }
}

/*********************
 * precompiled types *
 *********************/

#ifndef _WIN32
    extern template class xw::xmaterialize<xlf::xraster_layer>;
    extern template xw::xmaterialize<xlf::xraster_layer>::xmaterialize();
    extern template class xw::xtransport<xw::xmaterialize<xlf::xraster_layer>>;
    extern template class xw::xgenerator<xlf::xraster_layer>;
    extern template xw::xgenerator<xlf::xraster_layer>::xgenerator();
    extern template class xw::xtransport<xw::xgenerator<xlf::xraster_layer>>;
#endif

#endif
