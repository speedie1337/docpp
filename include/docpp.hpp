/**
 * docpp - Small C++ library for generating XML, HTML and CSS.
 * Licensed under the LGPL-3.0-or-later license.
 *
 * Author: speedie <speedie@speedie.site>
 *
 * @file docpp.hpp
 * @brief Header file for docpp
 * @author speedie
 * @date 2024
 * @copyright GNU Lesser General Public License 3.0
 * @version 0.0.1
 */
#pragma once

#include <string>
#include <vector>
#include <unordered_map>
#include <map>

/**
 * @brief A namespace to represent HTML elements and documents
 */
namespace docpp {
    /**
     * @brief A class to represent an exception when an index is out of range
     */
    class out_of_range : public std::exception {
        private:
            const char* message{"Out of range"};
        public:
            const char* what() const noexcept override {
                return message;
            }
            out_of_range() = default;
            out_of_range(const char* message) : message(message) {};
    };

    /**
     * @brief A class to represent an exception when an argument is invalid
     */
    class invalid_argument : public std::exception {
        private:
            const char* message{"Invalid argument"};
        public:
            const char* what() const noexcept override {
                return message;
            }
            invalid_argument() = default;
            invalid_argument(const char* message) : message(message) {};
    };

    /**
     * @brief A namespace to represent HTML elements and documents
     */
    namespace HTML {
        enum {
            SECTION_EMPTY,
            SECTION_HTML,
            SECTION_HEAD,
            SECTION_BODY,
            SECTION_FOOTER,
            SECTION_DIV,
            TYPE_SELF_CLOSING,
            TYPE_NON_SELF_CLOSING,
            TYPE_NON_CLOSED,
            TYPE_TEXT,
            TYPE_TEXT_TAB,
            FORMATTING_NONE,
            FORMATTING_PRETTY,
            FORMATTING_NEWLINE,
        };

        /**
         * @brief A class to represent an HTML property
         */
        class HTMLProperty {
            private:
                std::pair<std::string, std::string> property{};
            protected:
            public:
                /**
                 * @brief The npos value
                 */
                static const int npos = -1;

                /**
                 * @brief Construct a new HTMLProperty object
                 * @param key The key of the property
                 * @param value The value of the property
                 */
                HTMLProperty(const std::string& key, const std::string& value);
                /**
                 * @brief Construct a new HTMLProperty object
                 * @param property The property to set
                 */
                HTMLProperty(const std::pair<std::string, std::string>& property);
                HTMLProperty() = default;

                /**
                 * @brief Get the key of the property
                 * @return std::string The key of the property
                 */
                std::string getKey() const;
                /**
                 * @brief Get the value of the property
                 * @return std::string The value of the property
                 */
                std::string getValue() const;
                /**
                 * @brief Get the property.
                 * @return std::pair<std::string, std::string> The value of the property
                 */
                std::pair<std::string, std::string> get() const;
                /**
                 * @brief Set the key of the property.
                 * @param key The key.
                 */
                void setKey(const std::string& key);
                /**
                 * @brief Set the value of the property.
                 * @param value The value.
                 */
                void setValue(const std::string& value);
                /**
                 * @brief Set the property
                 * @param property The property.
                 */
                void set(const std::pair<std::string, std::string>& property);
        };

        /**
         * @brief A class to represent the properties of an HTML element
         */
        class HTMLProperties {
            private:
                std::vector<HTMLProperty> properties{};
            protected:
            public:
                using iterator = std::vector<HTMLProperty>::iterator;
                using const_iterator = std::vector<HTMLProperty>::const_iterator;
                using reverse_iterator = std::vector<HTMLProperty>::reverse_iterator;
                using const_reverse_iterator = std::vector<HTMLProperty>::const_reverse_iterator;

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
                 * @brief Return a const iterator to the beginning.
                 * @return const_iterator The const iterator to the beginning.
                 */
                const_iterator cbegin() const { return properties.cbegin(); }
                /**
                 * @brief Return a const iterator to the end.
                 * @return const_iterator The const iterator to the end.
                 */
                const_iterator cend() const { return properties.cend(); }
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
                const_reverse_iterator crbegin() { return properties.crbegin(); }
                /**
                 * @brief Return a const reverse iterator to the end.
                 * @return const_reverse_iterator The const reverse iterator to the end.
                 */
                const_reverse_iterator crend() { return properties.crend(); }

