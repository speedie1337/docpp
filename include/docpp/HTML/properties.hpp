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
#include <docpp/HTML/property.hpp>

/**
 * @brief A namespace to represent HTML elements and documents
 */
namespace docpp {
    /**
     * @brief A namespace to represent HTML elements and documents
     */
    namespace HTML {
        /**
         * @brief A class to represent the properties of an HTML element
         */
        class Properties {
            private:
                std::vector<Property> properties{};
            protected:
            public:
                using iterator = std::vector<Property>::iterator;
                using const_iterator = std::vector<Property>::const_iterator;
                using reverse_iterator = std::vector<Property>::reverse_iterator;
                using const_reverse_iterator = std::vector<Property>::const_reverse_iterator;

                /**
                 * @brief Return an iterator to the beginning.
                 * @return iterator The iterator to the beginning.
                 */
                iterator begin() { return properties.begin(); }
                /**
                 * @brief Return an iterator to the end.
                 * @return iterator The iterator to the end.
                 */
                iterator end() { return properties.end(); }
                /**
                 * @brief Return an iterator to the beginning.
                 * @return iterator The iterator to the beginning.
                 */
                [[nodiscard]] const_iterator begin() const { return properties.begin(); }
                /**
                 * @brief Return an iterator to the end.
                 * @return iterator The iterator to the end.
                 */
                [[nodiscard]] const_iterator end() const { return properties.end(); }
                /**
                 * @brief Return a const iterator to the beginning.
                 * @return const_iterator The const iterator to the beginning.
                 */
                [[nodiscard]] const_iterator cbegin() const { return properties.cbegin(); }
                /**
                 * @brief Return a const iterator to the end.
                 * @return const_iterator The const iterator to the end.
                 */
                [[nodiscard]] const_iterator cend() const { return properties.cend(); }
                /**
                 * @brief Return a reverse iterator to the beginning.
                 * @return reverse_iterator The reverse iterator to the beginning.
                 */
                reverse_iterator rbegin() { return properties.rbegin(); }
                /**
                 * @brief Return a reverse iterator to the end.
                 * @return reverse_iterator The reverse iterator to the end.
                 */
                reverse_iterator rend() { return properties.rend(); }
                /**
                 * @brief Return a const reverse iterator to the beginning.
                 * @return const_reverse_iterator The const reverse iterator to the beginning.
                 */
                [[nodiscard]] const_reverse_iterator crbegin() const { return properties.crbegin(); }
                /**
                 * @brief Return a const reverse iterator to the end.
                 * @return const_reverse_iterator The const reverse iterator to the end.
                 */
                [[nodiscard]] const_reverse_iterator crend() const { return properties.crend(); }

                /**
                 * @brief The npos value
                 */
                static constexpr size_type npos = -1;

                /**
                 * @brief Get the properties of the element
                 * @return std::vector<Property> The properties of the element
                 */
                [[nodiscard]] std::vector<Property> get_properties() const;
                /**
                 * @brief Set the properties of the element
                 * @param properties The properties to set
                 */
                void set(const std::vector<Property>& properties);
                /**
                 * @brief Get the property at an index
                 * @param index The index of the property
                 * @return Property The property at the index
                 */
                [[nodiscard]] Property at(size_type index) const;
                /**
                 * @brief Insert a property into the element
                 * @param index The index to insert the property
                 * @param property The property to insert
                 */
                void insert(size_type index, const Property& property);
                /**
                 * @brief Erase a property from the element
                 * @param index The index of the property to erase
                 */
                void erase(size_type index);
                /**
                 * @brief Find a property in the element
                 * @param property The property to find
                 * @return size_type The index of the property
                 */
                [[nodiscard]] size_type find(const docpp::HTML::Property &property) const;
                /**
                 * @brief Find a property in the element
                 * @param str The property to find
                 * @return size_type The index of the property
                 */
                [[nodiscard]] size_type find(const string_type& str) const;
                /**
                 * @brief Swap two properties in the element
                 * @param index1 The index of the first property
                 * @param index2 The index of the second property
                 */
                void swap(size_type index1, size_type index2);
                /**
                 * @brief Swap two properties in the element
                 * @param property1 The first property
                 * @param property2 The second property
                 */
                void swap(const docpp::HTML::Property& property1, const docpp::HTML::Property& property2);
                /**
                 * @brief Get the first property of the element
                 * @return Property The first property of the element
                 */
                [[nodiscard]] Property front() const;
                /**
                 * @brief Get the last property of the element
                 * @return Property The last property of the element
                 */
                [[nodiscard]] Property back() const;
                /**
                 * @brief Get the size of the element
                 * @return size_type The size of the element
                 */
                [[nodiscard]] size_type size() const;
                /**
                 * @brief Clear the properties
                 */
                void clear();
                /**
                 * @brief Check if the properties are empty
                 * @return bool True if the properties are empty, false otherwise
                 */
                [[nodiscard]] bool empty() const;
                /**
                 * @brief Prepend a property to the element
                 * @param property The property to add
                 */
                void push_front(const Property& property);
                /**
                 * @brief Append a property to the element
                 * @param property The property to add
                 */
                void push_back(const Property& property);
                template <typename... Args> explicit Properties(Args... args) { (this->push_back(args), ...); }
                /**
                 * @brief Construct a new Properties object
                 * @param properties The properties to set
                 */
                explicit Properties(const std::vector<Property>& properties) : properties(properties) {};
                /**
                 * @brief Construct a new Properties object
                 * @param property The property to add
                 */
                explicit Properties(const Property& property) : properties({property}) {};
                /**
                 * @brief Construct a new Properties object
                 * @param properties The properties to set
                 */
                Properties(const Properties& properties) = default;
                /**
                 * @brief Construct a new Properties object
                 */
                Properties() = default;
                /**
                 * @brief Destroy the Properties object
                 */
                ~Properties() = default;
                Properties& operator=(const Properties& properties);
                Properties& operator=(const std::vector<Property>& properties);
                Properties& operator=(const Property& property);
                bool operator==(const Properties& properties) const;
                bool operator==(const Property& property) const;
                bool operator!=(const Properties& properties) const;
                bool operator!=(const Property& property) const;
                Property operator[](const size_type& index) const;
                Properties& operator+=(const Property& property);
                Properties& operator+=(const Properties& properties);
        };

        template <typename... Args> Properties make_properties(Args&&... args) { return Properties(std::forward<Args>(args)...); }
    } // namespace HTML
} // namespace docpp
