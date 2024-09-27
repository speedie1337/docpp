/*
 * docpp - C++ library for generating HTML, CSS and SGML-like documents.
 *
 * SPDX-License-Identifier: LGPL-3.0-or-later
 * Copyright (c) 2024 speedie <speedie@speedie.site>
 */

#include <docpp/HTML/element.hpp>

docpp::HTML::Element& docpp::HTML::Element::operator=(const docpp::HTML::Element& element) {
    this->set(element.get_tag(), element.properties, element.get_data(), element.type);
    return *this;
}

docpp::HTML::Element& docpp::HTML::Element::operator+=(const docpp::string_type& data) {
    this->data += data;
    return *this;
}

bool docpp::HTML::Element::operator==(const docpp::HTML::Element& element) const {
    return this->tag == element.get_tag() && this->properties == element.properties && this->data == element.get_data() && this->type == element.type;
}

bool docpp::HTML::Element::operator!=(const docpp::HTML::Element& element) const {
    return this->tag != element.get_tag() || this->properties != element.properties || this->data != element.get_data() || this->type != element.type;
}

void docpp::HTML::Element::set(const docpp::string_type& tag, const Properties& properties, const docpp::string_type& data, const Type type) {
    this->set_tag(tag);
    this->set_properties(properties);
    this->set_data(data);
    this->set_type(type);
}

void docpp::HTML::Element::set(const Tag tag, const Properties& properties, const docpp::string_type& data) {
    this->set_tag(tag);
    this->set_properties(properties);
    this->set_data(data);
}

void docpp::HTML::Element::set_tag(const docpp::string_type& tag) {
    this->tag = tag;
}

void docpp::HTML::Element::set_tag(const Tag tag) {
    std::pair<docpp::string_type, docpp::HTML::Type> resolved{resolve_tag(tag)};
    this->tag = resolved.first;
    this->type = resolved.second;
}

void docpp::HTML::Element::set_data(const docpp::string_type& data) {
    this->data = data;
}

void docpp::HTML::Element::set_type(const Type type) {
    this->type = type;
}

void docpp::HTML::Element::set_properties(const Properties& properties) {
    this->properties = properties;
}

docpp::string_type docpp::HTML::Element::get(const Formatting formatting, const docpp::integer_type tabc) const {
    docpp::string_type ret{};

    if (this->type == docpp::HTML::Type::Text_No_Formatting) {
        return this->data;
    } else if (this->type == docpp::HTML::Type::Text) {
        for (size_type i{0}; i < tabc; i++) {
            ret += "\t";
        }

        return ret + this->data;
    }

    if (formatting == docpp::HTML::Formatting::Pretty) {
        for (size_type i{0}; i < tabc; i++) {
            ret += "\t";
        }
    }

    if (this->type == docpp::HTML::Type::Non_Opened) {
        ret += "</" + this->tag;
    } else {
        ret += "<" + this->tag;
    }

    for (const Property& it : this->properties.get_properties()) {
        if (it.get_key().empty() || it.get_value().empty()) {
            continue;
        }

        ret += " " + it.get_key() + "=\"" + it.get_value() + "\"";
    }

    if (this->type != docpp::HTML::Type::Self_Closing && this->type != docpp::HTML::Type::Non_Opened) {
        ret += ">";
    }

    if (this->type == docpp::HTML::Type::Non_Self_Closing) {
        ret += this->data + "</" + this->tag + ">";
    } else if (this->type == docpp::HTML::Type::Self_Closing) {
        ret += this->data + "/>";
    } else if (this->type == docpp::HTML::Type::Non_Opened) {
        ret += ">";
    }

    if (formatting == docpp::HTML::Formatting::Pretty || formatting == docpp::HTML::Formatting::Newline) {
        ret += "\n";
    }

    return ret;
}

docpp::string_type docpp::HTML::Element::get_tag() const {
    return this->tag;
}

docpp::string_type docpp::HTML::Element::get_data() const {
    return this->data;
}

docpp::HTML::Type docpp::HTML::Element::get_type() const {
    return this->type;
}

docpp::HTML::Properties docpp::HTML::Element::get_properties() const {
    return this->properties;
}

bool docpp::HTML::Element::empty() const {
    return this->tag.empty() && this->data.empty() && this->properties.empty();
}

void docpp::HTML::Element::clear() {
    this->tag.clear();
    this->data.clear();
    this->properties.clear();
}