                /**
                 * @brief The npos value
                 */
                static const int npos = -1;

                /**
                 * @brief Get the properties of the element
                 * @return std::vector<HTMLProperty> The properties of the element
                 */
                std::vector<HTMLProperty> getProperties() const;
                /**
                 * @brief Set the properties of the element
                 * @param properties The properties to set
                 */
                void set(const std::vector<HTMLProperty>& properties);
                /**
                 * @brief Get the property at an index
                 * @param index The index of the property
                 * @return HTMLProperty The property at the index
                 */
                HTMLProperty at(const int index) const;
                /**
                 * @brief Insert a property into the element
                 * @param index The index to insert the property
                 * @param property The property to insert
                 */
                void insert(const int index, const HTMLProperty& property);
                /**
                 * @brief Erase a property from the element
                 * @param index The index of the property to erase
                 */
                void erase(const int index);
                /**
                 * @brief Find a property in the element
                 * @param property The property to find
                 * @return int The index of the property
                 */
                int find(const HTMLProperty& property);
                /**
                 * @brief Find a property in the element
                 * @param str The property to find
                 * @return int The index of the property
                 */
                int find(const std::string& str);
                /**
                 * @brief Swap two properties in the element
                 * @param index1 The index of the first property
                 * @param index2 The index of the second property
                 */
                void swap(const int index1, const int index2);
                /**
                 * @brief Swap two properties in the element
                 * @param property1 The first property
                 * @param property2 The second property
                 */
                void swap(const HTMLProperty& property1, const HTMLProperty& property2);
                /**
                 * @brief Get the first property of the element
                 * @return HTMLProperty The first property of the element
                 */
                HTMLProperty front() const;
                /**
                 * @brief Get the last property of the element
                 * @return HTMLProperty The last property of the element
                 */
                HTMLProperty back() const;
                /**
                 * @brief Get the size of the element
                 * @return int The size of the element
                 */
                int size() const;
                /**
                 * @brief Prepend a property to the element
                 * @param property The property to add
                 */
                void push_front(const HTMLProperty& property);
                /**
                 * @brief Append a property to the element
                 * @param property The property to add
                 */
                void push_back(const HTMLProperty& property);
                /**
                 * @brief Construct a new HTMLProperties object
                 * @param properties The properties to set
                 */
                HTMLProperties(const std::vector<HTMLProperty>& properties);
                /**
                 * @brief Construct a new HTMLProperties object
                 * @param property The property to add
                 */
                HTMLProperties(const HTMLProperty& property);
                /**
                 * @brief Construct a new HTMLProperties object
                 */
                HTMLProperties() = default;
                HTMLProperties operator=(const HTMLProperties& properties);
                HTMLProperties operator=(const std::vector<HTMLProperty>& properties);
                HTMLProperties operator=(const HTMLProperty& property);
                void operator+=(const HTMLProperty& property);
        };

        using HTMLElementProperties = HTMLProperties;

        /**
         * @brief A class to represent an HTML element
         */
        class HTMLElement {
            private:
                std::string tag{};
                std::string data{};
                int type{TYPE_NON_SELF_CLOSING};
                HTMLProperties properties{};
            protected:
            public:
                /**
                 * @brief The npos value
                 */
                static const int npos = -1;

                /**
                 * @brief Construct a new HTMLElement object
                 * @param tag The tag of the element
                 * @param properties The properties of the element
                 * @param data The data of the element
                 */
                HTMLElement(const std::string& tag, const HTMLProperties& properties = {}, const std::string& data = {}, const int type = TYPE_NON_SELF_CLOSING);
                /**
                 * @brief Construct a new HTMLElement object
                 */
                HTMLElement() = default;
                /**
                 * @brief Set the tag, id, and classes of the element
                 * @param tag The tag of the element
                 * @param id The id of the element
                 * @param classes The classes of the element
                 */
                void set(const std::string& tag, const HTMLProperties& properties = {}, const std::string& data = {}, const int type = TYPE_NON_SELF_CLOSING);

