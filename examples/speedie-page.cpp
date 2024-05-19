#include <iostream>
#include <fstream>
#include <docpp/docpp.hpp>

docpp::HTML::Section getCSS() {
    docpp::HTML::Section css{docpp::HTML::Tag::Style};

    docpp::CSS::Stylesheet stylesheet{};

    stylesheet.push_back({"@font-face",
        {
            {"font-family", "Noto Sans"},
            {"src", "url(https://fonts.gstatic.com/s/notosansmono/v30/BngcUXNETWXI6LwhGYvaxZikqZqK6fBq6kPvUce2oAZ2evCj.woff2) format('woff2')"}
        }
    });

    stylesheet.push_back({"body",
        {
            {"margin", "0px"},
            {"padding", "0px"},
            {"font-family", "Noto Sans"},
            {"background-color", "#212121"},
            {"overflow-x", "hidden"},
            {"color", "#f0eee4"},
        }
    });

    stylesheet.push_back({"pre",
        {
            {"background-color", "#222222"},
            {"width", "fit-content"},
            {"padding", "5px"},
            {"border-left", "2px solid #cccccc"},
        }
    });

    stylesheet.push_back({"a",
        {
            {"color", "#89bfff"},
            {"text-decoration", "none"},
            {"transition", "0.1s"},
        }
    });

    stylesheet.push_back({"a:hover",
        {
            {"color", "#ccccff"},
            {"text-decoration", "underline"},
        }
    });

    stylesheet.push_back({"a:hover",
        {
            {"color", "#ccccff"},
            {"text-decoration", "underline"},
        }
    });

    stylesheet.push_back({".content",
        {
            {"padding", "5px"},
            {"padding-bottom", "100px"},
            {"max-width", "1000px"},
            {"margin", "auto"},
            {"text-align", "center"},
        }
    });

    stylesheet.push_back({".content li",
        {
            {"text-align", "left"},
        }
    });

    stylesheet.push_back({".content table",
        {
            {"margin-left", "auto"},
            {"margin-right", "auto"},
            {"text-align", "left"},
        }
    });

    stylesheet.push_back({".content th, td",
        {
            {"padding-right", "25px"},
        }
    });

    stylesheet.push_back({".links img",
        {
            {"transform", "translate(0m +20%)"},
            {"display", "inline"},
        }
    });

    stylesheet.push_back({".navbar",
        {
            {"background-color", "#363636"},
            {"color", "#1fccef"},
            {"position", "sticky"},
            {"top", "0px"},
            {"z-index", "6"},
            {"margin", "5px"},
            {"padding", "5px"},
            {"width", "auto"},
            {"text-align", "center"},
            {"border-radius", "10px"},
        }
    });

    stylesheet.push_back({".navbar a",
        {
            {"color", "#e6e6fa"},
            {"text-decoration", "none"},
            {"padding-top", "5px"},
            {"padding-bottom", "5px"},
            {"padding-left", "3px"},
            {"padding-right", "3px"},
        }
    });

    stylesheet.push_back({".navbar a:hover",
        {
            {"display", "inline"},
            {"text-decoration", "underline"},
        }
    });

    stylesheet.push_back({".navbar span",
        {
            {"padding", "5px"},
            {"display", "inline"},
        }
    });

    stylesheet.push_back({".navbar img",
        {
            {"transform", "translate(+30%, +25%)"},
        }
    });

    stylesheet.push_back({".warning",
        {
            {"color", "#ffff00"},
        }
    });

    stylesheet.push_back({"footer",
        {
            {"font-size", "8pt"},
            {"font-weight", "normal"},
            {"background-color", "transparent"},
            {"padding", "5px"},
            {"color", "#f0eee4"},
            {"background-color", "#363636"},
            {"text-align", "center"},
            {"position", "fixed"},
            {"bottom", "0px"},
            {"width", "100%"},
        }
    });

    stylesheet.push_back({"footer .links",
        {
            {"color", "#89bfff"},
        }
    });

    stylesheet.push_back({".links",
        {
            {"color", "#66667d"},
            {"padding", "5px"},
            {"padding-left", "2px"},
        }
    });

    stylesheet.push_back({".banner",
        {
            {"padding-top", "25px"},
        }
    });

    css.push_back({docpp::HTML::Tag::Empty_No_Formatting, {}, stylesheet.get<std::string>(docpp::CSS::Formatting::Pretty, 4)});

    return css;
}

docpp::HTML::Section getNavbar(docpp::HTML::Section& e) {
    docpp::HTML::Section navbar(docpp::HTML::Tag::Div, {{docpp::HTML::Property{{"class", "navbar"}}}});
    docpp::HTML::Section span(docpp::HTML::Tag::Span, {});

    span.push_back({docpp::HTML::Tag::Empty, {}, "speedie.site\n"});

    const auto append_to_span = [&](const std::string& img, const std::string& url, const std::string& text) {
        span.push_back({docpp::HTML::Tag::Img, {{docpp::HTML::Property{{"src", img}}, docpp::HTML::Property{{"width", "16"}}, docpp::HTML::Property{{"height", "16"}}}}, ""});
        span.push_back({docpp::HTML::Tag::A, {{docpp::HTML::Property{{"href", url}}}}, text});
    };

    append_to_span("img/home.png", "/", "Home");
    append_to_span("img/projects.png", "/projects.html", "Projects");
    append_to_span("img/blog.png", "/blog.html", "Blog");
    append_to_span("img/git.svg", "https://git.speedie.site/speedie", "Git");

    navbar.push_back(span);
    e.push_back(navbar);

    return e;
}

