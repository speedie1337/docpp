/*
 * docpp - C++ library for generating HTML, CSS and SGML-like documents.
 *
 * SPDX-License-Identifier: LGPL-3.0-or-later
 * Copyright (c) 2024 speedie <speedie@speedie.site>
 */
#pragma once

#include <tuple>
#include <docpp/types.hpp>
#include <docpp/except.hpp>

/**
 * @brief A namespace to represent HTML elements and documents
 */
namespace docpp {
    /**
     * @brief Get the version of the library
     * @return std::tuple<int, int, int> The version of the library
     */
    std::tuple<integer_type, integer_type, integer_type> version();
} // namespace docpp
