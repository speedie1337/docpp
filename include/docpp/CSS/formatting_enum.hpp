/*
 * docpp - C++ library for generating HTML, CSS and SGML-like documents.
 *
 * SPDX-License-Identifier: LGPL-3.0-or-later
 * Copyright (c) 2024 speedie <speedie@speedie.site>
 */
#pragma once

#include <string>
#include <vector>
#include <unordered_map>
#include <map>
#include <exception>
#include <tuple>
#include <docpp/types.hpp>
#include <docpp/except.hpp>

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
        enum class Formatting {
            None,
            Pretty,
            Newline,
        };
    } // namespace CSS
} // namespace docpp
