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
        enum Tag {
            ELEMENT_EMPTY, /* Empty element */
            ELEMENT_EMPTY_NO_FORMAT, /* Empty element, that ignores any formatting by get() calls. */
            ELEMENT_ABBREVIATION, /* <abbr></abbr> */
            ELEMENT_ABBR, /* <abbr></abbr> */
            ELEMENT_ACRONYM, /* <acronym></acronym> */
            ELEMENT_ADDRESS, /* <address></address> */
            ELEMENT_ANCHOR, /* <a></a> */
            ELEMENT_A, /* <a></a> */
            ELEMENT_APPLET, /* <applet></applet> */
            ELEMENT_ARTICLE, /* <article></article> */
            ELEMENT_AREA, /* <area></area> */
            ELEMENT_ASIDE, /* <aside></aside> */
            ELEMENT_AUDIO, /* <audio></audio> */
            ELEMENT_BASE, /* <base></base> */
            ELEMENT_BASEFONT, /* <basefont></basefont> */
            ELEMENT_BDI, /* <bdi></bdi> */
            ELEMENT_BDO, /* <bdo></bdo> */
            ELEMENT_BGSOUND, /* <bgsound></bgsound> */
            ELEMENT_BIG, /* <big></big> */
            ELEMENT_BLOCKQUOTE, /* <blockquote></blockquote> */
            ELEMENT_BODY, /* <body></body> */
            ELEMENT_BOLD, /* <b></b> */
            ELEMENT_B, /* <b></b> */
            ELEMENT_BR, /* <br> */
            ELEMENT_BREAK, /* <br> */
            ELEMENT_BUTTON, /* <button></button> */
            ELEMENT_CAPTION, /* <caption></caption> */
            ELEMENT_CANVAS, /* <canvas></canvas> */
            ELEMENT_CENTER, /* <center></center> */
            ELEMENT_CITE, /* <cite></cite> */
            ELEMENT_CODE, /* <code></code> */
            ELEMENT_COLGROUP, /* <colgroup></colgroup> */
            ELEMENT_COL, /* <col></col> */
            ELEMENT_COLUMN, /* <col></col> */
            ELEMENT_DATA, /* <data></data> */
            ELEMENT_DATALIST, /* <datalist></datalist> */
            ELEMENT_DD, /* <dd></dd> */
            ELEMENT_DFN, /* <dfn></dfn> */
            ELEMENT_DEFINE, /* <dfn></dfn> */
            ELEMENT_DELETE, /* <del></del> */
            ELEMENT_DEL, /* <del></del> */
            ELEMENT_DETAILS, /* <details></details> */
            ELEMENT_DIALOG, /* <dialog></dialog> */
            ELEMENT_DIR, /* <dir></dir> */
            ELEMENT_DIV, /* <div></div> */
            ELEMENT_DL, /* <dl></dl> */
            ELEMENT_DT, /* <dt></dt> */
            ELEMENT_EMBED, /* <embed></embed> */
            ELEMENT_FIELDSET, /* <fieldset></fieldset> */
            ELEMENT_FIGCAPTION, /* <figcaption></figcaption> */
            ELEMENT_FIGURE, /* <figure></figure> */
            ELEMENT_FONT, /* <font></font> */
            ELEMENT_FOOTER, /* <footer></footer> */
            ELEMENT_FORM, /* <form></form> */
            ELEMENT_FRAME, /* <frame></frame> */
            ELEMENT_FRAMESET, /* <frameset></frameset> */
            ELEMENT_HEAD, /* <head></head> */
            ELEMENT_HEADER, /* <header></header> */
            ELEMENT_H1, /* <h1></h1> */
            ELEMENT_H2, /* <h2></h2> */
            ELEMENT_H3, /* <h3></h3> */
            ELEMENT_H4, /* <h4></h4> */
            ELEMENT_H5, /* <h5></h5> */
            ELEMENT_H6, /* <h6></h6> */
            ELEMENT_HGROUP, /* <hgroup></hgroup> */
            ELEMENT_HR, /* <hr> */
            ELEMENT_HTML, /* <html></html> */
            ELEMENT_IFRAME, /* <iframe></iframe> */
            ELEMENT_IMAGE, /* <img> */
            ELEMENT_IMG, /* <img> */
            ELEMENT_INPUT, /* <input> */
            ELEMENT_INS, /* <ins></ins> */
            ELEMENT_ISINDEX, /* <isindex></isindex> */
            ELEMENT_ITALIC, /* <i></i> */
            ELEMENT_I, /* <i></i> */
            ELEMENT_KBD, /* <kbd></kbd> */
            ELEMENT_KEYGEN, /* <keygen></keygen> */
            ELEMENT_LABEL, /* <label></label> */
            ELEMENT_LEGEND, /* <legend></legend> */
            ELEMENT_LIST, /* <li></li> */
            ELEMENT_LI, /* <li></li> */
            ELEMENT_LINK, /* <link></link> */
            ELEMENT_MAIN, /* <main></main> */
            ELEMENT_MARK, /* <mark></mark> */
            ELEMENT_MARQUEE, /* <marquee></marquee> */
            ELEMENT_MENUITEM, /* <menuitem></menuitem> */
            ELEMENT_META, /* <meta></meta> */
            ELEMENT_METER, /* <meter></meter> */
            ELEMENT_NAV, /* <nav></nav> */
            ELEMENT_NOBREAK, /* <nobr></nobr> */
            ELEMENT_NOBR, /* <nobr></nobr> */
            ELEMENT_NOEMBED, /* <noembed></noembed> */
            ELEMENT_NOSCRIPT, /* <noscript></noscript> */
            ELEMENT_OBJECT, /* <object></object> */
            ELEMENT_OPTGROUP, /* <optgroup></optgroup> */
            ELEMENT_OPTION, /* <option></option> */
            ELEMENT_OUTPUT, /* <output></output> */
            ELEMENT_PARAGRAPH, /* <p></p> */
            ELEMENT_P, /* <p></p> */
            ELEMENT_PARAM, /* <param></param> */
            ELEMENT_PHRASE, /* <pharse></pharse> */
            ELEMENT_PRE, /* <pre></pre> */
            ELEMENT_PROGRESS, /* <progress></progress> */
            ELEMENT_QUOTE, /* <q></q> */
            ELEMENT_Q, /* <q></q> */
            ELEMENT_RP, /* <rp></rp> */
            ELEMENT_RT, /* <rt></rt> */
            ELEMENT_RUBY, /* <ruby></ruby> */
            ELEMENT_OUTDATED, /* <s></s> */
            ELEMENT_S, /* <s></s> */
            ELEMENT_SAMPLE, /* <samp></samp> */
            ELEMENT_SAMP, /* <samp></samp> */
            ELEMENT_SCRIPT, /* <script></script> */
            ELEMENT_SECTION, /* <section></section> */
            ELEMENT_SMALL, /* <small></small> */
            ELEMENT_SOURCE, /* <source></source> */
            ELEMENT_SPACER, /* <spacer></spacer> */
            ELEMENT_SPAN, /* <span></span> */
            ELEMENT_STRIKE, /* <strike></strike> */
            ELEMENT_STRONG, /* <strong></strong> */
            ELEMENT_STYLE, /* <style></style> */
            ELEMENT_SUB, /* <sub></sub> */
            ELEMENT_SUBSCRIPT, /* <sub></sub> */
            ELEMENT_SUP, /* <sup></sup> */
            ELEMENT_SUPERSCRIPT, /* <sup></sup> */
            ELEMENT_SUMMARY, /* <summary></summary> */
            ELEMENT_SVG, /* <svg></svg> */
            ELEMENT_TABLE, /* <table></table> */
            ELEMENT_TBODY, /* <tbody></tbody> */
            ELEMENT_TD, /* <td></td> */
            ELEMENT_TEMPLATE, /* <template></template> */
            ELEMENT_TFOOT, /* <tfoot></tfoot> */
            ELEMENT_TH, /* <th></th> */
            ELEMENT_THEAD, /* <thead></thead> */
            ELEMENT_TIME, /* <time></time> */
            ELEMENT_TITLE, /* <title></title> */
            ELEMENT_TR, /* <tr></tr> */
            ELEMENT_TRACK, /* <track></track> */
            ELEMENT_TT, /* <tt></tt> */
            ELEMENT_UNDERLINE, /* <u></u> */
            ELEMENT_U, /* <u></u> */
            ELEMENT_VAR, /* <var></var> */
            ELEMENT_VIDEO, /* <video></video> */
            ELEMENT_WBR, /* <wbr></wbr> */
            ELEMENT_XMP, /* <xmp></xmp> */
        };

        /**
         * @brief Enum for element types.
         */
        enum Type {
            TYPE_SELF_CLOSING, /* Self-closing element (<tag></tag>)*/
            TYPE_NON_SELF_CLOSING, /* Non-self-closing element (<tag>) */
            TYPE_NON_CLOSED, /* Non-closed element (<tag>) */
            TYPE_TEXT, /* Text element (my text here). Note that this does *not* append a newline character. */
            TYPE_TEXT_TAB, /* Text element with tab characters appropriately prepended (my text here). Note that this does *not* append a newline character. */
        };

        /**
         * @brief Enum for formatting options.
         */
        enum Formatting {
            FORMATTING_NONE, /* No formatting. Output is in the form of one long string of text, and a single newline character. */
            FORMATTING_PRETTY, /* Pretty formatting. Output is formatted with newlines and tabs as deemed appropriate. */
            FORMATTING_NEWLINE, /* Newline formatting. Each element has a newline appended. */
        };

        /**
         * @brief Resolve a tag to a string and type.
         * @param tag The tag to resolve
         * @return std::pair<std::string, Type> The resolved tag
         */
        std::pair<std::string, Type> resolve_tag(const Tag tag);

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
                explicit Property(const std::pair<std::string, std::string>& property) : property(property) {};
                Property() = default;

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
                 */
                Properties() = default;
                Properties operator=(const Properties& properties);
                Properties operator=(const std::vector<Property>& properties);
                Properties operator=(const Property& property);
                void operator+=(const Property& property);
        };

        /**
         * @brief A class to represent an HTML element
         */
        class Element {
            private:
                std::string tag{};
                std::string data{};
                Type type{TYPE_NON_SELF_CLOSING};
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
                Element(const std::string& tag, const Properties& properties = {}, const std::string& data = {}, const Type type = TYPE_NON_SELF_CLOSING) : tag(tag), properties(properties), data(data), type(type) {};
                /**
                 * @brief Construct a new Element object
                 * @param tag The tag of the element
                 * @param properties The properties of the element
                 * @param data The data of the element
                 */
                Element(const Tag tag, const Properties& properties = {}, const std::string& data = {}) : tag(resolve_tag(tag).first), properties(properties), data(data), type(resolve_tag(tag).second) {};
                /**
                 * @brief Construct a new Element object
                 */
                Element() = default;
                /**
                 * @brief Set the tag, properties, and data of the element
                 * @param tag The tag of the element
                 * @param properties The properties of the element
                 * @param data The data of the element
                 * @param type The close tag type.
                 */
                void set(const std::string& tag, const Properties& properties = {}, const std::string& data = {}, const Type type = TYPE_NON_SELF_CLOSING);

                /**
                 * @brief Get the element in the form of an HTML tag.
                 * @return std::string The tag of the element
                 */
                std::string get(const Formatting formatting = FORMATTING_NONE, const int tabc = 0) const;
                /**
                 * @brief Get the element in the form of a specific type.
                 * @return T The element in the form of a specific type
                 */
                template <typename T> T get(const Formatting formatting = FORMATTING_NONE, const int tabc = 0) const {
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

                Element operator=(const Element& element);
                void operator+=(const std::string& data);
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
                void set(const Tag tag, const Properties& properties = {});
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
                std::string get(const Formatting formatting = FORMATTING_NONE, const int tabc = 0) const;
                /**
                 * @brief Get the element in the form of a specific type.
                 * @return T The element in the form of a specific type
                 */
                template <typename T> T get(const Formatting formatting = FORMATTING_NONE, const int tabc = 0) const {
                    if (std::is_same<T, std::string>::value) {
                        return this->get(formatting, tabc);
                    }
                    return T(this->get(formatting, tabc));
                }

                Section operator=(const Section& section);
                void operator+=(const Element& element);
                void operator+=(const Section& section);
                Element operator[](const int& index) const;
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
                std::string get(const Formatting formatting = FORMATTING_NONE, const int tabc = 0) const;
                /**
                 * @brief Get the document in the form of a specific type.
                 * @return T The document in the form of a specific type
                 */
                template <typename T> T get(const Formatting formatting = FORMATTING_NONE, const int tabc = 0) const {
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
                 * @brief Construct a new Document object
                 */
                Document() = default;
                /**
                 * @brief Construct a new Document object
                 * @param document The document to set
                 */
                Document(const Section& document, const std::string& doctype = "<!DOCTYPE html>") : document(document), doctype(doctype) {};

                Document operator=(const Document& document);
                Document operator=(const Section& section);
        };
    } // namespace HTML

    /**
     * @brief A namespace to represent CSS elements and documents
     */
    namespace CSS {
        /**
         * @brief Enum for formatting options.
         */
        enum Formatting {
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
                explicit Property(const std::pair<std::string, std::string>& property) : property(property) {};
                Property() = default;

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
                explicit Element(const std::pair<std::string, std::vector<Property>>& element) : element(element) {};
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
                std::string get(const Formatting formatting = FORMATTING_NONE, const int tabc = 0) const;
                /**
                 * @brief Get the element in the form of a specific type.
                 * @return T The element in the form of a specific type
                 */
                template <typename T> T get(const Formatting formatting = FORMATTING_NONE, const int tabc = 0) const {
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

                Element operator=(const Element& element);
                Element operator=(const std::pair<std::string, std::vector<Property>>& element);
                void operator+=(const Property& property);
                Property operator[](const int& index) const;
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
                std::string get(const Formatting formatting = FORMATTING_NONE, const int tabc = 0) const;
                /**
                 * @brief Get the stylesheet in the form of a specific type.
                 * @return T The stylesheet in the form of a specific type
                 */
                template <typename T> T get(const Formatting formatting = FORMATTING_NONE, const int tabc = 0) const {
                    if (std::is_same<T, std::string>::value) {
                        return this->get(formatting, tabc);
                    }
                    return T(this->get(formatting, tabc));
                }

                Stylesheet operator=(const Stylesheet& stylesheet);
                void operator+=(const Element& element);
                Element operator[](const int& index) const;
        };
    } // namespace CSS
} // namespace docpp
