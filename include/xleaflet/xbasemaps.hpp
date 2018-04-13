/******************************************************************************
* Copyright (c) 2018, Sylvain Corlay and Johan Mabille, Wolf Vollprecht and   *
* Martin Renou                                                                *
*                                                                             *
* Distributed under the terms of the BSD 3-Clause License.                    *
*                                                                             *
* The full license is in the file LICENSE, distributed with this software.    *
*******************************************************************************/

#ifndef XLEAFLET_BASEMAPS_HPP
#define XLEAFLET_BASEMAPS_HPP

#include <fstream>
#include <iostream>
#include <vector>

#include "xeus/xjson.hpp"

#include "xget_basemaps_path.hpp"
#include "xtile_layer.hpp"

namespace detail
{
    inline xeus::xjson load_basemaps()
    {
        std::ifstream maps_json(xleaflet::get_basemaps_path());

        xeus::xjson maps;
        maps_json >> maps;

        return maps;
    }
}

namespace xleaflet
{
    inline const xeus::xjson& basemaps()
    {
        static xeus::xjson maps = detail::load_basemaps();

        return maps;
    }

    inline tile_layer basemap(const std::vector<std::string>& path, const std::string& day = "2018-01-01")
    {
        const xeus::xjson& maps = basemaps();

        const xeus::xjson* node = &maps;
        try
        {
            for (const auto& level : path)
            {
                node = &((*node)[level]);
            }
        }
        catch (const std::exception&)
        {
            std::cerr << "Invalid map spec" << std::endl;
            return tile_layer();
        }

        const xeus::xjson& mapspec = *node;
        if (mapspec.find("url") == mapspec.end())
        {
            std::cerr << "Invalid map spec" << std::endl;
            return tile_layer();
        }

        std::string url = mapspec["url"].get<std::string>();
        std::string attribution = "";
        std::string name = "";
        int max_zoom = 19;
        int min_zoom = 1;

        url.replace(url.find("%s"), 2, day);

        if (mapspec.find("attribution") != mapspec.end())
        {
            attribution = mapspec["attribution"].get<std::string>();
        }

        if (mapspec.find("name") != mapspec.end())
        {
            name = mapspec["name"].get<std::string>();
        }

        if (mapspec.find("max_zoom") != mapspec.end())
        {
            max_zoom = mapspec["max_zoom"].get<int>();
        }

        if (mapspec.find("min_zoom") != mapspec.end())
        {
            min_zoom = mapspec["min_zoom"].get<int>();
        }

        return tile_layer_generator()
            .url(url)
            .attribution(attribution)
            .name(name)
            .max_zoom(max_zoom)
            .min_zoom(min_zoom)
            .finalize();
    }
}

#endif