                /**
                 * @brief Get the element in the form of an HTML tag.
                 * @return std::string The tag of the element
                 */
                std::string get(const int formatting = FORMATTING_NONE, const int tabc = 0) const;

                /**
                 * @brief Get the tag of the element
                 * @return std::string The data of the element
                 */
                std::string getTag() const;

                /**
                 * @brief Get the data of the element
                 * @return std::string The data of the element
                 */
                std::string getData() const;
                HTMLElement operator=(const HTMLElement& element);
                void operator+=(const std::string& data);
        };

        /**
         * @brief A class to represent an HTML section (head, body, etc.)
         */
        class HTMLSection {
            private:
                int index{};
                std::string tag{};
                HTMLProperties properties{};

                std::map<int, HTMLElement> elements{};
                std::unordered_map<int, HTMLSection> sections{};
            protected:
            public:
                /**
                 * @brief A class to represent an iterator for the HTMLSection class
                 */
                template <typename T>
                class sect_iterator {
                    private:
                        T element{};
                    public:
                        sect_iterator(const T& element) : element(element) {}
                        sect_iterator operator++() { return ++element; }
                        HTMLElement operator*() { return element->second; }
                        bool operator==(const sect_iterator& other) { return element == other.element; }
                        bool operator!=(const sect_iterator& other) { return element != other.element; }
                };

                using iterator = sect_iterator<std::map<int, HTMLElement>::iterator>;
                using const_iterator = sect_iterator<std::map<int, HTMLElement>::const_iterator>;
                using reverse_iterator = sect_iterator<std::map<int, HTMLElement>::reverse_iterator>;
                using const_reverse_iterator = sect_iterator<std::map<int, HTMLElement>::const_reverse_iterator>;

                iterator begin() { return iterator(elements.begin()); }
                iterator end() { return iterator(elements.end()); }
                const_iterator cbegin() const { return const_iterator(elements.cbegin()); }
                const_iterator cend() const { return const_iterator(elements.cend()); }
                reverse_iterator rbegin() { return reverse_iterator(elements.rbegin()); }
                reverse_iterator rend() { return reverse_iterator(elements.rend()); }
                const_reverse_iterator crbegin() { return const_reverse_iterator(elements.crbegin()); }
                const_reverse_iterator crend() { return const_reverse_iterator(elements.crend()); }

                /**
                 * @brief The npos value
                 */
                static const int npos = -1;

                /**
                 * @brief Prepend an element to the section
                 * @param element The element to add
                 */
                void push_front(const HTMLElement& element);
                /**
                 * @brief Prepend a section to the section
                 * @param section The section to add
                 */
                void push_front(const HTMLSection& section);
                /**
                 * @brief Append an element to the section
                 * @param element The element to add
                 */
                void push_back(const HTMLElement& element);
                /**
                 * @brief Append a section to the section
                 * @param section The section to add
                 */
                void push_back(const HTMLSection& section);
                /**
                 * @brief Get the element at an index. To get a section, use at_section()
                 * @param index The index of the element
                 * @return HTMLElement The element at the index
                 */
                HTMLElement at(const int index) const;
                /**
                 * @brief Get the section at an index. To get an element, use at()
                 * @param index The index of the section
                 * @return HTMLSection The section at the index
                 */
                HTMLSection at_section(const int index) const;
                /**
                 * @brief Erase an element from the section. Note that this will NOT change the size/index.
                 * @param index The index of the element to erase
                 */
                void erase(const int index);
                /**
                 * @brief Erase a section from the section, by reading from a section. The section will be erased if it's identical to section. Note that this will NOT change the size/index.
                 * @param section The section to erase
                 */
                void erase(const HTMLSection& section);
                /**
                 * @brief Erase an element from the section, by reading from an element. The element will be erased if it's identical to element. Note that this will NOT change the size/index.
                 * @param element The element to erase
                 */
                void erase(const HTMLElement& element);
                /**
                 * @brief Find an element in the section
                 * @param element The element to find
                 * @return int The index of the element
                 */
                int find(const HTMLElement& element);
                /**
                 * @brief Find a section in the section
                 * @param section The section to find
                 * @return int The index of the section
                 */
                int find(const HTMLSection& section);
                /**
                 * @brief Find an element or section in the section
                 * @param str The element or section to find
                 * @return int The index of the element or section
                 */
                int find(const std::string& str);
                /**
                 * @brief Insert an element into the section
                 * @param index The index to insert the element
                 * @param element The element to insert
                 */
                void insert(const int index, const HTMLElement& element);
                /**
                 * @brief Insert a section into the section
                 * @param index The index to insert the section
                 * @param section The section to insert
                 */
                void insert(const int index, const HTMLSection& section);
                /**
                 * @brief Get the first element of the section
                 * @return HTMLElement The first element of the section
                 */
                HTMLElement front() const;
                /**
                 * @brief Get the last element of the section
                 * @return HTMLElement The last element of the section
                 */
                HTMLElement back() const;
                /**
                 * @brief Get the first section of the section
                 * @return HTMLSection The first section of the section
                 */
                HTMLSection front_section() const;
                /**
                 * @brief Get the last section of the section
                 * @return HTMLSection The last section of the section
                 */
                HTMLSection back_section() const;
                /**
                 * @brief Get the size of the section
                 * @return int The size of the section
                 */
                int size() const;

