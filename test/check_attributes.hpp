#ifndef TEST_PYTHON_ATTRIBUTES_HPP
#define TEST_PYTHON_ATTRIBUTES_HPP

#include <iostream>
#include <set>
#include <string>
#include <vector>

#include "pybind11_json/pybind11_json.hpp"

namespace py = pybind11;
namespace nl = nlohmann;

std::vector<std::string> compare_attributes(const std::set<std::string>& python_attributes,
                                            const std::set<std::string>& cpp_attributes)
{
    std::cout << std::endl << "Attributes present in Python not in C++: " << std::endl;

    std::vector<std::string> difference;
    std::set_difference(begin(python_attributes), end(python_attributes),
                        begin(cpp_attributes), end(cpp_attributes),
                        std::back_inserter(difference));
    std::vector<std::string>::iterator it = difference.begin();
    while(it != difference.end())
    {
        std::cout << *it++ << std::endl;
    }
    std::cout << std::endl;
    return difference;
}

std::set<std::string> extract_attributes_names(const nl::json& widget_representation)
{
    std::set<std::string> attribute_names;
    for(const auto& el: widget_representation.items())
    {
        attribute_names.insert(el.key());
    }
    return attribute_names;
}

template <class WT>
void check_attributes(const std::string& python_module_name, const std::string& python_class_name)
{
    std::cout << python_module_name << '.' << python_class_name << std::endl;

    // Get Python widget state as nl::json
    auto python_module = py::module::import(python_module_name.c_str());
    nl::json python_state = python_module.attr(python_class_name.c_str())().attr("get_state")();

    // Get C++ widget state as nl::json
    nl::json cpp_state;
    xeus::buffer_sequence cpp_buffers;

    WT widget;
    widget.serialize_state(cpp_state, cpp_buffers);

    // Check for missing attributes
    std::set<std::string> python_attribute_names = extract_attributes_names(python_state);
    std::set<std::string> cpp_attribute_names = extract_attributes_names(cpp_state);
    std::vector<std::string> leaflet_difference = compare_attributes(python_attribute_names, cpp_attribute_names);
}

#endif
