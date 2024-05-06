/**
 * docpp - Small C++ library for generating XML, HTML and CSS.
 * Licensed under the LGPL-3.0-or-later license.
 *
 * Author: speedie <speedie@speedie.site>
 *
 * @file docpp.cpp
 * @brief Implementation of the docpp library.
 * @author speedie
 * @date 2024
 * @copyright GNU Lesser General Public License 3.0.
 * @version 0.0.1
 */

#include <include/docpp.hpp>
#include <string>
#include <vector>
#include <unordered_map>
#include <stdexcept>

docpp::HTML::HTMLProperty::HTMLProperty(const std::string& key, const std::string& value) {
    this->setKey(key);
    this->setValue(value);
}

docpp::HTML::HTMLProperty::HTMLProperty(const std::pair<std::string, std::string>& property) {
    this->set(property);
}

std::string docpp::HTML::HTMLProperty::getKey() const {
    return this->property.first;
}

std::string docpp::HTML::HTMLProperty::getValue() const {
    return this->property.second;
}

std::pair<std::string, std::string> docpp::HTML::HTMLProperty::get() const {
    return this->property;
}

void docpp::HTML::HTMLProperty::setKey(const std::string& key) {
    this->property.first = key;
}

void docpp::HTML::HTMLProperty::setValue(const std::string& value) {
    this->property.second = value;
}

void docpp::HTML::HTMLProperty::set(const std::pair<std::string, std::string>& property) {
    this->property = property;
}

docpp::HTML::HTMLElementProperties::HTMLElementProperties(const std::vector<docpp::HTML::HTMLProperty>& properties) {
    this->set(properties);
}

docpp::HTML::HTMLElementProperties::HTMLElementProperties(const docpp::HTML::HTMLProperty& property) {
    this->push_back(property);
}

std::vector<docpp::HTML::HTMLProperty> docpp::HTML::HTMLElementProperties::get() const {
    return this->properties;
}

void docpp::HTML::HTMLElementProperties::set(const std::vector<docpp::HTML::HTMLProperty>& properties) {
    this->properties = properties;
}

void docpp::HTML::HTMLElementProperties::push_back(const docpp::HTML::HTMLProperty& property) {
    this->properties.push_back(property);
}

docpp::HTML::HTMLElement::HTMLElement(const std::string& tag, const HTMLElementProperties& properties, const std::string& data, const int type) {
    this->set(tag, properties, data, type);
}

void docpp::HTML::HTMLElement::set(const std::string& tag, const HTMLElementProperties& properties, const std::string& data, const int type) {
    this->tag = tag;
    this->data = data;
    this->properties = properties;
    this->type = type;
}

std::string docpp::HTML::HTMLElement::get(const int formatting) const {
    std::string ret{};

    ret += "<" + this->tag;

    for (const auto& it : this->properties.get()) {
        if (!it.getKey().compare("")) continue;
        if (!it.getValue().compare("")) continue;

        ret += " " + it.getKey() + "=\"" + it.getValue() + "\"";
    }

    if (this->type != docpp::HTML::TYPE_SELF_CLOSING) {
        ret += ">";
    }

    if (this->type == docpp::HTML::TYPE_NON_SELF_CLOSING) {
        ret += this->data + "</" + this->tag + ">";
    } else if (this->type == docpp::HTML::TYPE_SELF_CLOSING) {
        ret += this->data + "/>";
    }

    if (formatting == docpp::HTML::FORMATTING_PRETTY) {
        ret += "\n";
    }

    return std::move(ret);
}

std::string docpp::HTML::HTMLElement::getTag() const {
    return this->tag;
}

std::string docpp::HTML::HTMLElement::getData() const {
    return this->data;
}

docpp::HTML::HTMLSection::HTMLSection(const std::string& tag, const HTMLElementProperties& properties) {
    this->tag = tag;
    this->properties = properties;
}

docpp::HTML::HTMLSection::HTMLSection(const int tag, const HTMLElementProperties& properties) {
    if (tag == docpp::HTML::SECTION_DIV) {
        this->tag = "div";
    } else if (tag == docpp::HTML::SECTION_BODY) {
        this->tag = "body";
    } else if (tag == docpp::HTML::SECTION_FOOTER) {
        this->tag = "footer";
    } else if (tag == docpp::HTML::SECTION_HEAD) {
        this->tag = "head";
    } else if (tag == docpp::HTML::SECTION_HTML) {
        this->tag = "html";
    }

    this->properties = properties;
}

void docpp::HTML::HTMLSection::set(const std::string& tag, const HTMLElementProperties& properties) {
    this->tag = tag;
    this->properties = properties;
}

