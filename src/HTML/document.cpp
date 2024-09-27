/*
 * docpp - C++ library for generating HTML, CSS and SGML-like documents.
 *
 * SPDX-License-Identifier: LGPL-3.0-or-later
 * Copyright (c) 2024 speedie <speedie@speedie.site>
 */

#include <docpp/HTML/section.hpp>
#include <docpp/HTML/document.hpp>

docpp::string_type docpp::HTML::Document::get(const Formatting formatting, const docpp::integer_type tabc) const {
    return this->doctype + (formatting == Formatting::Pretty ? "\n" : formatting == Formatting::Newline ? "\n" : "") + this->document.get(formatting, tabc);
}

docpp::HTML::Section docpp::HTML::Document::get_section() const {
    return this->document;
}

docpp::HTML::Section& docpp::HTML::Document::get_section() {
    return this->document;
}

void docpp::HTML::Document::set(const docpp::HTML::Section& document) {
    this->document = document;
}

docpp::size_type docpp::HTML::Document::size() const {
    return this->document.size();
}

void docpp::HTML::Document::set_doctype(const docpp::string_type& doctype) {
    this->doctype = doctype;
}

void docpp::HTML::Document::clear() {
    this->doctype.clear();
    this->document.clear();
}

bool docpp::HTML::Document::empty() const {
    return this->doctype.empty() && this->document.empty();
}

docpp::HTML::Document& docpp::HTML::Document::operator=(const docpp::HTML::Document& document) {
    this->set(document.get_section());
    this->set_doctype(document.get_doctype());
    return *this;
}

docpp::HTML::Document& docpp::HTML::Document::operator=(const docpp::HTML::Section& section) {
    this->set(section);
    return *this;
}

bool docpp::HTML::Document::operator==(const docpp::HTML::Document& document) const {
    return this->get() == document.get();
}

bool docpp::HTML::Document::operator==(const docpp::HTML::Section& section) const {
    return this->document == section;
}

bool docpp::HTML::Document::operator!=(const docpp::HTML::Document& document) const {
    return this->doctype != document.get_doctype() || this->document != document.document;
}

bool docpp::HTML::Document::operator!=(const docpp::HTML::Section& section) const {
    return this->document != section;
}

docpp::string_type docpp::HTML::Document::get_doctype() const {
    return this->doctype;
}