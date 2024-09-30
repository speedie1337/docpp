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
        struct ColorStruct {
            double r{0};
            double g{0};
            double b{0};
            double a{0};
        };
    } // namespace CSS
} // namespace docpp
