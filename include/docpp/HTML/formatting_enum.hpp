/*
 * docpp - C++ library for generating HTML, CSS and SGML-like documents.
 *
 * SPDX-License-Identifier: LGPL-3.0-or-later
 * Copyright (c) 2024 speedie <speedie@speedie.site>
 */
#pragma once

/**
 * @brief A namespace to represent HTML elements and documents
 */
namespace docpp {
    /**
     * @brief A namespace to represent HTML elements and documents
     */
    namespace HTML {
        /**
         * @brief Enum for formatting options.
         */
        enum class Formatting {
            None, /* No formatting. Output is in the form of one long string of text, and a single newline character. */
            Pretty, /* Pretty formatting. Output is formatted with newlines and tabs as deemed appropriate. */
            Newline, /* Newline formatting. Each element has a newline appended. */
        };
    } // namespace HTML
} // namespace docpp
