/**
 * @file biteme.lol.cpp
 * @brief A simple program that replicates biteme.lol using docpp.
 * @details This program creates a simple HTML document that replicates the biteme.lol website.
 * @see https://biteme.lol
 * @license LGPL-3.0
 *
 * g++ -std=c++11 biteme.lol.cpp -o biteme.lol -ldocpp
 */
#include <fstream>
#include <docpp/docpp.hpp>

int main() {
    docpp::HTML::HTMLSection html(docpp::HTML::SECTION_HTML, {});

    html.push_back({"title", {}, "Google"});

    docpp::CSS::CSSStylesheet sheet{};

    sheet.push_back(docpp::CSS::CSSElement(
        ".center", {
            {"display", "flex"},
            {"flex-wrap", "wrap"},
            {"justify-content", "center"},
            {"align-items", "center"},
            {"font-size", "10vw"},
            {"height", "10vw"},
            {"padding", "10vw"},
        }
    ));

    sheet.push_back(docpp::CSS::CSSElement(
        "input[type=text], select", {
            {"width", "50vw"},
        }
    ));

    html.push_back({"style", {}, sheet.get(docpp::CSS::FORMATTING_PRETTY)});

    docpp::HTML::HTMLSection div{docpp::HTML::SECTION_DIV, {docpp::HTML::HTMLProperty("class", "center")}};

    div.push_back({"font", {docpp::HTML::HTMLProperty("color", "blue")}, "G"});
    div.push_back({"font", {docpp::HTML::HTMLProperty("color", "red")}, "o"});
    div.push_back({"font", {docpp::HTML::HTMLProperty("color", "yellow")}, "o"});
    div.push_back({"font", {docpp::HTML::HTMLProperty("color", "blue")}, "g"});
    div.push_back({"font", {docpp::HTML::HTMLProperty("color", "green")}, "l"});
    div.push_back({"font", {docpp::HTML::HTMLProperty("color", "red")}, "e"});

    html.push_back(div);

    docpp::HTML::HTMLSection div2{docpp::HTML::SECTION_DIV, {docpp::HTML::HTMLProperty("align", "center")}};
    docpp::HTML::HTMLSection form{"form", {{docpp::HTML::HTMLProperty("action", "https://google.com/search"), docpp::HTML::HTMLProperty("method", "get")}}};

    form.push_back({"input", docpp::HTML::HTMLProperties({docpp::HTML::HTMLProperty("type", "text"), docpp::HTML::HTMLProperty("name", "q")}), "", docpp::HTML::TYPE_SELF_CLOSING});
    form.push_back({"input", docpp::HTML::HTMLProperties({docpp::HTML::HTMLProperty("type", "submit"), docpp::HTML::HTMLProperty("value", "Search!")}), "", docpp::HTML::TYPE_SELF_CLOSING});

    div2.push_back(form);
    html.push_back(div2);

    docpp::HTML::HTMLDocument doc{html};

    std::ofstream file("biteme.lol.html");

    file << doc.get(docpp::HTML::FORMATTING_PRETTY);

    file.close();

    return 0;
}
