/*
 * docpp - C++ library for generating HTML, CSS and SGML-like documents.
 *
 * SPDX-License-Identifier: LGPL-3.0-or-later
 * Copyright (c) 2024 speedie <speedie@speedie.site>
 */
#pragma once

/**
 * @brief A namespace to represent HTML elements and documents
 */
namespace docpp {
    /**
     * @brief A namespace to represent CSS elements and documents
     */
    namespace CSS {
        /**
         * @brief Enum for formatting options.
         */
        enum class ColorFormatting {
          Undefined,
          Hex,
          Hex_A,
          Rgb,
          Rgb_A,
        };
    } // namespace CSS
} // namespace docpp
