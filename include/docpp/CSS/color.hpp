/*
 * docpp - C++ library for generating HTML, CSS and SGML-like documents.
 *
 * SPDX-License-Identifier: LGPL-3.0-or-later
 * Copyright (c) 2024 speedie <speedie@speedie.site>
 */
#pragma once

#include <docpp/types.hpp>
#include <docpp/CSS/color_type_enum.hpp>
#include <docpp/CSS/color_struct.hpp>

/**
 * @brief A namespace to represent HTML elements and documents
 */
namespace docpp {
    /**
     * @brief A namespace to represent CSS elements and documents
     */
    namespace CSS {
        class ColorFormatter {
            docpp::CSS::ColorFormatting formatting{docpp::CSS::ColorFormatting::Hex};
            docpp::CSS::ColorStruct color{};
        public:
            ColorFormatter() = default;
            explicit ColorFormatter(const docpp::CSS::ColorStruct& color, docpp::CSS::ColorFormatting formatting = docpp::CSS::ColorFormatting::Hex) : formatting(formatting), color(color) {};
            ~ColorFormatter() = default;

            /**
             * @brief Return a formatted string based on the constructor parameters.
             * @return docpp::string_type
             */
            [[nodiscard]] docpp::string_type get(docpp::CSS::ColorFormatting formatting) const;
            /**
             * @brief Return the object's ColorFormatting enum.
             * @return docpp::CSS::ColorFormatting
             */
            [[nodiscard]] docpp::CSS::ColorFormatting get_formatting() const;
            /**
             * @brief Return the object's ColorStruct struct.
             * @return docpp::CSS::ColorStruct
             */
            [[nodiscard]] docpp::CSS::ColorStruct get_color_struct() const;
            /**
             * @brief Set the formatting to the parameter specified.
             * @param formatting The formatting to use.
             */
            void set_formatting(const docpp::CSS::ColorFormatting& formatting);
            /**
             * @brief Set the color struct to the parameter specified.
             * @param color Color struct parameter.
             */
            void set_color_struct(const docpp::CSS::ColorStruct& color);
            /**
             * @brief Return a formatted string based on the constructor parameters.
             * @return docpp::string_type
             */
            template <typename T> [[nodiscard]] T get(const docpp::CSS::ColorFormatting formatting = docpp::CSS::ColorFormatting::Undefined) const {
                return {get(formatting)};
            }
        };

        docpp::CSS::ColorStruct from_hex(const docpp::string_type& str);
        docpp::CSS::ColorStruct from_rgba(int r, int g, int b, int a);
        docpp::CSS::ColorStruct from_float(float r, float g, float b, float a);
        docpp::CSS::ColorStruct from_double(double r, double g, double b, double a);
    } // namespace CSS
} // namespace docpp
