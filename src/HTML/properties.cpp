/*
 * docpp - C++ library for generating HTML, CSS and SGML-like documents.
 *
 * SPDX-License-Identifier: LGPL-3.0-or-later
 * Copyright (c) 2024 speedie <speedie@speedie.site>
 */

#include <algorithm>
#include <docpp/except.hpp>
#include <docpp/HTML/properties.hpp>

docpp::HTML::Properties& docpp::HTML::Properties::operator=(const docpp::HTML::Property& property) {
    this->properties = {property};
    return *this;
}

docpp::HTML::Properties& docpp::HTML::Properties::operator=(const docpp::HTML::Properties& properties) {
    this->set(properties.get_properties());
    return *this;
}

docpp::HTML::Properties& docpp::HTML::Properties::operator=(const std::vector<docpp::HTML::Property>& properties) {
    this->set(properties);
    return *this;
}

docpp::HTML::Property docpp::HTML::Properties::operator[](const size_type& index) const {
    return this->at(index);
}

bool docpp::HTML::Properties::operator==(const docpp::HTML::Properties& properties) const {
    return this->properties == properties.get_properties();
}

bool docpp::HTML::Properties::operator==(const docpp::HTML::Property& property) const {
    return std::any_of(this->properties.begin(), this->properties.end(),
                   [&property](const docpp::HTML::Property& it) {
                       return it.get() == property.get();
                   });
}

bool docpp::HTML::Properties::operator!=(const docpp::HTML::Properties& properties) const {
    return this->properties != properties.get_properties();
}

bool docpp::HTML::Properties::operator!=(const docpp::HTML::Property& property) const {
    return std::all_of(this->properties.begin(), this->properties.end(), [&property](const docpp::HTML::Property& it) {
        return it.get() == property.get();
        });
}

docpp::HTML::Properties& docpp::HTML::Properties::operator+=(const docpp::HTML::Property& property) {
    this->push_back(property);
    return *this;
}

docpp::HTML::Properties& docpp::HTML::Properties::operator+=(const docpp::HTML::Properties& properties) {
    for (const docpp::HTML::Property& it : properties) {
        this->push_back(it);
    }

    return *this;
}

std::vector<docpp::HTML::Property> docpp::HTML::Properties::get_properties() const {
    return this->properties;
}

docpp::HTML::Property docpp::HTML::Properties::at(const size_type index) const {
    if (index >= this->properties.size()) {
        throw docpp::out_of_range("Index out of range");
    }

    return this->properties.at(index);
}

void docpp::HTML::Properties::set(const std::vector<docpp::HTML::Property>& properties) {
    this->properties = properties;
}

void docpp::HTML::Properties::insert(const size_type index, const docpp::HTML::Property& property) {
    if (index >= this->properties.size()) {
        throw docpp::out_of_range("Index out of range");
    }

    this->properties.insert(this->properties.begin() + static_cast<long>(index), property);
}

void docpp::HTML::Properties::erase(const size_type index) {
    if (index >= this->properties.size()) {
        throw docpp::out_of_range("Index out of range");
    }

    this->properties.erase(this->properties.begin() + static_cast<long>(index));
}

void docpp::HTML::Properties::push_front(const docpp::HTML::Property& property) {
    this->properties.insert(this->properties.begin(), property);
}

void docpp::HTML::Properties::push_back(const docpp::HTML::Property& property) {
    this->properties.push_back(property);
}

docpp::size_type docpp::HTML::Properties::find(const docpp::HTML::Property& property) const {
    for (size_type i{0}; i < this->properties.size(); i++) {
        if (this->properties.at(i).get_value().find(property.get_value()) != docpp::string_type::npos
            || this->properties.at(i).get_key().find(property.get_key()) != docpp::string_type::npos) {
            return i;
        }
    }

    return docpp::HTML::Properties::npos;
}

docpp::size_type docpp::HTML::Properties::find(const docpp::string_type& str) const {
    for (size_type i{0}; i < this->properties.size(); i++) {
        if (this->properties.at(i).get_key().find(str) != docpp::string_type::npos ||
            this->properties.at(i).get_value().find(str) != docpp::string_type::npos) {
            return i;
        }
    }

    return docpp::HTML::Properties::npos;
}

docpp::HTML::Property docpp::HTML::Properties::front() const {
    return this->properties.front();
}

docpp::HTML::Property docpp::HTML::Properties::back() const {
    return this->properties.back();
}

docpp::size_type docpp::HTML::Properties::size() const {
    return this->properties.size();
}

void docpp::HTML::Properties::clear() {
    this->properties.clear();
}

bool docpp::HTML::Properties::empty() const {
    return this->properties.empty();
}

void docpp::HTML::Properties::swap(const size_type index1, const size_type index2) {
    if (index1 >= this->properties.size() || index2 >= this->properties.size()) {
        throw docpp::out_of_range("Index out of range");
    }

    std::swap(this->properties[index1], this->properties[index2]);
}

void docpp::HTML::Properties::swap(const docpp::HTML::Property& property1, const docpp::HTML::Property& property2) {
    this->swap(this->find(property1), this->find(property2));
}