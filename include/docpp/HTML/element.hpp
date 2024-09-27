/*
 * docpp - C++ library for generating HTML, CSS and SGML-like documents.
 *
 * SPDX-License-Identifier: LGPL-3.0-or-later
 * Copyright (c) 2024 speedie <speedie@speedie.site>
 */
#pragma once

#include <string>
#include <docpp/types.hpp>
#include <docpp/HTML/properties.hpp>

/**
 * @brief A namespace to represent HTML elements and documents
 */
namespace docpp {
    /**
     * @brief A namespace to represent HTML elements and documents
     */
    namespace HTML {
        /**
         * @brief A class to represent an HTML element
         */
        class Element {
            private:
                string_type tag{};
                Properties properties{};
                string_type data{};
                Type type{Type::Non_Self_Closing};
            public:
                /**
                 * @brief The npos value
                 */
                static constexpr size_type npos = -1;

                /**
                 * @brief Construct a new Element object
                 * @param tag The tag of the element
                 * @param properties The properties of the element
                 * @param data The data of the element
                 * @param type The close tag type.
                 */
                explicit Element(string_type tag, const Properties& properties = {}, string_type data = {}, const Type& type = Type::Non_Self_Closing) : tag(std::move(tag)), properties(properties), data(std::move(data)), type(type) {};
                /**
                 * @brief Construct a new Element object
                 * @param tag The tag of the element
                 * @param properties The properties of the element
                 * @param data The data of the element
                 */
                explicit Element(const Tag tag, const Properties& properties = {}, string_type data = {}) : tag(resolve_tag(tag).first), properties(properties), data(std::move(data)), type(resolve_tag(tag).second) {};
                /**
                 * @brief Construct a new Element object
                 * @param element The element to set
                 */
                Element(const Element& element) = default;
                /**
                 * @brief Construct a new Element object
                 */
                Element() = default;
                /**
                 * @brief Destroy the Element object
                 */
                ~Element() = default;
                /**
                 * @brief Set the tag, properties, and data of the element
                 * @param tag The tag of the element
                 * @param properties The properties of the element
                 * @param data The data of the element
                 * @param type The close tag type.
                 */
                void set(const string_type& tag, const Properties& properties = {}, const string_type& data = {}, Type type = Type::Non_Self_Closing);
                /**
                 * @brief Set the tag, properties, and data of the element
                 * @param tag The tag of the element
                 * @param properties The properties of the element
                 * @param data The data of the element
                 */
                void set(Tag tag, const Properties& properties = {}, const string_type& data = {});
                /**
                 * @brief Set the tag of the element
                 * @param tag The tag of the element
                 */
                void set_tag(const string_type& tag);
                /**
                 * @brief Set the tag of the element
                 * @param tag The tag of the element
                 */
                void set_tag(Tag tag);
                /**
                 * @brief Set the data of the element
                 * @param data The data of the element
                 */
                void set_data(const string_type& data);
                /**
                 * @brief Set the properties of the element
                 * @param properties The properties of the element
                 */
                void set_properties(const Properties& properties);
                /**
                 * @brief Set the type of the element
                 * @param type The type of the element
                 */
                void set_type(Type type);

                /**
                 * @brief Get the element in the form of an HTML tag.
                 * @return string_type The tag of the element
                 */
                [[nodiscard]] string_type get(Formatting formatting = Formatting::None, integer_type tabc = 0) const;
                /**
                 * @brief Get the element in the form of a specific type.
                 * @return T The element in the form of a specific type
                 */
                template <typename T> T get(const Formatting formatting = Formatting::None, const integer_type tabc = 0) const {
                    if (std::is_same_v<T, string_type>) {
                        return this->get(formatting, tabc);
                    }
                    return T(this->get(formatting, tabc));
                }

                /**
                 * @brief Get the tag of the element
                 * @return string_type The data of the element
                 */
                [[nodiscard]] string_type get_tag() const;
                /**
                 * @brief Get the tag of the element in a specific type
                 * @return T The tag of the element
                 */
                template <typename T> T get_tag() const {
                    if (std::is_same_v<T, string_type>) {
                        return this->tag;
                    }
                    return T(this->tag);
                }

                /**
                 * @brief Get the data of the element
                 * @return string_type The data of the element
                 */
                [[nodiscard]] string_type get_data() const;
                /**
                 * @brief Get the data of the element in a specific type
                 * @return T The data of the element
                 */
                template <typename T> T get_data() const {
                    if (std::is_same_v<T, string_type>) {
                        return this->data;
                    }
                    return T(this->data);
                }
                /**
                 * @brief Get the properties of the element
                 * @return Properties The properties of the element
                 */
                [[nodiscard]] Properties get_properties() const;
                /**
                 * @brief Get the type of the element
                 * @return Type The type of the element
                 */
                [[nodiscard]] Type get_type() const;
                /**
                 * @brief Clear the element
                 */
                void clear();
                /**
                 * @brief Check if the element is empty.
                 * @return bool True if the element is empty, false otherwise.
                 */
                [[nodiscard]] bool empty() const;

                Element& operator=(const Element& element);
                Element& operator+=(const string_type& data);
                bool operator==(const Element& element) const;
                bool operator!=(const Element& element) const;
        };
    } // namespace HTML
} // namespace docpp
