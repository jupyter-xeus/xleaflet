/******************************************************************************
* Copyright (c) 2018, Sylvain Corlay and Johan Mabille, Wolf Vollprecht and   *
* Martin Renou                                                                *
*                                                                             *
* Distributed under the terms of the BSD 3-Clause License.                    *
*                                                                             *
* The full license is in the file LICENSE, distributed with this software.    *
*******************************************************************************/

#ifndef XLEAFLET_MARKER_CLUSTER_HPP
#define XLEAFLET_MARKER_CLUSTER_HPP

#include <string>

#include "xwidgets/xmaterialize.hpp"
#include "xwidgets/xholder.hpp"
#include "xwidgets/xwidget.hpp"

#include "xleaflet_config.hpp"
#include "xlayer.hpp"
#include "xmarker.hpp"

namespace xlf
{
    /******************************
     * marker_cluster declaration *
     ******************************/

    template <class D>
    class xmarker_cluster : public xlayer<D>
    {
    public:

        using base_type = xlayer<D>;
        using derived_type = D;

        using marker_list_type = std::vector<xw::xholder<xmarker>>;

        void serialize_state(xeus::xjson&, xeus::buffer_sequence&) const;
        void apply_patch(const xeus::xjson&, const xeus::buffer_sequence&);

        XPROPERTY(std::vector<xw::xholder<xmarker>>, derived_type, markers);

    protected:

        xmarker_cluster();
        using base_type::base_type;

    private:

        void set_defaults();
    };

    using marker_cluster = xw::xmaterialize<xmarker_cluster>;

    using marker_cluster_generator = xw::xgenerator<xmarker_cluster>;

    /**********************************
     * xmarker_cluster implementation *
     **********************************/

    template <class D>
    inline void xmarker_cluster<D>::serialize_state(xeus::xjson& state, xeus::buffer_sequence& buffers) const
    {
        base_type::serialize_state(state, buffers);

        xw::set_patch_from_property(markers, state, buffers);
    }

    template <class D>
    inline void xmarker_cluster<D>::apply_patch(const xeus::xjson& patch, const xeus::buffer_sequence& buffers)
    {
        base_type::apply_patch(patch, buffers);

        xw::set_property_from_patch(markers, patch, buffers);
    }

    template <class D>
    inline xmarker_cluster<D>::xmarker_cluster()
        : base_type()
    {
        set_defaults();
    }

    template <class D>
    inline void xmarker_cluster<D>::set_defaults()
    {
        this->_model_name() = "LeafletMarkerClusterModel";
        this->_view_name() = "LeafletMarkerClusterView";
    }
}

/*********************
 * precompiled types *
 *********************/

#ifndef _WIN32
    extern template class xw::xmaterialize<xlf::xmarker_cluster>;
    extern template xw::xmaterialize<xlf::xmarker_cluster>::xmaterialize();
    extern template class xw::xtransport<xw::xmaterialize<xlf::xmarker_cluster>>;
    extern template class xw::xgenerator<xlf::xmarker_cluster>;
    extern template xw::xgenerator<xlf::xmarker_cluster>::xgenerator();
    extern template class xw::xtransport<xw::xgenerator<xlf::xmarker_cluster>>;
#endif

#endif