                /**
                 * @brief Construct a new HTMLSection object
                 * @param tag The tag of the section
                 * @param properties The properties of the section
                 */
                HTMLSection(const std::string& tag, const HTMLProperties& properties = {});
                /**
                 * @brief Construct a new HTMLSection object
                 * @param tag The tag of the section
                 * @param properties The properties of the section
                 */
                HTMLSection(const int tag, const HTMLProperties& properties = {});
                /**
                 * @brief Construct a new HTMLSection object
                 */
                HTMLSection() = default;
                /**
                 * @brief Set the tag, id, and classes of the section
                 * @param tag The tag of the section
                 * @param id The id of the section
                 * @param classes The classes of the section
                 */
                void set(const std::string& tag, const HTMLProperties& properties = {});
                /**
                 * @brief Set the tag, id, and classes of the section
                 * @param tag The tag of the section
                 * @param id The id of the section
                 * @param classes The classes of the section
                 */
                void set(const int tag, const HTMLProperties& properties = {});
                /**
                 * @brief Swap two elements in the section
                 * @param index1 The index of the first element
                 * @param index2 The index of the second element
                 */
                void swap(const int index1, const int index2);
                /**
                 * @brief Swap two elements in the section
                 * @param element1 The first element
                 * @param element2 The second element
                 */
                void swap(const HTMLElement& element1, const HTMLElement& element2);
                /**
                 * @brief Swap two sections in the section
                 * @param index1 The index of the first section
                 * @param index2 The index of the second section
                 */
                void swap(const HTMLSection& section1, const HTMLSection& section2);
                /**
                 * @brief Get the elements of the section
                 * @return std::vector<HTMLElement> The elements of the section
                 */
                std::vector<HTMLElement> getHTMLElements() const;
                /**
                 * @brief Get the sections of the section
                 * @return std::vector<HTMLSection> The sections of the section
                 */
                std::vector<HTMLSection> getHTMLSections() const;

                /**
                 * @brief Dump the entire section.
                 * @return std::string The section
                 */
                std::string get(const int formatting = FORMATTING_NONE, const int tabc = 0) const;

                HTMLSection operator=(const HTMLSection& section);
                void operator+=(const HTMLElement& element);
                void operator+=(const HTMLSection& section);
                HTMLElement operator[](const int& index) const;
        };

        /**
         * @brief A class to represent an HTML document
         */
        class HTMLDocument {
            private:
                std::string doctype{"<!DOCTYPE html>"};
                HTMLSection document{};
            protected:
            public:
                /**
                 * @brief The npos value
                 */
                static const int npos = -1;

