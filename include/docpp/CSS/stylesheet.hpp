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
#include <docpp/CSS/formatting_enum.hpp>
#include <docpp/CSS/element.hpp>

/**
 * @brief A namespace to represent HTML elements and documents
 */
namespace docpp {
    /**
     * @brief A namespace to represent CSS elements and documents
     */
    namespace CSS {
        /**
         * @brief A class to represent a CSS stylesheet
         */
        class Stylesheet {
            private:
                std::vector<Element> elements{};
            protected:
            public:
                using iterator = std::vector<Element>::iterator;
                using const_iterator = std::vector<Element>::const_iterator;
                using reverse_iterator = std::vector<Element>::reverse_iterator;
                using const_reverse_iterator = std::vector<Element>::const_reverse_iterator;

                /**
                 * @brief Return an iterator to the beginning.
                 * @return iterator The iterator to the beginning.
                 */
                iterator begin() { return elements.begin(); }
                /**
                 * @brief Return an iterator to the end.
                 * @return iterator The iterator to the end.
                 */
                iterator end() { return elements.end(); }
                /**
                 * @brief Return a const_iterator to the beginning.
                 * @return const_iterator The iterator to the beginning.
                 */
                [[nodiscard]] const_iterator begin() const { return elements.begin(); }
                /**
                 * @brief Return a const_iterator to the end.
                 * @return const_iterator The iterator to the end.
                 */
                [[nodiscard]] const_iterator end() const { return elements.end(); }
                /**
                 * @brief Return a const iterator to the beginning.
                 * @return const_iterator The const iterator to the beginning.
                 */
                [[nodiscard]] const_iterator cbegin() const { return elements.cbegin(); }
                /**
                 * @brief Return a const iterator to the end.
                 * @return const_iterator The const iterator to the end.
                 */
                [[nodiscard]] const_iterator cend() const { return elements.cend(); }
                /**
                 * @brief Return a reverse iterator to the beginning.
                 * @return reverse_iterator The reverse iterator to the beginning.
                 */
                reverse_iterator rbegin() { return elements.rbegin(); }
                /**
                 * @brief Return a reverse iterator to the end.
                 * @return reverse_iterator The reverse iterator to the end.
                 */
                reverse_iterator rend() { return elements.rend(); }
                /**
                 * @brief Return a const reverse iterator to the beginning.
                 * @return const_reverse_iterator The const reverse iterator to the beginning.
                 */
                [[nodiscard]] const_reverse_iterator crbegin() const { return elements.crbegin(); }
                /**
                 * @brief Return a const reverse iterator to the end.
                 * @return const_reverse_iterator The const reverse iterator to the end.
                 */
                [[nodiscard]] const_reverse_iterator crend() const { return elements.crend(); }

                /**
                 * @brief The npos value
                 */
                static constexpr size_type npos = -1;

                /**
                 * @brief Construct a new Stylesheet object
                 */
                template <typename... Args> explicit Stylesheet(Args... args) { (this->push_back(args), ...); }
                explicit Stylesheet(const std::vector<Element>& elements) : elements(elements) {};
                /**
                 * @brief Construct a new Stylesheet object
                 * @param stylesheet The stylesheet to set
                 */
                Stylesheet(const Stylesheet& stylesheet) = default;
                /**
                 * @brief Construct a new Stylesheet object
                 */
                Stylesheet() = default;
                /**
                 * @brief Destroy the Stylesheet object
                 */
                ~Stylesheet() = default;

                /**
                 * @brief Prepend an element to the stylesheet
                 * @param element The element to add
                 */
                void push_front(const Element& element);
                /**
                 * @brief Append an element to the stylesheet
                 * @param element The element to add
                 */
                void push_back(const Element& element);
                /**
                 * @brief Insert an element into the stylesheet
                 * @param index The index to insert the element
                 * @param element The element to insert
                 */
                void insert(size_type index, const Element& element);
                /**
                 * @brief Erase an element from the stylesheet. Note that this will NOT change the size/index.
                 * @param index The index of the element to erase
                 */
                void erase(size_type index);
                /**
                 * @brief Find an element in the stylesheet
                 * @param element The element to find
                 * @return size_type The index of the element
                 */
                [[nodiscard]] size_type find(const Element& element) const;
                /**
                 * @brief Find an element in the stylesheet
                 * @param str The element to find, either the tag or the stylesheet itself
                 * @return size_type The index of the element
                 */
                [[nodiscard]] size_type find(const string_type& str) const;
                /**
                 * @brief Get the element at an index
                 * @param index The index of the element
                 * @return Element The element at the index
                 */
                [[nodiscard]] Element at(size_type index) const;
                /**
                 * @brief Get the size of the stylesheet
                 * @return size_type The size of the stylesheet
                 */
                [[nodiscard]] size_type size() const;
                /**
                 * @brief Clear the stylesheet
                 */
                void clear();
                /**
                 * @brief Check if the stylesheet is empty
                 * @return bool True if the stylesheet is empty, false otherwise
                 */
                [[nodiscard]] bool empty() const;
                /**
                 * @brief Get the first element of the stylesheet
                 * @return Element The first element of the stylesheet
                 */
                [[nodiscard]] Element front() const;
                /**
                 * @brief Get the last element of the stylesheet
                 * @return Element The last element of the stylesheet
                 */
                [[nodiscard]] Element back() const;
                /**
                 * @brief Swap two elements in the stylesheet
                 * @param index1 The index of the first element
                 * @param index2 The index of the second element
                 */
                void swap(size_type index1, size_type index2);
                /**
                 * @brief Swap two elements in the stylesheet
                 * @param element1 The first element
                 * @param element2 The second element
                 */
                void swap(const Element& element1, const Element& element2);
                /**
                 * @brief Set the elements of the stylesheet
                 * @param elements The elements to set
                 */
                void set(const std::vector<Element>& elements);
                /**
                 * @brief Get the elements of the stylesheet
                 * @return std::vector<Element> The elements of the stylesheet
                 */
                [[nodiscard]] std::vector<Element> get_elements() const;
                /**
                 * @brief Get the stylesheet
                 * @return string_type The stylesheet
                 */
                [[nodiscard]] string_type get(Formatting formatting = Formatting::None, integer_type tabc = 0) const;
                /**
                 * @brief Get the stylesheet in the form of a specific type.
                 * @return T The stylesheet in the form of a specific type
                 */
                template <typename T> T get(const Formatting formatting = Formatting::None, const integer_type tabc = 0) const {
                    if (std::is_same_v<T, string_type>) {
                        return this->get(formatting, tabc);
                    }
                    return T(this->get(formatting, tabc));
                }

                Stylesheet& operator=(const Stylesheet& stylesheet);
                Stylesheet& operator+=(const Element& element);
                Element operator[](const int& index) const;
                bool operator==(const Stylesheet& stylesheet) const;
                bool operator!=(const Stylesheet& stylesheet) const;
        };

        template <typename... Args> Stylesheet make_stylesheet(Args&&... args) { return Stylesheet(std::forward<Args>(args)...); }
    } // namespace CSS
} // namespace docpp
