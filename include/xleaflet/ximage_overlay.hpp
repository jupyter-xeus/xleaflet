/******************************************************************************
* Copyright (c) 2018, Sylvain Corlay and Johan Mabille, Wolf Vollprecht and   *
* Martin Renou                                                                *
*                                                                             *
* Distributed under the terms of the BSD 3-Clause License.                    *
*                                                                             *
* The full license is in the file LICENSE, distributed with this software.    *
*******************************************************************************/

#ifndef XLEAFLET_IMAGE_OVERLAY_HPP
#define XLEAFLET_IMAGE_OVERLAY_HPP

#include <array>
#include <string>

#include "xwidgets/xmaterialize.hpp"
#include "xwidgets/xwidget.hpp"

#include "xleaflet_config.hpp"
#include "xraster_layer.hpp"

namespace xleaflet
{
    /*****************************
     * image_overlay declaration *
     *****************************/

    template <class D>
    class ximage_overlay : public xraster_layer<D>
    {
    public:

        using point_type = std::array<double, 2>;
        using bounds_type = std::array<point_type, 2>;

        using base_type = xraster_layer<D>;
        using derived_type = D;

        xeus::xjson get_state() const;
        void apply_patch(const xeus::xjson&);

        XPROPERTY(std::string, derived_type, url, "");
        XPROPERTY(bounds_type, derived_type, bounds);
        XPROPERTY(std::string, derived_type, attribution, "");

    protected:

        ximage_overlay();
        using base_type::base_type;

    private:

        void set_defaults();
    };

    using image_overlay = xw::xmaterialize<ximage_overlay>;

    using image_overlay_generator = xw::xgenerator<ximage_overlay>;

    /********************************
     * image_overlay implementation *
     ********************************/

    template <class D>
    inline xeus::xjson ximage_overlay<D>::get_state() const
    {
        xeus::xjson state = base_type::get_state();

        XOBJECT_SET_PATCH_FROM_PROPERTY(url, state);
        XOBJECT_SET_PATCH_FROM_PROPERTY(bounds, state);
        XOBJECT_SET_PATCH_FROM_PROPERTY(attribution, state);

        return state;
    }

    template <class D>
    inline void ximage_overlay<D>::apply_patch(const xeus::xjson& patch)
    {
        base_type::apply_patch(patch);

        XOBJECT_SET_PROPERTY_FROM_PATCH(url, patch);
        XOBJECT_SET_PROPERTY_FROM_PATCH(bounds, patch);
        XOBJECT_SET_PROPERTY_FROM_PATCH(attribution, patch);
    }

    template <class D>
    inline ximage_overlay<D>::ximage_overlay()
        : base_type()
    {
        set_defaults();
    }

    template <class D>
    inline void ximage_overlay<D>::set_defaults()
    {
        this->_model_name() = "LeafletImageOverlayModel";
        this->_view_name() = "LeafletImageOverlayView";

        this->bounds() = {{{0, 0}, {0, 0}}};

        this->options().insert(
            this->options().end(),
            {
                "attribution"
            }
        );
    }
}

/*********************
 * precompiled types *
 *********************/

#ifndef _WIN32
    extern template class xw::xmaterialize<xleaflet::ximage_overlay>;
    extern template xw::xmaterialize<xleaflet::ximage_overlay>::xmaterialize();
    extern template class xw::xtransport<xw::xmaterialize<xleaflet::ximage_overlay>>;
    extern template class xw::xgenerator<xleaflet::ximage_overlay>;
    extern template xw::xgenerator<xleaflet::ximage_overlay>::xgenerator();
    extern template class xw::xtransport<xw::xgenerator<xleaflet::ximage_overlay>>;
#endif

#endif