void docpp::HTML::HTMLSection::set(const int tag, const HTMLElementProperties& properties) {
    if (tag == docpp::HTML::SECTION_DIV) {
        this->tag = "div";
    } else if (tag == docpp::HTML::SECTION_BODY) {
        this->tag = "body";
    } else if (tag == docpp::HTML::SECTION_FOOTER) {
        this->tag = "footer";
    } else if (tag == docpp::HTML::SECTION_HEAD) {
        this->tag = "head";
    } else if (tag == docpp::HTML::SECTION_HTML) {
        this->tag = "html";
    }

    this->properties = properties;
}

void docpp::HTML::HTMLSection::push_front(const HTMLElement& element) {
    for (int i{this->index}; i > 0; i--) {
        this->elements[i] = this->elements.at(i - 1);
    }

    this->elements[0] = element;
    this->index++;
}

void docpp::HTML::HTMLSection::push_front(const HTMLSection& section) {
    for (int i{this->index}; i > 0; i--) {
        this->sections.at(i) = this->sections.at(i - 1);
    }

    this->sections[0] = section;
    this->index++;
}

void docpp::HTML::HTMLSection::push_back(const HTMLElement& element) {
    this->elements[this->index++] = element;
}

void docpp::HTML::HTMLSection::push_back(const HTMLSection& section) {
    this->sections[this->index++] = section;
}

void docpp::HTML::HTMLSection::erase(const int index) {
    bool erased{false};

    if (this->elements.find(index) != this->elements.end()) {
        this->elements.erase(index);
        erased = true;
    } else if (this->sections.find(index) != this->sections.end()) {
        this->sections.erase(index);
        erased = true;
    }

    if (!erased) {
        throw std::out_of_range("Index out of range");
    }
}

void docpp::HTML::HTMLSection::erase(const HTMLSection& section) {
    for (int i{0}; i < this->size(); i++) {
        const auto it = this->getHTMLSections().at(i);

        if (it.get() == section.get()) {
            this->erase(i);
            return;
        }
    }

    throw std::out_of_range("Section not found");
}

void docpp::HTML::HTMLSection::erase(const HTMLElement& element) {
    for (int i{0}; i < this->size(); i++) {
        const auto it = this->getHTMLElements().at(i);

        if (it.get() == element.get()) {
            this->erase(i);
            return;
        }
    }

    throw std::out_of_range("Element not found");
}

void docpp::HTML::HTMLSection::insert(const int index, const HTMLElement& element) {
    if (this->sections.find(index) != this->sections.end()) {
        throw std::invalid_argument("Index already occupied by a section");
    } else {
        this->elements[index] = element;
    }

    this->index = std::max(this->index, index) + 1;
}

void docpp::HTML::HTMLSection::insert(const int index, const HTMLSection& section) {
    this->sections[index] = section;
    this->index = std::max(this->index, index) + 1;
}

int docpp::HTML::HTMLSection::find(const HTMLElement& element) {
    for (int i{0}; i < this->size(); i++) {
        const auto it = this->getHTMLElements().at(i);

        if (it.get() == element.get()) {
            return i;
        }
    }

    return docpp::HTML::HTMLSection::npos;
}

int docpp::HTML::HTMLSection::find(const HTMLSection& section) {
    for (int i{0}; i < this->size(); i++) {
        const auto it = this->getHTMLSections().at(i);

        if (it.get() == section.get()) {
            return i;
        }
    }

    return docpp::HTML::HTMLSection::npos;
}

int docpp::HTML::HTMLSection::find(const std::string& str) {
    const auto elements = this->getHTMLElements();

    for (int i{0}; i < elements.size(); i++) {
        if (!elements.at(i).get().compare(str)) {
            return i;
        }
    }

    const auto sections = this->getHTMLSections();

    for (int i{0}; i < sections.size(); i++) {
        if (!sections.at(i).get().compare(str)) {
            return i;
        }
    }

    return docpp::HTML::HTMLSection::npos;
}

int docpp::HTML::HTMLSection::size() const {
    return this->index;
}

std::vector<docpp::HTML::HTMLElement> docpp::HTML::HTMLSection::getHTMLElements() {
    std::vector<docpp::HTML::HTMLElement> ret{};
    ret.reserve(this->index);
    for (int i{0}; i < this->index; i++) {
        if (this->elements.find(i) != this->elements.end()) {
            ret.push_back(this->elements.at(i));
        }
    }
    return std::move(ret);
}

std::vector<docpp::HTML::HTMLSection> docpp::HTML::HTMLSection::getHTMLSections() {
    std::vector<docpp::HTML::HTMLSection> ret{};
    ret.reserve(this->index);

    for (int i{0}; i < this->index; i++) {
        if (this->sections.find(i) != this->sections.end()) {
            ret.push_back(this->sections.at(i));
        }
    }

    return std::move(ret);
}

