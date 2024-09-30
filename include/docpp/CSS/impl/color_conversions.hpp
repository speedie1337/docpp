/*
 * docpp - C++ library for generating HTML, CSS and SGML-like documents.
 *
 * SPDX-License-Identifier: LGPL-3.0-or-later
 * Copyright (c) 2024 speedie <speedie@speedie.site>
 */
#pragma once

#include <tuple>
#include <docpp/types.hpp>
#include <docpp/CSS/color_struct.hpp>

namespace docpp {
    /**
     * @brief Convert a docpp::CSS::ColorStruct to an #RRGGBB formatted docpp::string_type
     * @param color The color to parse from.
     * @return docpp::string_type
     */
    docpp::string_type impl_color_to_string(const docpp::CSS::ColorStruct& color);
    /**
     * @brief Convert a docpp::CSS::ColorStruct to an #RRGGBBAA formatted docpp::string_type
     * @param color The color to parse from.
     * @return docpp::string_type
     */
    docpp::string_type impl_color_to_string_a(const docpp::CSS::ColorStruct& color);
    /**
     * @brief Convert a docpp::CSS::ColorStruct to an std::tuple<int, int, int>
     * @param color The color to parse from.
     * @return std::tuple<int, int, int>
     */
    std::tuple<int, int, int> impl_color_to_int(const docpp::CSS::ColorStruct& color);
    /**
     * @brief Convert a docpp::CSS::ColorStruct to an std::tuple<int, int, int, int>
     * @param color The color to parse from.
     * @return std::tuple<int, int, int, int>
     */
    std::tuple<int, int, int, int> impl_color_to_int_a(const docpp::CSS::ColorStruct& color);
} // namespace docpp