                /**
                 * @brief Get the document
                 * @param std::string The type to return
                 * @return std::string The document
                 */
                std::string get(const int formatting = FORMATTING_NONE, const int tabc = 0) const;

                /**
                 * @brief Get the section
                 * @return HTMLSection The section
                 */
                HTMLSection& getSection();

                /**
                 * @brief Get the doctype of the document
                 * @return std::string The doctype of the document
                 */
                std::string getDoctype() const;

                /**
                 * @brief Set the document
                 * @param document The document to set
                 */
                void set(const HTMLSection& document);
                /**
                 * @brief Set the doctype of the document
                 * @param doctype The doctype to set
                 */
                void setDoctype(const std::string& doctype);
                /**
                 * @brief Construct a new HTMLDocument object
                 */
                HTMLDocument() = default;
                /**
                 * @brief Construct a new HTMLDocument object
                 * @param document The document to set
                 */
                HTMLDocument(const HTMLSection& document, const std::string& doctype = "<!DOCTYPE html>");

                HTMLDocument operator=(const HTMLDocument& document);
                HTMLDocument operator=(const HTMLSection& section);
        };
    } // namespace HTML

    /**
     * @brief A namespace to represent CSS elements and documents
     */
    namespace CSS {
        enum {
            FORMATTING_NONE,
            FORMATTING_PRETTY,
            FORMATTING_NEWLINE,
        };

        /**
         * @brief A class to represent a CSS property
         */
        class CSSProperty {
            private:
                std::pair<std::string, std::string> property{};
            protected:
            public:
                /**
                 * @brief The npos value
                 */
                static const int npos = -1;

                /**
                 * @brief Construct a new CSSProperty object
                 * @param key The key of the property
                 * @param value The value of the property
                 */
                CSSProperty(const std::string& key, const std::string& value);
                /**
                 * @brief Construct a new CSSProperty object
                 * @param property The property to set
                 */
                CSSProperty(const std::pair<std::string, std::string>& property);
                CSSProperty() = default;

                /**
                 * @brief Get the key of the property
                 * @return std::string The key of the property
                 */
                std::string getKey() const;
                /**
                 * @brief Get the value of the property
                 * @return std::string The value of the property
                 */
                std::string getValue() const;
                /**
                 * @brief Get the property.
                 * @return std::pair<std::string, std::string> The value of the property
                 */
                std::pair<std::string, std::string> get() const;
                /**
                 * @brief Set the key of the property.
                 * @param key The key.
                 */
                void setKey(const std::string& key);
                /**
                 * @brief Set the value of the property.
                 * @param value The value.
                 */
                void setValue(const std::string& value);
                /**
                 * @brief Set the property
                 * @param property The property.
                 */
                void set(const std::pair<std::string, std::string>& property);
                /**
                 * @brief Set the property
                 * @param key The key of the property
                 * @param value The value of the property
                 */
                void set(const std::string& key, const std::string& value);

                CSSProperty operator=(const CSSProperty& property);
                CSSProperty operator=(const std::pair<std::string, std::string>& property);
        };

        class CSSElement {
            private:
                std::pair<std::string, std::vector<CSSProperty>> element{};
            protected:
            public:
                using iterator = std::vector<CSSProperty>::iterator;
                using const_iterator = std::vector<CSSProperty>::const_iterator;
                using reverse_iterator = std::vector<CSSProperty>::reverse_iterator;
                using const_reverse_iterator = std::vector<CSSProperty>::const_reverse_iterator;

