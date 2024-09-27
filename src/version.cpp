/*
 * docpp - C++ library for generating HTML, CSS and SGML-like documents.
 *
 * SPDX-License-Identifier: LGPL-3.0-or-later
 * Copyright (c) 2024 speedie <speedie@speedie.site>
 */

#include <docpp/version.hpp>

std::tuple<docpp::integer_type, docpp::integer_type, docpp::integer_type> docpp::version() {
#ifdef DOCPP_VERSION
    docpp::string_type version{DOCPP_VERSION};

    if (version.find('.') != docpp::string_type::npos) {
        docpp::string_type major = version.substr(0, version.find('.'));
        version = version.substr(version.find('.') + 1);

        if (version.find('.') != docpp::string_type::npos) {
            docpp::string_type minor = version.substr(0, version.find('.'));
            version = version.substr(version.find('.') + 1);

            if (version.find('.') != docpp::string_type::npos) {
                docpp::string_type patch = version.substr(0, version.find('.'));
                return {std::stoi(major), std::stoi(minor), std::stoi(patch)};
            }
        }
    }
#endif
    return {};
}
