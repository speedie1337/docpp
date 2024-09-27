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
#include <docpp/HTML/properties.hpp>
#include <docpp/HTML/element.hpp>

/**
 * @brief A namespace to represent HTML elements and documents
 */
namespace docpp {
    /**
     * @brief A namespace to represent HTML elements and documents
     */
    namespace HTML {
        /**
         * @brief A class to represent an HTML section (head, body, etc.)
         */
        class Section {
            protected:
            public:
                /**
                 * @brief A class to represent an iterator for the Section class
                 */
                template <typename T>
                class sect_iterator {
                    private:
                        T element{};
                    public:
                        explicit sect_iterator(const T& element) : element(element) {}
                        sect_iterator& operator++() {
                            ++element;
                            return *this;
                        }

                        auto operator*() const -> decltype(element->second) {
                            return element->second;
                        }

                        bool operator==(const sect_iterator& other) const {
                             return element == other.element;
                        }

                        bool operator!=(const sect_iterator& other) const {
                             return element != other.element;
                        }
                };

                using element_map = std::map<size_type, Element>;
                using iterator = sect_iterator<element_map::iterator>;
                using const_iterator = sect_iterator<element_map::const_iterator>;
                using reverse_iterator = sect_iterator<element_map::reverse_iterator>;
                using const_reverse_iterator = sect_iterator<element_map::const_reverse_iterator>;

                /**
                 * @brief Return an iterator to the beginning.
                 * @return iterator The iterator to the beginning.
                 */
                iterator begin() { return iterator(elements.begin()); }
                /**
                 * @brief Return an iterator to the end.
                 * @return iterator The iterator to the end.
                 */
                iterator end() { return iterator(elements.end()); }
                /**
                 * @brief Return an iterator to the beginning.
                 * @return const_iterator The iterator to the beginning.
                 */
                [[nodiscard]] const_iterator begin() const { return const_iterator(elements.begin()); }
                /**
                 * @brief Return an iterator to the end.
                 * @return const_iterator The iterator to the end.
                 */
                [[nodiscard]] const_iterator end() const { return const_iterator(elements.end()); }
                /**
                 * @brief Return a const iterator to the beginning.
                 * @return const_iterator The const iterator to the beginning.
                 */
                [[nodiscard]] const_iterator cbegin() const { return const_iterator(elements.cbegin()); }
                /**
                 * @brief Return a const iterator to the end.
                 * @return const_iterator The const iterator to the end.
                 */
                [[nodiscard]] const_iterator cend() const { return const_iterator(elements.cend()); }
                /**
                 * @brief Return a reverse iterator to the beginning.
                 * @return reverse_iterator The reverse iterator to the beginning.
                 */
                reverse_iterator rbegin() { return reverse_iterator(elements.rbegin()); }
                /**
                 * @brief Return a reverse iterator to the end.
                 * @return reverse_iterator The reverse iterator to the end.
                 */
                reverse_iterator rend() { return reverse_iterator(elements.rend()); }
                /**
                 * @brief Return a const reverse iterator to the beginning.
                 * @return const_reverse_iterator The const reverse iterator to the beginning.
                 */
                [[nodiscard]] const_reverse_iterator crbegin() const { return const_reverse_iterator(elements.crbegin()); }
                /**
                 * @brief Return a const reverse iterator to the end.
                 * @return const_reverse_iterator The const reverse iterator to the end.
                 */
                [[nodiscard]] const_reverse_iterator crend() const { return const_reverse_iterator(elements.crend()); }

                /**
                 * @brief The npos value
                 */
                static constexpr size_type npos = -1;

                /**
                 * @brief Prepend an element to the section
                 * @param element The element to add
                 */
                void push_front(const Element& element);
                /**
                 * @brief Prepend a section to the section
                 * @param section The section to add
                 */
                void push_front(const Section& section);
                /**
                 * @brief Append an element to the section
                 * @param element The element to add
                 */
                void push_back(const Element& element);
                /**
                 * @brief Append a section to the section
                 * @param section The section to add
                 */
                void push_back(const Section& section);

