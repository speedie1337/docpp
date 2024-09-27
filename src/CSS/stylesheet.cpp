/*
 * docpp - C++ library for generating HTML, CSS and SGML-like documents.
 *
 * SPDX-License-Identifier: LGPL-3.0-or-later
 * Copyright (c) 2024 speedie <speedie@speedie.site>
 */

#include <docpp/except.hpp>
#include <docpp/CSS/stylesheet.hpp>

void docpp::CSS::Stylesheet::set(const std::vector<Element>& elements) {
    this->elements = elements;
}

void docpp::CSS::Stylesheet::push_front(const Element& element) {
    this->elements.insert(this->elements.begin(), element);
}

void docpp::CSS::Stylesheet::push_back(const Element& element) {
    this->elements.push_back(element);
}

void docpp::CSS::Stylesheet::insert(const size_type index, const Element& element) {
    if (index >= this->elements.size()) {
        throw docpp::out_of_range("Index out of range");
    }

    this->elements.insert(this->elements.begin() + static_cast<long>(index), element);
}

void docpp::CSS::Stylesheet::erase(const size_type index) {
    if (index >= this->elements.size()) {
        throw docpp::out_of_range("Index out of range");
    }

    this->elements.erase(this->elements.begin() + static_cast<long>(index));
}

docpp::CSS::Stylesheet& docpp::CSS::Stylesheet::operator=(const docpp::CSS::Stylesheet& stylesheet) {
    this->set(stylesheet.get_elements());
    return *this;
}

docpp::CSS::Stylesheet& docpp::CSS::Stylesheet::operator+=(const Element& element) {
    this->push_back(element);
    return *this;
}

docpp::CSS::Element docpp::CSS::Stylesheet::operator[](const docpp::integer_type& index) const {
    return this->at(index);
}

bool docpp::CSS::Stylesheet::operator==(const docpp::CSS::Stylesheet& stylesheet) const {
    return this->get_elements() == stylesheet.get_elements();
}

bool docpp::CSS::Stylesheet::operator!=(const docpp::CSS::Stylesheet& stylesheet) const {
    return this->get_elements() != stylesheet.get_elements();
}

docpp::CSS::Element docpp::CSS::Stylesheet::at(const size_type index) const {
    if (index >= this->elements.size()) {
        throw docpp::out_of_range("Index out of range");
    }

    return this->elements.at(index);
}

docpp::size_type docpp::CSS::Stylesheet::find(const Element& element) const {
    for (size_type i{0}; i < this->elements.size(); i++) {
        if (this->elements.at(i).get() == element.get()) {
            return i;
        }
    }

    return docpp::CSS::Stylesheet::npos;
}

docpp::size_type docpp::CSS::Stylesheet::find(const docpp::string_type& str) const {
    for (size_type i{0}; i < this->elements.size(); i++) {
        if (this->elements.at(i).get() == str || this->elements.at(i).get_tag() == str) {
            return i;
        }
    }

    return docpp::CSS::Stylesheet::npos;
}

docpp::size_type docpp::CSS::Stylesheet::size() const {
    return this->elements.size();
}

bool docpp::CSS::Stylesheet::empty() const {
    return this->elements.empty();
}

void docpp::CSS::Stylesheet::clear() {
    this->elements.clear();
}

docpp::CSS::Element docpp::CSS::Stylesheet::front() const {
    return this->elements.front();
}

docpp::CSS::Element docpp::CSS::Stylesheet::back() const {
    return this->elements.back();
}

void docpp::CSS::Stylesheet::swap(const size_type index1, const size_type index2) {
    if (index1 >= this->elements.size() || index2 >= this->elements.size()) {
        throw docpp::out_of_range("Index out of range");
    }

    std::swap(this->elements[index1], this->elements[index2]);
}

void docpp::CSS::Stylesheet::swap(const Element& element1, const Element& element2) {
    this->swap(this->find(element1), this->find(element2));
}

std::vector<docpp::CSS::Element> docpp::CSS::Stylesheet::get_elements() const {
    return this->elements;
}

docpp::string_type docpp::CSS::Stylesheet::get(const Formatting formatting, const docpp::integer_type tabc) const {
    docpp::string_type ret{};

    for (const Element& it : this->elements) {
        ret += it.get(formatting, tabc);
    }

    return ret;
}