#include <Sites.hpp>

docpp::HTML::Section Sites::get_generic_header(const std::string& title, const std::string& description) {
    return docpp::HTML::Section{docpp::HTML::Tag::Head, {}, std::vector<docpp::HTML::Element> {
        docpp::HTML::Element{docpp::HTML::Tag::Title, {}, title},
        docpp::HTML::Element{docpp::HTML::Tag::Meta, docpp::HTML::make_properties(
            docpp::HTML::Property{"name", "description"},
            docpp::HTML::Property{"content", description}
            )},
        docpp::HTML::Element{docpp::HTML::Tag::Meta, docpp::HTML::make_properties(
            docpp::HTML::Property{"name", "viewport"},
            docpp::HTML::Property{"content", "width=device-width, initial-scale=1"}
            )}
    }};
}

docpp::HTML::Section Sites::get_generic_footer() {
    return docpp::HTML::Section{docpp::HTML::Tag::Footer, {}, std::vector<docpp::HTML::Section> {
        docpp::HTML::Section{docpp::HTML::Tag::Div, docpp::HTML::make_properties(docpp::HTML::Property{"id", "footer"}, docpp::HTML::Property{"class", "footer"}),
            std::vector<docpp::HTML::Element> {
                docpp::HTML::Element{docpp::HTML::Tag::P, {}, "My example footer here."}
            }
        }
    }};
}

docpp::HTML::Section Sites::create_body_container(const std::vector<docpp::HTML::Element>& elements) {
    return docpp::HTML::Section{docpp::HTML::Tag::Body, {}, std::vector<docpp::HTML::Section> {
        docpp::HTML::Section{docpp::HTML::Tag::Div, docpp::HTML::make_properties(docpp::HTML::Property{"id", "content"}, docpp::HTML::Property{"class", "content"}), elements}
    }};
}


docpp::HTML::Section Sites::get_index_site() {
    return Sites::create_body_container({
        docpp::HTML::Element{docpp::HTML::Tag::H1, {}, "Hello world!"},
        docpp::HTML::Element{docpp::HTML::Tag::P, {}, "Hello world! This is a test page, which was generated using what is probably the worst website generator in the entire world. But it's quite cool to be able to write a website in C++."},
    });
}