                /**
                 * @brief Get the element at an index. To get a section, use at_section()
                 * @param index The index of the element
                 * @return Element The element at the index
                 */
                [[nodiscard]] Element at(size_type index) const;
                /**
                 * @brief Get the section at an index. To get an element, use at()
                 * @param index The index of the section
                 * @return Section The section at the index
                 */
                [[nodiscard]] Section at_section(size_type index) const;
                /**
                 * @brief Get the element at an index. To get a section, use at_section()
                 * @param index The index of the element
                 * @return Element The element at the index
                 */
                Element& at(size_type index);
                /**
                 * @brief Get the section at an index. To get an element, use at()
                 * @param index The index of the section
                 * @return Section The section at the index
                 */
                Section& at_section(size_type index);

                /**
                 * @brief Erase an element from the section. Note that this will NOT change the size/index.
                 * @param index The index of the element to erase
                 */
                void erase(size_type index);
                /**
                 * @brief Erase a section from the section, by reading from a section. The section will be erased if it's identical to section. Note that this will NOT change the size/index.
                 * @param section The section to erase
                 */
                void erase(const Section& section);
                /**
                 * @brief Erase an element from the section, by reading from an element. The element will be erased if it's identical to element. Note that this will NOT change the size/index.
                 * @param element The element to erase
                 */
                void erase(const Element& element);
                /**
                 * @brief Find an element in the section
                 * @param element The element to find
                 * @return size_type The index of the element
                 */
                [[nodiscard]] size_type find(const Element& element) const;
                /**
                 * @brief Find a section in the section
                 * @param section The section to find
                 * @return size_type The index of the section
                 */
                [[nodiscard]] size_type find(const Section& section) const;
                /**
                 * @brief Find an element or section in the section
                 * @param str The element or section to find
                 * @return size_type The index of the element or section
                 */
                [[nodiscard]] size_type find(const string_type& str) const;
                /**
                 * @brief Insert an element into the section
                 * @param index The index to insert the element
                 * @param element The element to insert
                 */
                void insert(size_type index, const Element& element);
                /**
                 * @brief Insert a section into the section
                 * @param index The index to insert the section
                 * @param section The section to insert
                 */
                void insert(size_type index, const Section& section);
                /**
                 * @brief Get the first element of the section
                 * @return Element The first element of the section
                 */
                [[nodiscard]] Element front() const;
                /**
                 * @brief Get the first element of the section
                 * @return Element The first element of the section
                 */
                Element& front();
                /**
                 * @brief Get the last element of the section
                 * @return Element The last element of the section
                 */
                [[nodiscard]] Element back() const;
                /**
                 * @brief Get the last element of the section
                 * @return Element The last element of the section
                 */
                Element& back();
                /**
                 * @brief Get the first section of the section
                 * @return Section The first section of the section
                 */
                [[nodiscard]] Section front_section() const;
                /**
                 * @brief Get the first section of the section
                 * @return Section The first section of the section
                 */
                Section& front_section();
                /**
                 * @brief Get the last section of the section
                 * @return Section The last section of the section
                 */
                [[nodiscard]] Section back_section() const;
                /**
                 * @brief Get the last section of the section
                 * @return Section The last section of the section
                 */
                [[nodiscard]] Section& back_section();
                /**
                 * @brief Get the size of the section
                 * @return size_type The size of the section
                 */
                [[nodiscard]] size_type size() const;
                /**
                 * @brief Clear the section
                 */
                void clear();
                /**
                 * @brief Check if the section is empty
                 * @return bool True if the section is empty, false otherwise
                 */
                [[nodiscard]] bool empty() const;
                /**
                 * @brief Construct a new Section object
                 * @param tag The tag of the section
                 * @param properties The properties of the section
                 */
                explicit Section(string_type tag, const Properties& properties = {}) : tag(std::move(tag)), properties(properties) {};
                /**
                 * @brief Construct a new Section object
                 * @param tag The tag of the section
                 * @param properties The properties of the section
                 */
                explicit Section(const Tag tag, const Properties& properties = {}) : tag(resolve_tag(tag).first), properties(properties) {};
                /**
                 * @brief Construct a new Section object
                 * @param tag The tag of the section
                 * @param properties The properties of the section
                 * @param elements The elements of the section
                 */
                Section(string_type tag, const Properties& properties, const std::vector<Element>& elements) : tag(std::move(tag)), properties(properties) {
                    for (const auto& element : elements) this->push_back(element);
                };
                /**
                 * @brief Construct a new Section object
                 * @param tag The tag of the section
                 * @param properties The properties of the section
                 * @param elements The elements of the section
                 */
                Section(const Tag tag, const Properties& properties, const std::vector<Element>& elements) : tag(resolve_tag(tag).first), properties(properties) {
                    for (const auto& element : elements) this->push_back(element);
                };
                /**
                 * @brief Construct a new Section object
                 * @param tag The tag of the section
                 * @param properties The properties of the section
                 * @param sections The sections of the section
                 */
                Section(string_type tag, const Properties& properties, const std::vector<Section>& sections) : tag(std::move(tag)), properties(properties) {
                    for (const auto& section : sections) this->push_back(section);
                };
                /**
                 * @brief Construct a new Section object
                 * @param tag The tag of the section
                 * @param properties The properties of the section
                 * @param sections The sections of the section
                 */
                Section(const Tag tag, const Properties& properties, const std::vector<Section>& sections) : tag(resolve_tag(tag).first), properties(properties) {
                    for (const auto& section : sections) this->push_back(section);
                };
                /**
                 * @brief Construct a new Section object
                 * @param section The section to set
                 */
                Section(const Section& section) {
                    this->tag = section.tag;
                    this->properties = section.properties;
                    this->elements = section.elements;
                    this->sections = section.sections;
                    this->index = section.index;
                }
                /**
                 * @brief Construct a new Section object
                 */
                Section() = default;
                /**
                 * @brief Destroy the Section object
                 */
                ~Section() = default;
                /**
                 * @brief Set the tag and properties of the section
                 * @param tag The tag to assign to the section
                 * @param properties The properties to assign to the section tag
                 */
                void set(const string_type& tag, const Properties& properties = {});
                /**
                 * @brief Set the tag, id, and classes of the section
                 * @param tag The tag of the section
                 * @param properties The properties to assign the tag
                 */
                void set(Tag tag, const Properties& properties = {});
                /**
                 * @brief Set the tag of the section
                 * @param tag The tag of the section
                 */
                void set_tag(const string_type& tag);
                /**
                 * @brief Set the tag of the section
                 * @param tag The tag of the section
                 */
                void set_tag(Tag tag);
                /**
                 * @brief Set the properties of the section
                 * @param properties The properties of the section
                 */
                void set_properties(const Properties& properties);
                /**
                 * @brief Swap two elements in the section
                 * @param index1 The index of the first element
                 * @param index2 The index of the second element
                 */
                void swap(size_type index1, size_type index2);
                /**
                 * @brief Swap two elements in the section
                 * @param element1 The first element
                 * @param element2 The second element
                 */
                void swap(const Element& element1, const Element& element2);
                /**
                 * @brief Swap two sections in the section
                 * @param section1 The first section
                 * @param section2 The second section
                 */
                void swap(const Section& section1, const Section& section2);
                /**
                 * @brief Get the elements of the section
                 * @return std::vector<Element> The elements of the section
                 */
                [[nodiscard]] std::vector<Element> get_elements() const;
                /**
                 * @brief Get the sections of the section
                 * @return std::vector<Section> The sections of the section
                 */
                [[nodiscard]] std::vector<Section> get_sections() const;

