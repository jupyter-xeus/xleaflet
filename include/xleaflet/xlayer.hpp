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
#include "xwidgets/xwidget.hpp"

#include "xleaflet_config.hpp"

namespace xleaflet
{
    /*********************
     * layer declaration *
     *********************/

    template <class D>
    class xlayer : public xw::xwidget<D>
    {
    public:

        using base_type = xw::xwidget<D>;
        using derived_type = D;

        xeus::xjson get_state() const;
        void apply_patch(const xeus::xjson&);

        XPROPERTY(std::string, derived_type, name, "");
        XPROPERTY(bool, derived_type, base, true);
        XPROPERTY(bool, derived_type, bottom, true);
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
    inline xeus::xjson xlayer<D>::get_state() const
    {
        xeus::xjson state = base_type::get_state();

        XOBJECT_SET_PATCH_FROM_PROPERTY(name, state);
        XOBJECT_SET_PATCH_FROM_PROPERTY(base, state);
        XOBJECT_SET_PATCH_FROM_PROPERTY(bottom, state);
        XOBJECT_SET_PATCH_FROM_PROPERTY(options, state);

        return state;
    }

    template <class D>
    inline void xlayer<D>::apply_patch(const xeus::xjson& patch)
    {
        base_type::apply_patch(patch);

        XOBJECT_SET_PROPERTY_FROM_PATCH(name, patch);
        XOBJECT_SET_PROPERTY_FROM_PATCH(base, patch);
        XOBJECT_SET_PROPERTY_FROM_PATCH(bottom, patch);
        XOBJECT_SET_PROPERTY_FROM_PATCH(options, patch);
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
        this->_model_module_version() = XJUPYTER_LEAFLET_VERSION;
        this->_view_module_version() = XJUPYTER_LEAFLET_VERSION;

        this->options() = std::vector<std::string>();
    }

}

/*********************
 * precompiled types *
 *********************/

#ifndef _WIN32
    extern template class xw::xmaterialize<xleaflet::xlayer>;
    extern template xw::xmaterialize<xleaflet::xlayer>::xmaterialize();
    extern template class xw::xtransport<xw::xmaterialize<xleaflet::xlayer>>;
    extern template class xw::xgenerator<xleaflet::xlayer>;
    extern template xw::xgenerator<xleaflet::xlayer>::xgenerator();
    extern template class xw::xtransport<xw::xgenerator<xleaflet::xlayer>>;
#endif

#endif
