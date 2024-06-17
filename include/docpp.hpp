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
#include <utility>
#include <type_traits>
#include <tuple>

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
            explicit out_of_range(const char* message) : message(message) {};
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
            explicit invalid_argument(const char* message) : message(message) {};
    };

    /**
     * @brief A namespace to represent HTML elements and documents
     */
    namespace HTML {
        /**
         * @brief Enum for element tags.
         */
        enum class Tag {
            Empty, /* Empty element */
            Empty_No_Formatting, /* Empty element, that ignores any formatting by get() calls. */
            Abbreviation, /* <abbr></abbr> */
            Abbr, /* <abbr></abbr> */
            Acronym, /* <acronym></acronym> */
            Address, /* <address></address> */
            Anchor, /* <a></a> */
            A, /* <a></a> */
            Applet, /* <applet></applet> */
            Article, /* <article></article> */
            Area, /* <area></area> */
            Aside, /* <aside></aside> */
            Audio, /* <audio></audio> */
            Base, /* <base></base> */
            Basefont, /* <basefont></basefont> */
            Bdi, /* <bdi></bdi> */
            Bdo, /* <bdo></bdo> */
            Bgsound, /* <bgsound></bgsound> */
            Big, /* <big></big> */
            Blockquote, /* <blockquote></blockquote> */
            Body, /* <body></body> */
            Bold, /* <b></b> */
            B, /* <b></b> */
            Br, /* <br> */
            Break, /* <br> */
            Button, /* <button></button> */
            Caption, /* <caption></caption> */
            Canvas, /* <canvas></canvas> */
            Center, /* <center></center> */
            Cite, /* <cite></cite> */
            Code, /* <code></code> */
            Colgroup, /* <colgroup></colgroup> */
            Col, /* <col></col> */
            Column, /* <col></col> */
            Data, /* <data></data> */
            Datalist, /* <datalist></datalist> */
            Dd, /* <dd></dd> */
            Dfn, /* <dfn></dfn> */
            Define, /* <dfn></dfn> */
            Delete, /* <del></del> */
            Del, /* <del></del> */
            Details, /* <details></details> */
            Dialog, /* <dialog></dialog> */
            Dir, /* <dir></dir> */
            Div, /* <div></div> */
            Dl, /* <dl></dl> */
            Dt, /* <dt></dt> */
            Embed, /* <embed></embed> */
            Fieldset, /* <fieldset></fieldset> */
            Figcaption, /* <figcaption></figcaption> */
            Figure, /* <figure></figure> */
            Font, /* <font></font> */
            Footer, /* <footer></footer> */
            Form, /* <form></form> */
            Frame, /* <frame></frame> */
            Frameset, /* <frameset></frameset> */
            Head, /* <head></head> */
            Header, /* <header></header> */
            H1, /* <h1></h1> */
            H2, /* <h2></h2> */
            H3, /* <h3></h3> */
            H4, /* <h4></h4> */
            H5, /* <h5></h5> */
            H6, /* <h6></h6> */
            Hgroup, /* <hgroup></hgroup> */
            Hr, /* <hr> */
            Html, /* <html></html> */
            Iframe, /* <iframe></iframe> */
            Image, /* <img> */
            Img, /* <img> */
            Input, /* <input> */
            Ins, /* <ins></ins> */
            Isindex, /* <isindex></isindex> */
            Italic, /* <i></i> */
            I, /* <i></i> */
            Kbd, /* <kbd></kbd> */
            Keygen, /* <keygen></keygen> */
            Label, /* <label></label> */
            Legend, /* <legend></legend> */
            List, /* <li></li> */
            Li, /* <li></li> */
            Link, /* <link></link> */
            Main, /* <main></main> */
            Mark, /* <mark></mark> */
            Marquee, /* <marquee></marquee> */
            Menuitem, /* <menuitem></menuitem> */
            Meta, /* <meta></meta> */
            Meter, /* <meter></meter> */
            Nav, /* <nav></nav> */
            Nobreak, /* <nobr></nobr> */
            Nobr, /* <nobr></nobr> */
            Noembed, /* <noembed></noembed> */
            Noscript, /* <noscript></noscript> */
            Object, /* <object></object> */
            Optgroup, /* <optgroup></optgroup> */
            Option, /* <option></option> */
            Output, /* <output></output> */
            Paragraph, /* <p></p> */
            P, /* <p></p> */
            Param, /* <param></param> */
            Phrase, /* <pharse></pharse> */
            Pre, /* <pre></pre> */
            Progress, /* <progress></progress> */
            Quote, /* <q></q> */
            Q, /* <q></q> */
            Rp, /* <rp></rp> */
            Rt, /* <rt></rt> */
            Ruby, /* <ruby></ruby> */
            Outdated, /* <s></s> */
            S, /* <s></s> */
            Sample, /* <samp></samp> */
            Samp, /* <samp></samp> */
            Script, /* <script></script> */
            Section, /* <section></section> */
            Small, /* <small></small> */
            Source, /* <source></source> */
            Spacer, /* <spacer></spacer> */
            Span, /* <span></span> */
            Strike, /* <strike></strike> */
            Strong, /* <strong></strong> */
            Style, /* <style></style> */
            Sub, /* <sub></sub> */
            Subscript, /* <sub></sub> */
            Sup, /* <sup></sup> */
            Superscript, /* <sup></sup> */
            Summary, /* <summary></summary> */
            Svg, /* <svg></svg> */
            Table, /* <table></table> */
            Tbody, /* <tbody></tbody> */
            Td, /* <td></td> */
            Template, /* <template></template> */
            Tfoot, /* <tfoot></tfoot> */
            Th, /* <th></th> */
            Thead, /* <thead></thead> */
            Time, /* <time></time> */
            Title, /* <title></title> */
            Tr, /* <tr></tr> */
            Track, /* <track></track> */
            Tt, /* <tt></tt> */
            Underline, /* <u></u> */
            U, /* <u></u> */
            Var, /* <var></var> */
            Video, /* <video></video> */
            Wbr, /* <wbr></wbr> */
            Xmp, /* <xmp></xmp> */
        };

        /**
         * @brief Enum for element types.
         */
        enum class Type {
            Self_Closing, /* Self-closing element (<tag ... />)*/
            Non_Self_Closing, /* Non-self-closing element (<tag></tag>) */
            Non_Closed, /* Non-closed element (<tag>) */
            Non_Opened, /* Non-opened element (</tag>) */
            Text_No_Formatting, /* Text element with no formatting (my text here). */
            Text, /* Text element with tab characters appropriately prepended (my text here). Note that this does *not* append a newline character. */
        };

        /**
         * @brief Enum for formatting options.
         */
        enum class Formatting {
            None, /* No formatting. Output is in the form of one long string of text, and a single newline character. */
            Pretty, /* Pretty formatting. Output is formatted with newlines and tabs as deemed appropriate. */
            Newline, /* Newline formatting. Each element has a newline appended. */
        };

        /**
         * @brief Get a map of tags to strings and types.
         * @return std::unordered_map<docpp::HTML::Tag, std::pair<std::string, docpp::HTML::Type>> The map of tags to strings and types.
         */
        std::unordered_map<docpp::HTML::Tag, std::pair<std::string, docpp::HTML::Type>> get_tag_map();
        /**
         * @brief Resolve a tag to a string and type.
         * @param tag The tag to resolve
         * @return std::pair<std::string, Type> The resolved tag
         */
        std::pair<std::string, Type> resolve_tag(const Tag tag);
        /**
         * @brief Resolve a string tag to a Tag enum.
         * @param tag The tag to resolve
         * @return Tag The resolved tag
         */
        Tag resolve_tag(const std::string& tag);

        /**
         * @brief A class to represent an HTML property
         */
        class Property {
            private:
                std::pair<std::string, std::string> property{};
            protected:
            public:
                using size_type = std::size_t;

                /**
                 * @brief The npos value
                 */
                static const size_type npos = -1;

                /**
                 * @brief Construct a new Property object
                 * @param key The key of the property
                 * @param value The value of the property
                 */
                Property(const std::string& key, const std::string& value) : property(std::make_pair(key, value)) {};
                /**
                 * @brief Construct a new Property object
                 * @param property The property to set
                 */
                Property(const Property& property) : property(property.property) {};
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
                 * @return std::string The key of the property
                 */
                std::string get_key() const;
                /**
                 * @brief Get the key of the property in a specific type
                 * @return T The key of the property
                 */
                template <typename T> T get_key() const {
                    if (std::is_same<T, std::string>::value) {
                        return this->property.first;
                    }

                    return T(this->property.first);
                };
                /**
                 * @brief Get the value of the property
                 * @return std::string The value of the property
                 */
                std::string get_value() const;
                /**
                 * @brief Get the value of the property in a specific type
                 * @return T The value of the property
                 */
                template <typename T> T get_value() const {
                    if (std::is_same<T, std::string>::value) {
                        return this->property.second;
                    }
                    return T(this->property.second);
                }
                /**
                 * @brief Get the property.
                 * @return std::pair<std::string, std::string> The value of the property
                 */
                std::pair<std::string, std::string> get() const;
                /**
                 * @brief Get the property in a specific type.
                 * @return std::pair<T, T> The value of the property
                 */
                template <typename T> std::pair<T, T> get() const {
                    if (std::is_same<T, std::string>::value) {
                        return this->property;
                    }

                    return T(this->property);
                }
                /**
                 * @brief Set the key of the property.
                 * @param key The key.
                 */
                void set_key(const std::string& key);
                /**
                 * @brief Set the value of the property.
                 * @param value The value.
                 */
                void set_value(const std::string& value);
                /**
                 * @brief Set the property
                 * @param property The property.
                 */
                void set(const std::pair<std::string, std::string>& property);
                /**
                 * @brief Clear the property
                 */
                void clear();
                /**
                 * @brief Check if the property is empty
                 * @return bool True if the property is empty, false otherwise
                 */
                bool empty() const;

                Property& operator=(const Property& property);
                bool operator==(const Property& property) const;
                bool operator!=(const Property& property) const;

        };

        /**
         * @brief A class to represent the properties of an HTML element
         */
        class Properties {
            private:
                std::vector<Property> properties{};
            protected:
            public:
                using size_type = std::size_t;
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
                static const size_type npos = -1;

                /**
                 * @brief Get the properties of the element
                 * @return std::vector<Property> The properties of the element
                 */
                std::vector<Property> get_properties() const;
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
                Property at(const size_type index) const;
                /**
                 * @brief Insert a property into the element
                 * @param index The index to insert the property
                 * @param property The property to insert
                 */
                void insert(const size_type index, const Property& property);
                /**
                 * @brief Erase a property from the element
                 * @param index The index of the property to erase
                 */
                void erase(const size_type index);
                /**
                 * @brief Find a property in the element
                 * @param property The property to find
                 * @return size_type The index of the property
                 */
                size_type find(const Property& property);
                /**
                 * @brief Find a property in the element
                 * @param str The property to find
                 * @return size_type The index of the property
                 */
                size_type find(const std::string& str);
                /**
                 * @brief Swap two properties in the element
                 * @param index1 The index of the first property
                 * @param index2 The index of the second property
                 */
                void swap(const size_type index1, const size_type index2);
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
                 * @return size_type The size of the element
                 */
                size_type size() const;
                /**
                 * @brief Clear the properties
                 */
                void clear();
                /**
                 * @brief Check if the properties are empty
                 * @return bool True if the properties are empty, false otherwise
                 */
                bool empty() const;
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
                Properties(const std::vector<Property>& properties) : properties(properties) {};
                /**
                 * @brief Construct a new Properties object
                 * @param property The property to add
                 */
                Properties(const Property& property) : properties({property}) {};
                /**
                 * @brief Construct a new Properties object
                 * @param properties The properties to set
                 */
                Properties(const Properties& properties) : properties(properties.properties) {};
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

        /**
         * @brief A class to represent an HTML element
         */
        class Element {
            private:
                std::string tag{};
                std::string data{};
                Type type{Type::Non_Self_Closing};
                Properties properties{};
            protected:
            public:
                using size_type = std::size_t;
                /**
                 * @brief The npos value
                 */
                static const size_type npos = -1;

                /**
                 * @brief Construct a new Element object
                 * @param tag The tag of the element
                 * @param properties The properties of the element
                 * @param data The data of the element
                 * @param type The close tag type.
                 */
                Element(const std::string& tag, const Properties& properties = {}, const std::string& data = {}, const Type type = Type::Non_Self_Closing) : tag(tag), properties(properties), data(data), type(type) {};
                /**
                 * @brief Construct a new Element object
                 * @param tag The tag of the element
                 * @param properties The properties of the element
                 * @param data The data of the element
                 */
                Element(const Tag tag, const Properties& properties = {}, const std::string& data = {}) : tag(resolve_tag(tag).first), properties(properties), data(data), type(resolve_tag(tag).second) {};
                /**
                 * @brief Construct a new Element object
                 * @param element The element to set
                 */
                Element(const Element& element) : tag(element.tag), properties(element.properties), data(element.data), type(element.type) {};
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
                void set(const std::string& tag, const Properties& properties = {}, const std::string& data = {}, const Type type = Type::Non_Self_Closing);
                /**
                 * @brief Set the tag, properties, and data of the element
                 * @param tag The tag of the element
                 * @param properties The properties of the element
                 * @param data The data of the element
                 */
                void set(const Tag tag, const Properties& properties = {}, const std::string& data = {});
                /**
                 * @brief Set the tag of the element
                 * @param tag The tag of the element
                 */
                void set_tag(const std::string& tag);
                /**
                 * @brief Set the tag of the element
                 * @param tag The tag of the element
                 */
                void set_tag(const Tag tag);
                /**
                 * @brief Set the data of the element
                 * @param data The data of the element
                 */
                void set_data(const std::string& data);
                /**
                 * @brief Set the properties of the element
                 * @param properties The properties of the element
                 */
                void set_properties(const Properties& properties);
                /**
                 * @brief Set the type of the element
                 * @param type The type of the element
                 */
                void set_type(const Type type);

                /**
                 * @brief Get the element in the form of an HTML tag.
                 * @return std::string The tag of the element
                 */
                std::string get(const Formatting formatting = Formatting::None, const int tabc = 0) const;
                /**
                 * @brief Get the element in the form of a specific type.
                 * @return T The element in the form of a specific type
                 */
                template <typename T> T get(const Formatting formatting = Formatting::None, const int tabc = 0) const {
                    if (std::is_same<T, std::string>::value) {
                        return this->get(formatting, tabc);
                    }
                    return T(this->get(formatting, tabc));
                }

                /**
                 * @brief Get the tag of the element
                 * @return std::string The data of the element
                 */
                std::string get_tag() const;
                /**
                 * @brief Get the tag of the element in a specific type
                 * @return T The tag of the element
                 */
                template <typename T> T get_tag() const {
                    if (std::is_same<T, std::string>::value) {
                        return this->tag;
                    }
                    return T(this->tag);
                }

                /**
                 * @brief Get the data of the element
                 * @return std::string The data of the element
                 */
                std::string get_data() const;
                /**
                 * @brief Get the data of the element in a specific type
                 * @return T The data of the element
                 */
                template <typename T> T get_data() const {
                    if (std::is_same<T, std::string>::value) {
                        return this->data;
                    }
                    return T(this->data);
                }
                /**
                 * @brief Get the properties of the element
                 * @return Properties The properties of the element
                 */
                Properties get_properties() const;
                /**
                 * @brief Get the type of the element
                 * @return Type The type of the element
                 */
                Type get_type() const;
                /**
                 * @brief Clear the element
                 */
                void clear();
                /**
                 * @brief Check if the element is empty.
                 * @return bool True if the element is empty, false otherwise.
                 */
                bool empty() const;

                Element& operator=(const Element& element);
                Element& operator+=(const std::string& data);
                bool operator==(const Element& element) const;
                bool operator!=(const Element& element) const;
        };

        /**
         * @brief A class to represent an HTML section (head, body, etc.)
         */
        class Section {
            protected:
            public:
                using size_type = std::size_t;

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
                 * @brief Return a const iterator to the beginning.
                 * @return const_iterator The const iterator to the beginning.
                 */
                const_iterator cbegin() const { return const_iterator(elements.cbegin()); }
                /**
                 * @brief Return a const iterator to the end.
                 * @return const_iterator The const iterator to the end.
                 */
                const_iterator cend() const { return const_iterator(elements.cend()); }
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
                const_reverse_iterator crbegin() { return const_reverse_iterator(elements.crbegin()); }
                /**
                 * @brief Return a const reverse iterator to the end.
                 * @return const_reverse_iterator The const reverse iterator to the end.
                 */
                const_reverse_iterator crend() { return const_reverse_iterator(elements.crend()); }

                /**
                 * @brief The npos value
                 */
                static const size_type npos = -1;

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
                Element at(const size_type index) const;
                /**
                 * @brief Get the section at an index. To get an element, use at()
                 * @param index The index of the section
                 * @return Section The section at the index
                 */
                Section at_section(const size_type index) const;
                /**
                 * @brief Erase an element from the section. Note that this will NOT change the size/index.
                 * @param index The index of the element to erase
                 */
                void erase(const size_type index);
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
                size_type find(const Element& element);
                /**
                 * @brief Find a section in the section
                 * @param section The section to find
                 * @return size_type The index of the section
                 */
                size_type find(const Section& section);
                /**
                 * @brief Find an element or section in the section
                 * @param str The element or section to find
                 * @return size_type The index of the element or section
                 */
                size_type find(const std::string& str);
                /**
                 * @brief Insert an element into the section
                 * @param index The index to insert the element
                 * @param element The element to insert
                 */
                void insert(const size_type index, const Element& element);
                /**
                 * @brief Insert a section into the section
                 * @param index The index to insert the section
                 * @param section The section to insert
                 */
                void insert(const size_type index, const Section& section);
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
                 * @return size_type The size of the section
                 */
                size_type size() const;
                /**
                 * @brief Clear the section
                 */
                void clear();
                /**
                 * @brief Check if the section is empty
                 * @return bool True if the section is empty, false otherwise
                 */
                bool empty() const;

                /**
                 * @brief Construct a new Section object
                 * @param tag The tag of the section
                 * @param properties The properties of the section
                 */
                Section(const std::string& tag, const Properties& properties = {}) : tag(tag), properties(properties) {};
                /**
                 * @brief Construct a new Section object
                 * @param tag The tag of the section
                 * @param properties The properties of the section
                 */
                Section(const Tag tag, const Properties& properties = {}) : tag(resolve_tag(tag).first), properties(properties) {};
                /**
                 * @brief Construct a new Section object
                 * @param tag The tag of the section
                 * @param properties The properties of the section
                 * @param elements The elements of the section
                 */
                Section(const std::string& tag, const Properties& properties, const std::vector<Element>& elements) : tag(tag), properties(properties) {
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
                Section(const std::string& tag, const Properties& properties, const std::vector<Section>& sections) : tag(tag), properties(properties) {
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
                void set(const Tag tag, const Properties& properties = {});
                /**
                 * @brief Set the tag of the section
                 * @param tag The tag of the section
                 */
                void set_tag(const std::string& tag);
                /**
                 * @brief Set the tag of the section
                 * @param tag The tag of the section
                 */
                void set_tag(const Tag tag);
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
                void swap(const size_type index1, const size_type index2);
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
                std::vector<Element> get_elements() const;
                /**
                 * @brief Get the sections of the section
                 * @return std::vector<Section> The sections of the section
                 */
                std::vector<Section> get_sections() const;

                /**
                 * @brief Dump the entire section.
                 * @return std::string The section
                 */
                std::string get(const Formatting formatting = Formatting::None, const int tabc = 0) const;
                /**
                 * @brief Get the element in the form of a specific type.
                 * @return T The element in the form of a specific type
                 */
                template <typename T> T get(const Formatting formatting = Formatting::None, const int tabc = 0) const {
                    if (std::is_same<T, std::string>::value) {
                        return this->get(formatting, tabc);
                    }
                    return T(this->get(formatting, tabc));
                }

                /**
                 * @brief Get the tag of the section
                 * @return std::string The tag of the section
                 */
                std::string get_tag() const;
                /**
                 * @brief Get the tag of the section in a specific type
                 * @return T The tag of the section
                 */
                template <typename T> T get_tag() const {
                    if (std::is_same<T, std::string>::value) {
                        return this->tag;
                    }
                    return T(this->tag);
                }
                /**
                 * @brief Get the properties of the section
                 * @return Properties The properties of the section
                 */
                Properties get_properties() const;

                Section& operator=(const Section& section);
                Section& operator+=(const Element& element);
                Section& operator+=(const Section& section);
                bool operator==(const Element& element) const;
                bool operator==(const Section& section) const;
                bool operator!=(const Element& element) const;
                bool operator!=(const Section& section) const;
                Element operator[](const int& index) const;
                std::unordered_map<std::string, Element> operator[](const std::string& tag) const;
                std::unordered_map<std::string, Element> operator[](const Tag tag) const;
            private:
                size_type index{};
                std::string tag{};
                Properties properties{};

                std::map<int, Element> elements{};
                std::unordered_map<int, Section> sections{};
        };

        /**
         * @brief A class to represent an HTML document
         */
        class Document {
            private:
                std::string doctype{"<!DOCTYPE html>"};
                Section document{};
            protected:
            public:
                using size_type = std::size_t;

                /**
                 * @brief The npos value
                 */
                static const size_type npos = -1;

                /**
                 * @brief Get the document
                 * @param std::string The type to return
                 * @return std::string The document
                 */
                std::string get(const Formatting formatting = Formatting::None, const int tabc = 0) const;
                /**
                 * @brief Get the document in the form of a specific type.
                 * @return T The document in the form of a specific type
                 */
                template <typename T> T get(const Formatting formatting = Formatting::None, const int tabc = 0) const {
                    if (std::is_same<T, std::string>::value) {
                        return this->get(formatting, tabc);
                    }
                    return T(this->get(formatting, tabc));
                }

                /**
                 * @brief Get the section
                 * @return Section The section
                 */
                Section& get_section();

                /**
                 * @brief Get the doctype of the document
                 * @return std::string The doctype of the document
                 */
                std::string get_doctype() const;
                /**
                 * @brief Get the doctype of the document in a specific type
                 * @return T The doctype of the document
                 */
                template <typename T> T get_doctype() const {
                    if (std::is_same<T, std::string>::value) {
                        return this->doctype;
                    }
                    return T(this->doctype);
                }

                /**
                 * @brief Set the document
                 * @param document The document to set
                 */
                void set(const Section& document);
                /**
                 * @brief Set the doctype of the document
                 * @param doctype The doctype to set
                 */
                void set_doctype(const std::string& doctype);
                /**
                 * @brief Get the size of the document
                 * @return size_type The size of the document
                 */
                size_type size() const;
                /**
                 * @brief Check if the document is empty
                 */
                bool empty() const;
                /**
                 * @brief Clear the document
                 */
                void clear();
                /**
                 * @brief Construct a new Document object
                 */
                Document() = default;
                /**
                 * @brief Destroy the Document object
                 */
                ~Document() = default;
                /**
                 * @brief Construct a new Document object
                 * @param document The document to set
                 */
                Document(const Section& document, const std::string& doctype = "<!DOCTYPE html>") : document(document), doctype(doctype) {};
                /**
                 * @brief Construct a new Document object
                 * @param document The document to set
                 */
                Document(const Document& document) : document(document.document), doctype(document.doctype) {};

                Document& operator=(const Document& document);
                Document& operator=(const Section& section);
                bool operator==(const Document& document) const;
                bool operator==(const Section& section) const;
                bool operator!=(const Document& document) const;
                bool operator!=(const Section& section) const;
        };
    } // namespace HTML

    /**
     * @brief A namespace to represent CSS elements and documents
     */
    namespace CSS {
        /**
         * @brief Enum for formatting options.
         */
        enum class Formatting {
            None,
            Pretty,
            Newline,
        };

        /**
         * @brief A class to represent a CSS property
         */
        class Property {
            private:
                std::pair<std::string, std::string> property{};
            protected:
            public:
                using size_type = std::size_t;
                /**
                 * @brief The npos value
                 */
                static const size_type npos = -1;

                /**
                 * @brief Construct a new Property object
                 * @param key The key of the property
                 * @param value The value of the property
                 */
                Property(const std::string& key, const std::string& value) : property(std::make_pair(key, value)) {};
                /**
                 * @brief Construct a new Property object
                 */
                Property(const Property& property) : property(property.property) {};
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
                 * @return std::string The key of the property
                 */
                std::string get_key() const;
                /**
                 * @brief Get the key of the property in a specific type
                 * @return T The key of the property
                 */
                template <typename T> T get_key() const {
                    if (std::is_same<T, std::string>::value) {
                        return this->property.first;
                    }
                    return T(this->property.first);
                }
                /**
                 * @brief Get the value of the property
                 * @return std::string The value of the property
                 */
                std::string get_value() const;
                /**
                 * @brief Get the value of the property in a specific type
                 * @return T The value of the property
                 */
                template <typename T> T get_value() const {
                    if (std::is_same<T, std::string>::value) {
                        return this->property.second;
                    }
                    return T(this->property.second);
                }
                /**
                 * @brief Get the property.
                 * @return std::pair<std::string, std::string> The value of the property
                 */
                std::pair<std::string, std::string> get() const;
                /**
                 * @brief Get the property in a specific type.
                 * @return std::pair<T, T> The value of the property
                 */
                template <typename T> std::pair<T, T> get() const {
                    if (std::is_same<T, std::string>::value) {
                        return std::make_pair(this->property.first, this->property.second);
                    }
                    return std::pair<T, T>(this->property.first, this->property.second);
                }
                /**
                 * @brief Set the key of the property.
                 * @param key The key.
                 */
                void set_key(const std::string& key);
                /**
                 * @brief Set the value of the property.
                 * @param value The value.
                 */
                void set_value(const std::string& value);
                /**
                 * @brief Set the property
                 * @param key The key of the property
                 * @param value The value of the property
                 */
                void set(const std::string& key, const std::string& value);

                Property& operator=(const Property& property);
                bool operator==(const Property& property) const;
                bool operator!=(const Property& property) const;
        };

        /**
         * @brief A class to represent the properties of a CSS element
         */
        class Element {
            private:
                std::pair<std::string, std::vector<Property>> element{};
            protected:
            public:
                using size_type = std::size_t;
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
                static const size_type npos = -1;

                /**
                 * @brief Construct a new Element object
                 * @param tag The tag of the element
                 * @param properties The properties of the element
                 */
                Element(const std::string& tag, const std::vector<Property>& properties) : element(std::make_pair(tag, properties)) {};
                /**
                 * @brief Construct a new Element object
                 * @param element The element to set
                 */
                Element(const Element& element) : element(element.element) {};
                /**
                 * @brief Construct a new Element object
                 */
                Element() = default;
                /**
                 * @brief Destroy the Element object
                 */
                ~Element() = default;

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
                void insert(const size_type index, const Property& property);
                /**
                 * @brief Erase a property from the element
                 * @param index The index of the property to erase
                 */
                void erase(const size_type index);
                /**
                 * @brief Find a property in the element
                 * @param property The property to find
                 * @return size_type The index of the property
                 */
                size_type find(const Property& property);
                /**
                 * @brief Get the property at an index
                 * @param index The index of the property
                 * @return Property The property at the index
                 */
                Property at(const size_type index) const;
                /**
                 * @brief Find a property in the element
                 * @param str The property to find
                 * @return size_type The index of the property
                 */
                size_type find(const std::string& str);
                /**
                 * @brief Swap two properties in the element
                 * @param index1 The index of the first property
                 * @param index2 The index of the second property
                 */
                void swap(const size_type index1, const size_type index2);
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
                 * @return size_type The size of the element
                 */
                size_type size() const;
                /**
                 * @brief Clear the element
                 */
                void clear();
                /**
                 * @brief Check if the element is empty
                 * @return bool True if the element is empty, false otherwise
                 */
                bool empty() const;
                /**
                 * @brief Set the properties of the element
                 * @param tag The tag of the element
                 * @param properties The properties to set
                 */
                void set(const std::string& tag, const std::vector<Property>& properties);
                /**
                 * @brief Set the properties of the element
                 * @param tag The tag of the element
                 * @param properties The properties to set
                 */
                void set(const HTML::Tag tag, const std::vector<Property>& properties);
                /**
                 * @brief Set the tag of the element
                 * @param tag The tag to set
                 */
                void set_tag(const std::string& tag);
                /**
                 * @brief Set the tag of the element
                 * @param tag The tag to set
                 */
                void set_tag(const HTML::Tag tag);
                /**
                 * @brief Set the properties of the element
                 * @param properties The properties to set
                 */
                void set_properties(const std::vector<Property>& properties);
                /**
                 * @brief Get the element
                 * @return std::pair<std::string, std::vector<Property>> The element
                 */
                std::string get(const Formatting formatting = Formatting::None, const int tabc = 0) const;
                /**
                 * @brief Get the element in the form of a specific type.
                 * @return T The element in the form of a specific type
                 */
                template <typename T> T get(const Formatting formatting = Formatting::None, const int tabc = 0) const {
                    if (std::is_same<T, std::string>::value) {
                        return this->get(formatting, tabc);
                    }
                    return T(this->get(formatting, tabc));
                }
                /**
                 * @brief Get the tag of the element
                 * @return std::string The tag of the element
                 */
                std::string get_tag() const;
                /**
                 * @brief Get the tag of the element in a specific type
                 * @return T The tag of the element
                 */
                template <typename T> T get_tag() const {
                    if (std::is_same<T, std::string>::value) {
                        return this->element.first;
                    }
                    return T(this->element.first);
                }
                /**
                 * @brief Get the properties of the element
                 * @return std::vector<Property> The properties of the element
                 */
                std::vector<Property> get_properties() const;

                Element& operator=(const Element& element);
                Element& operator=(const std::pair<std::string, std::vector<Property>>& element);
                Element& operator+=(const Property& property);
                Property operator[](const size_type& index) const;
                bool operator==(const Element& element) const;
                bool operator!=(const Element& element) const;
        };

        /**
         * @brief A class to represent a CSS stylesheet
         */
        class Stylesheet {
            private:
                std::vector<Element> elements{};
            protected:
            public:
                using size_type = std::size_t;
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
                static const size_type npos = -1;

                /**
                 * @brief Construct a new Stylesheet object
                 * @param elements The elements to set
                 */
                explicit Stylesheet(const std::vector<Element>& elements) : elements(elements) {};
                /**
                 * @brief Construct a new Stylesheet object
                 * @param stylesheet The stylesheet to set
                 */
                Stylesheet(const Stylesheet& stylesheet) : elements(stylesheet.elements) {};
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
                void insert(const size_type index, const Element& element);
                /**
                 * @brief Erase an element from the stylesheet. Note that this will NOT change the size/index.
                 * @param index The index of the element to erase
                 */
                void erase(const size_type index);
                /**
                 * @brief Find an element in the stylesheet
                 * @param element The element to find
                 * @return size_type The index of the element
                 */
                size_type find(const Element& element);
                /**
                 * @brief Find an element in the stylesheet
                 * @param str The element to find, either the tag or the stylesheet itself
                 * @return size_type The index of the element
                 */
                size_type find(const std::string& str);
                /**
                 * @brief Get the element at an index
                 * @param index The index of the element
                 * @return Element The element at the index
                 */
                Element at(const size_type index) const;
                /**
                 * @brief Get the size of the stylesheet
                 * @return size_type The size of the stylesheet
                 */
                size_type size() const;
                /**
                 * @brief Clear the stylesheet
                 */
                void clear();
                /**
                 * @brief Check if the stylesheet is empty
                 * @return bool True if the stylesheet is empty, false otherwise
                 */
                bool empty() const;
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
                void swap(const size_type index1, const size_type index2);
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
                std::vector<Element> get_elements() const;
                /**
                 * @brief Get the stylesheet
                 * @return std::string The stylesheet
                 */
                std::string get(const Formatting formatting = Formatting::None, const int tabc = 0) const;
                /**
                 * @brief Get the stylesheet in the form of a specific type.
                 * @return T The stylesheet in the form of a specific type
                 */
                template <typename T> T get(const Formatting formatting = Formatting::None, const int tabc = 0) const {
                    if (std::is_same<T, std::string>::value) {
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
    } // namespace CSS

    /**
     * @brief Get the version of the library
     * @return std::tuple<int, int, int> The version of the library
     */
    std::tuple<int, int, int> version();
} // namespace docpp
