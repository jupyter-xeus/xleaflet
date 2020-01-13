/******************************************************************************
* Copyright (c) 2018, Sylvain Corlay and Johan Mabille, Wolf Vollprecht and   *
* Martin Renou                                                                *
*                                                                             *
* Distributed under the terms of the BSD 3-Clause License.                    *
*                                                                             *
* The full license is in the file LICENSE, distributed with this software.    *
*******************************************************************************/

#ifndef XLEAFLET_FEATURE_GROUP_HPP
#define XLEAFLET_FEATURE_GROUP_HPP

#include "xwidgets/xmaterialize.hpp"
#include "xwidgets/xwidget.hpp"

#include "xlayer_group.hpp"
#include "xleaflet_config.hpp"

namespace xlf
{
    /*****************************
     * feature_group declaration *
     *****************************/

    template <class D>
    class xfeature_group : public xlayer_group<D>
    {
    public:

        using base_type = xlayer_group<D>;
        using derived_type = D;

    protected:

        xfeature_group();
        using base_type::base_type;

    private:

        void set_defaults();
    };

    using feature_group = xw::xmaterialize<xfeature_group>;

    /*********************************
     * xfeature_group implementation *
     *********************************/

    template <class D>
    inline xfeature_group<D>::xfeature_group()
        : base_type()
    {
        set_defaults();
    }

    template <class D>
    inline void xfeature_group<D>::set_defaults()
    {
        this->_model_name() = "LeafletFeatureGroupModel";
        this->_view_name() = "LeafletFeatureGroupView";
    }
}

/*********************
 * precompiled types *
 *********************/

#ifndef _WIN32
    extern template class xw::xmaterialize<xlf::xfeature_group>;
    extern template xw::xmaterialize<xlf::xfeature_group>::xmaterialize();
    extern template class xw::xtransport<xw::xmaterialize<xlf::xfeature_group>>;
#endif

#endif
