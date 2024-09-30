/*
* docpp - C++ library for generating HTML, CSS and SGML-like documents.
 *
 * SPDX-License-Identifier: LGPL-3.0-or-later
 * Copyright (c) 2024 speedie <speedie@speedie.site>
 */

#include <sstream>
#include <tuple>
#include <docpp/types.hpp>
#include <docpp/except.hpp>
#include <docpp/CSS/color_struct.hpp>
#include <docpp/CSS/color.hpp>
#include <docpp/CSS/impl/color_conversions.hpp>

docpp::string_type docpp::CSS::ColorFormatter::get(const docpp::CSS::ColorFormatting formatting = docpp::CSS::ColorFormatting::Undefined) const {
    switch (formatting == docpp::CSS::ColorFormatting::Undefined ? this->formatting : formatting) {
        case docpp::CSS::ColorFormatting::Hex: {
            return docpp::impl_color_to_string(color);
        } case docpp::CSS::ColorFormatting::Hex_A: {
            return docpp::impl_color_to_string_a(color);
        } case docpp::CSS::ColorFormatting::Rgb: {
            std::tuple<int, int, int> tuple = docpp::impl_color_to_int(color);
            std::stringstream ss{};
            ss << "rgb(" << std::get<0>(tuple) << ", " << std::get<1>(tuple) << ", " << std::get<2>(tuple) << ")";
            return ss.str();
        } case docpp::CSS::ColorFormatting::Rgb_A: {
            std::tuple<int, int, int, int> tuple_ = docpp::impl_color_to_int_a(color);
            std::stringstream ss_{};
            ss_ << "rgba(" << std::get<0>(tuple_) << ", " << std::get<1>(tuple_) << ", " << std::get<2>(tuple_) << ", " << std::get<3>(tuple_) << ")";
            return ss_.str();
        } default: {
            break;
        }
    }

    throw docpp::invalid_argument{"Invalid formatting"};
}

docpp::CSS::ColorStruct docpp::CSS::ColorFormatter::get_color_struct() const {
    return this->color;
}

docpp::CSS::ColorFormatting docpp::CSS::ColorFormatter::get_formatting() const {
    return this->formatting;
}

void docpp::CSS::ColorFormatter::set_color_struct(const docpp::CSS::ColorStruct& color) {
    this->color = color;
}

void docpp::CSS::ColorFormatter::set_formatting(const docpp::CSS::ColorFormatting& formatting) {
    this->formatting = formatting;
}

docpp::CSS::ColorStruct docpp::CSS::from_hex(const docpp::string_type& str) {
    const auto convert_to_int = [](const docpp::string_type& str) -> int {
        int value;
        std::stringstream ss;
        ss << std::hex << str;
        ss >> value;
        return value;
    };

    if (str.length() < 7) {
        throw docpp::invalid_argument{"Invalid hex color"};
    }

    docpp::string_type hr{str.substr(1, 2)};
    docpp::string_type hg{str.substr(3, 2)};
    docpp::string_type hb{str.substr(5, 2)};

    docpp::CSS::ColorStruct color;

    color.r = convert_to_int(hr) / 255.0;
    color.g = convert_to_int(hg) / 255.0;
    color.b = convert_to_int(hb) / 255.0;
    color.a = 1;

    if (str.length() == 9) {
        std::string ha{str.substr(7, 2)};
        color.a = convert_to_int(ha) / 255.0;
    }

    /* Whether invalid argument is the right exception to throw is debatable, but if this fails,
       then it's most probable that an invalid argument was passed to this function.
     */
    if (color.r < 0.0 || color.r > 1.0 || color.g < 0.0 ||
        color.g > 1.0 || color.b < 0.0 || color.b > 1.0 ||
        color.a < 0.0 || color.a > 1.0) {
        throw docpp::invalid_argument{"Invalid hex color"};
    }

    return color;
}

docpp::CSS::ColorStruct docpp::CSS::from_rgba(int r, int g, int b, int a) {
    if (r < 0 || g < 0 || b < 0 || a < 0 || r > 255 || g > 255 || b > 255 || a > 255) {
        throw docpp::invalid_argument{"Invalid hex color"};
    }

    return {r / 255.0, g / 255.0, b / 255.0, a / 255.0};
};

docpp::CSS::ColorStruct docpp::CSS::from_float(float r, float g, float b, float a) {
    if (r < 0.0 || r > 1.0 || g < 0.0 || g > 1.0 || b < 0.0 || b > 1.0) {
        throw docpp::invalid_argument{"Invalid color r/g/b"};
    }

    return {r,g,b,a};
}

docpp::CSS::ColorStruct docpp::CSS::from_double(double r, double g, double b, double a) {
    if (r < 0.0 || r > 1.0 || g < 0.0 || g > 1.0 || b < 0.0 || b > 1.0) {
        throw docpp::invalid_argument{"Invalid color r/g/b"};
    }

    return {r,g,b,a};
}