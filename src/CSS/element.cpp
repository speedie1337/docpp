/*
 * docpp - C++ library for generating HTML, CSS and SGML-like documents.
 *
 * SPDX-License-Identifier: LGPL-3.0-or-later
 * Copyright (c) 2024 speedie <speedie@speedie.site>
 */

#include <docpp/except.hpp>
#include <docpp/CSS/element.hpp>

docpp::CSS::Element& docpp::CSS::Element::operator=(const docpp::CSS::Element& element) {
    this->set(element.get_tag(), element.get_properties());
    return *this;
}

docpp::CSS::Element& docpp::CSS::Element::operator+=(const Property& property) {
    this->push_back(property);
    return *this;
}

docpp::CSS::Property docpp::CSS::Element::operator[](const size_type& index) const {
    return this->at(index);
}

bool docpp::CSS::Element::operator==(const docpp::CSS::Element& element) const {
    return this->get() == element.get();
}

bool docpp::CSS::Element::operator!=(const docpp::CSS::Element& element) const {
    return this->get() != element.get();
}

void docpp::CSS::Element::set(const docpp::string_type& tag, const std::vector<Property>& properties) {
    this->element.first = tag;
    this->element.second = properties;
}

void docpp::CSS::Element::set_tag(const docpp::string_type& tag) {
    this->element.first = tag;
}

void docpp::CSS::Element::set_tag(const HTML::Tag tag) {
    this->element.first = resolve_tag(tag).first;
}

void docpp::CSS::Element::set_properties(const std::vector<Property>& properties) {
    this->element.second = properties;
}

void docpp::CSS::Element::push_front(const Property& property) {
    this->element.second.insert(this->element.second.begin(), property);
}

void docpp::CSS::Element::push_back(const Property& property) {
    this->element.second.push_back(property);
}

void docpp::CSS::Element::insert(const size_type index, const Property& property) {
    if (index >= this->element.second.size()) {
        throw docpp::out_of_range("Index out of range");
    }

    this->element.second.insert(this->element.second.begin() + static_cast<long>(index), property);
}

void docpp::CSS::Element::erase(const size_type index) {
    if (index >= this->element.second.size()) {
        throw docpp::out_of_range("Index out of range");
    }

    this->element.second.erase(this->element.second.begin() + static_cast<long>(index));
}

docpp::CSS::Property docpp::CSS::Element::at(const size_type index) const {
    if (index >= this->element.second.size()) {
        throw docpp::out_of_range("Index out of range");
    }

    return this->element.second.at(index);
}

docpp::CSS::Property& docpp::CSS::Element::at(const size_type index) {
    if (index >= this->element.second.size()) {
        throw docpp::out_of_range("Index out of range");
    }

    return this->element.second.at(index);
}

docpp::size_type docpp::CSS::Element::find(const Property& property) const {
    for (size_type i{0}; i < this->element.second.size(); i++) {
        if (this->element.second.at(i).get() == property.get()) {
            return i;
        }
    }

    return docpp::CSS::Element::npos;
}

docpp::size_type docpp::CSS::Element::find(const docpp::string_type& str) const {
    for (size_type i{0}; i < this->element.second.size(); i++) {
        if (this->element.second.at(i).get_key() == str || this->element.second.at(i).get_value() == str) {
            return i;
        }
    }

    return docpp::CSS::Element::npos;
}

docpp::CSS::Property docpp::CSS::Element::front() const {
    return this->element.second.front();
}

docpp::CSS::Property docpp::CSS::Element::back() const {
    return this->element.second.back();
}

docpp::CSS::Property& docpp::CSS::Element::front() {
    return this->element.second.front();
}

docpp::CSS::Property& docpp::CSS::Element::back() {
    return this->element.second.back();
}

docpp::size_type docpp::CSS::Element::size() const {
    return this->element.second.size();
}

bool docpp::CSS::Element::empty() const {
    return this->element.second.empty();
}

void docpp::CSS::Element::clear() {
    this->element.first.clear();
    this->element.second.clear();
}

void docpp::CSS::Element::swap(const size_type index1, const size_type index2) {
    if (index1 >= this->element.second.size() || index2 >= this->element.second.size()) {
        throw docpp::out_of_range("Index out of range");
    }

    std::swap(this->element.second[index1], this->element.second[index2]);
}

void docpp::CSS::Element::swap(const Property& property1, const Property& property2) {
    this->swap(this->find(property1), this->find(property2));
}

docpp::string_type docpp::CSS::Element::get(const Formatting formatting, const docpp::integer_type tabc) const {
    docpp::string_type ret{};

    if (!this->element.first.empty()) {
        if (formatting == docpp::CSS::Formatting::Pretty) {
            for (size_type i{0}; i < tabc; i++) {
                ret += "\t";
            }
        }

        ret += this->element.first + " {";

        if (formatting == docpp::CSS::Formatting::Pretty || formatting == docpp::CSS::Formatting::Newline) {
            ret += "\n";
        }

        for (const Property& it : this->element.second) {
            if (it.get_key().empty() || it.get_value().empty()) {
                continue;
            }

            if (formatting == docpp::CSS::Formatting::Pretty) {
                for (size_type i{0}; i < tabc + 1; i++) {
                    ret += "\t";
                }
            }

            ret += it.get_key() + ": " + it.get_value() + ";";

            if (formatting == docpp::CSS::Formatting::Pretty || formatting == docpp::CSS::Formatting::Newline) {
                ret += "\n";
            }
        }

        if (formatting == docpp::CSS::Formatting::Pretty) {
            for (size_type i{0}; i < tabc; i++) {
                ret += "\t";
            }
        }

        ret += "}";

        if (formatting == docpp::CSS::Formatting::Pretty || formatting == docpp::CSS::Formatting::Newline) {
            ret += "\n";
        }
    }

    return ret;
}

docpp::string_type docpp::CSS::Element::get_tag() const {
    return this->element.first;
}

std::vector<docpp::CSS::Property> docpp::CSS::Element::get_properties() const {
    return this->element.second;
}