std::string docpp::HTML::HTMLSection::get(const int formatting) const {
    std::string ret{};

    ret += "<" + this->tag;

    for (const auto& it : this->properties.get()) {
        if (!it.getKey().compare("")) continue;
        if (!it.getValue().compare("")) continue;

        ret += " " + it.getKey() + "=\"" + it.getValue() + "\"";
    }

    ret += ">";

    if (formatting == docpp::HTML::FORMATTING_PRETTY) {
        ret += "\n";
    }

    for (int i{0}; i < this->index; i++) {
        if (this->elements.find(i) != this->elements.end()) {
            ret += this->elements.at(i).get(formatting);
        } else if (this->sections.find(i) != this->sections.end()) {
            ret += this->sections.at(i).get(formatting);

            if (formatting == docpp::HTML::FORMATTING_PRETTY) {
                ret += "\n";
            }
        }
    }

    ret += "</" + this->tag + ">";

    return std::move(ret);
}

void docpp::HTML::HTMLSection::swap(const int index1, const int index2) {
    if (this->elements.find(index1) != this->elements.end() && this->elements.find(index2) != this->elements.end()) {
        std::swap(this->elements[index1], this->elements[index2]);
    } else if (this->sections.find(index1) != this->sections.end() && this->sections.find(index2) != this->sections.end()) {
        std::swap(this->sections[index1], this->sections[index2]);
    } else {
        throw std::out_of_range("Index out of range");
    }
}

void docpp::HTML::HTMLSection::swap(const HTMLElement& element1, const HTMLElement& element2) {
    this->swap(this->find(element1), this->find(element2));
}

void docpp::HTML::HTMLSection::swap(const HTMLSection& section1, const HTMLSection& section2) {
    this->swap(this->find(section1), this->find(section2));
}

std::string docpp::HTML::HTMLDocument::get(const int formatting) const {
    return this->doctype + (formatting == FORMATTING_PRETTY ? "\n" : "") + this->document.get(formatting);
}

void docpp::HTML::HTMLDocument::set(const docpp::HTML::HTMLSection& document) {
    this->document = document;
}

void docpp::HTML::HTMLDocument::setDoctype(const std::string& doctype) {
    this->doctype = doctype;
}

docpp::HTML::HTMLDocument::HTMLDocument(const docpp::HTML::HTMLSection& document, const std::string& doctype) {
    this->set(document);
    this->setDoctype(doctype);
}

std::string docpp::HTML::HTMLDocument::getDoctype() const {
    return this->doctype;
}

docpp::CSS::CSSProperty::CSSProperty(const std::string& key, const std::string& value) {
    this->set(key, value);
}

docpp::CSS::CSSProperty::CSSProperty(const std::pair<std::string, std::string>& property) {
    this->set(property);
}

std::string docpp::CSS::CSSProperty::getKey() const {
    return this->property.first;
}

std::string docpp::CSS::CSSProperty::getValue() const {
    return this->property.second;
}

std::pair<std::string, std::string> docpp::CSS::CSSProperty::get() const {
    return this->property;
}

void docpp::CSS::CSSProperty::setKey(const std::string& key) {
    this->property.first = key;
}

void docpp::CSS::CSSProperty::setValue(const std::string& value) {
    this->property.second = value;
}

void docpp::CSS::CSSProperty::set(const std::pair<std::string, std::string>& property) {
    this->property = property;
}

void docpp::CSS::CSSProperty::set(const std::string& key, const std::string& value) {
    this->property = std::make_pair(key, value);
}

docpp::CSS::CSSElement::CSSElement(const std::string& tag, const std::vector<CSSProperty>& properties) {
    this->set(tag, properties);
}

docpp::CSS::CSSElement::CSSElement(const std::pair<std::string, std::vector<CSSProperty>>& element) {
    this->set(element);
}

void docpp::CSS::CSSElement::set(const std::string& tag, const std::vector<CSSProperty>& properties) {
    this->element.first = tag;
    this->element.second = properties;
}

void docpp::CSS::CSSElement::set(const std::pair<std::string, std::vector<CSSProperty>>& element) {
    this->element = element;
}

void docpp::CSS::CSSElement::push_front(const CSSProperty& property) {
    this->element.second.insert(this->element.second.begin(), property);
}

void docpp::CSS::CSSElement::push_back(const CSSProperty& property) {
    this->element.second.push_back(property);
}

void docpp::CSS::CSSElement::insert(const int index, const CSSProperty& property) {
    if (index < 0 || index >= this->element.second.size()) {
        throw std::out_of_range("Index out of range");
    }

    this->element.second.insert(this->element.second.begin() + index, property);
}

void docpp::CSS::CSSElement::erase(const int index) {
    if (index < 0 || index >= this->element.second.size()) {
        throw std::out_of_range("Index out of range");
    }

    this->element.second.erase(this->element.second.begin() + index);
}

