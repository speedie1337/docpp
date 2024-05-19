/*
 * docpp - C++ library for generating HTML, CSS and SGML-like documents.
 *
 * SPDX-License-Identifier: LGPL-3.0-or-later
 * Copyright (c) 2024 speedie <speedie@speedie.site>
 */

#include <include/docpp.hpp>
#include <string>
#include <unordered_map>
#include <vector>

std::string docpp::HTML::Property::get_key() const {
    return this->property.first;
}

std::string docpp::HTML::Property::get_value() const {
    return this->property.second;
}

std::pair<std::string, std::string> docpp::HTML::Property::get() const {
    return this->property;
}

void docpp::HTML::Property::set_key(const std::string& key) {
    this->property.first = key;
}

void docpp::HTML::Property::set_value(const std::string& value) {
    this->property.second = value;
}

void docpp::HTML::Property::set(const std::pair<std::string, std::string>& property) {
    this->property = property;
}

docpp::HTML::Property& docpp::HTML::Property::operator=(const docpp::HTML::Property& property) {
    this->set(property.get());
    return *this;
}

docpp::HTML::Property& docpp::HTML::Property::operator=(const std::pair<std::string, std::string>& property) {
    this->set(property);
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
    for (const docpp::HTML::Property& it : this->properties) {
        if (it.get() == property.get()) {
            return true;
        }
    }

    return false;
}

bool docpp::HTML::Properties::operator!=(const docpp::HTML::Properties& properties) const {
    return this->properties != properties.get_properties();
}

bool docpp::HTML::Properties::operator!=(const docpp::HTML::Property& property) const {
    for (const docpp::HTML::Property& it : this->properties) {
        if (it.get() == property.get()) {
            return false;
        }
    }

    return true;
}

docpp::HTML::Properties& docpp::HTML::Properties::operator+=(const docpp::HTML::Property& property) {
    this->push_back(property);
    return *this;
}

docpp::HTML::Properties& docpp::HTML::Properties::operator+=(const docpp::HTML::Properties& properties) {
    for (docpp::HTML::Properties::const_iterator it{properties.cbegin()}; it != properties.cend(); it++) {
        this->push_back(*it);
    }

    return *this;
}

std::vector<docpp::HTML::Property> docpp::HTML::Properties::get_properties() const {
    return this->properties;
}

docpp::HTML::Property docpp::HTML::Properties::at(const size_type index) const {
    if (index < 0 || index >= this->properties.size()) {
        throw docpp::out_of_range("Index out of range");
    }

    return this->properties.at(index);
}

void docpp::HTML::Properties::set(const std::vector<docpp::HTML::Property>& properties) {
    this->properties = properties;
}

void docpp::HTML::Properties::insert(const size_type index, const docpp::HTML::Property& property) {
    if (index < 0 || index >= this->properties.size()) {
        throw docpp::out_of_range("Index out of range");
    }

    this->properties.insert(this->properties.begin() + index, property);
}

void docpp::HTML::Properties::erase(const size_type index) {
    if (index < 0 || index >= this->properties.size()) {
        throw docpp::out_of_range("Index out of range");
    }

    this->properties.erase(this->properties.begin() + index);
}

void docpp::HTML::Properties::push_front(const docpp::HTML::Property& property) {
    this->properties.insert(this->properties.begin(), property);
}

void docpp::HTML::Properties::push_back(const docpp::HTML::Property& property) {
    this->properties.push_back(property);
}

docpp::HTML::Properties::size_type docpp::HTML::Properties::find(const docpp::HTML::Property& property) {
    for (size_type i{0}; i < this->properties.size(); i++) {
        if (!this->properties.at(i).get_key().compare(property.get_key())) {
            return i;
        } else if (!this->properties.at(i).get_value().compare(property.get_value())) {
            return i;
        } else if (this->properties.at(i).get_value().find(property.get_value()) != std::string::npos) {
            return i;
        } else if (this->properties.at(i).get_key().find(property.get_key()) != std::string::npos) {
            return i;
        } else if (this->properties.at(i).get() == property.get()) {
            return i;
        }
    }

    return docpp::HTML::Properties::npos;
}

