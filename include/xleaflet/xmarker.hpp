/******************************************************************************
* Copyright (c) 2018, Sylvain Corlay and Johan Mabille, and Wolf Vollprecht   *
*                                                                             *
* Distributed under the terms of the BSD 3-Clause License.                    *
*                                                                             *
* The full license is in the file LICENSE, distributed with this software.    *
*******************************************************************************/

#ifndef XLEAFLET_MARKER_HPP
#define XLEAFLET_MARKER_HPP

#include <string>

#include "xwidgets/xmaterialize.hpp"
#include "xwidgets/xwidget.hpp"

#include "xui_layer.hpp"

namespace xleaflet
{
    /**********************
     * marker declaration *
     **********************/

    template <class D>
    class xmarker : public xui_layer<D>
    {
    public:

        using move_callback_type = std::function<void(const xeus::xjson&)>;

        using point_type = std::array<double, 2>;

        using base_type = xui_layer<D>;
        using derived_type = D;

        xeus::xjson get_state() const;
        void apply_patch(const xeus::xjson&);

        void on_move(move_callback_type);

        void handle_custom_message(const xeus::xjson&);

        XPROPERTY(point_type, derived_type, location);
        XPROPERTY(int, derived_type, z_index_offset, 0.0);
        XPROPERTY(bool, derived_type, clickable, true);
        XPROPERTY(bool, derived_type, draggable, true);
        XPROPERTY(bool, derived_type, keyboard, true);
        XPROPERTY(std::string, derived_type, title, "");
        XPROPERTY(std::string, derived_type, alt, "");
        XPROPERTY(bool, derived_type, rise_on_hover, false);
        //TODO: bounded between 0.0 and 1.0
        XPROPERTY(float, derived_type, opacity, 1.0);
        XPROPERTY(bool, derived_type, visible, true);
        XPROPERTY(int, derived_type, rise_offset, 250);

    protected:

        xmarker();
        using base_type::base_type;

    private:

        void set_defaults();

        std::list<move_callback_type> m_move_callbacks;
    };

    using marker = xw::xmaterialize<xmarker>;

    using marker_generator = xw::xgenerator<xmarker>;

    /******************************
     * xmarker implementation *
     ******************************/

    template <class D>
    inline xeus::xjson xmarker<D>::get_state() const
    {
        xeus::xjson state = base_type::get_state();

        XOBJECT_SET_PATCH_FROM_PROPERTY(location, state);
        XOBJECT_SET_PATCH_FROM_PROPERTY(z_index_offset, state);
        XOBJECT_SET_PATCH_FROM_PROPERTY(clickable, state);
        XOBJECT_SET_PATCH_FROM_PROPERTY(draggable, state);
        XOBJECT_SET_PATCH_FROM_PROPERTY(keyboard, state);
        XOBJECT_SET_PATCH_FROM_PROPERTY(title, state);
        XOBJECT_SET_PATCH_FROM_PROPERTY(alt, state);
        XOBJECT_SET_PATCH_FROM_PROPERTY(rise_on_hover, state);
        XOBJECT_SET_PATCH_FROM_PROPERTY(opacity, state);
        XOBJECT_SET_PATCH_FROM_PROPERTY(visible, state);
        XOBJECT_SET_PATCH_FROM_PROPERTY(rise_offset, state);

        return state;
    }

    template <class D>
    inline void xmarker<D>::apply_patch(const xeus::xjson& patch)
    {
        base_type::apply_patch(patch);

        XOBJECT_SET_PROPERTY_FROM_PATCH(location, patch);
        XOBJECT_SET_PROPERTY_FROM_PATCH(z_index_offset, patch);
        XOBJECT_SET_PROPERTY_FROM_PATCH(clickable, patch);
        XOBJECT_SET_PROPERTY_FROM_PATCH(draggable, patch);
        XOBJECT_SET_PROPERTY_FROM_PATCH(keyboard, patch);
        XOBJECT_SET_PROPERTY_FROM_PATCH(title, patch);
        XOBJECT_SET_PROPERTY_FROM_PATCH(alt, patch);
        XOBJECT_SET_PROPERTY_FROM_PATCH(rise_on_hover, patch);
        XOBJECT_SET_PROPERTY_FROM_PATCH(opacity, patch);
        XOBJECT_SET_PROPERTY_FROM_PATCH(visible, patch);
        XOBJECT_SET_PROPERTY_FROM_PATCH(rise_offset, patch);
    }

    template <class D>
    inline void xmarker<D>::on_move(move_callback_type callback)
    {
        m_move_callbacks.emplace_back(std::move(callback));
    }

    template <class D>
    inline xmarker<D>::xmarker()
        : base_type()
    {
        set_defaults();
    }

    template <class D>
    inline void xmarker<D>::set_defaults()
    {
        this->_model_name() = "LeafletMarkerModel";
        this->_view_name() = "LeafletMarkerView";

        this->location() = {0, 0};

        this->options().insert(
            this->options().end(),
            {
                "z_index_offset",
                "clickable",
                "draggable",
                "keyboard",
                "title",
                "alt",
                "rise_on_hover",
                "rise_offset"
            }
        );
    }

    template <class D>
    inline void xmarker<D>::handle_custom_message(const xeus::xjson& content)
    {
        auto it = content.find("event");
        if (it != content.end() && it.value() == "move")
        {
            for (auto it = m_move_callbacks.begin(); it != m_move_callbacks.end(); ++it)
            {
                it->operator()(content);
            }
        }
    }
}

#endif