int docpp::CSS::CSSElement::find(const CSSProperty& property) {
    for (int i{0}; i < this->element.second.size(); i++) {
        if (this->element.second.at(i).get() == property.get()) {
            return i;
        }
    }

    return docpp::CSS::CSSElement::npos;
}

int docpp::CSS::CSSElement::find(const std::string& str) {
    for (int i{0}; i < this->element.second.size(); i++) {
        if (!this->element.second.at(i).getKey().compare(str) || !this->element.second.at(i).getValue().compare(str)) {
            return i;
        }
    }

    return docpp::CSS::CSSElement::npos;
}

int docpp::CSS::CSSElement::size() const {
    return this->element.second.size();
}

void docpp::CSS::CSSElement::swap(const int index1, const int index2) {
    if (index1 < 0 || index1 >= this->element.second.size() || index2 < 0 || index2 >= this->element.second.size()) {
        throw std::out_of_range("Index out of range");
    }

    std::swap(this->element.second[index1], this->element.second[index2]);
}

void docpp::CSS::CSSElement::swap(const CSSProperty& property1, const CSSProperty& property2) {
    this->swap(this->find(property1), this->find(property2));
}

std::string docpp::CSS::CSSElement::get(const int formatting) const {
    std::string ret{};

    if (this->element.first.compare("")) {
        ret += this->element.first + " {";

        if (formatting == docpp::CSS::FORMATTING_PRETTY) {
            ret += "\n";
        }

        for (const auto& it : this->element.second) {
            if (!it.getKey().compare("")) continue;
            if (!it.getValue().compare("")) continue;

            ret += it.getKey() + ": " + it.getValue() + ";";

            if (formatting == docpp::CSS::FORMATTING_PRETTY) {
                ret += "\n";
            }
        }

        ret += "}";

        if (formatting == docpp::CSS::FORMATTING_PRETTY) {
            ret += "\n";
        }
    }

    return std::move(ret);
}

std::string docpp::CSS::CSSElement::getTag() const {
    return this->element.first;
}

std::vector<docpp::CSS::CSSProperty> docpp::CSS::CSSElement::getProperties() const {
    return this->element.second;
}

docpp::CSS::CSSStylesheet::CSSStylesheet(const std::vector<CSSElement>& elements) {
    this->set(elements);
}

void docpp::CSS::CSSStylesheet::set(const std::vector<CSSElement>& elements) {
    this->elements = elements;
}

void docpp::CSS::CSSStylesheet::push_front(const CSSElement& element) {
    this->elements.insert(this->elements.begin(), element);
}

void docpp::CSS::CSSStylesheet::push_back(const CSSElement& element) {
    this->elements.push_back(element);
}

void docpp::CSS::CSSStylesheet::insert(const int index, const CSSElement& element) {
    if (index < 0 || index >= this->elements.size()) {
        throw std::out_of_range("Index out of range");
    }

    this->elements.insert(this->elements.begin() + index, element);
}

void docpp::CSS::CSSStylesheet::erase(const int index) {
    if (index < 0 || index >= this->elements.size()) {
        throw std::out_of_range("Index out of range");
    }

    this->elements.erase(this->elements.begin() + index);
}

int docpp::CSS::CSSStylesheet::find(const CSSElement& element) {
    for (int i{0}; i < this->elements.size(); i++) {
        if (this->elements.at(i).get() == element.get()) {
            return i;
        }
    }

    return docpp::CSS::CSSStylesheet::npos;
}

int docpp::CSS::CSSStylesheet::find(const std::string& str) {
    for (int i{0}; i < this->elements.size(); i++) {
        if (!this->elements.at(i).get().compare(str) || !this->elements.at(i).getTag().compare(str)) {
            return i;
        }
    }

    return docpp::CSS::CSSStylesheet::npos;
}

int docpp::CSS::CSSStylesheet::size() const {
    return this->elements.size();
}

void docpp::CSS::CSSStylesheet::swap(const int index1, const int index2) {
    if (index1 < 0 || index1 >= this->elements.size() || index2 < 0 || index2 >= this->elements.size()) {
        throw std::out_of_range("Index out of range");
    }

    std::swap(this->elements[index1], this->elements[index2]);
}

void docpp::CSS::CSSStylesheet::swap(const CSSElement& element1, const CSSElement& element2) {
    this->swap(this->find(element1), this->find(element2));
}

std::vector<docpp::CSS::CSSElement> docpp::CSS::CSSStylesheet::getElements() const {
    return this->elements;
}

std::string docpp::CSS::CSSStylesheet::get(const int formatting) const {
    std::string ret{};

    for (const auto& it : this->elements) {
        ret += it.get(formatting);
    }

    return std::move(ret);
}
