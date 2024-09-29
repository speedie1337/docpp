/*
 * docpp - C++ library for generating HTML, CSS and SGML-like documents.
 *
 * SPDX-License-Identifier: LGPL-3.0-or-later
 * Copyright (c) 2024 speedie <speedie@speedie.site>
 */

#include <algorithm>
#include <sstream>
#include <stack>
#include <docpp/except.hpp>
#include <docpp/HTML/tag.hpp>
#include <docpp/HTML/section.hpp>

docpp::HTML::Section& docpp::HTML::Section::operator=(const docpp::HTML::Section& section) = default;

docpp::HTML::Section& docpp::HTML::Section::operator+=(const docpp::HTML::Element& element) {
    this->push_back(element);
    return *this;
}

docpp::HTML::Section& docpp::HTML::Section::operator+=(const docpp::HTML::Section& section) {
    this->push_back(section);
    return *this;
}

docpp::HTML::Element docpp::HTML::Section::operator[](const docpp::integer_type& index) const {
    return this->at(index);
}

std::unordered_map<docpp::string_type, docpp::HTML::Element> docpp::HTML::Section::operator[](const docpp::string_type& tag) const {
    std::unordered_map<docpp::string_type, docpp::HTML::Element> ret{};

    for (const Element& it : this->get_elements()) {
        if (it.get_tag() == tag) {
            ret[it.get_data()] = it;
        }
    }

    return ret;
}

std::unordered_map<docpp::string_type, docpp::HTML::Element> docpp::HTML::Section::operator[](const Tag tag) const {
    std::unordered_map<docpp::string_type, docpp::HTML::Element> ret{};

    for (const Element& it : this->get_elements()) {
        if (it.get_tag() == resolve_tag(tag).first) {
            ret[it.get_data()] = it;
        }
    }

    return ret;
}

bool docpp::HTML::Section::operator==(const docpp::HTML::Section& section) const {
    return this->tag == section.tag && this->properties == section.properties && this->elements == section.elements && this->sections == section.sections && this->index == section.index;
}

bool docpp::HTML::Section::operator==(const docpp::HTML::Element& element) const {
    return std::any_of(this->get_elements().begin(), this->get_elements().end(),
                   [&element](const docpp::HTML::Element& it) {
                       return it.get() == element.get();
                   });
}

bool docpp::HTML::Section::operator!=(const docpp::HTML::Section& section) const {
    return this->tag != section.tag || this->properties != section.properties || this->elements != section.elements || this->sections != section.sections || this->index != section.index;
}

bool docpp::HTML::Section::operator!=(const docpp::HTML::Element& element) const {
    return std::any_of(this->get_elements().begin(), this->get_elements().end(), [&element](const Element& it) {
        return it.get() == element.get();
    });
}

void docpp::HTML::Section::set(const docpp::string_type& tag, const Properties& properties) {
    this->tag = tag;
    this->properties = properties;
}

void docpp::HTML::Section::set_tag(const docpp::string_type& tag) {
    this->tag = tag;
}

void docpp::HTML::Section::set_tag(const Tag tag) {
    std::pair<docpp::string_type, docpp::HTML::Type> resolved{resolve_tag(tag)};
    this->tag = resolved.first;
}

void docpp::HTML::Section::set_properties(const Properties& properties) {
    this->properties = properties;
}

void docpp::HTML::Section::set(const Tag tag, const Properties& properties) {
    this->tag = resolve_tag(tag).first;
    this->properties = properties;
}

void docpp::HTML::Section::push_front(const Element& element) {
    for (size_type i{this->index}; i > 0; i--) {
        this->elements[i] = this->elements.at(i - 1);
    }

    this->elements[0] = element;
    this->index++;
}

void docpp::HTML::Section::push_front(const Section& section) {
    for (size_type i{this->index}; i > 0; i--) {
        this->sections.at(i) = this->sections.at(i - 1);
    }

    this->sections[0] = section;
    this->index++;
}

void docpp::HTML::Section::push_back(const Element& element) {
    this->elements[this->index++] = element;
}

