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

namespace xleaflet
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

#ifdef _MSC_VER
        template <class T>
        using marker_type = xmarker<T>;

        using marker_list_type = std::vector<xw::xholder<marker_type>>;
#else
        using marker_list_type = std::vector<xw::xholder<xmarker>>;
#endif

        xeus::xjson get_state() const;
        void apply_patch(const xeus::xjson&);

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
    inline xeus::xjson xmarker_cluster<D>::get_state() const
    {
        xeus::xjson state = base_type::get_state();

        XOBJECT_SET_PATCH_FROM_PROPERTY(markers, state);

        return state;
    }

    template <class D>
    inline void xmarker_cluster<D>::apply_patch(const xeus::xjson& patch)
    {
        base_type::apply_patch(patch);

        XOBJECT_SET_PROPERTY_FROM_PATCH(markers, patch);
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

#endif
