/**
 * docpp - Small C++ library for generating XML, HTML and CSS.
 * Licensed under the LGPL-3.0-or-later license.
 *
 * Author: speedie <speedie@speedie.site>
 */

#include <include/docpp.hpp>
#include <string>
#include <vector>

docpp::HTML::Property::Property(const std::string& key, const std::string& value) {
    this->setKey(key);
    this->setValue(value);
}

docpp::HTML::Property::Property(const std::pair<std::string, std::string>& property) {
    this->set(property);
}

std::string docpp::HTML::Property::getKey() const {
    return this->property.first;
}

std::string docpp::HTML::Property::getValue() const {
    return this->property.second;
}

std::pair<std::string, std::string> docpp::HTML::Property::get() const {
    return this->property;
}

void docpp::HTML::Property::setKey(const std::string& key) {
    this->property.first = key;
}

void docpp::HTML::Property::setValue(const std::string& value) {
    this->property.second = value;
}

void docpp::HTML::Property::set(const std::pair<std::string, std::string>& property) {
    this->property = property;
}

docpp::HTML::Properties::Properties(const std::vector<docpp::HTML::Property>& properties) {
    this->set(properties);
}

docpp::HTML::Properties::Properties(const docpp::HTML::Property& property) {
    this->push_back(property);
}

docpp::HTML::Properties docpp::HTML::Properties::operator=(const docpp::HTML::Property& property) {
    this->properties = {property};
    return *this;
}

docpp::HTML::Properties docpp::HTML::Properties::operator=(const docpp::HTML::Properties& properties) {
    this->set(properties.getProperties());
    return *this;
}

docpp::HTML::Properties docpp::HTML::Properties::operator=(const std::vector<docpp::HTML::Property>& properties) {
    this->set(properties);
    return *this;
}

void docpp::HTML::Properties::operator+=(const docpp::HTML::Property& property) {
    this->push_back(property);
}

std::vector<docpp::HTML::Property> docpp::HTML::Properties::getProperties() const {
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
        if (!this->properties.at(i).getKey().compare(property.getKey())) {
            return i;
        } else if (!this->properties.at(i).getValue().compare(property.getValue())) {
            return i;
        } else if (this->properties.at(i).getValue().find(property.getValue()) != std::string::npos) {
            return i;
        } else if (this->properties.at(i).getKey().find(property.getKey()) != std::string::npos) {
            return i;
        } else if (this->properties.at(i).get() == property.get()) {
            return i;
        }
    }

    return docpp::HTML::Properties::npos;
}

