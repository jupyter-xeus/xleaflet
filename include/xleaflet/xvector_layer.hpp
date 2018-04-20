/******************************************************************************
* Copyright (c) 2018, Sylvain Corlay and Johan Mabille, Wolf Vollprecht and   *
* Martin Renou                                                                *
*                                                                             *
* Distributed under the terms of the BSD 3-Clause License.                    *
*                                                                             *
* The full license is in the file LICENSE, distributed with this software.    *
*******************************************************************************/

#ifndef XLEAFLET_VECTOR_LAYER_HPP
#define XLEAFLET_VECTOR_LAYER_HPP

#include <string>

#include "xwidgets/xmaterialize.hpp"
#include "xwidgets/xwidget.hpp"

#include "xlayer.hpp"

namespace xlf
{
    /****************************
     * vector_layer declaration *
     ****************************/

    template <class D>
    class xvector_layer : public xlayer<D>
    {
    public:

        using base_type = xlayer<D>;
        using derived_type = D;

        void serialize_state(xeus::xjson&, xeus::buffer_sequence&) const;
        void apply_patch(const xeus::xjson&, const xeus::buffer_sequence&);

    protected:

        xvector_layer();
        using base_type::base_type;

    private:

        void set_defaults();
    };

    using vector_layer = xw::xmaterialize<xvector_layer>;

    using vector_layer_generator = xw::xgenerator<xvector_layer>;

    /********************************
     * xvector_layer implementation *
     ********************************/

    template <class D>
    inline void xvector_layer<D>::serialize_state(xeus::xjson& state, xeus::buffer_sequence& buffers) const
    {
        base_type::serialize_state(state, buffers);

    }

    template <class D>
    inline void xvector_layer<D>::apply_patch(const xeus::xjson& patch, const xeus::buffer_sequence& buffers)
    {
        base_type::apply_patch(patch, buffers);
    }

    template <class D>
    inline xvector_layer<D>::xvector_layer()
        : base_type()
    {
        set_defaults();
    }

    template <class D>
    inline void xvector_layer<D>::set_defaults()
    {
        this->_model_name() = "LeafletVectorLayerModel";
        this->_view_name() = "LeafletVectorLayerView";
    }
}

/*********************
 * precompiled types *
 *********************/

#ifndef _WIN32
    extern template class xw::xmaterialize<xlf::xvector_layer>;
    extern template xw::xmaterialize<xlf::xvector_layer>::xmaterialize();
    extern template class xw::xtransport<xw::xmaterialize<xlf::xvector_layer>>;
    extern template class xw::xgenerator<xlf::xvector_layer>;
    extern template xw::xgenerator<xlf::xvector_layer>::xgenerator();
    extern template class xw::xtransport<xw::xgenerator<xlf::xvector_layer>>;
#endif

#endif
