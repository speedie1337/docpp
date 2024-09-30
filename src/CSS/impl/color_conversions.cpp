/*
 * docpp - C++ library for generating HTML, CSS and SGML-like documents.
 *
 * SPDX-License-Identifier: LGPL-3.0-or-later
 * Copyright (c) 2024 speedie <speedie@speedie.site>
 */

#include <sstream>
#include <iomanip>
#include <tuple>
#include <docpp/types.hpp>
#include <docpp/CSS/color_struct.hpp>
#include <docpp/CSS/impl/color_conversions.hpp>

docpp::string_type docpp::impl_color_to_string(const docpp::CSS::ColorStruct& color) {
   std::stringstream ss{};
   ss << "#" << std::hex << std::setfill('0') << std::setw(2)
   << static_cast<int>(color.r * 255) << std::setfill('0') << std::setw(2)
   << static_cast<int>(color.g * 255) << std::setfill('0') << std::setw(2)
   << static_cast<int>(color.b * 255);
   return ss.str();
}

docpp::string_type docpp::impl_color_to_string_a(const docpp::CSS::ColorStruct& color) {
 std::stringstream ss{};
 ss << "#" << std::hex << std::setfill('0') << std::setw(2)
 << static_cast<int>(color.r * 255) << std::setfill('0') << std::setw(2)
 << static_cast<int>(color.g * 255) << std::setfill('0') << std::setw(2)
 << static_cast<int>(color.b * 255) << std::setfill('0') << std::setw(2)
 << static_cast<int>(color.a * 255);
 return ss.str();
}

std::tuple<int, int, int> docpp::impl_color_to_int(const docpp::CSS::ColorStruct& color) {
    return std::make_tuple(static_cast<int>(color.r * 255), static_cast<int>(color.g * 255), static_cast<int>(color.b * 255));
}

std::tuple<int, int, int, int> docpp::impl_color_to_int_a(const docpp::CSS::ColorStruct& color) {
    return std::make_tuple(static_cast<int>(color.r * 255), static_cast<int>(color.g * 255), static_cast<int>(color.b * 255), static_cast<int>(color.a * 255));
}
