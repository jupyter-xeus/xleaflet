/******************************************************************************
* Copyright (c) 2018, Sylvain Corlay and Johan Mabille, and Wolf Vollprecht   *
*                                                                             *
* Distributed under the terms of the BSD 3-Clause License.                    *
*                                                                             *
* The full license is in the file LICENSE, distributed with this software.    *
*******************************************************************************/

#ifndef XLEAFLET_LAYER_GROUP_HPP
#define XLEAFLET_LAYER_GROUP_HPP

#include <algorithm>
#include <utility>
#include <vector>

#include "xwidgets/xholder.hpp"
#include "xwidgets/xmaterialize.hpp"
#include "xwidgets/xwidget.hpp"

#include "xlayer.hpp"
#include "xleaflet_config.hpp"

namespace xlf
{
    /***************************
     * layer_group declaration *
     ***************************/

    template <class D>
    class xlayer_group : public xlayer<D>
    {
    public:

        using base_type = xlayer<D>;
        using derived_type = D;

#ifdef _MSC_VER
        template <class T>
        using layer_type = xlayer<T>;

        using layer_list_type = std::vector<xw::xholder<layer_type>>;
#else
        using layer_list_type = std::vector<xw::xholder<xlayer>>;
#endif

        void serialize_state(xeus::xjson&, xeus::buffer_sequence&) const;
        void apply_patch(const xeus::xjson&, const xeus::buffer_sequence&);

        template <class T>
        void add_layer(const xlayer<T>& l);

        template <class T>
        void add_layer(xlayer<T>&& l);

        template <class T>
        void remove_layer(const xlayer<T>& l);

        void clear_layers();

        XPROPERTY(layer_list_type, derived_type, layers);

    protected:

        xlayer_group();
        using base_type::base_type;

    private:

        void set_defaults();
    };

    using layer_group = xw::xmaterialize<xlayer_group>;

    using layer_group_generator = xw::xgenerator<xlayer_group>;

    /*******************************
     * xlayer_group implementation *
     *******************************/

    template <class D>
    inline void xlayer_group<D>::serialize_state(xeus::xjson& state,
                                                 xeus::buffer_sequence& buffers) const
    {
        base_type::serialize_state(state, buffers);

        using xw::set_patch_from_property;

        set_patch_from_property(layers, state, buffers);
    }

    template <class D>
    inline void xlayer_group<D>::apply_patch(const xeus::xjson& patch,
                                             const xeus::buffer_sequence& buffers)
    {
        base_type::apply_patch(patch, buffers);

        using xw::set_property_from_patch;

        set_property_from_patch(layers, patch, buffers);
    }

    template <class D>
    template <class T>
    inline void xlayer_group<D>::add_layer(const xlayer<T>& l)
    {
        this->layers().emplace_back(xw::make_id_holder<xlayer>(l.id()));
        xeus::xjson state;
        xeus::buffer_sequence buffers;
        using xw::set_patch_from_property;
        set_patch_from_property(layers, state, buffers);
        this->send_patch(std::move(state), std::move(buffers));
    }

    template <class D>
    template <class T>
    inline void xlayer_group<D>::add_layer(xlayer<T>&& l)
    {
        this->layers().emplace_back(xw::make_owning_holder(std::move(l)));
        xeus::xjson state;
        xeus::buffer_sequence buffers;
        using xw::set_patch_from_property;
        set_patch_from_property(layers, state, buffers);
        this->send_patch(std::move(state), std::move(buffers));
    }

    template <class D>
    template <class T>
    inline void xlayer_group<D>::remove_layer(const xlayer<T>& l)
    {
        this->layers().erase(
            std::remove_if(
                this->layers().begin(), this->layers().end(),
                [&l](const xw::xholder<xlayer>& element) {
                    return element.id() == l.id();
                }
            ),
            this->layers().end()
        );
        xeus::xjson state;
        xeus::buffer_sequence buffers;
        using xw::set_patch_from_property;
        set_patch_from_property(layers, state, buffers);
        this->send_patch(std::move(state), std::move(buffers));
    }

    template <class D>
    inline void xlayer_group<D>::clear_layers()
    {
        this->layers() = {};
        xeus::xjson state;
        xeus::buffer_sequence buffers;
        using xw::set_patch_from_property;
        set_patch_from_property(layers, state, buffers);
        this->send_patch(std::move(state), std::move(buffers));
    }

    template <class D>
    inline xlayer_group<D>::xlayer_group()
        : base_type()
    {
        set_defaults();
    }

    template <class D>
    inline void xlayer_group<D>::set_defaults()
    {
        this->_model_name() = "LeafletLayerGroupModel";
        this->_view_name() = "LeafletLayerGroupView";
    }
}

/*********************
 * precompiled types *
 *********************/

#ifndef _WIN32
    extern template class xw::xmaterialize<xlf::xlayer_group>;
    extern template xw::xmaterialize<xlf::xlayer_group>::xmaterialize();
    extern template class xw::xtransport<xw::xmaterialize<xlf::xlayer_group>>;
    extern template class xw::xgenerator<xlf::xlayer_group>;
    extern template xw::xgenerator<xlf::xlayer_group>::xgenerator();
    extern template class xw::xtransport<xw::xgenerator<xlf::xlayer_group>>;
#endif

#endif
