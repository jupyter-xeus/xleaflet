/******************************************************************************
* Copyright (c) 2018, Sylvain Corlay and Johan Mabille, Wolf Vollprecht and   *
* Martin Renou                                                                *
*                                                                             *
* Distributed under the terms of the BSD 3-Clause License.                    *
*                                                                             *
* The full license is in the file LICENSE, distributed with this software.    *
*******************************************************************************/

#ifndef XLEAFLET_SPLIT_MAP_CONTROL_HPP
#define XLEAFLET_SPLIT_MAP_CONTROL_HPP

#include <string>
#include <vector>

#include "xwidgets/xholder.hpp"
#include "xwidgets/xmaterialize.hpp"
#include "xwidgets/xwidget.hpp"

#include "xcontrol.hpp"
#include "xleaflet_config.hpp"
#include "xtile_layer.hpp"

namespace xlf
{
    /*********************************
     * split_map_control declaration *
     *********************************/

    template <class D>
    class xsplit_map_control : public xcontrol<D>
    {
    public:

        using base_type = xcontrol<D>;
        using derived_type = D;

        using tile_layer_type = xw::xholder<xtile_layer>;

        void serialize_state(xeus::xjson&, xeus::buffer_sequence&) const;
        void apply_patch(const xeus::xjson&, const xeus::buffer_sequence&);

        XPROPERTY(tile_layer_type, derived_type, left_layer);
        XPROPERTY(tile_layer_type, derived_type, right_layer);

    protected:

        xsplit_map_control();
        using base_type::base_type;

    private:

        void set_defaults();
    };

    using split_map_control = xw::xmaterialize<xsplit_map_control>;

    using split_map_control_generator = xw::xgenerator<xsplit_map_control>;

    /*************************************
     * xsplit_map_control implementation *
     *************************************/

    template <class D>
    inline void xsplit_map_control<D>::serialize_state(xeus::xjson& state,
                                                       xeus::buffer_sequence& buffers) const
    {
        base_type::serialize_state(state, buffers);

        using xw::set_patch_from_property;

        set_patch_from_property(left_layer, state, buffers);
        set_patch_from_property(right_layer, state, buffers);
    }

    template <class D>
    inline void xsplit_map_control<D>::apply_patch(const xeus::xjson& patch,
                                                   const xeus::buffer_sequence& buffers)
    {
        base_type::apply_patch(patch, buffers);

        using xw::set_property_from_patch;

        set_property_from_patch(left_layer, patch, buffers);
        set_property_from_patch(right_layer, patch, buffers);
    }

    template <class D>
    inline xsplit_map_control<D>::xsplit_map_control()
        : base_type()
    {
        set_defaults();
    }

    template <class D>
    inline void xsplit_map_control<D>::set_defaults()
    {
        this->_model_name() = "LeafletSplitMapControlModel";
        this->_view_name() = "LeafletSplitMapControlView";

        this->left_layer() = tile_layer();
        this->right_layer() = tile_layer();
    }

}

/*********************
 * precompiled types *
 *********************/

#ifndef _WIN32
    extern template class xw::xmaterialize<xlf::xsplit_map_control>;
    extern template xw::xmaterialize<xlf::xsplit_map_control>::xmaterialize();
    extern template class xw::xtransport<xw::xmaterialize<xlf::xsplit_map_control>>;
    extern template class xw::xgenerator<xlf::xsplit_map_control>;
    extern template xw::xgenerator<xlf::xsplit_map_control>::xgenerator();
    extern template class xw::xtransport<xw::xgenerator<xlf::xsplit_map_control>>;
#endif

#endif
