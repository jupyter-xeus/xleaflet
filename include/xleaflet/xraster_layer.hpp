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

#include "xleaflet_config.hpp"
#include "xlayer.hpp"

namespace xleaflet
{
    /*******************
     * tile_layer declaration *
     *******************/

    template <class D>
    class xraster_layer : public xlayer<D>
    {
    public:

        using base_type = xlayer<D>;
        using derived_type = D;

        xeus::xjson get_state() const;
        void apply_patch(const xeus::xjson&);

        XPROPERTY(float, derived_type, opacity, 1.0);
        XPROPERTY(bool, derived_type, visible, true);

    protected:

        xraster_layer();
        using base_type::base_type;

    private:

        void set_defaults();

        void setup_properties();
    };

    using raster_layer = xw::xmaterialize<xlayer>;

    using raster_layer_generator = xw::xgenerator<xlayer>;

    /***********************
     * xraster_layer implementation *
     ***********************/

    template <class D>
    inline xeus::xjson xraster_layer<D>::get_state() const
    {
        xeus::xjson state = base_type::get_state();

        XOBJECT_SET_PATCH_FROM_PROPERTY(opacity, state);
        XOBJECT_SET_PATCH_FROM_PROPERTY(visible, state);

        return state;
    }

    template <class D>
    inline void xraster_layer<D>::apply_patch(const xeus::xjson& patch)
    {
        base_type::apply_patch(patch);

        XOBJECT_SET_PROPERTY_FROM_PATCH(opacity, patch);
        XOBJECT_SET_PROPERTY_FROM_PATCH(visible, patch);
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
        //TODO: Create a class for bounded integer/float/double instead of
        // having a validator when needed
        auto self = this->self();
        self->template validate<decltype(self->opacity)>([](auto& owner, auto& proposal) {
            if (proposal > 1.0)
            {
                proposal = 1.0;
            }
            if (proposal < 0.0)
            {
                proposal = 0.0;
            }
        });
    }

    template <class D>
    inline void xraster_layer<D>::set_defaults()
    {
        this->_model_name() = "LeafletRasterLayerModel";
        this->_view_name() = "LeafletRasterLayerView";
    }
}

#endif
