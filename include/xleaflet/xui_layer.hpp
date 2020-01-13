/******************************************************************************
* Copyright (c) 2018, Sylvain Corlay and Johan Mabille, and Wolf Vollprecht   *
*                                                                             *
* Distributed under the terms of the BSD 3-Clause License.                    *
*                                                                             *
* The full license is in the file LICENSE, distributed with this software.    *
*******************************************************************************/

#ifndef XLEAFLET_UI_LAYER_HPP
#define XLEAFLET_UI_LAYER_HPP

#include "xwidgets/xmaterialize.hpp"

#include "xlayer.hpp"

namespace nl = nlohmann;

namespace xlf
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

        void serialize_state(nl::json&, xeus::buffer_sequence&) const;
        void apply_patch(const nl::json&, const xeus::buffer_sequence&);

    protected:

        xui_layer();
        using base_type::base_type;

    private:

        void set_defaults();
    };

    using ui_layer = xw::xmaterialize<xui_layer>;

    /****************************
     * xui_layer implementation *
     ****************************/

    template <class D>
    inline void xui_layer<D>::serialize_state(nl::json& state,
                                              xeus::buffer_sequence& buffers) const
    {
        base_type::serialize_state(state, buffers);
    }

    template <class D>
    inline void xui_layer<D>::apply_patch(const nl::json& patch,
                                          const xeus::buffer_sequence& buffers)
    {
        base_type::apply_patch(patch, buffers);
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

/*********************
 * precompiled types *
 *********************/

#ifndef _WIN32
    extern template class xw::xmaterialize<xlf::xui_layer>;
    extern template xw::xmaterialize<xlf::xui_layer>::xmaterialize();
    extern template class xw::xtransport<xw::xmaterialize<xlf::xui_layer>>;
#endif

#endif
