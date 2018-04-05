/******************************************************************************
* Copyright (c) 2018, Sylvain Corlay and Johan Mabille, and Wolf Vollprecht   *
*                                                                             *
* Distributed under the terms of the BSD 3-Clause License.                    *
*                                                                             *
* The full license is in the file LICENSE, distributed with this software.    *
*******************************************************************************/

#ifndef XLEAFLET_UI_LAYER_HPP
#define XLEAFLET_UI_LAYER_HPP

#include <string>

#include "xwidgets/xmaterialize.hpp"

#include "xlayer.hpp"

namespace xleaflet
{
    /************************
     * ui_layer declaration *
     ************************/

    template <class D>
    class xui_layer : public xlayer<D>
    {
    public:

        using base_type = xlayer<D>;
        using derived_type = D;

        xeus::xjson get_state() const;
        void apply_patch(const xeus::xjson&);

    protected:

        xui_layer();
        using base_type::base_type;

    private:

        void set_defaults();
    };

    using ui_layer = xw::xmaterialize<xui_layer>;

    using ui_layer_generator = xw::xgenerator<xui_layer>;

    /****************************
     * xui_layer implementation *
     ****************************/

    template <class D>
    inline xeus::xjson xui_layer<D>::get_state() const
    {
        xeus::xjson state = base_type::get_state();

        return state;
    }

    template <class D>
    inline void xui_layer<D>::apply_patch(const xeus::xjson& patch)
    {
        base_type::apply_patch(patch);
    }

    template <class D>
    inline xui_layer<D>::xui_layer()
        : base_type()
    {
        set_defaults();
    }

    template <class D>
    inline void xui_layer<D>::set_defaults()
    {
        this->_model_name() = "LeafletUILayerModel";
        this->_view_name() = "LeafletUILayerView";
    }
}

#endif
