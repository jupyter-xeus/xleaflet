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

#include "xwidgets/xmaterialize.hpp"
#include "xwidgets/xholder.hpp"
#include "xwidgets/xwidget.hpp"

#include "xleaflet_config.hpp"
#include "xtile_layer.hpp"
#include "xcontrol.hpp"

namespace xleaflet
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

        xeus::xjson get_state() const;
        void apply_patch(const xeus::xjson&);

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
     inline xeus::xjson xsplit_map_control<D>::get_state() const
     {
         xeus::xjson state = base_type::get_state();

         XOBJECT_SET_PATCH_FROM_PROPERTY(left_layer, state);
         XOBJECT_SET_PATCH_FROM_PROPERTY(right_layer, state);

         return state;
     }

     template <class D>
     inline void xsplit_map_control<D>::apply_patch(const xeus::xjson& patch)
     {
         base_type::apply_patch(patch);

         XOBJECT_SET_PROPERTY_FROM_PATCH(left_layer, patch);
         XOBJECT_SET_PROPERTY_FROM_PATCH(right_layer, patch);
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

#endif
