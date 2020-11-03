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

namespace nl = nlohmann;

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

        using layer_list_type = std::vector<xw::xholder>;

        void serialize_state(nl::json&, xeus::buffer_sequence&) const;
        void apply_patch(const nl::json&, const xeus::buffer_sequence&);

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

    /*******************************
     * xlayer_group implementation *
     *******************************/

    template <class D>
    inline void xlayer_group<D>::serialize_state(nl::json& state,
                                                 xeus::buffer_sequence& buffers) const
    {
        base_type::serialize_state(state, buffers);

        using xw::xwidgets_serialize;

        xwidgets_serialize(layers(), state["layers"], buffers);
    }

    template <class D>
    inline void xlayer_group<D>::apply_patch(const nl::json& patch,
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
        this->layers().emplace_back(xw::make_id_holder(l.id()));
        nl::json state;
        xeus::buffer_sequence buffers;
        using xw::xwidgets_serialize;
        xwidgets_serialize(layers(), state["layers"], buffers);
        this->send_patch(std::move(state), std::move(buffers));
    }

    template <class D>
    template <class T>
    inline void xlayer_group<D>::add_layer(xlayer<T>&& l)
    {
        this->layers().emplace_back(xw::make_owning_holder(std::move(l)));
        nl::json state;
        xeus::buffer_sequence buffers;
        using xw::xwidgets_serialize;
        xwidgets_serialize(layers(), state["layers"], buffers);
        this->send_patch(std::move(state), std::move(buffers));
    }

    template <class D>
    template <class T>
    inline void xlayer_group<D>::remove_layer(const xlayer<T>& l)
    {
        this->layers().erase(
            std::remove_if(
                this->layers().begin(), this->layers().end(),
                [&l](const xw::xholder& element) {
                    return element.id() == l.id();
                }
            ),
            this->layers().end()
        );
        nl::json state;
        xeus::buffer_sequence buffers;
        using xw::xwidgets_serialize;
        xwidgets_serialize(layers(), state["layers"], buffers);
        this->send_patch(std::move(state), std::move(buffers));
    }

    template <class D>
    inline void xlayer_group<D>::clear_layers()
    {
        this->layers() = {};
        nl::json state;
        xeus::buffer_sequence buffers;
        using xw::xwidgets_serialize;
        xwidgets_serialize(layers(), state["layers"], buffers);
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

    extern template class xw::xmaterialize<xlf::xlayer_group>;
    extern template class xw::xtransport<xw::xmaterialize<xlf::xlayer_group>>;

#endif
