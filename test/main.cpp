/***************************************************************************
* Copyright (c) 2016, Johan Mabille and Sylvain Corlay                     *
*                                                                          *
* Distributed under the terms of the BSD 3-Clause License.                 *
*                                                                          *
* The full license is in the file LICENSE, distributed with this software. *
****************************************************************************/

#include "gtest/gtest.h"

#include <pybind11/embed.h>

namespace py = pybind11;

int main(int argc, char* argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    py::scoped_interpreter guard{};
    return RUN_ALL_TESTS();
}