void docpp::HTML::Section::push_back(const Section& section) {
    this->sections[this->index++] = section;
}

void docpp::HTML::Section::erase(const size_type index) {
    bool erased{false};

    if (this->elements.find(index) != this->elements.end()) {
        this->elements.erase(index);
        erased = true;
    } else if (this->sections.find(index) != this->sections.end()) {
        this->sections.erase(index);
        erased = true;
    }

    if (!erased) {
        throw docpp::out_of_range("Index out of range");
    }
}

void docpp::HTML::Section::erase(const Section& section) {
    for (size_type i{0}; i < this->size(); i++) {
        const Section it = this->get_sections().at(i);

        if (it.get() == section.get()) {
            this->erase(i);
            return;
        }
    }

    throw docpp::out_of_range("Section not found");
}

void docpp::HTML::Section::erase(const Element& element) {
    for (size_type i{0}; i < this->size(); i++) {
        const Element it = this->get_elements().at(i);

        if (it.get() == element.get()) {
            this->erase(i);
            return;
        }
    }

    throw docpp::out_of_range("Element not found");
}

void docpp::HTML::Section::insert(const size_type index, const Element& element) {
    if (this->sections.find(index) != this->sections.end()) {
        throw docpp::invalid_argument("Index already occupied by a section");
    } else {
        this->elements[index] = element;
    }

    this->index = std::max(this->index, index) + 1;
}

void docpp::HTML::Section::insert(const size_type index, const Section& section) {
    this->sections[index] = section;
    this->index = std::max(this->index, index) + 1;
}

docpp::HTML::Element docpp::HTML::Section::at(const size_type index) const {
    if (this->elements.find(index) != this->elements.end()) {
        return this->elements.at(index);
    }

    throw docpp::out_of_range("Index out of range");
}

docpp::HTML::Element& docpp::HTML::Section::at(const size_type index) {
    if (this->elements.find(index) != this->elements.end()) {
        return this->elements.at(index);
    }

    throw docpp::out_of_range("Index out of range");
}

docpp::HTML::Section docpp::HTML::Section::at_section(const size_type index) const {
    if (this->sections.find(index) != this->sections.end()) {
        return this->sections.at(index);
    }

    throw docpp::out_of_range("Index out of range");
}

docpp::HTML::Section& docpp::HTML::Section::at_section(const size_type index) {
    if (this->sections.find(index) != this->sections.end()) {
        return this->sections.at(index);
    }

    throw docpp::out_of_range("Index out of range");
}

docpp::size_type docpp::HTML::Section::find(const Element& element) const {
    for (size_type i{0}; i < this->size(); i++) {
        const Element it = this->get_elements().at(i);

        if (it.get() == element.get()) {
            return i;
        }
    }

    return docpp::HTML::Section::npos;
}

docpp::size_type docpp::HTML::Section::find(const Section& section) const {
    for (size_type i{0}; i < this->size(); i++) {
        const Section it = this->get_sections().at(i);

        if (it.get() == section.get()) {
            return i;
        }
    }

    return docpp::HTML::Section::npos;
}

docpp::size_type docpp::HTML::Section::find(const docpp::string_type& str) const {
    const std::vector<docpp::HTML::Element> elements{this->get_elements()};

    for (size_type i{0}; i < this->size(); i++) {
        if (elements.size() <= i) {
            break;
        }

        if (elements.at(i).get().find(str) != docpp::HTML::Section::npos) {
            return i;
        }
    }

    const std::vector<docpp::HTML::Section> sections{this->get_sections()};

    for (size_type i{0}; i < this->size(); i++) {
        if (elements.size() <= i) {
            break;
        }

        if (elements.at(i).get().find(str) != docpp::HTML::Section::npos) {
            return i;
        }
    }

    return docpp::HTML::Section::npos;
}

docpp::HTML::Element docpp::HTML::Section::front() const {
    if (this->elements.find(0) != this->elements.end()) {
        return this->elements.at(0);
    }

    throw docpp::out_of_range("Index out of range");
}

