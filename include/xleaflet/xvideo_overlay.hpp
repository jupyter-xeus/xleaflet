/******************************************************************************
* Copyright (c) 2018, Sylvain Corlay and Johan Mabille, Wolf Vollprecht and   *
* Martin Renou                                                                *
*                                                                             *
* Distributed under the terms of the BSD 3-Clause License.                    *
*                                                                             *
* The full license is in the file LICENSE, distributed with this software.    *
*******************************************************************************/

#ifndef XLEAFLET_VIDEO_OVERLAY_HPP
#define XLEAFLET_VIDEO_OVERLAY_HPP

#include <array>
#include <string>

#include "xwidgets/xmaterialize.hpp"
#include "xwidgets/xwidget.hpp"

#include "xleaflet_config.hpp"
#include "xraster_layer.hpp"

namespace xleaflet
{
    /*****************************
     * video_overlay declaration *
     *****************************/

    template <class D>
    class xvideo_overlay : public xraster_layer<D>
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

        xvideo_overlay();
        using base_type::base_type;

    private:

        void set_defaults();
    };

    using video_overlay = xw::xmaterialize<xvideo_overlay>;

    using video_overlay_generator = xw::xgenerator<xvideo_overlay>;

    /********************************
     * video_overlay implementation *
     ********************************/

    template <class D>
    inline xeus::xjson xvideo_overlay<D>::get_state() const
    {
        xeus::xjson state = base_type::get_state();

        XOBJECT_SET_PATCH_FROM_PROPERTY(url, state);
        XOBJECT_SET_PATCH_FROM_PROPERTY(bounds, state);
        XOBJECT_SET_PATCH_FROM_PROPERTY(attribution, state);

        return state;
    }

    template <class D>
    inline void xvideo_overlay<D>::apply_patch(const xeus::xjson& patch)
    {
        base_type::apply_patch(patch);

        XOBJECT_SET_PROPERTY_FROM_PATCH(url, patch);
        XOBJECT_SET_PROPERTY_FROM_PATCH(bounds, patch);
        XOBJECT_SET_PROPERTY_FROM_PATCH(attribution, patch);
    }

    template <class D>
    inline xvideo_overlay<D>::xvideo_overlay()
        : base_type()
    {
        set_defaults();
    }

    template <class D>
    inline void xvideo_overlay<D>::set_defaults()
    {
        this->_model_name() = "LeafletVideoOverlayModel";
        this->_view_name() = "LeafletVideoOverlayView";

        this->bounds() = {{{0, 0}, {0, 0}}};
    }
}

#endif