docpp::HTML::Properties::size_type docpp::HTML::Properties::find(const std::string& str) {
    for (size_type i{0}; i < this->properties.size(); i++) {
        if (!this->properties.at(i).get_key().compare(str) || !this->properties.at(i).get_value().compare(str)) {
            return i;
        } else if (this->properties.at(i).get_key().find(str) != std::string::npos || this->properties.at(i).get_value().find(str) != std::string::npos) {
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

docpp::HTML::Properties::size_type docpp::HTML::Properties::size() const {
    return this->properties.size();
}

void docpp::HTML::Properties::clear() {
    this->properties.clear();
}

bool docpp::HTML::Properties::empty() const {
    return this->properties.empty();
}

void docpp::HTML::Properties::swap(const size_type index1, const size_type index2) {
    if (index1 < 0 || index1 >= this->properties.size() || index2 < 0 || index2 >= this->properties.size()) {
        throw docpp::out_of_range("Index out of range");
    }

    std::swap(this->properties[index1], this->properties[index2]);
}

void docpp::HTML::Properties::swap(const docpp::HTML::Property& property1, const docpp::HTML::Property& property2) {
    this->swap(this->find(property1), this->find(property2));
}


docpp::HTML::Element& docpp::HTML::Element::operator=(const docpp::HTML::Element& element) {
    this->set(element.get_tag(), element.properties, element.get_data(), element.type);
    return *this;
}

docpp::HTML::Element& docpp::HTML::Element::operator+=(const std::string& data) {
    this->data += data;
    return *this;
}

bool docpp::HTML::Element::operator==(const docpp::HTML::Element& element) const {
    return this->tag == element.get_tag() && this->properties == element.properties && this->data == element.get_data() && this->type == element.type;
}

bool docpp::HTML::Element::operator!=(const docpp::HTML::Element& element) const {
    return this->tag != element.get_tag() || this->properties != element.properties || this->data != element.get_data() || this->type != element.type;
}

void docpp::HTML::Element::set(const std::string& tag, const Properties& properties, const std::string& data, const Type type) {
    this->set_tag(tag);
    this->set_properties(properties);
    this->set_data(data);
    this->set_type(type);
}

void docpp::HTML::Element::set(const Tag tag, const Properties& properties, const std::string& data) {
    this->set_tag(tag);
    this->set_properties(properties);
    this->set_data(data);
}

void docpp::HTML::Element::set_tag(const std::string& tag) {
    this->tag = tag;
}

void docpp::HTML::Element::set_tag(const Tag tag) {
    std::pair<std::string, docpp::HTML::Type> resolved{resolve_tag(tag)};
    this->tag = resolved.first;
    this->type = resolved.second;
}

void docpp::HTML::Element::set_data(const std::string& data) {
    this->data = data;
}

void docpp::HTML::Element::set_type(const Type type) {
    this->type = type;
}

void docpp::HTML::Element::set_properties(const Properties& properties) {
    this->properties = properties;
}

std::string docpp::HTML::Element::get(const Formatting formatting, const int tabc) const {
    std::string ret{};

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

    ret += "<" + this->tag;

    for (const Property& it : this->properties.get_properties()) {
        if (!it.get_key().compare("")) continue;
        if (!it.get_value().compare("")) continue;

        ret += " " + it.get_key() + "=\"" + it.get_value() + "\"";
    }

    if (this->type != docpp::HTML::Type::Self_Closing) {
        ret += ">";
    }

    if (this->type == docpp::HTML::Type::Non_Self_Closing) {
        ret += this->data + "</" + this->tag + ">";
    } else if (this->type == docpp::HTML::Type::Self_Closing) {
        ret += this->data + "/>";
    }

    if (formatting == docpp::HTML::Formatting::Pretty || formatting == docpp::HTML::Formatting::Newline) {
        ret += "\n";
    }

    return std::move(ret);
}

std::string docpp::HTML::Element::get_tag() const {
    return this->tag;
}

std::string docpp::HTML::Element::get_data() const {
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

docpp::HTML::Section& docpp::HTML::Section::operator=(const docpp::HTML::Section& section) {
    this->tag = section.tag;
    this->properties = section.properties;
    this->elements = section.elements;
    this->sections = section.sections;
    this->index = section.index;

    return *this;
}

docpp::HTML::Section& docpp::HTML::Section::operator+=(const docpp::HTML::Element& element) {
    this->push_back(element);
    return *this;
}

docpp::HTML::Section& docpp::HTML::Section::operator+=(const docpp::HTML::Section& section) {
    this->push_back(section);
    return *this;
}

docpp::HTML::Element docpp::HTML::Section::operator[](const int& index) const {
    return this->at(index);
}

bool docpp::HTML::Section::operator==(const docpp::HTML::Section& section) const {
    return this->tag == section.tag && this->properties == section.properties && this->elements == section.elements && this->sections == section.sections && this->index == section.index;
}

bool docpp::HTML::Section::operator==(const docpp::HTML::Element& element) const {
    for (const Element& it : this->get_elements()) {
        if (it.get() == element.get()) {
            return true;
        }
    }

    return false;
}

bool docpp::HTML::Section::operator!=(const docpp::HTML::Section& section) const {
    return this->tag != section.tag || this->properties != section.properties || this->elements != section.elements || this->sections != section.sections || this->index != section.index;
}

bool docpp::HTML::Section::operator!=(const docpp::HTML::Element& element) const {
    for (const Element& it : this->get_elements()) {
        if (it.get() == element.get()) {
            return false;
        }
    }

    return true;
}

void docpp::HTML::Section::set(const std::string& tag, const Properties& properties) {
    this->tag = tag;
    this->properties = properties;
}

void docpp::HTML::Section::set_tag(const std::string& tag) {
    this->tag = tag;
}

void docpp::HTML::Section::set_tag(const Tag tag) {
    std::pair<std::string, docpp::HTML::Type> resolved{resolve_tag(tag)};
    this->tag = resolved.first;
}

void docpp::HTML::Section::set_properties(const Properties& properties) {
    this->properties = properties;
}

std::pair<std::string, docpp::HTML::Type> docpp::HTML::resolve_tag(const Tag tag) {
    static const std::unordered_map<docpp::HTML::Tag, std::pair<std::string, docpp::HTML::Type>> tag_map{
        {Tag::Empty, {"", docpp::HTML::Type::Text}},
        {Tag::Empty_No_Formatting, {"", docpp::HTML::Type::Text_No_Formatting}},
        {Tag::Abbreviation, {"abbr", docpp::HTML::Type::Non_Self_Closing}},
        {Tag::Abbr, {"abbr", docpp::HTML::Type::Non_Self_Closing}},
        {Tag::Acronym, {"acronym", docpp::HTML::Type::Non_Self_Closing}},
        {Tag::Address, {"address", docpp::HTML::Type::Non_Self_Closing}},
        {Tag::Applet, {"applet", docpp::HTML::Type::Non_Self_Closing}},
        {Tag::Anchor, {"a", docpp::HTML::Type::Non_Self_Closing}},
        {Tag::A, {"a", docpp::HTML::Type::Non_Self_Closing}},
        {Tag::Article, {"article", docpp::HTML::Type::Non_Self_Closing}},
        {Tag::Area, {"area", docpp::HTML::Type::Non_Closed}},
        {Tag::Aside, {"aside", docpp::HTML::Type::Non_Self_Closing}},
        {Tag::Audio, {"audio", docpp::HTML::Type::Non_Self_Closing}},
        {Tag::Base, {"base", docpp::HTML::Type::Non_Closed}},
        {Tag::Basefont, {"basefont", docpp::HTML::Type::Non_Closed}},
        {Tag::Bdi, {"bdi", docpp::HTML::Type::Non_Self_Closing}},
        {Tag::Bdo, {"bdo", docpp::HTML::Type::Non_Self_Closing}},
        {Tag::Bgsound, {"bgsound", docpp::HTML::Type::Non_Self_Closing}},
        {Tag::Big, {"big", docpp::HTML::Type::Non_Self_Closing}},
        {Tag::Blockquote, {"blockquote", docpp::HTML::Type::Non_Self_Closing}},
        {Tag::Body, {"body", docpp::HTML::Type::Non_Self_Closing}},
        {Tag::B, {"b", docpp::HTML::Type::Non_Self_Closing}},
        {Tag::Bold, {"b", docpp::HTML::Type::Non_Self_Closing}},
        {Tag::Br, {"br", docpp::HTML::Type::Non_Closed}},
        {Tag::Break, {"br", docpp::HTML::Type::Non_Closed}},
        {Tag::Button, {"button", docpp::HTML::Type::Non_Closed}},
        {Tag::Caption, {"caption", docpp::HTML::Type::Non_Self_Closing}},
        {Tag::Canvas, {"canvas", docpp::HTML::Type::Non_Self_Closing}},
        {Tag::Center, {"center", docpp::HTML::Type::Non_Self_Closing}},
        {Tag::Cite, {"cite", docpp::HTML::Type::Non_Self_Closing}},
        {Tag::Code, {"code", docpp::HTML::Type::Non_Self_Closing}},
        {Tag::Colgroup, {"colgroup", docpp::HTML::Type::Non_Self_Closing}},
        {Tag::Column, {"col", docpp::HTML::Type::Non_Closed}},
        {Tag::Col, {"col", docpp::HTML::Type::Non_Closed}},
        {Tag::Data, {"data", docpp::HTML::Type::Non_Self_Closing}},
        {Tag::Datalist, {"datalist", docpp::HTML::Type::Non_Self_Closing}},
        {Tag::Dd, {"dd", docpp::HTML::Type::Non_Self_Closing}},
        {Tag::Dfn, {"dfn", docpp::HTML::Type::Non_Self_Closing}},
        {Tag::Define, {"dfn", docpp::HTML::Type::Non_Self_Closing}},
        {Tag::Delete, {"del", docpp::HTML::Type::Non_Self_Closing}},
        {Tag::Del, {"del", docpp::HTML::Type::Non_Self_Closing}},
        {Tag::Details, {"details", docpp::HTML::Type::Non_Self_Closing}},
        {Tag::Dialog, {"dialog", docpp::HTML::Type::Non_Self_Closing}},
        {Tag::Dir, {"dir", docpp::HTML::Type::Non_Self_Closing}},
        {Tag::Div, {"div", docpp::HTML::Type::Non_Self_Closing}},
        {Tag::Dl, {"dl", docpp::HTML::Type::Non_Self_Closing}},
        {Tag::Dt, {"dt", docpp::HTML::Type::Non_Self_Closing}},
        {Tag::Embed, {"embed", docpp::HTML::Type::Non_Closed}},
        {Tag::Fieldset, {"fieldset", docpp::HTML::Type::Non_Self_Closing}},
        {Tag::Figcaption, {"figcaption", docpp::HTML::Type::Non_Self_Closing}},
        {Tag::Figure, {"figure", docpp::HTML::Type::Non_Self_Closing}},
        {Tag::Font, {"font", docpp::HTML::Type::Non_Self_Closing}},
        {Tag::Footer, {"footer", docpp::HTML::Type::Non_Self_Closing}},
        {Tag::Form, {"form", docpp::HTML::Type::Non_Self_Closing}},
        {Tag::Frame, {"frame", docpp::HTML::Type::Self_Closing}},
        {Tag::Frameset, {"frameset", docpp::HTML::Type::Non_Self_Closing}},
        {Tag::Head, {"head", docpp::HTML::Type::Non_Self_Closing}},
        {Tag::Header, {"header", docpp::HTML::Type::Non_Self_Closing}},
        {Tag::H1, {"h1", docpp::HTML::Type::Non_Self_Closing}},
        {Tag::H2, {"h2", docpp::HTML::Type::Non_Self_Closing}},
        {Tag::H3, {"h3", docpp::HTML::Type::Non_Self_Closing}},
        {Tag::H4, {"h4", docpp::HTML::Type::Non_Self_Closing}},
        {Tag::H5, {"h5", docpp::HTML::Type::Non_Self_Closing}},
        {Tag::H6, {"h6", docpp::HTML::Type::Non_Self_Closing}},
        {Tag::Hr, {"hr", docpp::HTML::Type::Non_Closed}},
        {Tag::Hgroup, {"hgroup", docpp::HTML::Type::Non_Self_Closing}},
        {Tag::Html, {"html", docpp::HTML::Type::Non_Self_Closing}},
        {Tag::Iframe, {"iframe", docpp::HTML::Type::Non_Self_Closing}},
        {Tag::Image, {"img", docpp::HTML::Type::Non_Closed}},
        {Tag::Img, {"img", docpp::HTML::Type::Non_Closed}},
        {Tag::Input, {"input", docpp::HTML::Type::Self_Closing}},
        {Tag::Ins, {"ins", docpp::HTML::Type::Non_Self_Closing}},
        {Tag::Isindex, {"isindex", docpp::HTML::Type::Non_Closed}},
        {Tag::Italic, {"i", docpp::HTML::Type::Non_Self_Closing}},
        {Tag::I, {"i", docpp::HTML::Type::Non_Self_Closing}},
        {Tag::Kbd, {"kbd", docpp::HTML::Type::Non_Self_Closing}},
        {Tag::Keygen, {"keygen", docpp::HTML::Type::Non_Closed}},
        {Tag::Label, {"label", docpp::HTML::Type::Non_Self_Closing}},
        {Tag::Legend, {"legend", docpp::HTML::Type::Non_Self_Closing}},
        {Tag::List, {"li", docpp::HTML::Type::Non_Self_Closing}},
        {Tag::Li, {"li", docpp::HTML::Type::Non_Self_Closing}},
        {Tag::Link, {"link", docpp::HTML::Type::Non_Closed}},
        {Tag::Main, {"main", docpp::HTML::Type::Non_Self_Closing}},
        {Tag::Mark, {"mark", docpp::HTML::Type::Non_Self_Closing}},
        {Tag::Marquee, {"marquee", docpp::HTML::Type::Non_Self_Closing}},
        {Tag::Menuitem, {"menuitem", docpp::HTML::Type::Non_Self_Closing}},
        {Tag::Meta, {"meta", docpp::HTML::Type::Non_Closed}},
        {Tag::Meter, {"meter", docpp::HTML::Type::Non_Self_Closing}},
        {Tag::Nav, {"nav", docpp::HTML::Type::Non_Self_Closing}},
        {Tag::Nobreak, {"nobr", docpp::HTML::Type::Non_Self_Closing}},
        {Tag::Nobr, {"nobr", docpp::HTML::Type::Non_Self_Closing}},
        {Tag::Noembed, {"noembed", docpp::HTML::Type::Non_Self_Closing}},
        {Tag::Noscript, {"noscript", docpp::HTML::Type::Non_Self_Closing}},
        {Tag::Object, {"object", docpp::HTML::Type::Non_Self_Closing}},
        {Tag::Optgroup, {"optgroup", docpp::HTML::Type::Non_Self_Closing}},
        {Tag::Option, {"option", docpp::HTML::Type::Non_Self_Closing}},
        {Tag::Output, {"output", docpp::HTML::Type::Non_Self_Closing}},
        {Tag::Paragraph, {"p", docpp::HTML::Type::Non_Self_Closing}},
        {Tag::P, {"p", docpp::HTML::Type::Non_Self_Closing}},
        {Tag::Param, {"param", docpp::HTML::Type::Non_Closed}},
        {Tag::Phrase, {"phrase", docpp::HTML::Type::Non_Self_Closing}},
        {Tag::Pre, {"pre", docpp::HTML::Type::Non_Self_Closing}},
        {Tag::Progress, {"progress", docpp::HTML::Type::Non_Self_Closing}},
        {Tag::Quote, {"q", docpp::HTML::Type::Non_Self_Closing}},
        {Tag::Q, {"q", docpp::HTML::Type::Non_Self_Closing}},
        {Tag::Rp, {"rp", docpp::HTML::Type::Non_Self_Closing}},
        {Tag::Rt, {"rt", docpp::HTML::Type::Non_Self_Closing}},
        {Tag::Ruby, {"ruby", docpp::HTML::Type::Non_Self_Closing}},
        {Tag::Outdated, {"s", docpp::HTML::Type::Non_Self_Closing}},
        {Tag::S, {"s", docpp::HTML::Type::Non_Self_Closing}},
        {Tag::Sample, {"samp", docpp::HTML::Type::Non_Self_Closing}},
        {Tag::Samp, {"samp", docpp::HTML::Type::Non_Self_Closing}},
        {Tag::Script, {"script", docpp::HTML::Type::Non_Self_Closing}},
        {Tag::Section, {"section", docpp::HTML::Type::Non_Self_Closing}},
        {Tag::Small, {"small", docpp::HTML::Type::Non_Self_Closing}},
        {Tag::Source, {"source", docpp::HTML::Type::Non_Self_Closing}},
        {Tag::Spacer, {"spacer", docpp::HTML::Type::Non_Self_Closing}},
        {Tag::Span, {"span", docpp::HTML::Type::Non_Self_Closing}},
        {Tag::Strike, {"strike", docpp::HTML::Type::Non_Self_Closing}},
        {Tag::Strong, {"strong", docpp::HTML::Type::Non_Self_Closing}},
        {Tag::Style, {"style", docpp::HTML::Type::Non_Closed}},
        {Tag::Sub, {"sub", docpp::HTML::Type::Non_Self_Closing}},
        {Tag::Subscript, {"sub", docpp::HTML::Type::Non_Self_Closing}},
        {Tag::Sup, {"sup", docpp::HTML::Type::Non_Self_Closing}},
        {Tag::Superscript, {"sup", docpp::HTML::Type::Non_Self_Closing}},
        {Tag::Summary, {"summary", docpp::HTML::Type::Non_Self_Closing}},
        {Tag::Svg, {"svg", docpp::HTML::Type::Non_Closed}},
        {Tag::Table, {"table", docpp::HTML::Type::Non_Self_Closing}},
        {Tag::Tbody, {"tbody", docpp::HTML::Type::Non_Self_Closing}},
        {Tag::Td, {"td", docpp::HTML::Type::Non_Self_Closing}},
        {Tag::Template, {"template", docpp::HTML::Type::Non_Self_Closing}},
        {Tag::Tfoot, {"tfoot", docpp::HTML::Type::Non_Self_Closing}},
        {Tag::Th, {"th", docpp::HTML::Type::Non_Self_Closing}},
        {Tag::Tr, {"tr", docpp::HTML::Type::Non_Self_Closing}},
        {Tag::Thead, {"thead", docpp::HTML::Type::Non_Self_Closing}},
        {Tag::Time, {"time", docpp::HTML::Type::Non_Self_Closing}},
        {Tag::Title, {"title", docpp::HTML::Type::Non_Self_Closing}},
        {Tag::Track, {"track", docpp::HTML::Type::Non_Closed}},
        {Tag::Tt, {"tt", docpp::HTML::Type::Non_Self_Closing}},
        {Tag::Underline, {"u", docpp::HTML::Type::Non_Self_Closing}},
        {Tag::U, {"u", docpp::HTML::Type::Non_Self_Closing}},
        {Tag::Var, {"var", docpp::HTML::Type::Non_Self_Closing}},
        {Tag::Video, {"video", docpp::HTML::Type::Non_Self_Closing}},
        {Tag::Wbr, {"wbr", docpp::HTML::Type::Non_Closed}},
        {Tag::Xmp, {"xmp", docpp::HTML::Type::Non_Self_Closing}},
    };

    if (tag_map.find(tag) != tag_map.end()) {
        return tag_map.at(tag);
    }

    const std::string throwmsg{"Invalid tag: " + std::to_string(static_cast<int>(tag))};
    throw docpp::invalid_argument{throwmsg.c_str()};
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

docpp::HTML::Section docpp::HTML::Section::at_section(const size_type index) const {
    if (this->sections.find(index) != this->sections.end()) {
        return this->sections.at(index);
    }

    throw docpp::out_of_range("Index out of range");
}

docpp::HTML::Section::size_type docpp::HTML::Section::find(const Element& element) {
    for (size_type i{0}; i < this->size(); i++) {
        const Element it = this->get_elements().at(i);

        if (it.get() == element.get()) {
            return i;
        }
    }

    return docpp::HTML::Section::npos;
}

docpp::HTML::Section::size_type docpp::HTML::Section::find(const Section& section) {
    for (size_type i{0}; i < this->size(); i++) {
        const Section it = this->get_sections().at(i);

        if (it.get() == section.get()) {
            return i;
        }
    }

    return docpp::HTML::Section::npos;
}

docpp::HTML::Section::size_type docpp::HTML::Section::find(const std::string& str) {
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

docpp::HTML::Section docpp::HTML::Section::front_section() const {
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

docpp::HTML::Section docpp::HTML::Section::back_section() const {
    if (this->sections.find(this->index - 1) != this->sections.end()) {
        return this->sections.at(this->index - 1);
    }

    throw docpp::out_of_range("Index out of range");
}

docpp::HTML::Section::size_type docpp::HTML::Section::size() const {
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
    return std::move(ret);
}

std::vector<docpp::HTML::Section> docpp::HTML::Section::get_sections() const {
    std::vector<docpp::HTML::Section> ret{};
    ret.reserve(this->index);

    for (size_type i{0}; i < this->index; i++) {
        if (this->sections.find(i) != this->sections.end()) {
            ret.push_back(this->sections.at(i));
        }
    }

    return std::move(ret);
}

std::string docpp::HTML::Section::get(const Formatting formatting, const int tabc) const {
    std::string ret{};
    int tabcount{tabc};

    if (!this->tag.compare("")) {
        --tabcount; // i guess this means the section only contains elements and sections, and isn't a tag itself

        if (tabcount < -1) {
            tabcount = -1; // will be incremented by 1, so it will be 0
        }
    }

    if (formatting == docpp::HTML::Formatting::Pretty) {
        for (size_type i{0}; i < tabcount; i++) {
            ret += "\t";
        }
    }

    if (this->tag.compare("")) {
        ret += "<" + this->tag;

        for (const Property& it : this->properties.get_properties()) {
            if (!it.get_key().compare("")) continue;
            if (!it.get_value().compare("")) continue;

            ret += " " + it.get_key() + "=\"" + it.get_value() + "\"";
        }

        ret += ">";

        if (formatting == docpp::HTML::Formatting::Pretty || formatting == docpp::HTML::Formatting::Newline) {
            ret += "\n";
        }
    }

    for (size_type i{0}; i < this->index; i++) {
        if (this->elements.find(i) != this->elements.end()) {
            ret += this->elements.at(i).get(formatting, tabcount + 1);
        } else if (this->sections.find(i) != this->sections.end()) {
            ret += this->sections.at(i).get(formatting, tabcount + 1);

            if (formatting == docpp::HTML::Formatting::Pretty || formatting == docpp::HTML::Formatting::Newline) {
                ret += "\n";
            }
        }
    }

    if (formatting == docpp::HTML::Formatting::Pretty) {
        for (size_type i{0}; i < tabcount; i++) {
            ret += "\t";
        }
    }

    ret += this->tag.compare("") ? ("</" + this->tag + ">") : "";

    return std::move(ret);
}

std::string docpp::HTML::Section::get_tag() const {
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

std::string docpp::HTML::Document::get(const Formatting formatting, const int tabc) const {
    return this->doctype + (formatting == Formatting::Pretty ? "\n" : formatting == Formatting::Newline ? "\n" : "") + this->document.get(formatting, tabc);
}

docpp::HTML::Section& docpp::HTML::Document::get_section() {
    return this->document;
}

void docpp::HTML::Document::set(const docpp::HTML::Section& document) {
    this->document = document;
}

void docpp::HTML::Document::set_doctype(const std::string& doctype) {
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
    this->set(document.get());
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

std::string docpp::HTML::Document::get_doctype() const {
    return this->doctype;
}

std::string docpp::CSS::Property::get_key() const {
    return this->property.first;
}

std::string docpp::CSS::Property::get_value() const {
    return this->property.second;
}

std::pair<std::string, std::string> docpp::CSS::Property::get() const {
    return this->property;
}

void docpp::CSS::Property::set_key(const std::string& key) {
    this->property.first = key;
}

void docpp::CSS::Property::set_value(const std::string& value) {
    this->property.second = value;
}

void docpp::CSS::Property::set(const std::pair<std::string, std::string>& property) {
    this->property = property;
}

void docpp::CSS::Property::set(const std::string& key, const std::string& value) {
    this->property = std::make_pair(key, value);
}

docpp::CSS::Property& docpp::CSS::Property::operator=(const docpp::CSS::Property& property) {
    this->set(property.get());
    return *this;
}

docpp::CSS::Property& docpp::CSS::Property::operator=(const std::pair<std::string, std::string>& property) {
    this->set(property);
    return *this;
}

docpp::CSS::Element& docpp::CSS::Element::operator=(const docpp::CSS::Element& element) {
    this->set({element.get_tag(), element.get_properties()});
    return *this;
}

docpp::CSS::Element& docpp::CSS::Element::operator+=(const Property& property) {
    this->push_back(property);
    return *this;
}

docpp::CSS::Property docpp::CSS::Element::operator[](const size_type& index) const {
    return this->at(index);
}

void docpp::CSS::Element::set(const std::string& tag, const std::vector<Property>& properties) {
    this->element.first = tag;
    this->element.second = properties;
}

void docpp::CSS::Element::set(const std::pair<std::string, std::vector<Property>>& element) {
    this->element = element;
}

void docpp::CSS::Element::push_front(const Property& property) {
    this->element.second.insert(this->element.second.begin(), property);
}

void docpp::CSS::Element::push_back(const Property& property) {
    this->element.second.push_back(property);
}

void docpp::CSS::Element::insert(const size_type index, const Property& property) {
    if (index < 0 || index >= this->element.second.size()) {
        throw docpp::out_of_range("Index out of range");
    }

    this->element.second.insert(this->element.second.begin() + index, property);
}

void docpp::CSS::Element::erase(const size_type index) {
    if (index < 0 || index >= this->element.second.size()) {
        throw docpp::out_of_range("Index out of range");
    }

    this->element.second.erase(this->element.second.begin() + index);
}

docpp::CSS::Property docpp::CSS::Element::at(const size_type index) const {
    if (index < 0 || index >= this->element.second.size()) {
        throw docpp::out_of_range("Index out of range");
    }

    return this->element.second.at(index);
}

docpp::CSS::Element::size_type docpp::CSS::Element::find(const Property& property) {
    for (size_type i{0}; i < this->element.second.size(); i++) {
        if (this->element.second.at(i).get() == property.get()) {
            return i;
        }
    }

    return docpp::CSS::Element::npos;
}

docpp::CSS::Element::size_type docpp::CSS::Element::find(const std::string& str) {
    for (size_type i{0}; i < this->element.second.size(); i++) {
        if (!this->element.second.at(i).get_key().compare(str) || !this->element.second.at(i).get_value().compare(str)) {
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

docpp::CSS::Element::size_type docpp::CSS::Element::size() const {
    return this->element.second.size();
}

void docpp::CSS::Element::swap(const size_type index1, const size_type index2) {
    if (index1 < 0 || index1 >= this->element.second.size() || index2 < 0 || index2 >= this->element.second.size()) {
        throw docpp::out_of_range("Index out of range");
    }

    std::swap(this->element.second[index1], this->element.second[index2]);
}

void docpp::CSS::Element::swap(const Property& property1, const Property& property2) {
    this->swap(this->find(property1), this->find(property2));
}

std::string docpp::CSS::Element::get(const Formatting formatting, const int tabc) const {
    std::string ret{};

    if (this->element.first.compare("")) {
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
            if (!it.get_key().compare("")) continue;
            if (!it.get_value().compare("")) continue;

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

    return std::move(ret);
}

std::string docpp::CSS::Element::get_tag() const {
    return this->element.first;
}

std::vector<docpp::CSS::Property> docpp::CSS::Element::get_properties() const {
    return this->element.second;
}

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
    if (index < 0 || index >= this->elements.size()) {
        throw docpp::out_of_range("Index out of range");
    }

    this->elements.insert(this->elements.begin() + index, element);
}

void docpp::CSS::Stylesheet::erase(const size_type index) {
    if (index < 0 || index >= this->elements.size()) {
        throw docpp::out_of_range("Index out of range");
    }

    this->elements.erase(this->elements.begin() + index);
}

docpp::CSS::Stylesheet& docpp::CSS::Stylesheet::operator=(const docpp::CSS::Stylesheet& stylesheet) {
    this->set(stylesheet.get_elements());
    return *this;
}

docpp::CSS::Stylesheet& docpp::CSS::Stylesheet::operator+=(const Element& element) {
    this->push_back(element);
    return *this;
}

docpp::CSS::Element docpp::CSS::Stylesheet::operator[](const int& index) const {
    return this->at(index);
}

docpp::CSS::Element docpp::CSS::Stylesheet::at(const size_type index) const {
    if (index < 0 || index >= this->elements.size()) {
        throw docpp::out_of_range("Index out of range");
    }

    return this->elements.at(index);
}

docpp::CSS::Stylesheet::size_type docpp::CSS::Stylesheet::find(const Element& element) {
    for (size_type i{0}; i < this->elements.size(); i++) {
        if (this->elements.at(i).get() == element.get()) {
            return i;
        }
    }

    return docpp::CSS::Stylesheet::npos;
}

docpp::CSS::Stylesheet::size_type docpp::CSS::Stylesheet::find(const std::string& str) {
    for (size_type i{0}; i < this->elements.size(); i++) {
        if (!this->elements.at(i).get().compare(str) || !this->elements.at(i).get_tag().compare(str)) {
            return i;
        }
    }

    return docpp::CSS::Stylesheet::npos;
}

docpp::CSS::Stylesheet::size_type docpp::CSS::Stylesheet::size() const {
    return this->elements.size();
}

docpp::CSS::Element docpp::CSS::Stylesheet::front() const {
    return this->elements.front();
}

docpp::CSS::Element docpp::CSS::Stylesheet::back() const {
    return this->elements.back();
}

void docpp::CSS::Stylesheet::swap(const size_type index1, const size_type index2) {
    if (index1 < 0 || index1 >= this->elements.size() || index2 < 0 || index2 >= this->elements.size()) {
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

std::string docpp::CSS::Stylesheet::get(const Formatting formatting, const int tabc) const {
    std::string ret{};

    for (const Element& it : this->elements) {
        ret += it.get(formatting, tabc);
    }

    return std::move(ret);
}
