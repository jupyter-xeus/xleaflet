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

        xeus::xjson get_state() const;
        void apply_patch(const xeus::xjson&);

        XPROPERTY(bounds_type, derived_type, bounds);

    protected:

        xrectangle();
        using base_type::base_type;

    private:

        void set_defaults();
    };

    using rectangle = xw::xmaterialize<xrectangle>;

    using rectangle_generator = xw::xgenerator<xrectangle>;

    /*****************************
     * xrectangle implementation *
     *****************************/

    template <class D>
    inline xeus::xjson xrectangle<D>::get_state() const
    {
        xeus::xjson state = base_type::get_state();

        XOBJECT_SET_PATCH_FROM_PROPERTY(bounds, state);

        return state;
    }

    template <class D>
    inline void xrectangle<D>::apply_patch(const xeus::xjson& patch)
    {
        base_type::apply_patch(patch);

        XOBJECT_SET_PROPERTY_FROM_PATCH(bounds, patch);
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

#ifndef _WIN32
    extern template class xw::xmaterialize<xlf::xrectangle>;
    extern template xw::xmaterialize<xlf::xrectangle>::xmaterialize();
    extern template class xw::xtransport<xw::xmaterialize<xlf::xrectangle>>;
    extern template class xw::xgenerator<xlf::xrectangle>;
    extern template xw::xgenerator<xlf::xrectangle>::xgenerator();
    extern template class xw::xtransport<xw::xgenerator<xlf::xrectangle>>;
#endif

#endif
