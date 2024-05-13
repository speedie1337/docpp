#include <string>
#include <include/docpp.hpp>
#include <src/docpp.cpp>
#include <catch2/catch_test_macros.hpp>

/**
 * @brief Test cases for the docpp namespace.
 */
SCENARIO("Test HTML", "[HTML]") {
    const auto test1 = []() {
        docpp::HTML::Document doc{};
        docpp::HTML::Section html(docpp::HTML::SECTION_HTML, {});

        docpp::HTML::Section head(docpp::HTML::SECTION_HEAD, {});
        docpp::HTML::Section body(docpp::HTML::SECTION_BODY, {});
        docpp::HTML::Section div(docpp::HTML::SECTION_DIV, {});
        docpp::HTML::Section footer(docpp::HTML::SECTION_FOOTER, {});

        head.push_back(docpp::HTML::Element("title", {}, "Test Title"));
        body.push_back(docpp::HTML::Element("h1", {}, "Test Header"));
        body.push_back(docpp::HTML::Element("p", {}, "Test Paragraph"));

        docpp::HTML::Properties prop{};
        prop.push_back(docpp::HTML::Property(std::pair<std::string, std::string>("id", "test_id")));

        body.push_back(docpp::HTML::Element("p", prop, "Test Paragraph With ID"));

        div.push_back(docpp::HTML::Element("p", {}, "Test Paragraph In Div"));
        body.push_back(div);

        prop.push_back(docpp::HTML::Property(std::pair<std::string, std::string>("class", "class1 class2 class3")));

        body.push_back(docpp::HTML::Element("p", prop, "Test Paragraph With ID And Class"));

        html.push_back(head);
        html.push_back(body);
        html.push_back(footer);

        doc.set(html);

        const std::string expected_html{"<!DOCTYPE html><html><head><title>Test Title</title></head><body><h1>Test Header</h1><p>Test Paragraph</p><p id=\"test_id\">Test Paragraph With ID</p><div><p>Test Paragraph In Div</p></div><p id=\"test_id\" class=\"class1 class2 class3\">Test Paragraph With ID And Class</p></body><footer></footer></html>"};

        REQUIRE(doc.get() == expected_html);
        REQUIRE(doc.get(docpp::HTML::FORMATTING_NEWLINE) == "<!DOCTYPE html>\n<html>\n<head>\n<title>Test Title</title>\n</head>\n<body>\n<h1>Test Header</h1>\n<p>Test Paragraph</p>\n<p id=\"test_id\">Test Paragraph With ID</p>\n<div>\n<p>Test Paragraph In Div</p>\n</div>\n<p id=\"test_id\" class=\"class1 class2 class3\">Test Paragraph With ID And Class</p>\n</body>\n<footer>\n</footer>\n</html>");
    };

    const auto test2 = []() {
        docpp::HTML::Section section(docpp::HTML::SECTION_HTML, {});

        section.push_back(docpp::HTML::Element("p", {}, "Test 1"));
        section.push_back(docpp::HTML::Element("p", {}, "Test 2"));
        section.push_back(docpp::HTML::Element("p", {}, "Test 3"));

        section.erase(docpp::HTML::Element("p", {}, "Test 2"));

        REQUIRE(section.get() == "<html><p>Test 1</p><p>Test 3</p></html>");
        REQUIRE(section.get(docpp::HTML::FORMATTING_NEWLINE) == "<html>\n<p>Test 1</p>\n<p>Test 3</p>\n</html>");
    };

    const auto test3 = []() {
        docpp::HTML::Section section = docpp::HTML::Section(docpp::HTML::SECTION_HTML, {});

        section.push_back(docpp::HTML::Element("p", {}, "Test 1"));
        section.push_back(docpp::HTML::Element("p", {}, "Test 2"));
        section.push_back(docpp::HTML::Element("p", {}, "Test 3"));

        std::size_t pos = section.find(docpp::HTML::Element("p", {}, "Test 2"));
        section.insert(pos, docpp::HTML::Element("p", {}, "Test 2.5"));

        REQUIRE(section.get() == "<html><p>Test 1</p><p>Test 2.5</p><p>Test 3</p></html>");
        REQUIRE(section.get(docpp::HTML::FORMATTING_NEWLINE) == "<html>\n<p>Test 1</p>\n<p>Test 2.5</p>\n<p>Test 3</p>\n</html>");
    };

    const auto test4 = []() {
        docpp::HTML::Section section = docpp::HTML::Section(docpp::HTML::SECTION_HTML, {});

        section.push_back(docpp::HTML::Element("p", {}, "Test 1"));
        section.push_back(docpp::HTML::Element("p", {}, "Test 2"));
        section.push_back(docpp::HTML::Element("p", {}, "Test 3"));

        std::size_t pos = section.find(docpp::HTML::Element("p", {}, "Test 2"));

        section.erase(pos);

        REQUIRE(section.get() == "<html><p>Test 1</p><p>Test 3</p></html>");
        REQUIRE(section.get(docpp::HTML::FORMATTING_NEWLINE) == "<html>\n<p>Test 1</p>\n<p>Test 3</p>\n</html>");
    };

    const auto test5 = []() {
        docpp::HTML::Section section = docpp::HTML::Section(docpp::HTML::SECTION_HTML, {});
        docpp::HTML::Section subsection(docpp::HTML::SECTION_DIV, {});

        subsection.push_back(docpp::HTML::Element("p", {}, "Test 1"));

        docpp::HTML::Section subsection2(docpp::HTML::SECTION_DIV, {});
        subsection2.push_back(docpp::HTML::Element("p", {}, "Test 2"));

        subsection.push_back(subsection2);

        section.push_back(subsection);

        docpp::HTML::Document doc{};
        doc.set(section);

        REQUIRE(doc.get() == "<!DOCTYPE html><html><div><p>Test 1</p><div><p>Test 2</p></div></div></html>");
        REQUIRE(doc.get(docpp::HTML::FORMATTING_NEWLINE) == "<!DOCTYPE html>\n<html>\n<div>\n<p>Test 1</p>\n<div>\n<p>Test 2</p>\n</div>\n</div>\n</html>");
    };

    const auto test6 = []() {
        docpp::CSS::Stylesheet css{};
        docpp::CSS::Element element{"p", {{"color", "red"}, {"font-size", "16px"}, {"font-family", "Arial"}}};

        css.push_back(element);

        REQUIRE(css.get() == "p {color: red;font-size: 16px;font-family: Arial;}");
        REQUIRE(css.get(docpp::CSS::FORMATTING_NEWLINE) == "p {\ncolor: red;\nfont-size: 16px;\nfont-family: Arial;\n}\n");
    };

    const auto test7 = []() {
        docpp::CSS::Stylesheet css = docpp::CSS::Stylesheet{};
        docpp::CSS::Element element = docpp::CSS::Element{"p", {{"color", "red"}, {"font-size", "16px"}, {"font-family", "Arial"}}};
        docpp::CSS::Element element2{"div", {{"color", "blue"}, {"font-size", "12px"}, {"font-family", "Arial"}}};

        css.push_back(element);
        css.push_front(element2);

        REQUIRE(css.get() == "div {color: blue;font-size: 12px;font-family: Arial;}p {color: red;font-size: 16px;font-family: Arial;}");
    };

    const auto test8 = []() {
        docpp::CSS::Stylesheet css = docpp::CSS::Stylesheet{};
        docpp::CSS::Element element = docpp::CSS::Element{"p", {{"color", "red"}, {"font-size", "16px"}, {"font-family", "Arial"}}};
        docpp::CSS::Element element2{"div", {{"color", "blue"}, {"font-size", "12px"}, {"font-family", "Arial"}}};

        css.push_back(element);
        css.push_front(element2);

        css.erase(css.find(element2));

        REQUIRE(css.get() == "p {color: red;font-size: 16px;font-family: Arial;}");
    };

    const auto test9 = []() {
        docpp::CSS::Stylesheet css = docpp::CSS::Stylesheet{};
        docpp::CSS::Element element = docpp::CSS::Element{"p", {{"color", "red"}, {"font-size", "16px"}, {"font-family", "Arial"}}};
        docpp::CSS::Element element2{"div", {{"color", "blue"}, {"font-size", "12px"}, {"font-family", "Arial"}}};

        css.push_back(element);
        css.push_front(element2);

        css.erase(css.find(element2));
        css.push_front(element2);

        css.swap(css.find(element), css.find(element2));

        REQUIRE(css.get() == "p {color: red;font-size: 16px;font-family: Arial;}div {color: blue;font-size: 12px;font-family: Arial;}");

        element.push_front(docpp::CSS::Property("font-weight", "bold"));

        REQUIRE(element.get() == "p {font-weight: bold;color: red;font-size: 16px;font-family: Arial;}");
    };

    const auto test10 = []() {
        docpp::HTML::Section section = docpp::HTML::Section(docpp::HTML::SECTION_HTML, {});

        section.push_back(docpp::HTML::Element("p", {}, "Test 1"));
        section.push_back(docpp::HTML::Element("p", {}, "Test 2"));
        section.push_back(docpp::HTML::Element("p", {}, "Test 3"));

        section.swap(section.find(docpp::HTML::Element("p", {}, "Test 2")), section.find(docpp::HTML::Element("p", {}, "Test 3")));

        REQUIRE(section.get() == "<html><p>Test 1</p><p>Test 3</p><p>Test 2</p></html>");
    };

    const auto test11 = []() {
        docpp::HTML::Section section = docpp::HTML::Section(docpp::HTML::SECTION_HTML, {});

        section.push_back(docpp::HTML::Element("p", {}, "Test 1"));
        section.push_back(docpp::HTML::Element("p", {}, "Test 2"));
        section.push_back(docpp::HTML::Element("p", {}, "Test 3"));

        section.swap(docpp::HTML::Element("p", {}, "Test 2"), docpp::HTML::Element("p", {}, "Test 3"));

        REQUIRE(section.get() == "<html><p>Test 1</p><p>Test 3</p><p>Test 2</p></html>");
    };

    const auto test12 = []() {
        docpp::HTML::Section section = docpp::HTML::Section(docpp::HTML::SECTION_HTML, {});

        section.push_back(docpp::HTML::Element("p", {}, "Test 1"));
        section.push_back(docpp::HTML::Element("p", {}, "Test 2"));
        section.push_back(docpp::HTML::Element("p", {}, "Test 3"));

        section.push_front(docpp::HTML::Element("p", {}, "Test 0"));

        REQUIRE(section.get() == "<html><p>Test 0</p><p>Test 1</p><p>Test 2</p><p>Test 3</p></html>");
    };

    const auto test13 = []() {
        docpp::HTML::Section section = docpp::HTML::Section(docpp::HTML::SECTION_HTML, {});

        section.push_back(docpp::HTML::Element("p", {}, "Test 1"));
        section.push_back(docpp::HTML::Element("p", {}, "Test 2"));
        section.push_back(docpp::HTML::Element("p", {}, "Test 3"));
        section.push_back(docpp::HTML::Element("p", {}, "Test 4"));
        section.push_back(docpp::HTML::Element("p", {}, "Test 5"));
        section.push_back(docpp::HTML::Element("p", {}, "Test 6"));

        const std::size_t pos{section.find("<p>Test 2</p>")};

        REQUIRE(pos != docpp::HTML::Section::npos);

        const std::size_t pos2{section.find("<p>Test 6</p>")};

        section.erase(pos);
        section.erase(pos2);

        REQUIRE(section.get() == "<html><p>Test 1</p><p>Test 3</p><p>Test 4</p><p>Test 5</p></html>");
    };

    const auto test14 = []() {
        docpp::CSS::Element element{"p", {{"color", "red"}, {"font-size", "16px"}, {"font-family", "Arial"}}};

        const int red = element.find("color");

        REQUIRE(red != docpp::CSS::Element::npos);

        const int blue = element.find("blue");

        REQUIRE(blue == docpp::CSS::Element::npos);

        element.erase(red);

        REQUIRE(element.get() == "p {font-size: 16px;font-family: Arial;}");

        element.insert(red, docpp::CSS::Property("color", "red"));

        REQUIRE(element.get() == "p {color: red;font-size: 16px;font-family: Arial;}");
    };

    const auto test15 = []() {
        docpp::HTML::Properties prop{};

        prop.push_back(docpp::HTML::Property(std::pair<std::string, std::string>("id", "test_id")));
        prop.push_back(docpp::HTML::Property(std::pair<std::string, std::string>("class", "class1 class2 class3")));

        REQUIRE(docpp::HTML::Element("p", prop, {}).get() == "<p id=\"test_id\" class=\"class1 class2 class3\"></p>");

        const int pos = prop.find("class");

        REQUIRE(pos != docpp::HTML::Properties::npos);

        const int pos2 = prop.find("class2");

        REQUIRE(prop.at(pos2).get_key() == "class");
        REQUIRE(prop.at(pos2).get_value() == "class1 class2 class3");

        REQUIRE(pos2 != docpp::HTML::Properties::npos);

        const int pos3 = prop.find("class4");

        REQUIRE(pos3 == docpp::HTML::Properties::npos);

        prop.erase(pos);

        REQUIRE(docpp::HTML::Element("p", prop, {}).get() == "<p id=\"test_id\"></p>");
    };

    const auto test16 = []() {
        docpp::HTML::Document doc = docpp::HTML::Section({});

        doc.get_section().push_back(docpp::HTML::Element("p", {}, "Test 1"));
        doc.get_section().push_back(docpp::HTML::Element("p", {}, "Test 2"));
        doc.get_section().push_back(docpp::HTML::Element("p", {}, "Test 3"));

        doc.get_section() = docpp::HTML::Section(docpp::HTML::SECTION_HTML, {});

        doc.get_section().push_back(docpp::HTML::Element("p", {}, "Test 4"));
        doc.get_section().push_back(docpp::HTML::Element("p", {}, "Test 5"));
        doc.get_section().push_back(docpp::HTML::Element("p", {}, "Test 6"));

        doc.get_section() += docpp::HTML::Element("p", {}, "Test 7");

        REQUIRE(doc.get() == "<!DOCTYPE html><html><p>Test 4</p><p>Test 5</p><p>Test 6</p><p>Test 7</p></html>");
    };

    const auto test17 = []() {
        docpp::HTML::Section section = docpp::HTML::Section(docpp::HTML::SECTION_HTML, {});

        section.push_back(docpp::HTML::Element("p", {}, "Test 1"));
        section.push_back(docpp::HTML::Element("p", {}, "Test 2"));
        section.push_back(docpp::HTML::Element("p", {}, "Test 3"));

        docpp::HTML::Document doc{section};

        REQUIRE(doc.get(docpp::HTML::FORMATTING_PRETTY) == "<!DOCTYPE html>\n<html>\n\t<p>Test 1</p>\n\t<p>Test 2</p>\n\t<p>Test 3</p>\n</html>");
    };

    const auto test18 = []() {
        docpp::HTML::Section section = docpp::HTML::Section(docpp::HTML::SECTION_EMPTY, {});

        section.push_back(docpp::HTML::Element("p", {}, "Test 1"));
        section.push_back(docpp::HTML::Element("p", {}, "Test 2"));
        section.push_back(docpp::HTML::Element("p", {}, "Test 3"));

        REQUIRE(section.get() == "<p>Test 1</p><p>Test 2</p><p>Test 3</p>");
    };

    const auto test19 = []() {
        docpp::HTML::Section section = docpp::HTML::Section(docpp::HTML::SECTION_HTML, {});

        section.push_back(docpp::HTML::Element("p", {}, "Test 1"));
        section.push_back(docpp::HTML::Element("p", {}, "Test 2"));
        section.push_back(docpp::HTML::Element("p", {}, "Test 3"));

        REQUIRE(section.front().get() == "<p>Test 1</p>");
        REQUIRE(section.back().get() == "<p>Test 3</p>");
    };

    const auto test20 = []() {
        docpp::HTML::Properties prop{};

        prop.push_back(docpp::HTML::Property(std::pair<std::string, std::string>("id", "test_id")));
        prop.push_back(docpp::HTML::Property(std::pair<std::string, std::string>("class", "class1 class2 class3")));
        prop.push_back(docpp::HTML::Property(std::pair<std::string, std::string>("style", "color: red; font-size: 16px; font-family: Arial;")));

        for (const docpp::HTML::Property& p : prop) {
            REQUIRE(p.get_key() == "id");
            REQUIRE(p.get_value() == "test_id");
            break;
        }

        for (docpp::HTML::Properties::iterator it = ++prop.begin(); it != prop.end(); ++it) {
            REQUIRE(it->get_key() == "class");
            REQUIRE(it->get_value() == "class1 class2 class3");
            break;
        }
    };

    const auto test21 = []() {
        docpp::HTML::Section sect{};

        sect.push_back(docpp::HTML::Element("p", {}, "Test 1"));
        sect.push_back(docpp::HTML::Element("p", {}, "Test 2"));
        sect.push_back(docpp::HTML::Element("p", {}, "Test 3"));

        for (const docpp::HTML::Element& elem : sect) {
            REQUIRE(elem.get() == "<p>Test 1</p>");
            break;
        }

        for (docpp::HTML::Section::iterator it = ++sect.begin(); it != sect.end(); ++it) {
            docpp::HTML::Element elem = *it;
            REQUIRE(elem.get() == "<p>Test 2</p>");
            break;
        }
    };

    const auto test22 = []() {
        docpp::HTML::Section sect{};

        sect.push_back(docpp::HTML::Element("p", {}, "Test 1"));
        sect.push_back(docpp::HTML::Element("p", {}, "Test 2"));
        sect.push_back(docpp::HTML::Element("p", {}, "Test 3"));

        bool caught{false};
        try {
            sect.at(1337);
        } catch (const docpp::out_of_range& e) {
            caught = true;
        }

        REQUIRE(caught);
    };

    const auto test23 = []() {
        docpp::HTML::Section sect{};

        sect.push_back(docpp::HTML::Element("p", {}, "Test 1"));
        sect.push_back(docpp::HTML::Element("p", {}, "Test 2"));
        sect.push_back(docpp::HTML::Element("p", {}, "Test 3"));

        REQUIRE(sect.get<std::string>() == "<p>Test 1</p><p>Test 2</p><p>Test 3</p>");
    };

    std::vector<void (*)()> tests{
        test1,
        test2,
        test3,
        test4,
        test5,
        test6,
        test7,
        test8,
        test9,
        test10,
        test11,
        test12,
        test13,
        test14,
        test15,
        test16,
        test17,
        test18,
        test19,
        test20,
        test21,
        test22,
        test23,
    };

    for (const auto& test : tests) {
        test();
    }
}
