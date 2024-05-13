/**
 * @file hello-world.cpp
 * @brief A simple Hello World program, demonstrating the use of docpp.
 * @details This program creates a simple HTML document with a title, a meta description, a body with a div containing a header and a paragraph, and a footer with a paragraph. It also includes a CSS stylesheet that sets the background color of the body to black and the text color to white. It then writes the document to a file called hello-world.html.
 * @license LGPL-3.0
 *
 * g++ -std=c++11 hello-world.cpp -o hello-world -ldocpp
 */
#include <fstream>
#include <docpp/docpp.hpp>

int main() {
    /* This is your root document. It can hold *one* HTML section, and that section can hold any number of elements and/or sections.
     * By default, the root document will prepend a doctype declaration. If you don't want that (e.g., if you're writing XML), you can
     * use docpp::HTML::Document::set_doctype() to set the doctype to your preferred value.
     *
     * To get the document as an std::string object, call doc.get().
     */
    docpp::HTML::Document doc{};

    /* This is an HTML section. It can hold any number of elements and/or sections.
     * The first argument is the type of section, and this can either be a predefined value (e.g., docpp::HTML::SECTION_HTML) or a
     * custom value in the form of an std::string object.
     *
     * The second argument is an HTMLProperties object, which is a collection of Property objects. Each property is a std::pair of an
     * attribute name and an attribute value. If you don't want to specify any attributes, you can pass an empty ElementAttributes object.
     * If you need to change the tag and/or attributes later, you can use the set() method.
     *
     * Note that it is very important that you do not append a section or element to a section until you have finished its construction,
     * because push_back() makes a copy of the object you pass to it. If you need to make changes later, you can use methods such as find() and swap(),
     * or construct a new object. An alternative is to append using the += operator, which does the same thing as push_back().
     *
     * To get the section as an std::string object, call section.get().
     */
    docpp::HTML::Section htmlSection(docpp::HTML::SECTION_HTML, {}); // <html></html>
    docpp::HTML::Section headSection(docpp::HTML::SECTION_HEAD, {}); // <head></head>
    docpp::HTML::Section bodySection(docpp::HTML::SECTION_BODY, {}); // <body></body>
    docpp::HTML::Section footerSection(docpp::HTML::SECTION_FOOTER, {}); // <footer></footer>

    /* This is an HTML element. Unlike a section, an element cannot hold any other elements or sections, rather it holds text and/or attributes.
     * The first argument is the type of element, and this should simply be the tag name (e.g., "p", "h1", "a", etc.).
     *
     * The second argument is an HTMLProperties object, which is a collection of Property objects. Each property is a std::pair of an
     * attribute name and an attribute value. If you don't want to specify any attributes, you can pass an empty ElementAttributes object.
     * If you need to change the element's tag, attributes, type or text later, you can use the set() method.
     *
     * The third argument is the text content of the element. If you don't want to specify any text, you can pass an empty std::string object.
     *
     * The fourth argument is an integer representing the closing tag type. This can be one of the following:
     *
     * - docpp::HTML::TYPE_NON_CLOSED: No closing tag will be appended.
     *   Example: <img src="example.jpg">
     * - docpp::HTML::TYPE_NON_SELF_CLOSING: A closing tag will be appended.
     *   Example: <p>Hello world</p>
     * - docpp::HTML::TYPE_SELF_CLOSING: A self-closing tag will be appended.
     *   Example: <img src="example.jpg">
     *
     *  To get the element as an std::string object, call element.get().
     */
    docpp::HTML::Element titleElement("title", {}, "Hello world document"); // <title>Hello world document</title>

    /* Add the title and meta elements to the head section. */
    headSection.push_back(titleElement);
    headSection.push_back(docpp::HTML::Element("meta", {{docpp::HTML::Property("name", "description"), docpp::HTML::Property("content", "Hello world document description!")}}, "", docpp::HTML::TYPE_NON_CLOSED));

    /* This is a CSS document. It is essentially the CSS equivalent of an HTML section.
     * It is essentially a collection of Element objects, which is a collection of Property objects.
     *
     * In other words, a CSS document is a collection of CSS elements, which are collections of CSS properties.
     */
    docpp::CSS::Stylesheet stylesheet{};

    /* This is a CSS element. It is essentially a collection of CSS properties.
     * The first argument is the type of element, and this should simply be the tag name (e.g., "body", "p", "h1", etc.).
     *
     * The second argument is a CSSProperties object, which is a collection of Property objects. Each property is a std::pair of a
     * property name and a property value. If you don't want to specify any properties, you can pass an empty CSSProperties object, but... of course, that's not very useful.
     *
     * To get the element as an std::string object, call element.get().
     */
    docpp::CSS::Element bodyStyling("body", {{docpp::CSS::Property("background-color", "black"), docpp::CSS::Property("color", "white")}}); // body { background-color: black; color: white; }

    /* Now, let's add the body style to the stylesheet. */
    stylesheet.push_back(bodyStyling);

    /* To get the stylesheet as an std::string object, call stylesheet.get(). It can then be used in an Element object. */
    const std::string& css = stylesheet.get(docpp::CSS::FORMATTING_PRETTY); // body { background-color: black; color: white; }

    headSection.push_back(docpp::HTML::Element("style", {}, css)); // <style>body { background-color: black; color: white; }</style>

    /* Add a paragraph element to the footer section. */
    footerSection.push_back(docpp::HTML::Element("p", {}, "This is the footer.")); // <p>This is the footer.</p>

    docpp::HTML::Section divSection(docpp::HTML::SECTION_DIV, {{docpp::HTML::Property("id", "main")}}); // <div id="main"></div>

    /* Add a header element and a paragraph element to the div section. */
    divSection.push_back(docpp::HTML::Element("h1", {}, "Hello world!")); // <h1>Hello world!</h1>
    divSection.push_back(docpp::HTML::Element("p", {}, "This is a paragraph.")); // <p>This is a paragraph.</p>

    /* Add the div section to the body section. */
    bodySection.push_back(divSection);

    /* Now, let's add the header, body and footer section to the html section.
     * The order does matter, because an identifier is used internally. You can get this identifier by e.g. using find().
     */
    htmlSection.push_back(headSection); // <html><head>...</head></html>
    htmlSection.push_back(bodySection); // <html><head>...</head><body>...</body></html>
    htmlSection.push_back(footerSection); // <html><head>...</head><body>...</body><footer>...</footer></html>

    /* Now, let's add the html section to the document. */
    doc.set(htmlSection);

    /* Finally, let's output the document to a file and print it to standard output. */
    std::ofstream file("hello-world.html");

    /* Optionally, you can use the get() method with the docpp::HTML::FORMATTING_PRETTY argument to get a *slightly* more readable document.
     * The same goes for the CSS document. Or, you can use docpp::HTML::FORMATTING_NEWLINE to get a document with elements separated by newlines.
     */
    file << doc.get(docpp::HTML::FORMATTING_PRETTY);

    file.close();

    /* And we're done! */
    return 0;

}
