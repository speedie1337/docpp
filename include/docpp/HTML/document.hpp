/*
 * docpp - C++ library for generating HTML, CSS and SGML-like documents.
 *
 * SPDX-License-Identifier: LGPL-3.0-or-later
 * Copyright (c) 2024 speedie <speedie@speedie.site>
 */
#pragma once

#include <string>
#include <docpp/types.hpp>
#include <docpp/HTML/section.hpp>

/**
 * @brief A namespace to represent HTML elements and documents
 */
namespace docpp {
    /**
     * @brief A namespace to represent HTML elements and documents
     */
    namespace HTML {
        /**
         * @brief A class to represent an HTML document
         */
        class Document {
            private:
                Section document{};
                string_type doctype{"<!DOCTYPE html>"};
            protected:
            public:
                /**
                 * @brief The npos value
                 */
                static constexpr size_type npos = -1;

                /**
                 * @brief Get the document
                 * @param formatting The formatting type to use
                 * @param tabc Number of tab indents to start with, when using Formatting::Pretty
                 * @return string_type The document
                 */
                [[nodiscard]] string_type get(Formatting formatting = Formatting::None, integer_type tabc = 0) const;
                /**
                 * @brief Get the document in the form of a specific type.
                 * @return T The document in the form of a specific type
                 */
                template <typename T> T get(const Formatting formatting = Formatting::None, integer_type tabc = 0) const {
                    if (std::is_same_v<T, string_type>) {
                        return this->get(formatting, tabc);
                    }
                    return T(this->get(formatting, tabc));
                }
                /**
                 * @brief Get the section
                 * @return Section The section
                 */
                [[nodiscard]] Section get_section() const;
                /**
                 * @brief Get the section
                 * @return Section The section
                 */
                Section& get_section();
                /**
                 * @brief Get the doctype of the document
                 * @return string_type The doctype of the document
                 */
                [[nodiscard]] string_type get_doctype() const;
                /**
                 * @brief Get the doctype of the document in a specific type
                 * @return T The doctype of the document
                 */
                template <typename T> T get_doctype() const {
                    if (std::is_same_v<T, string_type>) {
                        return this->doctype;
                    }
                    return T(this->doctype);
                }

                /**
                 * @brief Set the document
                 * @param document The document to set
                 */
                void set(const Section& document);
                /**
                 * @brief Set the doctype of the document
                 * @param doctype The doctype to set
                 */
                void set_doctype(const string_type& doctype);
                /**
                 * @brief Get the size of the document
                 * @return size_type The size of the document
                 */
                [[nodiscard]] size_type size() const;
                /**
                 * @brief Check if the document is empty
                 */
                [[nodiscard]] bool empty() const;
                /**
                 * @brief Clear the document
                 */
                void clear();
                /**
                 * @brief Construct a new Document object
                 */
                Document() = default;
                /**
                 * @brief Destroy the Document object
                 */
                ~Document() = default;
                /**
                 * @brief Construct a new Document object
                 * @param document The section to be assigned to the document
                 * @param doctype The doctype to prepend at the top, before the section
                 */
                explicit Document(const Section& document, string_type doctype = "<!DOCTYPE html>") : document(document), doctype(std::move(doctype)) {};
                /**
                 * @brief Construct a new Document object
                 * @param document The document to set
                 */
                Document(const Document& document) = default;

                Document& operator=(const Document& document);
                Document& operator=(const Section& section);
                bool operator==(const Document& document) const;
                bool operator==(const Section& section) const;
                bool operator!=(const Document& document) const;
                bool operator!=(const Section& section) const;
        };
    } // namespace HTML
} // namespace docpp