docpp::HTML::Section getHead() {
    docpp::HTML::Section e{docpp::HTML::Tag::Head};

    docpp::HTML::Element content_type{docpp::HTML::Tag::Meta, {{docpp::HTML::Property{{"http-equiv", "content-type"}}, docpp::HTML::Property{{"content", "text/html; charset=utf-8"}}}}};
    docpp::HTML::Element charset{docpp::HTML::Tag::Meta, {{docpp::HTML::Property{{"charset", "UTF-8"}}}}};
    docpp::HTML::Element favicon(docpp::HTML::Tag::Link, {{docpp::HTML::Property{{"rel", "icon"}}, docpp::HTML::Property{{"type", "image/x-icon"}}, docpp::HTML::Property{{"href", "/img/favicon.svg"}}}});
    docpp::HTML::Element description(docpp::HTML::Tag::Meta, {{docpp::HTML::Property{{"name", "description"}}, docpp::HTML::Property{{"content", "Welcome to my personal website."}}}});
    docpp::HTML::Element author(docpp::HTML::Tag::Meta, {{docpp::HTML::Property{{"name", "author"}}, docpp::HTML::Property{{"content", "speedie"}}}});
    docpp::HTML::Element title(docpp::HTML::Tag::Title, {}, "speedie's site");
    docpp::HTML::Section css{docpp::HTML::Tag::Style};

    e.push_back(content_type);
    e.push_back(favicon);
    e.push_back(getCSS());
    e.push_back(charset);
    e.push_back(description);
    e.push_back(title);

    return getNavbar(e);
}

docpp::HTML::Section getMain() {
    docpp::HTML::Section content(docpp::HTML::Tag::Div, {{docpp::HTML::Property{{"class", "content"}}}});

    content.push_back({docpp::HTML::Tag::H2, {}, "Hello world!"});
    content.push_back({docpp::HTML::Tag::P, {}, "Hello there! This is a replica of my old website, using docpp to generate the HTML. With that said. This only provides the index page, so many links are not functional. This is more to show off that docpp can be used to generate a proper website."});
    content.push_back({docpp::HTML::Tag::H3, {}, "Links"});

    docpp::HTML::Section links(docpp::HTML::Tag::Div, {{docpp::HTML::Property{{"class", "links"}}}});
    docpp::HTML::Section table(docpp::HTML::Tag::Table);

    static const auto append_to_table = [&](const std::string& img, const std::string& url, const std::string& short_text, const std::string& long_text) {
        docpp::HTML::Section tr{docpp::HTML::Tag::Tr};
        docpp::HTML::Section td{docpp::HTML::Tag::Td};
        docpp::HTML::Section td2{docpp::HTML::Tag::Td};

        td.push_back({docpp::HTML::Tag::Img, {{docpp::HTML::Property{{"src", img}}, docpp::HTML::Property{{"width", "16"}}, docpp::HTML::Property{{"height", "16"}}}}, ""});
        td.push_back({docpp::HTML::Tag::A, {{docpp::HTML::Property{{"href", url}}}}, short_text});
        td2.push_back({docpp::HTML::Tag::Empty, {}, long_text + "\n"});

        tr.push_back(td);
        tr.push_back(td2);
        table.push_back(tr);
    };

    append_to_table("img/aboutme.png", "about-me.html", "About me", "Learn more about me.");
    append_to_table("img/blog.png", "blog.html", "Blog", "Read my blog.");
    append_to_table("img/projects.png", "projects.html", "Projects", "List of the software projects I work on.");
    append_to_table("img/git.svg", "https://git.speedie.site/speedie", "Git", "Git server, where all my software projects are hosted.");
    append_to_table("img/github.svg", "https://github.com/speedie1337", "GitHub", "My GitHub account, used for backups and contributions.");

    links.push_back(table);
    content.push_back(links);

    return content;
}

docpp::HTML::Section getFooter() {
    docpp::HTML::Section footer(docpp::HTML::Tag::Footer);
    docpp::HTML::Section div(docpp::HTML::Tag::Div, {{docpp::HTML::Property("class", "column")}});
    docpp::HTML::Section span(docpp::HTML::Tag::Span, {{docpp::HTML::Property("class", "links")}});

    span.push_back({docpp::HTML::Tag::A, {{docpp::HTML::Property("class", "links"), docpp::HTML::Property("href", "https://git.speedie.site")}}, "Git"});
    span.push_back({docpp::HTML::Tag::A, {{docpp::HTML::Property("class", "links"), docpp::HTML::Property("href", "https://ls.speedie.site")}}, "Downloads"});
    span.push_back({docpp::HTML::Tag::A, {{docpp::HTML::Property("class", "links"), docpp::HTML::Property("href", "privacy.html")}}, "Licensing"});

    div.push_back(span);
    div.push_back({docpp::HTML::Tag::P, {{docpp::HTML::Property("style", "padding-top: 0px;")}}, "Made in Sweden"});
    footer.push_back(div);

    return footer;
}

int main() {
    docpp::HTML::Section html_section = docpp::HTML::Section(docpp::HTML::Tag::Html);
    docpp::HTML::Section head{getHead()};
    docpp::HTML::Section body(docpp::HTML::Tag::Body);

    body.push_back(getMain());

    docpp::HTML::Section footer(getFooter());

    html_section.push_back(head);
    html_section.push_back(body);
    html_section.push_back(footer);

    docpp::HTML::Document html_doc(html_section);

    std::cout << html_doc.get<std::string>(docpp::HTML::Formatting::Pretty) << "\n";
    std::ofstream fs{"speedie-page.html"};
    fs << html_doc.get<std::string>(docpp::HTML::Formatting::Pretty);
    fs.close();
}