docpp::HTML::Element& docpp::HTML::Section::front() {
    if (this->elements.find(0) != this->elements.end()) {
        return this->elements.at(0);
    }

    throw docpp::out_of_range("Index out of range");
}

docpp::HTML::Section docpp::HTML::Section::front_section() const {
    if (this->sections.find(0) != this->sections.end()) {
        return this->sections.at(0);
    }

    throw docpp::out_of_range("Index out of range");
}

docpp::HTML::Section& docpp::HTML::Section::front_section() {
    if (this->sections.find(0) != this->sections.end()) {
        return this->sections.at(0);
    }

    throw docpp::out_of_range("Index out of range");
}

docpp::HTML::Element docpp::HTML::Section::back() const {
    if (this->elements.find(this->index - 1) != this->elements.end()) {
        return this->elements.at(this->index - 1);
    }

    throw docpp::out_of_range("Index out of range");
}

docpp::HTML::Element& docpp::HTML::Section::back() {
    if (this->elements.find(this->index - 1) != this->elements.end()) {
        return this->elements.at(this->index - 1);
    }

    throw docpp::out_of_range("Index out of range");
}

docpp::HTML::Section docpp::HTML::Section::back_section() const {
    if (this->sections.find(this->index - 1) != this->sections.end()) {
        return this->sections.at(this->index - 1);
    }

    throw docpp::out_of_range("Index out of range");
}

docpp::HTML::Section& docpp::HTML::Section::back_section() {
    if (this->sections.find(this->index - 1) != this->sections.end()) {
        return this->sections.at(this->index - 1);
    }

    throw docpp::out_of_range("Index out of range");
}

docpp::size_type docpp::HTML::Section::size() const {
    return this->index;
}

void docpp::HTML::Section::clear() {
    this->tag.clear();
    this->properties.clear();
    this->elements.clear();
    this->sections.clear();
    this->index = 0;
}

bool docpp::HTML::Section::empty() const {
    return this->index == 0;
}

std::vector<docpp::HTML::Element> docpp::HTML::Section::get_elements() const {
    std::vector<docpp::HTML::Element> ret{};
    ret.reserve(this->index);
    for (size_type i{0}; i < this->index; i++) {
        if (this->elements.find(i) != this->elements.end()) {
            ret.push_back(this->elements.at(i));
        }
    }
    return ret;
}

std::vector<docpp::HTML::Section> docpp::HTML::Section::get_sections() const {
    std::vector<docpp::HTML::Section> ret{};
    ret.reserve(this->index);

    for (size_type i{0}; i < this->index; i++) {
        if (this->sections.find(i) != this->sections.end()) {
            ret.push_back(this->sections.at(i));
        }
    }

    return ret;
}

/*
docpp::string_type docpp::HTML::Section::get(const Formatting formatting, const docpp::integer_type tabc) const { // NOLINT
    std::ostringstream ret{};
    docpp::integer_type tabcount{tabc};

    if (this->tag.empty() && this->properties.empty() && this->sections.empty() && this->elements.empty()) {
        return {};
    }

    if (this->tag.empty() && tabcount-1 >= -1) {
        --tabcount; // prevent an indent when there's no tag for the section itself (i.e. the section is only a container)
    }

    if (formatting == docpp::HTML::Formatting::Pretty) {
        for (size_type i{0}; i < tabcount; i++) ret << "\t";
    }
    if (!this->tag.empty()) {
        ret << "<" + this->tag;

        for (const Property& it : this->properties.get_properties()) {
            if (it.get_key().empty() || it.get_value().empty()) {
                continue;
            }
            ret << " " + it.get_key() + "=\"" + it.get_value() + "\"";
        }

        ret << ">";

        if (formatting == docpp::HTML::Formatting::Pretty || formatting == docpp::HTML::Formatting::Newline) {
            ret << "\n";
        }
    }

    for (size_type i{0}; i < this->index; i++) {
        if (this->elements.find(i) != this->elements.end()) {
            ret << this->elements.at(i).get(formatting, tabcount + 1);
        } else if (this->sections.find(i) != this->sections.end()) {
            const Section* sect_ptr = &this->sections.at(i);

            if (this == sect_ptr) {
                throw docpp::invalid_argument{"get() cannot be called on this"};
            }

            ret << sect_ptr->get(formatting, tabcount + 1);

            if (formatting == docpp::HTML::Formatting::Pretty || formatting == docpp::HTML::Formatting::Newline) {
                ret << "\n";
            }
        }
    }

    if (formatting == docpp::HTML::Formatting::Pretty) {
        for (size_type i{0}; i < tabcount; i++) {
            ret << "\t";
        }
    }

    if (this->tag.empty() == false) {
        ret << "</" << this->tag << ">";
    }

    return ret.str();
}
*/

