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
         * @brief Enum for element types.
         */
        enum class Type {
            Self_Closing, /* Self-closing element (<tag ... /> - Primarily useful for XHTML or HTML written by perfectionists) */
            Non_Self_Closing, /* Non-self-closing element (<tag></tag>) */
            Non_Closed, /* Non-closed element (<tag> - Invalid in XHTML) */
            Non_Opened, /* Non-opened element (</tag>) */
            Text_No_Formatting, /* Text element with no formatting (my text here). */
            Text, /* Text element with tab characters appropriately prepended (my text here). Note that this does *not* append a newline character. */
        };
    }
} // namespace docpp
