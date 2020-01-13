/******************************************************************************
* Copyright (c) 2018, Sylvain Corlay and Johan Mabille, Wolf Vollprecht and   *
* Martin Renou                                                                *
*                                                                             *
* Distributed under the terms of the BSD 3-Clause License.                    *
*                                                                             *
* The full license is in the file LICENSE, distributed with this software.    *
*******************************************************************************/

#ifndef XLEAFLET_CONTROL_HPP
#define XLEAFLET_CONTROL_HPP

#include <string>
#include <vector>

#include "nlohmann/json.hpp"

#include "xwidgets/xmaterialize.hpp"
#include "xwidgets/xobject.hpp"
#include "xwidgets/xeither.hpp"
#include "xleaflet_config.hpp"

namespace nl = nlohmann;

namespace xlf
{
    /*********************
     * control declaration *
     *********************/

    template <class D>
    class xcontrol : public xw::xobject<D>
    {
    public:

        using base_type = xw::xobject<D>;
        using derived_type = D;

        void serialize_state(nl::json&, xeus::buffer_sequence&) const;
        void apply_patch(const nl::json&, const xeus::buffer_sequence&);

        XPROPERTY(std::vector<std::string>, derived_type, options);
        XPROPERTY(std::string, derived_type, position, "topleft", XEITHER("topright", "topleft", "bottomright", "bottomleft"));

    protected:

        xcontrol();
        using base_type::base_type;

    private:

        void set_defaults();
    };

    using control = xw::xmaterialize<xcontrol>;

    /***************************
     * xcontrol implementation *
     ***************************/

    template <class D>
    inline void xcontrol<D>::serialize_state(nl::json& state,
                                             xeus::buffer_sequence& buffers) const
    {
        base_type::serialize_state(state, buffers);

        using xw::xwidgets_serialize;

        xwidgets_serialize(options(), state["options"], buffers);
        xwidgets_serialize(position(), state["position"], buffers);
    }

    template <class D>
    inline void xcontrol<D>::apply_patch(const nl::json& patch,
                                         const xeus::buffer_sequence& buffers)
    {
        base_type::apply_patch(patch, buffers);

        using xw::set_property_from_patch;

        set_property_from_patch(options, patch, buffers);
        set_property_from_patch(position, patch, buffers);
    }

    template <class D>
    inline xcontrol<D>::xcontrol()
        : base_type()
    {
        set_defaults();
    }

    template <class D>
    inline void xcontrol<D>::set_defaults()
    {
        this->_model_module() = "jupyter-leaflet";
        this->_view_module() = "jupyter-leaflet";
        this->_model_name() = "LeafletControlModel";
        this->_view_name() = "LeafletControlView";
        this->_model_module_version() = jupyter_leaflet_semver();
        this->_view_module_version() = jupyter_leaflet_semver();
        this->options() = {"position"};
    }

}

/*********************
 * precompiled types *
 *********************/

#ifndef _WIN32
    extern template class xw::xmaterialize<xlf::xcontrol>;
    extern template xw::xmaterialize<xlf::xcontrol>::xmaterialize();
    extern template class xw::xtransport<xw::xmaterialize<xlf::xcontrol>>;
#endif

#endif
