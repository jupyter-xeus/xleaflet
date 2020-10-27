/******************************************************************************
* Copyright (c) 2018, Sylvain Corlay and Johan Mabille, Wolf Vollprecht and   *
* Martin Renou                                                                *
*                                                                             *
* Distributed under the terms of the BSD 3-Clause License.                    *
*                                                                             *
* The full license is in the file LICENSE, distributed with this software.    *
*******************************************************************************/

#ifndef XLEAFLET_RECTANGLE_HPP
#define XLEAFLET_RECTANGLE_HPP

#include <array>

#include "xwidgets/xmaterialize.hpp"
#include "xwidgets/xwidget.hpp"

#include "xpolygon.hpp"

namespace nl = nlohmann;

namespace xlf
{
    /*************************
     * rectangle declaration *
     *************************/

    template <class D>
    class xrectangle : public xpolygon<D>
    {
    public:

        using point_type = std::array<double, 2>;
        using bounds_type = std::array<point_type, 2>;

        using base_type = xpolygon<D>;
        using derived_type = D;

        void serialize_state(nl::json&, xeus::buffer_sequence&) const;
        void apply_patch(const nl::json&, const xeus::buffer_sequence&);

        XPROPERTY(bounds_type, derived_type, bounds);

    protected:

        xrectangle();
        using base_type::base_type;

    private:

        void set_defaults();
    };

    using rectangle = xw::xmaterialize<xrectangle>;

    /*****************************
     * xrectangle implementation *
     *****************************/

    template <class D>
    inline void xrectangle<D>::serialize_state(nl::json& state,
                                               xeus::buffer_sequence& buffers) const
    {
        base_type::serialize_state(state, buffers);

        using xw::xwidgets_serialize;

        xwidgets_serialize(bounds(), state["bounds"], buffers);
    }

    template <class D>
    inline void xrectangle<D>::apply_patch(const nl::json& patch,
                                           const xeus::buffer_sequence& buffers)
    {
        base_type::apply_patch(patch, buffers);

        using xw::set_property_from_patch;

        set_property_from_patch(bounds, patch, buffers);
    }

    template <class D>
    inline xrectangle<D>::xrectangle()
        : base_type()
    {
        set_defaults();
    }

    template <class D>
    inline void xrectangle<D>::set_defaults()
    {
        this->_model_name() = "LeafletRectangleModel";
        this->_view_name() = "LeafletRectangleView";
    }
}

/*********************
 * precompiled types *
 *********************/

    extern template class xw::xmaterialize<xlf::xrectangle>;
    extern template class xw::xtransport<xw::xmaterialize<xlf::xrectangle>>;

#endif
