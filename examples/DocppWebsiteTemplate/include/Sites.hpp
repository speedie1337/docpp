#ifndef SITES_HPP
#define SITES_HPP

#include <docpp/docpp.hpp>

struct PageProperties {
    std::string name{};
    std::string description{};
    std::string lang{};
};

namespace Sites {
    docpp::HTML::Section get_generic_header(const std::string&, const std::string& = {});
    docpp::HTML::Section get_generic_footer();
    docpp::HTML::Section get_index_site();
    docpp::HTML::Section create_body_container(const std::vector<docpp::HTML::Element>&);
}

#endif //SITES_HPP
