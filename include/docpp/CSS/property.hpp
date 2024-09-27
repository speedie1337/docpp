/*
 * docpp - C++ library for generating HTML, CSS and SGML-like documents.
 *
 * SPDX-License-Identifier: LGPL-3.0-or-later
 * Copyright (c) 2024 speedie <speedie@speedie.site>
 */
#pragma once

#include <string>
#include <vector>
#include <docpp/types.hpp>

/**
 * @brief A namespace to represent HTML elements and documents
 */
namespace docpp {
    /**
     * @brief A namespace to represent CSS elements and documents
     */
    namespace CSS {
        /**
         * @brief A class to represent a CSS property
         */
        class Property {
            private:
                std::pair<string_type, string_type> property{};
            protected:
            public:
                /**
                 * @brief The npos value
                 */
                static constexpr size_type npos = -1;

                /**
                 * @brief Construct a new Property object
                 * @param key The key of the property
                 * @param value The value of the property
                 */
                Property(const string_type& key, const string_type& value) : property(std::make_pair(key, value)) {};
                /**
                 * @brief Construct a new Property object
                 */
                Property(const Property& property) = default;
                /**
                 * @brief Construct a new Property object
                 */
                Property() = default;
                /**
                 * @brief Destroy the Property object
                 */
                ~Property() = default;

                /**
                 * @brief Get the key of the property
                 * @return string_type The key of the property
                 */
                [[nodiscard]] string_type get_key() const;
                /**
                 * @brief Get the key of the property in a specific type
                 * @return T The key of the property
                 */
                template <typename T> T get_key() const {
                    if (std::is_same_v<T, string_type>) {
                        return this->property.first;
                    }
                    return T(this->property.first);
                }
                /**
                 * @brief Get the value of the property
                 * @return string_type The value of the property
                 */
                [[nodiscard]] string_type get_value() const;
                /**
                 * @brief Get the value of the property in a specific type
                 * @return T The value of the property
                 */
                template <typename T> T get_value() const {
                    if (std::is_same_v<T, string_type>) {
                        return this->property.second;
                    }
                    return T(this->property.second);
                }
                /**
                 * @brief Get the property.
                 * @return std::pair<string_type, string_type> The value of the property
                 */
                [[nodiscard]] std::pair<string_type, string_type> get() const;
                /**
                 * @brief Get the property in a specific type.
                 * @return std::pair<T, T> The value of the property
                 */
                template <typename T> std::pair<T, T> get() const {
                    if (std::is_same_v<T, string_type>) {
                        return std::make_pair(this->property.first, this->property.second);
                    }
                    return std::pair<T, T>(this->property.first, this->property.second);
                }
                /**
                 * @brief Set the key of the property.
                 * @param key The key.
                 */
                void set_key(const string_type& key);
                /**
                 * @brief Set the value of the property.
                 * @param value The value.
                 */
                void set_value(const string_type& value);
                /**
                 * @brief Set the property
                 * @param key The key of the property
                 * @param value The value of the property
                 */
                void set(const string_type& key, const string_type& value);

                Property& operator=(const Property& property);
                bool operator==(const Property& property) const;
                bool operator!=(const Property& property) const;
        };

        template <typename... Args> std::vector<Property> make_properties(Args&&... args) { return {std::forward<Args>(args)...}; }
    } // namespace CSS
} // namespace docpp