                /**
                 * @brief Return an iterator to the beginning.
                 * @return iterator The iterator to the beginning.
                 */
                iterator begin() { return element.second.begin(); }
                /**
                 * @brief Return an iterator to the end.
                 * @return iterator The iterator to the end.
                 */
                iterator end() { return element.second.end(); }
                /**
                 * @brief Return a const iterator to the beginning.
                 * @return const_iterator The const iterator to the beginning.
                 */
                const_iterator cbegin() const { return element.second.cbegin(); }
                /**
                 * @brief Return a const iterator to the end.
                 * @return const_iterator The const iterator to the end.
                 */
                const_iterator cend() const { return element.second.cend(); }
                /**
                 * @brief Return a reverse iterator to the beginning.
                 * @return reverse_iterator The reverse iterator to the beginning.
                 */
                reverse_iterator rbegin() { return element.second.rbegin(); }
                /**
                 * @brief Return a reverse iterator to the end.
                 * @return reverse_iterator The reverse iterator to the end.
                 */
                reverse_iterator rend() { return element.second.rend(); }
                /**
                 * @brief Return a const reverse iterator to the beginning.
                 * @return const_reverse_iterator The const reverse iterator to the beginning.
                 */
                const_reverse_iterator crbegin() { return element.second.crbegin(); }
                /**
                 * @brief Return a const reverse iterator to the end.
                 * @return const_reverse_iterator The const reverse iterator to the end.
                 */
                const_reverse_iterator crend() { return element.second.crend(); }

                /**
                 * @brief The npos value
                 */
                static const int npos = -1;

                /**
                 * @brief Construct a new CSSElement object
                 * @param tag The tag of the element
                 * @param properties The properties of the element
                 */
                CSSElement(const std::string& tag, const std::vector<CSSProperty>& properties);
                /**
                 * @brief Construct a new CSSElement object
                 * @param element The element to set
                 */
                CSSElement(const std::pair<std::string, std::vector<CSSProperty>>& element);
                CSSElement() = default;

                /**
                 * @brief Prepend a property to the element
                 * @param property The property to push
                 */
                void push_front(const CSSProperty& property);
                /**
                 * @brief Append a property to the element
                 * @param property The property to push
                 */
                void push_back(const CSSProperty& property);
                /**
                 * @brief Insert a property into the element
                 * @param index The index to insert the property
                 * @param property The property to insert
                 */
                void insert(const int index, const CSSProperty& property);
                /**
                 * @brief Erase a property from the element
                 * @param index The index of the property to erase
                 */
                void erase(const int index);
                /**
                 * @brief Find a property in the element
                 * @param property The property to find
                 * @return int The index of the property
                 */
                int find(const CSSProperty& property);
                /**
                 * @brief Get the property at an index
                 * @param index The index of the property
                 * @return CSSProperty The property at the index
                 */
                CSSProperty at(const int index) const;
                /**
                 * @brief Find a property in the element
                 * @param str The property to find
                 * @return int The index of the property
                 */
                int find(const std::string& str);
                /**
                 * @brief Swap two properties in the element
                 * @param index1 The index of the first property
                 * @param index2 The index of the second property
                 */
                void swap(const int index1, const int index2);
                /**
                 * @brief Swap two properties in the element
                 * @param property1 The first property
                 * @param property2 The second property
                 */
                void swap(const CSSProperty& property1, const CSSProperty& property2);
                /**
                 * @brief Get the first property of the element
                 * @return CSSProperty The first property of the element
                 */
                CSSProperty front() const;
                /**
                 * @brief Get the last property of the element
                 * @return CSSProperty The last property of the element
                 */
                CSSProperty back() const;
                /**
                 * @brief Get the size of the element
                 * @return int The size of the element
                 */
                int size() const;
                /**
                 * @brief Set the properties of the element
                 * @param properties The properties to set
                 */
                void set(const std::string& tag, const std::vector<CSSProperty>& properties);
                /**
                 * @brief Set the properties of the element
                 * @param element The element to set
                 */
                void set(const std::pair<std::string, std::vector<CSSProperty>>& element);
                /**
                 * @brief Get the element
                 * @return std::pair<std::string, std::vector<CSSProperty>> The element
                 */
                std::string get(const int formatting = FORMATTING_NONE, const int tabc = 0) const;
                /**
                 * @brief Get the tag of the element
                 * @return std::string The tag of the element
                 */
                std::string getTag() const;
                /**
                 * @brief Get the properties of the element
                 * @return std::vector<CSSProperty> The properties of the element
                 */
                std::vector<CSSProperty> getProperties() const;

                CSSElement operator=(const CSSElement& element);
                CSSElement operator=(const std::pair<std::string, std::vector<CSSProperty>>& element);
                void operator+=(const CSSProperty& property);
                CSSProperty operator[](const int& index) const;
        };

