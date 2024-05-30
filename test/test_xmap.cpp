/***************************************************************************
* Copyright (c) 2016, Johan Mabille and Sylvain Corlay                     *
*                                                                          *
* Distributed under the terms of the BSD 3-Clause License.                 *
*                                                                          *
* The full license is in the file LICENSE, distributed with this software. *
****************************************************************************/

#include <doctest/doctest.h>
#include "xleaflet/xmap.hpp"

namespace xleaflet
{
    TEST_SUITE("xmap")
    {
        TEST_CASE("map")
        {
            int res = 64;
            CHECK_EQ(64, res);
        }
    }
}
