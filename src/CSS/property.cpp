/*
 * docpp - C++ library for generating HTML, CSS and SGML-like documents.
 *
 * SPDX-License-Identifier: LGPL-3.0-or-later
 * Copyright (c) 2024 speedie <speedie@speedie.site>
 */

#include <docpp/CSS/property.hpp>

docpp::string_type docpp::CSS::Property::get_key() const {
    return this->property.first;
}

docpp::string_type docpp::CSS::Property::get_value() const {
    return this->property.second;
}

std::pair<docpp::string_type, docpp::string_type> docpp::CSS::Property::get() const {
    return this->property;
}

void docpp::CSS::Property::set_key(const docpp::string_type& key) {
    this->property.first = key;
}

void docpp::CSS::Property::set_value(const docpp::string_type& value) {
    this->property.second = value;
}

void docpp::CSS::Property::set(const docpp::string_type& key, const docpp::string_type& value) {
    this->property = std::make_pair(key, value);
}

docpp::CSS::Property& docpp::CSS::Property::operator=(const docpp::CSS::Property& property) {
    this->set(property.get().first, property.get().second);
    return *this;
}

bool docpp::CSS::Property::operator==(const docpp::CSS::Property& property) const {
    return this->get() == property.get();
}

bool docpp::CSS::Property::operator!=(const docpp::CSS::Property& property) const {
    return this->get() != property.get();
}