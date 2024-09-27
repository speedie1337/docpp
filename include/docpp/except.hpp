/*
 * docpp - C++ library for generating HTML, CSS and SGML-like documents.
 *
 * SPDX-License-Identifier: LGPL-3.0-or-later
 * Copyright (c) 2024 speedie <speedie@speedie.site>
 */
#pragma once

#include <docpp/types.hpp>

/**
 * @brief A namespace to represent HTML elements and documents
 */
namespace docpp {
    /**
     * @brief A class to represent an exception when an index is out of range
     */
    class out_of_range : public exception_type {
        private:
            const char* message{"Out of range"};
        public:
            [[nodiscard]] const char* what() const noexcept override {
                return message;
            }
            out_of_range() = default;
            explicit out_of_range(const char* message) : message(message) {};
    };

    /**
     * @brief A class to represent an exception when an argument is invalid
     */
    class invalid_argument : public exception_type {
        private:
            const char* message{"Invalid argument"};
        public:
            [[nodiscard]] const char* what() const noexcept override {
                return message;
            }
            invalid_argument() = default;
            explicit invalid_argument(const char* message) : message(message) {};
    };
} // namespace docpp
