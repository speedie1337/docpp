#include <Endpoint.hpp>
#include <Sites.hpp>
#include <docpp/docpp.hpp>

int main() {
    static const std::vector<std::tuple<std::string, docpp::HTML::Section, PageProperties>> website_tree{
        {"index.html", Sites::get_index_site(), PageProperties{"Example.com", "This is a test description", "en"}}
    };

    for (const auto& it : website_tree) {
        Endpoint endpoint(std::get<0>(it));

        docpp::HTML::Section root{docpp::HTML::Tag::Html, docpp::HTML::make_properties(docpp::HTML::Property{"lang", std::get<2>(it).lang})};

        root += Sites::get_generic_header(std::get<2>(it).name, std::get<2>(it).description);
        root += std::get<1>(it);
        root += Sites::get_generic_footer();

        endpoint.open();
        endpoint.append_string(docpp::HTML::Document(root).get<std::string>(docpp::HTML::Formatting::Pretty));
        endpoint.close();
    }
}