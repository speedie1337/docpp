/*
 * docpp - C++ library for generating HTML, CSS and SGML-like documents.
 *
 * SPDX-License-Identifier: LGPL-3.0-or-later
 * Copyright (c) 2024 speedie <speedie@speedie.site>
 */

#include <docpp/HTML/property.hpp>

docpp::string_type docpp::HTML::Property::get_key() const {
    return this->property.first;
}

docpp::string_type docpp::HTML::Property::get_value() const {
    return this->property.second;
}

std::pair<docpp::string_type, docpp::string_type> docpp::HTML::Property::get() const {
    return this->property;
}

void docpp::HTML::Property::set_key(const docpp::string_type& key) {
    this->property.first = key;
}

void docpp::HTML::Property::set_value(const docpp::string_type& value) {
    this->property.second = value;
}

void docpp::HTML::Property::set(const std::pair<docpp::string_type, docpp::string_type>& property) {
    this->property = property;
}

docpp::HTML::Property& docpp::HTML::Property::operator=(const docpp::HTML::Property& property) {
    this->set(property.get());
    return *this;
}

bool docpp::HTML::Property::operator==(const docpp::HTML::Property& property) const {
    return this->property == property.get();
}

bool docpp::HTML::Property::operator!=(const docpp::HTML::Property& property) const {
    return this->property != property.get();
}

void docpp::HTML::Property::clear() {
    this->property = {};
}

bool docpp::HTML::Property::empty() const {
    return this->property.first.empty() && this->property.second.empty();
}