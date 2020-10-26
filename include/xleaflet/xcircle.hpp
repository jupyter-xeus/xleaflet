/******************************************************************************
* Copyright (c) 2018, Sylvain Corlay and Johan Mabille, Wolf Vollprecht and   *
* Martin Renou                                                                *
*                                                                             *
* Distributed under the terms of the BSD 3-Clause License.                    *
*                                                                             *
* The full license is in the file LICENSE, distributed with this software.    *
*******************************************************************************/

#ifndef XLEAFLET_CIRCLE_HPP
#define XLEAFLET_CIRCLE_HPP

#include <array>

#include "nlohmann/json.hpp"

#include "xwidgets/xmaterialize.hpp"
#include "xwidgets/xwidget.hpp"

#include "xpath.hpp"

namespace nl = nlohmann;

namespace xlf
{
    /**********************
     * circle declaration *
     **********************/

    template <class D>
    class xcircle : public xpath<D>
    {
    public:

        using point_type = std::array<double, 2>;

        using base_type = xpath<D>;
        using derived_type = D;

        void serialize_state(nl::json&, xeus::buffer_sequence&) const;
        void apply_patch(const nl::json&, const xeus::buffer_sequence&);

        XPROPERTY(point_type, derived_type, location);
        XPROPERTY(int, derived_type, radius, 1000);

    protected:

        xcircle();
        using base_type::base_type;

    private:

        void set_defaults();
    };

    using circle = xw::xmaterialize<xcircle>;

    /**************************
     * xcircle implementation *
     **************************/

    template <class D>
    inline void xcircle<D>::serialize_state(nl::json& state,
                                            xeus::buffer_sequence& buffers) const
    {
        base_type::serialize_state(state, buffers);

        using xw::xwidgets_serialize;

        xwidgets_serialize(location(), state["location"], buffers);
        xwidgets_serialize(radius(), state["radius"], buffers);
    }

    template <class D>
    inline void xcircle<D>::apply_patch(const nl::json& patch,
                                        const xeus::buffer_sequence& buffers)
    {
        base_type::apply_patch(patch, buffers);

        using xw::set_property_from_patch;

        set_property_from_patch(location, patch, buffers);
        set_property_from_patch(radius, patch, buffers);
    }

    template <class D>
    inline xcircle<D>::xcircle()
        : base_type()
    {
        set_defaults();
    }

    template <class D>
    inline void xcircle<D>::set_defaults()
    {
        this->_model_name() = "LeafletCircleModel";
        this->_view_name() = "LeafletCircleView";

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

    extern template class xw::xmaterialize<xlf::xcircle>;
    extern template class xw::xtransport<xw::xmaterialize<xlf::xcircle>>;

#endif
