/******************************************************************************
* Copyright (c) 2018, Sylvain Corlay and Johan Mabille, and Wolf Vollprecht   *
*                                                                             *
* Distributed under the terms of the BSD 3-Clause License.                    *
*                                                                             *
* The full license is in the file LICENSE, distributed with this software.    *
*******************************************************************************/

#ifndef XLEAFLET_LAYER_HPP
#define XLEAFLET_LAYER_HPP

#include <string>
#include <vector>

#include "xwidgets/xmaterialize.hpp"
#include "xwidgets/xobject.hpp"

#include "xleaflet_config.hpp"

namespace xlf
{
    /*********************
     * layer declaration *
     *********************/

    template <class D>
    class xlayer : public xw::xobject<D>
    {
    public:

        using base_type = xw::xobject<D>;
        using derived_type = D;

        using widget_type = xw::xholder<xw::xobject>;

        void serialize_state(xeus::xjson&, xeus::buffer_sequence&) const;
        void apply_patch(const xeus::xjson&, const xeus::buffer_sequence&);

        XPROPERTY(std::string, derived_type, name, "");
        XPROPERTY(bool, derived_type, base, true);
        XPROPERTY(bool, derived_type, bottom, true);
        XPROPERTY(xtl::xoptional<widget_type>, derived_type, popup);
        XPROPERTY(std::vector<std::string>, derived_type, options);

    protected:

        xlayer();
        using base_type::base_type;

    private:

        void set_defaults();
    };

    using layer = xw::xmaterialize<xlayer>;

    using layer_generator = xw::xgenerator<xlayer>;

    /*************************
     * xlayer implementation *
     *************************/

    template <class D>
    inline void xlayer<D>::serialize_state(xeus::xjson& state,
                                           xeus::buffer_sequence& buffers) const
    {
        base_type::serialize_state(state, buffers);

        using xw::set_patch_from_property;

        set_patch_from_property(name, state, buffers);
        set_patch_from_property(base, state, buffers);
        set_patch_from_property(bottom, state, buffers);
        set_patch_from_property(popup, state, buffers);
        set_patch_from_property(options, state, buffers);
    }

    template <class D>
    inline void xlayer<D>::apply_patch(const xeus::xjson& patch,
                                       const xeus::buffer_sequence& buffers)
    {
        base_type::apply_patch(patch, buffers);

        using xw::set_property_from_patch;

        set_property_from_patch(name, patch, buffers);
        set_property_from_patch(base, patch, buffers);
        set_property_from_patch(bottom, patch, buffers);
        set_property_from_patch(popup, patch, buffers);
        set_property_from_patch(options, patch, buffers);
    }

    template <class D>
    inline xlayer<D>::xlayer()
        : base_type()
    {
        set_defaults();
    }

    template <class D>
    inline void xlayer<D>::set_defaults()
    {
        this->_model_module() = "jupyter-leaflet";
        this->_view_module() = "jupyter-leaflet";
        this->_model_name() = "LeafletLayerModel";
        this->_view_name() = "LeafletLayerView";
        this->_model_module_version() = jupyter_leaflet_semver();
        this->_view_module_version() = jupyter_leaflet_semver();

        this->options() = std::vector<std::string>();
    }

}

/*********************
 * precompiled types *
 *********************/

#ifndef _WIN32
    extern template class xw::xmaterialize<xlf::xlayer>;
    extern template xw::xmaterialize<xlf::xlayer>::xmaterialize();
    extern template class xw::xtransport<xw::xmaterialize<xlf::xlayer>>;
    extern template class xw::xgenerator<xlf::xlayer>;
    extern template xw::xgenerator<xlf::xlayer>::xgenerator();
    extern template class xw::xtransport<xw::xgenerator<xlf::xlayer>>;
#endif

#endif
