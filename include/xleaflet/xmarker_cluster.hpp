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

#include <vector>

#include "xwidgets/xholder.hpp"
#include "xwidgets/xmaterialize.hpp"
#include "xwidgets/xwidget.hpp"

#include "xlayer.hpp"
#include "xleaflet_config.hpp"
#include "xmarker.hpp"

namespace nl = nlohmann;

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

        using marker_list_type = std::vector<xw::xholder>;

        void serialize_state(nl::json&, xeus::buffer_sequence&) const;
        void apply_patch(const nl::json&, const xeus::buffer_sequence&);

        XPROPERTY(std::vector<xw::xholder>, derived_type, markers);

    protected:

        xmarker_cluster();
        using base_type::base_type;

    private:

        void set_defaults();
    };

    using marker_cluster = xw::xmaterialize<xmarker_cluster>;

    /**********************************
     * xmarker_cluster implementation *
     **********************************/

    template <class D>
    inline void xmarker_cluster<D>::serialize_state(nl::json& state,
                                                    xeus::buffer_sequence& buffers) const
    {
        base_type::serialize_state(state, buffers);

        using xw::xwidgets_serialize;

        xwidgets_serialize(markers(), state["markers"], buffers);
    }

    template <class D>
    inline void xmarker_cluster<D>::apply_patch(const nl::json& patch,
                                                const xeus::buffer_sequence& buffers)
    {
        base_type::apply_patch(patch, buffers);

        using xw::set_property_from_patch;

        set_property_from_patch(markers, patch, buffers);
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

    extern template class xw::xmaterialize<xlf::xmarker_cluster>;
    extern template class xw::xtransport<xw::xmaterialize<xlf::xmarker_cluster>>;

#endif
