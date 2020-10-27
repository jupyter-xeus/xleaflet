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

namespace nl = nlohmann;

namespace xlf
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

        void serialize_state(nl::json&, xeus::buffer_sequence&) const;
        void apply_patch(const nl::json&, const xeus::buffer_sequence&);

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

    /********************************
     * image_overlay implementation *
     ********************************/

    template <class D>
    inline void ximage_overlay<D>::serialize_state(nl::json& state,
                                                   xeus::buffer_sequence& buffers) const
    {
        base_type::serialize_state(state, buffers);

        using xw::xwidgets_serialize;

        xwidgets_serialize(url(), state["url"], buffers);
        xwidgets_serialize(bounds(), state["bounds"], buffers);
        xwidgets_serialize(attribution(), state["attribution"], buffers);
    }

    template <class D>
    inline void ximage_overlay<D>::apply_patch(const nl::json& patch,
                                               const xeus::buffer_sequence& buffers)
    {
        base_type::apply_patch(patch, buffers);

        using xw::set_property_from_patch;

        set_property_from_patch(url, patch, buffers);
        set_property_from_patch(bounds, patch, buffers);
        set_property_from_patch(attribution, patch, buffers);
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

    extern template class xw::xmaterialize<xlf::ximage_overlay>;
    extern template class xw::xtransport<xw::xmaterialize<xlf::ximage_overlay>>;

#endif
