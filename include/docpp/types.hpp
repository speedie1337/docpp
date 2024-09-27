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

/**
 * @brief A namespace to represent HTML elements and documents
 */
namespace docpp {
#ifndef DOCPP_STRING_TYPE
    using string_type = std::string;
#else
    using string_type = DOCPP_STRING_TYPE;
#endif
#ifndef DOCPP_SIZE_TYPE
    using size_type = std::size_t;
#else
    using size_type = DOCPP_SIZE_TYPE;
#endif
#ifndef DOCPP_EXCEPTION_CLASS
    using exception_type = std::exception;
#else
    using exception_type = DOCPP_EXCEPTION_CLASS;
#endif
#ifndef DOCPP_INTEGER_TYPE
    using integer_type = int;
#else
    using integer_type = DOCPP_INTEGER_TYPE;
#endif
} // namespace docpp
