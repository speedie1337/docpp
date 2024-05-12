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
        class Property {
            private:
                std::pair<std::string, std::string> property{};
            protected:
            public:
                /**
                 * @brief The npos value
                 */
                static const int npos = -1;

                /**
                 * @brief Construct a new Property object
                 * @param key The key of the property
                 * @param value The value of the property
                 */
                Property(const std::string& key, const std::string& value);
                /**
                 * @brief Construct a new Property object
                 * @param property The property to set
                 */
                Property(const std::pair<std::string, std::string>& property);
                Property() = default;

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

        using HTMLProperty = Property;

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
                 * @return std::vector<Property> The properties of the element
                 */
                std::vector<Property> getProperties() const;
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
                Property at(const int index) const;
                /**
                 * @brief Insert a property into the element
                 * @param index The index to insert the property
                 * @param property The property to insert
                 */
                void insert(const int index, const Property& property);
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
                int find(const Property& property);
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
                void swap(const Property& property1, const Property& property2);
                /**
                 * @brief Get the first property of the element
                 * @return Property The first property of the element
                 */
                Property front() const;
                /**
                 * @brief Get the last property of the element
                 * @return Property The last property of the element
                 */
                Property back() const;
                /**
                 * @brief Get the size of the element
                 * @return int The size of the element
                 */
                int size() const;
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
                /**
                 * @brief Construct a new Properties object
                 * @param properties The properties to set
                 */
                Properties(const std::vector<Property>& properties);
                /**
                 * @brief Construct a new Properties object
                 * @param property The property to add
                 */
                Properties(const Property& property);
                /**
                 * @brief Construct a new Properties object
                 */
                Properties() = default;
                Properties operator=(const Properties& properties);
                Properties operator=(const std::vector<Property>& properties);
                Properties operator=(const Property& property);
                void operator+=(const Property& property);
        };

        using HTMLElementProperties = Properties;

        /**
         * @brief A class to represent an HTML element
         */
        class Element {
            private:
                std::string tag{};
                std::string data{};
                int type{TYPE_NON_SELF_CLOSING};
                Properties properties{};
            protected:
            public:
                /**
                 * @brief The npos value
                 */
                static const int npos = -1;

                /**
                 * @brief Construct a new Element object
                 * @param tag The tag of the element
                 * @param properties The properties of the element
                 * @param data The data of the element
                 */
                Element(const std::string& tag, const Properties& properties = {}, const std::string& data = {}, const int type = TYPE_NON_SELF_CLOSING);
                /**
                 * @brief Construct a new Element object
                 */
                Element() = default;
                /**
                 * @brief Set the tag, id, and classes of the element
                 * @param tag The tag of the element
                 * @param id The id of the element
                 * @param classes The classes of the element
                 */
                void set(const std::string& tag, const Properties& properties = {}, const std::string& data = {}, const int type = TYPE_NON_SELF_CLOSING);

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
                Element operator=(const Element& element);
                void operator+=(const std::string& data);
        };

        using HTMLElement = Element;

        /**
         * @brief A class to represent an HTML section (head, body, etc.)
         */
        class Section {
            private:
                int index{};
                std::string tag{};
                Properties properties{};

                std::map<int, Element> elements{};
                std::unordered_map<int, Section> sections{};
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
                        sect_iterator(const T& element) : element(element) {}
                        sect_iterator operator++() { return ++element; }
                        Element operator*() { return element->second; }
                        bool operator==(const sect_iterator& other) { return element == other.element; }
                        bool operator!=(const sect_iterator& other) { return element != other.element; }
                };

                using iterator = sect_iterator<std::map<int, Element>::iterator>;
                using const_iterator = sect_iterator<std::map<int, Element>::const_iterator>;
                using reverse_iterator = sect_iterator<std::map<int, Element>::reverse_iterator>;
                using const_reverse_iterator = sect_iterator<std::map<int, Element>::const_reverse_iterator>;

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
                Element at(const int index) const;
                /**
                 * @brief Get the section at an index. To get an element, use at()
                 * @param index The index of the section
                 * @return Section The section at the index
                 */
                Section at_section(const int index) const;
                /**
                 * @brief Erase an element from the section. Note that this will NOT change the size/index.
                 * @param index The index of the element to erase
                 */
                void erase(const int index);
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
                 * @return int The index of the element
                 */
                int find(const Element& element);
                /**
                 * @brief Find a section in the section
                 * @param section The section to find
                 * @return int The index of the section
                 */
                int find(const Section& section);
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
                void insert(const int index, const Element& element);
                /**
                 * @brief Insert a section into the section
                 * @param index The index to insert the section
                 * @param section The section to insert
                 */
                void insert(const int index, const Section& section);
                /**
                 * @brief Get the first element of the section
                 * @return Element The first element of the section
                 */
                Element front() const;
                /**
                 * @brief Get the last element of the section
                 * @return Element The last element of the section
                 */
                Element back() const;
                /**
                 * @brief Get the first section of the section
                 * @return Section The first section of the section
                 */
                Section front_section() const;
                /**
                 * @brief Get the last section of the section
                 * @return Section The last section of the section
                 */
                Section back_section() const;
                /**
                 * @brief Get the size of the section
                 * @return int The size of the section
                 */
                int size() const;

                /**
                 * @brief Construct a new Section object
                 * @param tag The tag of the section
                 * @param properties The properties of the section
                 */
                Section(const std::string& tag, const Properties& properties = {});
                /**
                 * @brief Construct a new Section object
                 * @param tag The tag of the section
                 * @param properties The properties of the section
                 */
                Section(const int tag, const Properties& properties = {});
                /**
                 * @brief Construct a new Section object
                 */
                Section() = default;
                /**
                 * @brief Set the tag, id, and classes of the section
                 * @param tag The tag of the section
                 * @param id The id of the section
                 * @param classes The classes of the section
                 */
                void set(const std::string& tag, const Properties& properties = {});
                /**
                 * @brief Set the tag, id, and classes of the section
                 * @param tag The tag of the section
                 * @param id The id of the section
                 * @param classes The classes of the section
                 */
                void set(const int tag, const Properties& properties = {});
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
                void swap(const Element& element1, const Element& element2);
                /**
                 * @brief Swap two sections in the section
                 * @param index1 The index of the first section
                 * @param index2 The index of the second section
                 */
                void swap(const Section& section1, const Section& section2);
                /**
                 * @brief Get the elements of the section
                 * @return std::vector<Element> The elements of the section
                 */
                std::vector<Element> getElements() const;
                /**
                 * @brief Get the sections of the section
                 * @return std::vector<Section> The sections of the section
                 */
                std::vector<Section> getSections() const;

                /**
                 * @brief Dump the entire section.
                 * @return std::string The section
                 */
                std::string get(const int formatting = FORMATTING_NONE, const int tabc = 0) const;

                Section operator=(const Section& section);
                void operator+=(const Element& element);
                void operator+=(const Section& section);
                Element operator[](const int& index) const;
        };

        using HTMLSection = Section;

        /**
         * @brief A class to represent an HTML document
         */
        class Document {
            private:
                std::string doctype{"<!DOCTYPE html>"};
                Section document{};
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
                 * @return Section The section
                 */
                Section& getSection();

                /**
                 * @brief Get the doctype of the document
                 * @return std::string The doctype of the document
                 */
                std::string getDoctype() const;

                /**
                 * @brief Set the document
                 * @param document The document to set
                 */
                void set(const Section& document);
                /**
                 * @brief Set the doctype of the document
                 * @param doctype The doctype to set
                 */
                void setDoctype(const std::string& doctype);
                /**
                 * @brief Construct a new Document object
                 */
                Document() = default;
                /**
                 * @brief Construct a new Document object
                 * @param document The document to set
                 */
                Document(const Section& document, const std::string& doctype = "<!DOCTYPE html>");

                Document operator=(const Document& document);
                Document operator=(const Section& section);
        };

        using HTMLDocument = Document;
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
        class Property {
            private:
                std::pair<std::string, std::string> property{};
            protected:
            public:
                /**
                 * @brief The npos value
                 */
                static const int npos = -1;

                /**
                 * @brief Construct a new Property object
                 * @param key The key of the property
                 * @param value The value of the property
                 */
                Property(const std::string& key, const std::string& value);
                /**
                 * @brief Construct a new Property object
                 * @param property The property to set
                 */
                Property(const std::pair<std::string, std::string>& property);
                Property() = default;

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

                Property operator=(const Property& property);
                Property operator=(const std::pair<std::string, std::string>& property);
        };

        using CSSProperty = Property;

        class Element {
            private:
                std::pair<std::string, std::vector<Property>> element{};
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
                 * @brief Construct a new Element object
                 * @param tag The tag of the element
                 * @param properties The properties of the element
                 */
                Element(const std::string& tag, const std::vector<Property>& properties);
                /**
                 * @brief Construct a new Element object
                 * @param element The element to set
                 */
                Element(const std::pair<std::string, std::vector<Property>>& element);
                Element() = default;

                /**
                 * @brief Prepend a property to the element
                 * @param property The property to push
                 */
                void push_front(const Property& property);
                /**
                 * @brief Append a property to the element
                 * @param property The property to push
                 */
                void push_back(const Property& property);
                /**
                 * @brief Insert a property into the element
                 * @param index The index to insert the property
                 * @param property The property to insert
                 */
                void insert(const int index, const Property& property);
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
                int find(const Property& property);
                /**
                 * @brief Get the property at an index
                 * @param index The index of the property
                 * @return Property The property at the index
                 */
                Property at(const int index) const;
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
                void swap(const Property& property1, const Property& property2);
                /**
                 * @brief Get the first property of the element
                 * @return Property The first property of the element
                 */
                Property front() const;
                /**
                 * @brief Get the last property of the element
                 * @return Property The last property of the element
                 */
                Property back() const;
                /**
                 * @brief Get the size of the element
                 * @return int The size of the element
                 */
                int size() const;
                /**
                 * @brief Set the properties of the element
                 * @param properties The properties to set
                 */
                void set(const std::string& tag, const std::vector<Property>& properties);
                /**
                 * @brief Set the properties of the element
                 * @param element The element to set
                 */
                void set(const std::pair<std::string, std::vector<Property>>& element);
                /**
                 * @brief Get the element
                 * @return std::pair<std::string, std::vector<Property>> The element
                 */
                std::string get(const int formatting = FORMATTING_NONE, const int tabc = 0) const;
                /**
                 * @brief Get the tag of the element
                 * @return std::string The tag of the element
                 */
                std::string getTag() const;
                /**
                 * @brief Get the properties of the element
                 * @return std::vector<Property> The properties of the element
                 */
                std::vector<Property> getProperties() const;

                Element operator=(const Element& element);
                Element operator=(const std::pair<std::string, std::vector<Property>>& element);
                void operator+=(const Property& property);
                Property operator[](const int& index) const;
        };

        using CSSElement = Element;

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
                 * @brief Construct a new Stylesheet object
                 * @param elements The elements to set
                 */
                Stylesheet(const std::vector<Element>& elements);
                Stylesheet() = default;

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
                void insert(const int index, const Element& element);
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
                int find(const Element& element);
                /**
                 * @brief Find an element in the stylesheet
                 * @param str The element to find, either the tag or the stylesheet itself
                 * @return int The index of the element
                 */
                int find(const std::string& str);
                /**
                 * @brief Get the element at an index
                 * @param index The index of the element
                 * @return Element The element at the index
                 */
                Element at(const int index) const;
                /**
                 * @brief Get the size of the stylesheet
                 * @return int The size of the stylesheet
                 */
                int size() const;
                /**
                 * @brief Get the first element of the stylesheet
                 * @return Element The first element of the stylesheet
                 */
                Element front() const;
                /**
                 * @brief Get the last element of the stylesheet
                 * @return Element The last element of the stylesheet
                 */
                Element back() const;
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
                std::vector<Element> getElements() const;
                /**
                 * @brief Get the stylesheet
                 * @return std::string The stylesheet
                 */
                std::string get(const int formatting = FORMATTING_NONE, const int tabc = 0) const;

                Stylesheet operator=(const Stylesheet& stylesheet);
                void operator+=(const Element& element);
                Element operator[](const int& index) const;
        };

        using CSSStylesheet = Stylesheet;
    }
}