                /**
                 * @brief Dump the entire section.
                 * @return string_type The section
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
                 * @brief Get the tag of the section
                 * @return string_type The tag of the section
                 */
                [[nodiscard]] string_type get_tag() const;
                /**
                 * @brief Get the tag of the section in a specific type
                 * @return T The tag of the section
                 */
                template <typename T> T get_tag() const {
                    if (std::is_same_v<T, string_type>) {
                        return this->tag;
                    }
                    return T(this->tag);
                }
                /**
                 * @brief Get the properties of the section
                 * @return Properties The properties of the section
                 */
                [[nodiscard]] Properties get_properties() const;

                Section& operator=(const Section& section);
                Section& operator+=(const Element& element);
                Section& operator+=(const Section& section);
                bool operator==(const Element& element) const;
                bool operator==(const Section& section) const;
                bool operator!=(const Element& element) const;
                bool operator!=(const Section& section) const;
                Element operator[](const int& index) const;
                std::unordered_map<string_type, Element> operator[](const string_type& tag) const;
                std::unordered_map<string_type, Element> operator[](Tag tag) const;
            private:
                size_type index{};
                string_type tag{};
                Properties properties{};

                std::map<size_type, Element> elements{};
                std::unordered_map<size_type, Section> sections{};
        };
    } // namespace HTML
} // namespace docpp