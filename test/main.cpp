/***************************************************************************
* Copyright (c) 2016, Johan Mabille and Sylvain Corlay                     *
*                                                                          *
* Distributed under the terms of the BSD 3-Clause License.                 *
*                                                                          *
* The full license is in the file LICENSE, distributed with this software. *
****************************************************************************/

#define DOCTEST_CONFIG_IMPLEMENT
#include <doctest/doctest.h>

#include <pybind11/embed.h>
namespace py = pybind11;

int main(int argc, char* argv[])
{
    py::scoped_interpreter guard{};
    doctest::Context context;
    context.applyCommandLine(argc, argv);
    int res = context.run();
    return res;
}