docpp::HTML::Properties::size_type docpp::HTML::Properties::find(const std::string& str) {
    for (size_type i{0}; i < this->properties.size(); i++) {
        if (!this->properties.at(i).getKey().compare(str) || !this->properties.at(i).getValue().compare(str)) {
            return i;
        } else if (this->properties.at(i).getKey().find(str) != std::string::npos || this->properties.at(i).getValue().find(str) != std::string::npos) {
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

void docpp::HTML::Properties::swap(const size_type index1, const size_type index2) {
    if (index1 < 0 || index1 >= this->properties.size() || index2 < 0 || index2 >= this->properties.size()) {
        throw docpp::out_of_range("Index out of range");
    }

    std::swap(this->properties[index1], this->properties[index2]);
}

void docpp::HTML::Properties::swap(const docpp::HTML::Property& property1, const docpp::HTML::Property& property2) {
    this->swap(this->find(property1), this->find(property2));
}

docpp::HTML::Element::Element(const std::string& tag, const Properties& properties, const std::string& data, const int type) {
    this->set(tag, properties, data, type);
}

docpp::HTML::Element docpp::HTML::Element::operator=(const docpp::HTML::Element& element) {
    this->set(element.getTag(), element.properties, element.getData(), element.type);
    return *this;
}

void docpp::HTML::Element::operator+=(const std::string& data) {
    this->data += data;
}

void docpp::HTML::Element::set(const std::string& tag, const Properties& properties, const std::string& data, const int type) {
    this->tag = tag;
    this->data = data;
    this->properties = properties;
    this->type = type;
}

std::string docpp::HTML::Element::get(const int formatting, const int tabc) const {
    std::string ret{};

    if (this->type == docpp::HTML::TYPE_TEXT) {
        return this->data;
    } else if (this->type == docpp::HTML::TYPE_TEXT_TAB) {
        for (size_type i{0}; i < tabc; i++) {
            ret += "\t";
        }

        return ret + this->data;
    }

    if (formatting == docpp::HTML::FORMATTING_PRETTY) {
        for (size_type i{0}; i < tabc; i++) {
            ret += "\t";
        }
    }

    ret += "<" + this->tag;

    for (const auto& it : this->properties.getProperties()) {
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

    if (formatting == docpp::HTML::FORMATTING_PRETTY || formatting == docpp::HTML::FORMATTING_NEWLINE) {
        ret += "\n";
    }

    return std::move(ret);
}

std::string docpp::HTML::Element::getTag() const {
    return this->tag;
}

std::string docpp::HTML::Element::getData() const {
    return this->data;
}

docpp::HTML::Section::Section(const std::string& tag, const Properties& properties) {
    this->tag = tag;
    this->properties = properties;
}

docpp::HTML::Section docpp::HTML::Section::operator=(const docpp::HTML::Section& section) {
    this->tag = section.tag;
    this->properties = section.properties;
    this->elements = section.elements;
    this->sections = section.sections;
    this->index = section.index;

    return *this;
}

void docpp::HTML::Section::operator+=(const docpp::HTML::Element& element) {
    this->push_back(element);
}

void docpp::HTML::Section::operator+=(const docpp::HTML::Section& section) {
    this->push_back(section);
}

docpp::HTML::Element docpp::HTML::Section::operator[](const int& index) const {
    return this->at(index);
}

docpp::HTML::Section::Section(const int tag, const Properties& properties) {
    this->set(tag, properties);
}

void docpp::HTML::Section::set(const std::string& tag, const Properties& properties) {
    this->tag = tag;
    this->properties = properties;
}

void docpp::HTML::Section::set(const int tag, const Properties& properties) {
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
        const auto it = this->getSections().at(i);

        if (it.get() == section.get()) {
            this->erase(i);
            return;
        }
    }

    throw docpp::out_of_range("Section not found");
}

void docpp::HTML::Section::erase(const Element& element) {
    for (size_type i{0}; i < this->size(); i++) {
        const auto it = this->getElements().at(i);

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
        const auto it = this->getElements().at(i);

        if (it.get() == element.get()) {
            return i;
        }
    }

    return docpp::HTML::Section::npos;
}

docpp::HTML::Section::size_type docpp::HTML::Section::find(const Section& section) {
    for (size_type i{0}; i < this->size(); i++) {
        const auto it = this->getSections().at(i);

        if (it.get() == section.get()) {
            return i;
        }
    }

    return docpp::HTML::Section::npos;
}

docpp::HTML::Section::size_type docpp::HTML::Section::find(const std::string& str) {
    const auto elements = this->getElements();

    for (size_type i{0}; i < elements.size(); i++) {
        if (!elements.at(i).get().compare(str)) {
            return i;
        }
    }

    const auto sections = this->getSections();

    for (size_type i{0}; i < sections.size(); i++) {
        if (!sections.at(i).get().compare(str)) {
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

std::vector<docpp::HTML::Element> docpp::HTML::Section::getElements() const {
    std::vector<docpp::HTML::Element> ret{};
    ret.reserve(this->index);
    for (size_type i{0}; i < this->index; i++) {
        if (this->elements.find(i) != this->elements.end()) {
            ret.push_back(this->elements.at(i));
        }
    }
    return std::move(ret);
}

std::vector<docpp::HTML::Section> docpp::HTML::Section::getSections() const {
    std::vector<docpp::HTML::Section> ret{};
    ret.reserve(this->index);

    for (size_type i{0}; i < this->index; i++) {
        if (this->sections.find(i) != this->sections.end()) {
            ret.push_back(this->sections.at(i));
        }
    }

    return std::move(ret);
}

std::string docpp::HTML::Section::get(const int formatting, const int tabc) const {
    std::string ret{};
    int tabcount{tabc};

    if (!this->tag.compare("")) {
        --tabcount; // i guess this means the section only contains elements and sections, and isn't a tag itself

        if (tabcount < -1) {
            tabcount = -1; // will be incremented by 1, so it will be 0
        }
    }

    if (formatting == docpp::HTML::FORMATTING_PRETTY) {
        for (size_type i{0}; i < tabcount; i++) {
            ret += "\t";
        }
    }

    if (this->tag.compare("")) {
        ret += "<" + this->tag;

        for (const auto& it : this->properties.getProperties()) {
            if (!it.getKey().compare("")) continue;
            if (!it.getValue().compare("")) continue;

            ret += " " + it.getKey() + "=\"" + it.getValue() + "\"";
        }

        ret += ">";

        if (formatting == docpp::HTML::FORMATTING_PRETTY || formatting == docpp::HTML::FORMATTING_NEWLINE) {
            ret += "\n";
        }
    }

    for (size_type i{0}; i < this->index; i++) {
        if (this->elements.find(i) != this->elements.end()) {
            ret += this->elements.at(i).get(formatting, tabcount + 1);
        } else if (this->sections.find(i) != this->sections.end()) {
            ret += this->sections.at(i).get(formatting, tabcount + 1);

            if (formatting == docpp::HTML::FORMATTING_PRETTY || formatting == docpp::HTML::FORMATTING_NEWLINE) {
                ret += "\n";
            }
        }
    }

    if (formatting == docpp::HTML::FORMATTING_PRETTY) {
        for (size_type i{0}; i < tabcount; i++) {
            ret += "\t";
        }
    }

    ret += this->tag.compare("") ? ("</" + this->tag + ">") : "";

    return std::move(ret);
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

std::string docpp::HTML::Document::get(const int formatting, const int tabc) const {
    return this->doctype + (formatting == FORMATTING_PRETTY ? "\n" : formatting == FORMATTING_NEWLINE ? "\n" : "") + this->document.get(formatting, tabc);
}

docpp::HTML::Section& docpp::HTML::Document::getSection() {
    return this->document;
}

void docpp::HTML::Document::set(const docpp::HTML::Section& document) {
    this->document = document;
}

void docpp::HTML::Document::setDoctype(const std::string& doctype) {
    this->doctype = doctype;
}

docpp::HTML::Document docpp::HTML::Document::operator=(const docpp::HTML::Document& document) {
    this->set(document.get());
    this->setDoctype(document.getDoctype());
    return *this;
}

docpp::HTML::Document docpp::HTML::Document::operator=(const docpp::HTML::Section& section) {
    this->set(section);
    return *this;
}

docpp::HTML::Document::Document(const docpp::HTML::Section& document, const std::string& doctype) {
    this->set(document);
    this->setDoctype(doctype);
}

std::string docpp::HTML::Document::getDoctype() const {
    return this->doctype;
}

docpp::CSS::Property::Property(const std::string& key, const std::string& value) {
    this->set(key, value);
}

docpp::CSS::Property::Property(const std::pair<std::string, std::string>& property) {
    this->set(property);
}

std::string docpp::CSS::Property::getKey() const {
    return this->property.first;
}

std::string docpp::CSS::Property::getValue() const {
    return this->property.second;
}

std::pair<std::string, std::string> docpp::CSS::Property::get() const {
    return this->property;
}

void docpp::CSS::Property::setKey(const std::string& key) {
    this->property.first = key;
}

void docpp::CSS::Property::setValue(const std::string& value) {
    this->property.second = value;
}

void docpp::CSS::Property::set(const std::pair<std::string, std::string>& property) {
    this->property = property;
}

void docpp::CSS::Property::set(const std::string& key, const std::string& value) {
    this->property = std::make_pair(key, value);
}

docpp::CSS::Property docpp::CSS::Property::operator=(const docpp::CSS::Property& property) {
    this->set(property.get());
    return *this;
}

docpp::CSS::Property docpp::CSS::Property::operator=(const std::pair<std::string, std::string>& property) {
    this->set(property);
    return *this;
}

docpp::CSS::Element::Element(const std::string& tag, const std::vector<Property>& properties) {
    this->set(tag, properties);
}

docpp::CSS::Element::Element(const std::pair<std::string, std::vector<Property>>& element) {
    this->set(element);
}

docpp::CSS::Element docpp::CSS::Element::operator=(const docpp::CSS::Element& element) {
    this->set({element.getTag(), element.getProperties()});
    return *this;
}

void docpp::CSS::Element::operator+=(const Property& property) {
    this->push_back(property);
}

docpp::CSS::Property docpp::CSS::Element::operator[](const int& index) const {
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
        if (!this->element.second.at(i).getKey().compare(str) || !this->element.second.at(i).getValue().compare(str)) {
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

std::string docpp::CSS::Element::get(const int formatting, const int tabc) const {
    std::string ret{};

    if (this->element.first.compare("")) {
        ret += this->element.first + " {";

        if (formatting == docpp::CSS::FORMATTING_PRETTY || formatting == docpp::CSS::FORMATTING_NEWLINE) {
            ret += "\n";
        }

        for (const auto& it : this->element.second) {
            if (!it.getKey().compare("")) continue;
            if (!it.getValue().compare("")) continue;

            if (formatting == docpp::CSS::FORMATTING_PRETTY) {
                for (size_type i{0}; i < tabc + 1; i++) {
                    ret += "\t";
                }
            }

            ret += it.getKey() + ": " + it.getValue() + ";";

            if (formatting == docpp::CSS::FORMATTING_PRETTY || formatting == docpp::CSS::FORMATTING_NEWLINE) {
                ret += "\n";
            }
        }

        ret += "}";

        if (formatting == docpp::CSS::FORMATTING_PRETTY || formatting == docpp::CSS::FORMATTING_NEWLINE) {
            ret += "\n";
        }
    }

    return std::move(ret);
}

std::string docpp::CSS::Element::getTag() const {
    return this->element.first;
}

std::vector<docpp::CSS::Property> docpp::CSS::Element::getProperties() const {
    return this->element.second;
}

docpp::CSS::Stylesheet::Stylesheet(const std::vector<Element>& elements) {
    this->set(elements);
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

docpp::CSS::Stylesheet docpp::CSS::Stylesheet::operator=(const docpp::CSS::Stylesheet& stylesheet) {
    this->set(stylesheet.getElements());
    return *this;
}

void docpp::CSS::Stylesheet::operator+=(const Element& element) {
    this->push_back(element);
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
        if (!this->elements.at(i).get().compare(str) || !this->elements.at(i).getTag().compare(str)) {
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

std::vector<docpp::CSS::Element> docpp::CSS::Stylesheet::getElements() const {
    return this->elements;
}

std::string docpp::CSS::Stylesheet::get(const int formatting, const int tabc) const {
    std::string ret{};

    for (const auto& it : this->elements) {
        ret += it.get(formatting, tabc);
    }

    return std::move(ret);
}