        /**
         * @brief A class to represent a CSS stylesheet
         */
        class CSSStylesheet {
            private:
                std::vector<CSSElement> elements{};
            protected:
            public:
                using iterator = std::vector<CSSElement>::iterator;
                using const_iterator = std::vector<CSSElement>::const_iterator;
                using reverse_iterator = std::vector<CSSElement>::reverse_iterator;
                using const_reverse_iterator = std::vector<CSSElement>::const_reverse_iterator;

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
                 * @brief Return a const iterator to the beginning.
                 * @return const_iterator The const iterator to the beginning.
                 */
                const_iterator cbegin() const { return elements.cbegin(); }
                /**
                 * @brief Return a const iterator to the end.
                 * @return const_iterator The const iterator to the end.
                 */
                const_iterator cend() const { return elements.cend(); }
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
                const_reverse_iterator crbegin() { return elements.crbegin(); }
                /**
                 * @brief Return a const reverse iterator to the end.
                 * @return const_reverse_iterator The const reverse iterator to the end.
                 */
                const_reverse_iterator crend() { return elements.crend(); }

                /**
                 * @brief The npos value
                 */
                static const int npos = -1;

                /**
                 * @brief Construct a new CSSStylesheet object
                 * @param elements The elements to set
                 */
                CSSStylesheet(const std::vector<CSSElement>& elements);
                CSSStylesheet() = default;

                /**
                 * @brief Prepend an element to the stylesheet
                 * @param element The element to add
                 */
                void push_front(const CSSElement& element);
                /**
                 * @brief Append an element to the stylesheet
                 * @param element The element to add
                 */
                void push_back(const CSSElement& element);
                /**
                 * @brief Insert an element into the stylesheet
                 * @param index The index to insert the element
                 * @param element The element to insert
                 */
                void insert(const int index, const CSSElement& element);
                /**
                 * @brief Erase an element from the stylesheet. Note that this will NOT change the size/index.
                 * @param index The index of the element to erase
                 */
                void erase(const int index);
                /**
                 * @brief Find an element in the stylesheet
                 * @param element The element to find
                 * @return int The index of the element
                 */
                int find(const CSSElement& element);
                /**
                 * @brief Find an element in the stylesheet
                 * @param str The element to find, either the tag or the stylesheet itself
                 * @return int The index of the element
                 */
                int find(const std::string& str);
                /**
                 * @brief Get the element at an index
                 * @param index The index of the element
                 * @return CSSElement The element at the index
                 */
                CSSElement at(const int index) const;
                /**
                 * @brief Get the size of the stylesheet
                 * @return int The size of the stylesheet
                 */
                int size() const;
                /**
                 * @brief Get the first element of the stylesheet
                 * @return CSSElement The first element of the stylesheet
                 */
                CSSElement front() const;
                /**
                 * @brief Get the last element of the stylesheet
                 * @return CSSElement The last element of the stylesheet
                 */
                CSSElement back() const;
                /**
                 * @brief Swap two elements in the stylesheet
                 * @param index1 The index of the first element
                 * @param index2 The index of the second element
                 */
                void swap(const int index1, const int index2);
                /**
                 * @brief Swap two elements in the stylesheet
                 * @param element1 The first element
                 * @param element2 The second element
                 */
                void swap(const CSSElement& element1, const CSSElement& element2);
                /**
                 * @brief Set the elements of the stylesheet
                 * @param elements The elements to set
                 */
                void set(const std::vector<CSSElement>& elements);
                /**
                 * @brief Get the elements of the stylesheet
                 * @return std::vector<CSSElement> The elements of the stylesheet
                 */
                std::vector<CSSElement> getElements() const;
                /**
                 * @brief Get the stylesheet
                 * @return std::string The stylesheet
                 */
                std::string get(const int formatting = FORMATTING_NONE, const int tabc = 0) const;

                CSSStylesheet operator=(const CSSStylesheet& stylesheet);
                void operator+=(const CSSElement& element);
                CSSElement operator[](const int& index) const;
        };
    }
}
