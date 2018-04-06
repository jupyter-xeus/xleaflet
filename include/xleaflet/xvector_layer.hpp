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

namespace xleaflet
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

        xeus::xjson get_state() const;
        void apply_patch(const xeus::xjson&);

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
    inline xeus::xjson xvector_layer<D>::get_state() const
    {
        xeus::xjson state = base_type::get_state();

        return state;
    }

    template <class D>
    inline void xvector_layer<D>::apply_patch(const xeus::xjson& patch)
    {
        base_type::apply_patch(patch);
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

#endif