docpp::string_type docpp::HTML::Section::get(const Formatting formatting, const docpp::integer_type tabc) const {
    std::ostringstream ret{};

    struct Entry {
        const Section* section{nullptr};
        docpp::integer_type tabc{tabc};
        bool processing{false};
    };

    std::stack<Entry> s_stack{};
    s_stack.push({this, tabc, false});

    while (!s_stack.empty()) {
        Entry& c_entry{s_stack.top()};
        const Section* c_sect{c_entry.section};
        docpp::integer_type c_tabc{c_entry.tabc};

        if (!c_entry.processing) {
            if (c_sect->tag.empty() && c_sect->properties.empty() && c_sect->sections.empty() && c_sect->elements.empty()) {
                s_stack.pop();
                continue;
            }

            if (formatting == docpp::HTML::Formatting::Pretty) {
                for (size_type i{0}; i < c_tabc; i++) {
                    ret << "\t";
                }
            }

            if (!c_sect->tag.empty()) {
                ret << "<" + c_sect->tag;

                for (const Property& it : c_sect->properties.get_properties()) {
                    if (it.get_key().empty() || it.get_value().empty()) {
                        continue;
                    }

                    ret << " " + it.get_key() + "=\"" + it.get_value() + "\"";
                }

                ret << ">";

                if (formatting == docpp::HTML::Formatting::Pretty || formatting == docpp::HTML::Formatting::Newline) {
                    ret << "\n";
                }
            } else { // if Section is just a container, we don't need to indent
                --c_tabc;
            }

            c_entry.processing = true;

            for (size_type i = 0; i < c_sect->index; i++) {
                if (c_sect->sections.find(i) != c_sect->sections.end()) {
                    s_stack.push({&c_sect->sections.at(i), c_tabc + 1, false});
                } else if (c_sect->elements.find(i) != c_sect->elements.end()) {
                    ret << c_sect->elements.at(i).get(formatting, c_tabc + 1);
                }
            }
        } else {
            if (!c_sect->tag.empty()) {
                if (formatting == docpp::HTML::Formatting::Pretty) {
                    for (size_type i{0}; i < c_tabc; i++) {
                        ret << "\t";
                    }
                }
                ret << "</" + c_sect->tag + ">";
            }

            s_stack.pop();
        }
    }

    return ret.str();
}

docpp::string_type docpp::HTML::Section::get_tag() const {
    return this->tag;
}

docpp::HTML::Properties docpp::HTML::Section::get_properties() const {
    return this->properties;
}

void docpp::HTML::Section::swap(const size_type index1, const size_type index2) {
    if (this->elements.find(index1) != this->elements.end() && this->elements.find(index2) != this->elements.end()) {
        std::swap(this->elements[index1], this->elements[index2]);
    } else if (this->sections.find(index1) != this->sections.end() && this->sections.find(index2) != this->sections.end()) {
        std::swap(this->sections[index1], this->sections[index2]);
    } else {
        throw docpp::out_of_range("Index out of range");
    }
}

void docpp::HTML::Section::swap(const Element& element1, const Element& element2) {
    this->swap(this->find(element1), this->find(element2));
}

void docpp::HTML::Section::swap(const Section& section1, const Section& section2) {
    this->swap(this->find(section1), this->find(section2));
}