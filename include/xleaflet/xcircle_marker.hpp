/******************************************************************************
* Copyright (c) 2018, Sylvain Corlay and Johan Mabille, Wolf Vollprecht and   *
* Martin Renou                                                                *
*                                                                             *
* Distributed under the terms of the BSD 3-Clause License.                    *
*                                                                             *
* The full license is in the file LICENSE, distributed with this software.    *
*******************************************************************************/

#ifndef XLEAFLET_CIRCLE_MARKER_HPP
#define XLEAFLET_CIRCLE_MARKER_HPP

#include "xwidgets/xmaterialize.hpp"
#include "xwidgets/xwidget.hpp"

#include "xcircle.hpp"

namespace xlf
{
    /*****************************
     * circle_marker declaration *
     *****************************/

    template <class D>
    class xcircle_marker : public xcircle<D>
    {
    public:

        using base_type = xcircle<D>;
        using derived_type = D;

        void serialize_state(xeus::xjson&, xeus::buffer_sequence&) const;
        void apply_patch(const xeus::xjson&, const xeus::buffer_sequence&);

        XPROPERTY(int, derived_type, radius, 10);

    protected:

        xcircle_marker();
        using base_type::base_type;

    private:

        void set_defaults();
    };

    using circle_marker = xw::xmaterialize<xcircle_marker>;

    using circle_marker_generator = xw::xgenerator<xcircle_marker>;

    /*********************************
     * xcircle_marker implementation *
     *********************************/

    template <class D>
    inline void xcircle_marker<D>::serialize_state(xeus::xjson& state, xeus::buffer_sequence& buffers) const
    {
        base_type::serialize_state(state, buffers);

        xw::set_patch_from_property(radius, state, buffers);
    }

    template <class D>
    inline void xcircle_marker<D>::apply_patch(const xeus::xjson& patch, const xeus::buffer_sequence& buffers)
    {
        base_type::apply_patch(patch, buffers);

        xw::set_property_from_patch(radius, patch, buffers);
    }

    template <class D>
    inline xcircle_marker<D>::xcircle_marker()
        : base_type()
    {
        set_defaults();
    }

    template <class D>
    inline void xcircle_marker<D>::set_defaults()
    {
        this->_model_name() = "LeafletCircleMarkerModel";
        this->_view_name() = "LeafletCircleMarkerView";

        this->options().insert(
            this->options().end(),
            {
                "radius"
            }
        );
    }
}

/*********************
 * precompiled types *
 *********************/

#ifndef _WIN32
    extern template class xw::xmaterialize<xlf::xcircle_marker>;
    extern template xw::xmaterialize<xlf::xcircle_marker>::xmaterialize();
    extern template class xw::xtransport<xw::xmaterialize<xlf::xcircle_marker>>;
    extern template class xw::xgenerator<xlf::xcircle_marker>;
    extern template xw::xgenerator<xlf::xcircle_marker>::xgenerator();
    extern template class xw::xtransport<xw::xgenerator<xlf::xcircle_marker>>;
#endif

#endif
