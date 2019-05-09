#ifndef TEST_XLEAFLET_HPP
#define TEST_XLEAFLET_HPP

#include "xleaflet/xpopup.hpp"
#include <pybind11/embed.h>
namespace py = pybind11;
namespace nl = nlohmann;

namespace nlohmann
{
    template <>
    struct adl_serializer<py::object>
    {
        static py::object from_json(const json& j);
        static void to_json(json& j, const py::object& obj);
    };
}

namespace nlohmann
{
    namespace detail
    {
        py::object from_json_impl(const json& j)
        {
            if (j.is_null())
            {
                return py::none();
            }
            else if (j.is_boolean())
            {
                return py::bool_(j.get<bool>());
            }
            else if (j.is_number())
            {
                double number = j.get<double>();
                if (number == std::floor(number))
                {
                    return py::int_(j.get<long>());
                }
                else
                {
                    return py::float_(number);
                }
            }
            else if (j.is_string())
            {
                return py::str(j.get<std::string>());
            }
            else if (j.is_array())
            {
                py::list obj;
                for (const auto& el : j)
                {
                    obj.attr("append")(from_json_impl(el));
                }
                return obj;
            }
            else // Object
            {
                py::dict obj;
                for (json::const_iterator it = j.cbegin(); it != j.cend(); ++it)
                {
                    obj[py::str(it.key())] = from_json_impl(it.value());
                }
                return obj;
            }
        }

        json to_json_impl(const py::handle& obj)
        {
            if (obj.is_none())
            {
                return nullptr;
            }
            if (py::isinstance<py::bool_>(obj))
            {
                return obj.cast<bool>();
            }
            if (py::isinstance<py::int_>(obj))
            {
                return obj.cast<long>();
            }
            if (py::isinstance<py::float_>(obj))
            {
                return obj.cast<double>();
            }
            if (py::isinstance<py::str>(obj))
            {
                return obj.cast<std::string>();
            }
            if (py::isinstance<py::tuple>(obj) || py::isinstance<py::list>(obj))
            {
                auto out = json::array();
                for (const py::handle& value : obj)
                {
                    out.push_back(to_json_impl(value));
                }
                return out;
            }
            if (py::isinstance<py::dict>(obj))
            {
                auto out = json::object();
                for (const py::handle& key : obj)
                {
                    out[py::str(key).cast<std::string>()] = to_json_impl(obj[key]);
                }
                return out;
            }
            throw std::runtime_error("to_json not implemented for this type of object: " + obj.cast<std::string>());
        }
    }

    py::object adl_serializer<py::object>::from_json(const json& j)
    {
        return detail::from_json_impl(j);
    }

    void adl_serializer<py::object>::to_json(json& j, const py::object& obj)
    {
        j = detail::to_json_impl(obj);
    }
}

std::vector<std::string> compare_attributes(const std::set<std::string>& parsed_set, const std::set<std::string>& state_set)
{
    std::cout << "\nAttributes present in ipyleaflet not in xleaflet : " << "\n" << std::endl;

    std::vector<std::string> difference;
    std::set_difference(begin(parsed_set), end(parsed_set),
                        begin(state_set), end(state_set),
                        std::back_inserter(difference));
    std::vector<std::string>::iterator it = difference.begin();
    while(it != difference.end())
    {
        std::cout << *it << " \n";
        it++;
    }
    std::cout<<std::endl;
    return difference;
}

std::set<std::string> extract_attributes_names(const xeus::xjson& widget_representation)
{
    std::set<std::string> attribute_names;
    for(const auto& el: widget_representation.items()){
        attribute_names.insert(el.key());
    }
    return attribute_names;
}

namespace xlf
{
    template <class WT>
    void test_xleaflet(const std::string& ipyleaflet_widget)
    {
        std::cout << ipyleaflet_widget << std::endl;
        py::object ipyleaflet = py::module::import("ipyleaflet");
        py::object ipyleaflet_widget_state = ipyleaflet.attr(ipyleaflet_widget.c_str())().attr("get_state")();
        xeus::xjson ipyleaflet_set = ipyleaflet_widget_state;
        std::set<std::string> ipyleaflet_attribute_names = extract_attributes_names(ipyleaflet_set);

        xeus::xjson state; xeus::buffer_sequence buffers;
        WT().serialize_state(state, buffers);
        std::set<std::string> xleaflet_attribute_names = extract_attributes_names(state);

        std::vector<std::string> leaflet_difference = compare_attributes(ipyleaflet_attribute_names, xleaflet_attribute_names);
    }
}

#endif
