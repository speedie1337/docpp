#include <iostream>
#include <string>
#include <unordered_map>
#include <src/docpp.cpp>
#include <catch2/catch_test_macros.hpp>

// NOLINTBEGIN
// Disable linting. This is a test program and the code is intentionally bad in some places.
// As such, I think it's best to turn linting off rather than to try and resolve any such warnings.

inline namespace HTML {
    void test_tag() {
        const auto expected_values = docpp::HTML::get_tag_map();

        for (const auto& it : expected_values) {
            REQUIRE((docpp::HTML::resolve_tag(it.first).first == it.second.first && docpp::HTML::resolve_tag(it.first).second == it.second.second));
        }
    }

    void test_property() {
        const auto test_get_and_set = []() {
            using namespace docpp::HTML;

            Property property;
            REQUIRE((property.get().first.empty() && property.get().second.empty() && property.get_key().empty() && property.get_value().empty()));

            property.set({"key", "value"});

            REQUIRE(property.get().first == "key");
            REQUIRE(property.get().second == "value");
            REQUIRE(property.get_key() == "key");
            REQUIRE(property.get_value() == "value");

            property.set_key("new_key");
            property.set_value("new_value");

            REQUIRE(property.get().first == "new_key");
            REQUIRE(property.get().second == "new_value");
            REQUIRE(property.get_key() == "new_key");
            REQUIRE(property.get_value() == "new_value");

            property.set_key("newer_key");

            REQUIRE(property.get().first == "newer_key");
            REQUIRE(property.get().second == "new_value");
            REQUIRE(property.get_key() == "newer_key");
            REQUIRE(property.get_value() == "new_value");

            property.set_value("newer_value");

            REQUIRE(property.get().first == "newer_key");
            REQUIRE(property.get().second == "newer_value");
            REQUIRE(property.get_key() == "newer_key");
            REQUIRE(property.get_value() == "newer_value");

            REQUIRE(property.empty() == false);

            property.clear();

            REQUIRE(property.empty() == true);
        };

        const auto test_copy_property = []() {
            using namespace docpp::HTML;

            docpp::HTML::Property property;

            property.set({"key", "value"});
        };

        test_get_and_set();
        test_copy_property();
    }

    void test_properties() {
        const auto test_get_and_set = []() {
            using namespace docpp::HTML;

            Properties properties;

            REQUIRE(properties.empty());

            properties.push_back({"key1", "value1"});
            properties.push_back({"key2", "value2"});
            properties.push_back({"key3", "value3"});

            REQUIRE(properties.size() == 3);

            std::size_t index = 0;
            for (const auto& it : properties) {
                if (index == 0) {
                    REQUIRE(it.get().first == "key1");
                    REQUIRE(it.get().second == "value1");
                } else if (index == 1) {
                    REQUIRE(it.get().first == "key2");
                    REQUIRE(it.get().second == "value2");
                } else if (index == 2) {
                    REQUIRE(it.get().first == "key3");
                    REQUIRE(it.get().second == "value3");
                }

                ++index;
            }

            REQUIRE(properties.at(0).get().first == "key1");
            REQUIRE(properties.at(0).get().second == "value1");
            REQUIRE(properties.at(1).get().first == "key2");
            REQUIRE(properties.at(1).get().second == "value2");
            REQUIRE(properties.at(2).get().first == "key3");
            REQUIRE(properties.at(2).get().second == "value3");

            // should fail, out of range
            try {
                static_cast<void>(properties.at(3));
            } catch (const docpp::out_of_range& e) {
                REQUIRE(std::string(e.what()) == "Index out of range");
            }

            REQUIRE(properties[0] == properties.at(0));
            REQUIRE(properties[1] == properties.at(1));
            REQUIRE(properties[2] == properties.at(2));
        };

        const auto test_copy_properties = []() {
            using namespace docpp::HTML;

            Properties properties;

            properties += {"key1", "value1"};
            properties += {"key2", "value2"};
            properties += {"key3", "value3"};

            Properties new_properties = properties;

            REQUIRE(properties == new_properties);

            properties.clear();
        };

        const auto test_iterators = []() {
            using namespace docpp::HTML;

            Properties properties = make_properties(Property{"key1", "value1"}, Property{"key2", "value2"}, Property{"key3", "value3"});

            std::size_t index{0};
            for (auto it = properties.begin(); it != properties.end(); ++it) {
                if (index == 0) {
                    REQUIRE(it->get().first == "key1");
                    REQUIRE(it->get().second == "value1");
                } else if (index == 1) {
                    REQUIRE(it->get().first == "key2");
                    REQUIRE(it->get().second == "value2");
                } else if (index == 2) {
                    REQUIRE(it->get().first == "key3");
                    REQUIRE(it->get().second == "value3");
                }

                ++index;
            }

            index = 0;
            for (auto it = properties.cbegin(); it != properties.cend(); ++it) {
                if (index == 0) {
                    REQUIRE(it->get().first == "key1");
                    REQUIRE(it->get().second == "value1");
                } else if (index == 1) {
                    REQUIRE(it->get().first == "key2");
                    REQUIRE(it->get().second == "value2");
                } else if (index == 2) {
                    REQUIRE(it->get().first == "key3");
                    REQUIRE(it->get().second == "value3");
                }

                ++index;
            }

            index = 0;
            for (auto it = properties.rbegin(); it != properties.rend(); ++it) {
                if (index == 0) {
                    REQUIRE(it->get().first == "key3");
                    REQUIRE(it->get().second == "value3");
                } else if (index == 1) {
                    REQUIRE(it->get().first == "key2");
                    REQUIRE(it->get().second == "value2");
                } else if (index == 2) {
                    REQUIRE(it->get().first == "key1");
                    REQUIRE(it->get().second == "value1");
                }

                ++index;
            }

            index = 0;
            for (auto it = properties.crbegin(); it != properties.crend(); ++it) {
                if (index == 0) {
                    REQUIRE(it->get().first == "key3");
                    REQUIRE(it->get().second == "value3");
                } else if (index == 1) {
                    REQUIRE(it->get().first == "key2");
                    REQUIRE(it->get().second == "value2");
                } else if (index == 2) {
                    REQUIRE(it->get().first == "key1");
                    REQUIRE(it->get().second == "value1");
                }

                ++index;
            }

            index = 0;
            for (const auto& it : properties) {
                if (index == 0) {
                    REQUIRE(it.get().first == "key1");
                    REQUIRE(it.get().second == "value1");
                } else if (index == 1) {
                    REQUIRE(it.get().first == "key2");
                    REQUIRE(it.get().second == "value2");
                } else if (index == 2) {
                    REQUIRE(it.get().first == "key3");
                    REQUIRE(it.get().second == "value3");
                }

                ++index;
            }
        };

        const auto test_find = []() {
            using namespace docpp::HTML;

            Properties properties = make_properties(Property{"key1", "value1"}, Property{"key2", "value2"}, Property{"key3", "value3"});

            REQUIRE(properties.find(Property("key1", "value1")) == 0);
            REQUIRE(properties.find(Property("key2", "value2")) == 1);
            REQUIRE(properties.find(Property("key3", "value3")) == 2);
            REQUIRE(properties.find(Property("key4", "value4")) == Properties::npos);

            REQUIRE(properties.find("key1") == 0);
            REQUIRE(properties.find("key2") == 1);
            REQUIRE(properties.find("key3") == 2);
            REQUIRE(properties.find("key4") == Properties::npos);

            REQUIRE(properties.find("value1") == 0);
            REQUIRE(properties.find("value2") == 1);
            REQUIRE(properties.find("value3") == 2);
            REQUIRE(properties.find("value4") == Properties::npos);

            std::size_t pos = properties.find("key1");

            REQUIRE(properties[pos].get().first == "key1");
            REQUIRE(properties.at(pos).get().first == "key1");
            REQUIRE(properties[pos].get().second == "value1");
            REQUIRE(properties.at(pos).get().second == "value1");

            pos = properties.find("key2");

            REQUIRE(properties[pos].get().first == "key2");
            REQUIRE(properties.at(pos).get().first == "key2");
            REQUIRE(properties[pos].get().second == "value2");
            REQUIRE(properties.at(pos).get().second == "value2");

            pos = properties.find("key3");

            REQUIRE(properties[pos].get().first == "key3");
            REQUIRE(properties.at(pos).get().first == "key3");
            REQUIRE(properties[pos].get().second == "value3");
            REQUIRE(properties.at(pos).get().second == "value3");

            pos = properties.find("key4");

            REQUIRE(pos == Properties::npos);

            try {
                static_cast<void>(properties.at(pos));
            } catch (const docpp::out_of_range& e) {
                REQUIRE(std::string(e.what()) == "Index out of range");
            }
        };

        const auto test_insert = []() {
            using namespace docpp::HTML;

            Properties properties = make_properties(Property{"key1", "value1"}, Property{"key2", "value2"}, Property{"key3", "value3"});

            std::size_t pos = properties.find("key1");
            Property found_property = properties[pos];

            std::size_t pos2 = properties.find("value2");
            properties.insert(pos2, found_property);

            REQUIRE(properties.at(pos2) == found_property);
            REQUIRE(properties.get_properties().at(pos2) == found_property);
            REQUIRE(properties.get_properties().at(pos2).get().first == "key1");
        };

        const auto test_swap = []() {
            using namespace docpp::HTML;

            Properties properties = make_properties(Property{"key1", "value1"}, Property{"key2", "value2"}, Property{"key3", "value3"});

            std::size_t pos1 = properties.find("key1");
            Property property1 = properties[pos1];

            std::size_t pos2 = properties.find("key2");
            Property property2 = properties[pos2];

            properties.swap(pos1, pos2);

            REQUIRE(properties[pos1] == property2);
            REQUIRE(properties[pos2] == property1);

            properties.swap(property1, property2);

            REQUIRE(properties[pos1] == property1);
            REQUIRE(properties[pos2] == property2);
        };

        const auto test_front_and_back = []() {
            using namespace docpp::HTML;

            Properties properties = make_properties(Property{"key1", "value1"}, Property{"key2", "value2"}, Property{"key3", "value3"});

            REQUIRE(properties.front().get().first == "key1");
            REQUIRE(properties.front().get().second == "value1");

            REQUIRE(properties.back().get().first == "key3");
            REQUIRE(properties.back().get().second == "value3");
        };

        const auto test_size_empty_and_clear = []() {
            using namespace docpp::HTML;

            Properties properties = make_properties(Property{"key1", "value1"}, Property{"key2", "value2"}, Property{"key3", "value3"});

            REQUIRE(properties.size() == 3);
            REQUIRE(properties.empty() == false);

            properties.clear();

            REQUIRE(properties.size() == 0);
            REQUIRE(properties.empty() == true);
        };

        const auto test_push_front_and_back = []() {
            using namespace docpp::HTML;

            Properties properties;

            properties.push_front({"key1", "value1"});
            properties.push_back({"key2", "value2"});

            REQUIRE(properties.front().get().first == "key1");
            REQUIRE(properties.front().get().second == "value1");

            REQUIRE(properties.back().get().first == "key2");
            REQUIRE(properties.back().get().second == "value2");
        };

        const auto test_constructors = []() {
            using namespace docpp::HTML;

            Properties properties = make_properties(Property{"key1", "value1"}, Property{"key2", "value2"}, Property{"key3", "value3"});
            Properties new_properties = properties;

            REQUIRE(properties == new_properties);

            Properties new_properties2(properties.get_properties());

            REQUIRE(properties == new_properties2);

            Property property1{"key1", "value1"};
            Properties new_properties3 = make_properties(property1);

            REQUIRE(new_properties3.size() == 1);
        };

        test_get_and_set();
        test_copy_properties();
        test_iterators();
        test_find();
        test_insert();
        test_swap();
        test_front_and_back();
        test_size_empty_and_clear();
        test_push_front_and_back();
        test_constructors();
    }

    void test_element() {
        const auto test_get_and_set = []() {
            using namespace docpp::HTML;

            Element element;

            element.set("my_element", {}, {}, docpp::HTML::Type::Non_Self_Closing);

            REQUIRE(element.get_tag() == "my_element");
            REQUIRE(element.get_data() == "");
            REQUIRE(element.get_properties() == Properties{});
            REQUIRE(element.get_type() == docpp::HTML::Type::Non_Self_Closing);

            element.set_tag("new_element");
            element.set_data("new_data");
            element.set_properties(Properties(std::vector<Property>{{"key", "value"}, {"key2", "value2"}}));
            element.set_type(docpp::HTML::Type::Non_Closed);

            REQUIRE(element.get_tag() == "new_element");
            REQUIRE(element.get_data() == "new_data");
            REQUIRE(element.get_properties().at(0).get().first == "key");
            REQUIRE(element.get_properties().at(0).get().second == "value");
            REQUIRE(element.get_properties().at(1).get().first == "key2");
            REQUIRE(element.get_properties().at(1).get().second == "value2");
            REQUIRE(element.get_type() == docpp::HTML::Type::Non_Closed);
        };

        const auto test_copy_element = []() {
            using namespace docpp::HTML;

            Element element;

            element.set("my_element", {}, {}, docpp::HTML::Type::Non_Self_Closing);

            Element new_element = element;

            REQUIRE(element == new_element);
            REQUIRE(element.empty() == false);

            element.clear();

            REQUIRE(element.empty() == true);

            element = std::move(new_element);

            REQUIRE(element.empty() == false);
        };

        const auto test_operators = []() {
            using namespace docpp::HTML;

            Element element1;
            Element element2;

            element1.set("my_element", {}, {}, docpp::HTML::Type::Non_Self_Closing);
            element2.set("my_element", {}, {}, docpp::HTML::Type::Non_Self_Closing);

            REQUIRE(element1 == element2);

            element2.set("new_element", {}, {}, docpp::HTML::Type::Non_Self_Closing);

            REQUIRE(element1 != element2);

            element2 = element1;

            REQUIRE(element1 == element2);
        };

        const auto test_constructors = []() {
            using namespace docpp::HTML;

            Element elem{};

            REQUIRE(elem.get_tag() == "");
            REQUIRE(elem.get_data() == "");
            REQUIRE(elem.get_properties() == Properties{});
            REQUIRE(elem.get_type() == docpp::HTML::Type::Non_Self_Closing);

            Element elem2("my_element", {}, "data", docpp::HTML::Type::Non_Closed);

            REQUIRE(elem2.get_tag() == "my_element");
            REQUIRE(elem2.get_data() == "data");
            REQUIRE(elem2.get_properties() == Properties{});
            REQUIRE(elem2.get_type() == docpp::HTML::Type::Non_Closed);

            Element elem3(docpp::HTML::Tag::H1, {}, "data");

            REQUIRE(elem3.get_tag() == "h1");
            REQUIRE(elem3.get_data() == "data");
            REQUIRE(elem3.get_properties() == Properties{});
            REQUIRE(elem3.get_type() == docpp::HTML::Type::Non_Self_Closing);
        };

        const auto test_string_get = []() {
            using namespace docpp::HTML;

            Element element(docpp::HTML::Tag::H1, {}, "data");

            REQUIRE(element.get() == "<h1>data</h1>");
            REQUIRE(element.get<std::string>() == "<h1>data</h1>");
            REQUIRE(element.get<std::string>(docpp::HTML::Formatting::None) == "<h1>data</h1>");
            REQUIRE(element.get<std::string>(docpp::HTML::Formatting::Pretty) == "<h1>data</h1>\n");
            REQUIRE(element.get<std::string>(docpp::HTML::Formatting::Newline) == "<h1>data</h1>\n");

            element.set_type(docpp::HTML::Type::Non_Opened);
            REQUIRE(element.get<std::string>() == "</h1>");
        };

        test_get_and_set();
        test_copy_element();
        test_operators();
        test_constructors();
        test_string_get();
    }

    void test_section() {
        const auto test_get_and_set = []() {
            using namespace docpp::HTML;

            Section section;

            section.set_tag("my_section");

            REQUIRE(section.get_tag() == "my_section");
            REQUIRE(section.get_sections().empty());
            REQUIRE(section.get_elements().empty());
            REQUIRE(section.get_properties().empty());

            section.set_tag("new_section");
            section.set_properties(make_properties(Property("key", "value"), Property("key2", "value2")));

            REQUIRE(section.get_tag() == "new_section");
            REQUIRE(section.get_properties().at(0).get().first == "key");
            REQUIRE(section.get_properties().at(0).get().second == "value");
            REQUIRE(section.get_properties().at(1).get().first == "key2");
            REQUIRE(section.get_properties().at(1).get().second == "value2");

            section.set("new_section", Properties(Property("key", "value"), Property("key2", "value2")));

            REQUIRE(section.get_tag() == "new_section");
            REQUIRE(section.get_properties().at(0).get().first == "key");
            REQUIRE(section.get_properties().at(0).get().second == "value");
            REQUIRE(section.get_properties().at(1).get().first == "key2");
            REQUIRE(section.get_properties().at(1).get().second == "value2");

            section.set_properties(make_properties(Property("key3", "value3"), Property("key4", "value4")));

            REQUIRE(section.get_properties().at(0).get().first == "key3");
            REQUIRE(section.get_properties().at(0).get().second == "value3");
            REQUIRE(section.get_properties().at(1).get().first == "key4");
            REQUIRE(section.get_properties().at(1).get().second == "value4");

            Section completely_empty_section;

            static_cast<void>(completely_empty_section.get(docpp::HTML::Formatting::None));
            static_cast<void>(completely_empty_section.get(docpp::HTML::Formatting::Newline));
            static_cast<void>(completely_empty_section.get(docpp::HTML::Formatting::Pretty));
        };

        const auto test_copy_section = []() {
            using namespace docpp::HTML;

            Section section;
            section.set("my_section", make_properties(Property("key", "value"), Property("key2", "value2")));

            Section new_section = section;

            REQUIRE(section == new_section);
            REQUIRE(section.empty() == true); // should still be empty, because the
                                              // section itself is not an element, it's more of a container element
                                              // in the same vein as a <div> element

            section.push_back(Element{});

            REQUIRE(section.empty() == false);
            REQUIRE(section != new_section);

            section.clear();

            REQUIRE(section.empty() == true);

            section = std::move(new_section);

            REQUIRE(section.empty() == true);
        };

        const auto test_operators = []() {
            using namespace docpp::HTML;

            Section section1;
            Section section2;

            section1.set("my_section", make_properties(Property("key", "value"), Property("key2", "value2")));
            section2.set("my_section", make_properties(Property("key", "value"), Property("key2", "value2")));

            REQUIRE(section1 == section2);

            section2.set("new_section", make_properties(Property("key", "value"), Property("key2", "value2")));

            REQUIRE(section1 != section2);

            section2 = section1;

            REQUIRE(section1 == section2);

            Section section3;

            section3 += Element{docpp::HTML::Tag::H1, {}, "This is some data."};
            section3 += Element{docpp::HTML::Tag::H1, {}, "This is some data two."};
            section3 += Element{docpp::HTML::Tag::H2, {}, "This is some more data."};

            REQUIRE(section3["h1"]["This is some data."] == section3.get_elements().at(0));
            REQUIRE(section3["h1"]["This is some data two."] == section3.get_elements().at(1));
            REQUIRE(section3["h2"]["This is some more data."] == section3.get_elements().at(2));
            REQUIRE(section3["h3"]["This is some more data."] == Element{});
            REQUIRE(section3["h4"]["This is some more data."] == Element{});
            REQUIRE(section3[Tag::H1]["This is some data."] == section3.get_elements().at(0));
            REQUIRE(section3[Tag::H1]["This is some data two."] == section3.get_elements().at(1));
            REQUIRE(section3[Tag::H2]["This is some more data."] == section3.get_elements().at(2));
            REQUIRE(section3[Tag::H3]["This is some more data."] == Element{});
            REQUIRE(section3[Tag::H4]["This is some more data."] == Element{});
        };

        const auto test_constructors = []() {
            using namespace docpp::HTML;

            Section section{};

            REQUIRE(section.get_tag() == "");
            REQUIRE(section.get_sections().empty());
            REQUIRE(section.get_elements().empty());
            REQUIRE(section.get_properties().empty());

            Section section2("my_section", make_properties(Property("key", "value"), Property("key2", "value2")));

            REQUIRE(section2.get_tag() == "my_section");
            REQUIRE(section2.get_properties().at(0).get().first == "key");
            REQUIRE(section2.get_properties().at(0).get().second == "value");
            REQUIRE(section2.get_properties().at(1).get().first == "key2");
            REQUIRE(section2.get_properties().at(1).get().second == "value2");

            Section section3(docpp::HTML::Tag::H1, make_properties(Property{"key", "value"}, Property{"key2", "value2"}), {Element{}});

            REQUIRE(section3.get_tag() == "h1");
            REQUIRE(section3.get_properties().at(0).get().first == "key");
            REQUIRE(section3.get_properties().at(0).get().second == "value");
            REQUIRE(section3.get_properties().at(1).get().first == "key2");
            REQUIRE(section3.get_properties().at(1).get().second == "value2");
        };

        const auto test_iterators = []() {
            using namespace docpp::HTML;

            Section section{docpp::HTML::Tag::Html, {}};

            section.push_back(Element{docpp::HTML::Tag::H2, {}});
            section.push_back(Element{docpp::HTML::Tag::H3, {}});
            section.push_back(Element{docpp::HTML::Tag::H4, {}});
            section.push_back(Element{docpp::HTML::Tag::H5, {}});
            section.push_back(Element{docpp::HTML::Tag::H6, {}});

            Element element;

            std::size_t index{0};
            for (auto it = section.begin(); it != section.end(); ++it) {
                Element element = *it;

                if (index == 0) {
                    REQUIRE(element.get_tag() == "h2");
                    REQUIRE(element.get_type() == docpp::HTML::Type::Non_Self_Closing);
                    REQUIRE(element.get() == "<h2></h2>");
                } else if (index == 1) {
                    REQUIRE(element.get_tag() == "h3");
                    REQUIRE(element.get_type() == docpp::HTML::Type::Non_Self_Closing);
                    REQUIRE(element.get() == "<h3></h3>");
                } else if (index == 2) {
                    REQUIRE(element.get_tag() == "h4");
                    REQUIRE(element.get_type() == docpp::HTML::Type::Non_Self_Closing);
                    REQUIRE(element.get() == "<h4></h4>");
                } else if (index == 3) {
                    REQUIRE(element.get_tag() == "h5");
                    REQUIRE(element.get_type() == docpp::HTML::Type::Non_Self_Closing);
                    REQUIRE(element.get() == "<h5></h5>");
                } else if (index == 4) {
                    REQUIRE(element.get_tag() == "h6");
                    REQUIRE(element.get_type() == docpp::HTML::Type::Non_Self_Closing);
                    REQUIRE(element.get() == "<h6></h6>");
                }

                ++index;
            }

            index = 0;
            for (Section::const_iterator it = section.cbegin(); it != section.cend(); ++it) {
                Element element = *it;

                if (index == 0) {
                    REQUIRE(element.get_tag() == "h2");
                    REQUIRE(element.get_type() == docpp::HTML::Type::Non_Self_Closing);
                    REQUIRE(element.get() == "<h2></h2>");
                } else if (index == 1) {
                    REQUIRE(element.get_tag() == "h3");
                    REQUIRE(element.get_type() == docpp::HTML::Type::Non_Self_Closing);
                    REQUIRE(element.get() == "<h3></h3>");
                } else if (index == 2) {
                    REQUIRE(element.get_tag() == "h4");
                    REQUIRE(element.get_type() == docpp::HTML::Type::Non_Self_Closing);
                    REQUIRE(element.get() == "<h4></h4>");
                } else if (index == 3) {
                    REQUIRE(element.get_tag() == "h5");
                    REQUIRE(element.get_type() == docpp::HTML::Type::Non_Self_Closing);
                    REQUIRE(element.get() == "<h5></h5>");
                } else if (index == 4) {
                    REQUIRE(element.get_tag() == "h6");
                    REQUIRE(element.get_type() == docpp::HTML::Type::Non_Self_Closing);
                    REQUIRE(element.get() == "<h6></h6>");
                }

                ++index;
            }

            index = 0;
            for (Section::reverse_iterator it = section.rbegin(); it != section.rend(); ++it) {
                Element element = *it;

                if (index == 0) {
                    REQUIRE(element.get_tag() == "h6");
                    REQUIRE(element.get_type() == docpp::HTML::Type::Non_Self_Closing);
                    REQUIRE(element.get() == "<h6></h6>");
                } else if (index == 1) {
                    REQUIRE(element.get_tag() == "h5");
                    REQUIRE(element.get_type() == docpp::HTML::Type::Non_Self_Closing);
                    REQUIRE(element.get() == "<h5></h5>");
                } else if (index == 2) {
                    REQUIRE(element.get_tag() == "h4");
                    REQUIRE(element.get_type() == docpp::HTML::Type::Non_Self_Closing);
                    REQUIRE(element.get() == "<h4></h4>");
                } else if (index == 3) {
                    REQUIRE(element.get_tag() == "h3");
                    REQUIRE(element.get_type() == docpp::HTML::Type::Non_Self_Closing);
                    REQUIRE(element.get() == "<h3></h3>");
                } else if (index == 4) {
                    REQUIRE(element.get_tag() == "h2");
                    REQUIRE(element.get_type() == docpp::HTML::Type::Non_Self_Closing);
                    REQUIRE(element.get() == "<h2></h2>");
                }

                ++index;
            }

            index = 0;
            for (Section::const_reverse_iterator it = section.crbegin(); it != section.crend(); ++it) {
                Element element = *it;

                if (index == 0) {
                    REQUIRE(element.get_tag() == "h6");
                    REQUIRE(element.get_type() == docpp::HTML::Type::Non_Self_Closing);
                    REQUIRE(element.get() == "<h6></h6>");
                } else if (index == 1) {
                    REQUIRE(element.get_tag() == "h5");
                    REQUIRE(element.get_type() == docpp::HTML::Type::Non_Self_Closing);
                    REQUIRE(element.get() == "<h5></h5>");
                } else if (index == 2) {
                    REQUIRE(element.get_tag() == "h4");
                    REQUIRE(element.get_type() == docpp::HTML::Type::Non_Self_Closing);
                    REQUIRE(element.get() == "<h4></h4>");
                } else if (index == 3) {
                    REQUIRE(element.get_tag() == "h3");
                    REQUIRE(element.get_type() == docpp::HTML::Type::Non_Self_Closing);
                    REQUIRE(element.get() == "<h3></h3>");
                } else if (index == 4) {
                    REQUIRE(element.get_tag() == "h2");
                    REQUIRE(element.get_type() == docpp::HTML::Type::Non_Self_Closing);
                    REQUIRE(element.get() == "<h2></h2>");
                }

                ++index;
            }
        };

        const auto test_find = []() {
            using namespace docpp::HTML;

            Section section{docpp::HTML::Tag::Html, {}};

            section.push_back(Element{docpp::HTML::Tag::H2, {}, "data"});
            section.push_back(Element{docpp::HTML::Tag::H3, {}, "data"});
            section.push_back(Element{docpp::HTML::Tag::H4, {}, "data"});
            section.push_back(Element{docpp::HTML::Tag::H5, {}, "data"});
            section.push_back(Element{docpp::HTML::Tag::H6, {}, "data"});

            REQUIRE(section.find(Element{docpp::HTML::Tag::H2, {}, "data"}) == 0);
            REQUIRE(section.find(Element{docpp::HTML::Tag::H3, {}, "data"}) == 1);
            REQUIRE(section.find(Element{docpp::HTML::Tag::H4, {}, "data"}) == 2);
            REQUIRE(section.find(Element{docpp::HTML::Tag::H5, {}, "data"}) == 3);
            REQUIRE(section.find(Element{docpp::HTML::Tag::H6, {}, "data"}) == 4);
            REQUIRE(section.find(Element{docpp::HTML::Tag::H1, {}, "data"}) == Section::npos);

            REQUIRE(section.find("h2") == 0);
            REQUIRE(section.find("h3") == 1);
            REQUIRE(section.find("h4") == 2);
            REQUIRE(section.find("h5") == 3);
            REQUIRE(section.find("h6") == 4);

            REQUIRE(section.find("<h2>data</h2>") == 0);
            REQUIRE(section.find("<h3>data</h3>") == 1);
            REQUIRE(section.find("<h4>data</h4>") == 2);
            REQUIRE(section.find("<h5>data</h5>") == 3);
            REQUIRE(section.find("<h6>data</h6>") == 4);
            REQUIRE(section.find("data") == 0);
            REQUIRE(section.find("h1") == Section::npos);
            REQUIRE(section.find("docpp sucks") == Section::npos);
        };

        const auto test_insert = []() {
            using namespace docpp::HTML;

            Section section{docpp::HTML::Tag::Html, {}};

            section.push_back(Element{docpp::HTML::Tag::H2, {}, "data"});
            section.push_back(Element{docpp::HTML::Tag::H3, {}, "data"});
            section.push_back(Element{docpp::HTML::Tag::H4, {}, "data"});
            section.push_back(Element{docpp::HTML::Tag::H5, {}, "data"});
            section.push_back(Element{docpp::HTML::Tag::H6, {}, "data"});

            std::size_t pos = section.find("h2");

            Element element = section[pos];

            std::size_t pos2 = section.find("h4");

            section.insert(pos2, element);

            REQUIRE(section.at(pos2) == element);
            REQUIRE(section.get_elements().at(pos2) == element);
            REQUIRE(section.get_elements().at(pos2).get_tag() == "h2");
        };

        const auto test_swap = []() {
            using namespace docpp::HTML;

            Section section{docpp::HTML::Tag::Html, {}};

            section.push_back(Element{docpp::HTML::Tag::H2, {}, "data"});
            section.push_back(Element{docpp::HTML::Tag::H3, {}, "data"});
            section.push_back(Element{docpp::HTML::Tag::H4, {}, "data"});
            section.push_back(Element{docpp::HTML::Tag::H5, {}, "data"});
            section.push_back(Element{docpp::HTML::Tag::H6, {}, "data"});

            std::size_t pos1 = section.find("h2");
            Element element1 = section[pos1];

            std::size_t pos2 = section.find("h4");
            Element element2 = section[pos2];

            section.swap(pos1, pos2);

            REQUIRE(section[pos1] == element2);
            REQUIRE(section[pos2] == element1);

            section.swap(element1, element2);

            REQUIRE(section[pos1] == element1);
            REQUIRE(section[pos2] == element2);
        };

        const auto test_front_and_back = []() {
            using namespace docpp::HTML;

            Section section{docpp::HTML::Tag::Html, {}};

            section.push_back(Element{docpp::HTML::Tag::H2, {}, "data"});
            section.push_back(Element{docpp::HTML::Tag::H3, {}, "data"});
            section.push_back(Element{docpp::HTML::Tag::H4, {}, "data"});
            section.push_back(Element{docpp::HTML::Tag::H5, {}, "data"});
            section.push_back(Element{docpp::HTML::Tag::H6, {}, "data"});

            REQUIRE(section.front().get_tag() == "h2");
            REQUIRE(section.front().get_data() == "data");

            REQUIRE(section.back().get_tag() == "h6");
            REQUIRE(section.back().get_data() == "data");
        };

        const auto test_size_empty_and_clear = []() {
            using namespace docpp::HTML;

            Section section{docpp::HTML::Tag::Html, {}};

            section.push_back(Element{docpp::HTML::Tag::H2, {}, "data"});
            section.push_back(Element{docpp::HTML::Tag::H3, {}, "data"});
            section.push_back(Element{docpp::HTML::Tag::H4, {}, "data"});
            section.push_back(Element{docpp::HTML::Tag::H5, {}, "data"});
            section.push_back(Element{docpp::HTML::Tag::H6, {}, "data"});

            REQUIRE(section.size() == 5);
            REQUIRE(section.empty() == false);

            section.clear();

            REQUIRE(section.size() == 0);
            REQUIRE(section.empty() == true);
        };

        const auto test_push_front_and_back = []() {
            using namespace docpp::HTML;

            Section section{docpp::HTML::Tag::Html, {}};

            section.push_front(Element{docpp::HTML::Tag::H2, {}, "data"});
            section.push_back(Element{docpp::HTML::Tag::H3, {}, "data"});

            REQUIRE(section.front().get_tag() == "h2");
            REQUIRE(section.front().get_data() == "data");

            REQUIRE(section.back().get_tag() == "h3");
            REQUIRE(section.back().get_data() == "data");
        };

        const auto test_string_get = []() {
            using namespace docpp::HTML;

            Section section{docpp::HTML::Tag::Html, {}};

            section.push_back(Element{docpp::HTML::Tag::H2, {}, "data"});
            section.push_back(Element{docpp::HTML::Tag::H3, {}, "data"});
            section.push_back(Element{docpp::HTML::Tag::H4, {}, "data"});
            section.push_back(Element{docpp::HTML::Tag::H5, {}, "data"});

            const std::string expected_1 = "<html><h2>data</h2><h3>data</h3><h4>data</h4><h5>data</h5></html>";
            const std::string expected_2 = "<html>\n<h2>data</h2>\n<h3>data</h3>\n<h4>data</h4>\n<h5>data</h5>\n</html>";
            const std::string expected_3 = "<html>\n\t<h2>data</h2>\n\t<h3>data</h3>\n\t<h4>data</h4>\n\t<h5>data</h5>\n</html>";

            REQUIRE(section.get() == expected_1);
            REQUIRE(section.get<std::string>() == expected_1);
            REQUIRE(section.get<std::string>(docpp::HTML::Formatting::None) == expected_1);
            REQUIRE(section.get<std::string>(docpp::HTML::Formatting::Newline) == expected_2);
            REQUIRE(section.get<std::string>(docpp::HTML::Formatting::Pretty) == expected_3);
        };

        const auto test_handle_elements = []() {
            using namespace docpp::HTML;

            Section section{docpp::HTML::Tag::Html, {}};

            section.push_back(Element{docpp::HTML::Tag::H2, {}, "data"});
            section.push_back(Element{docpp::HTML::Tag::H3, {}, "data"});
            section.push_back(Element{docpp::HTML::Tag::H4, {}, "data"});
            section.push_back(Element{docpp::HTML::Tag::H5, {}, "data"});

            Element retrieved_elem1 = section.get_elements().at(0);
            Element retrieved_elem2 = section.get_elements().at(1);
            Element retrieved_elem3 = section.get_elements().at(2);
            Element retrieved_elem4 = section.get_elements().at(3);

            REQUIRE(retrieved_elem1.get_tag() == "h2");
            REQUIRE(retrieved_elem1.get_data() == "data");
            REQUIRE(retrieved_elem2.get_tag() == "h3");
            REQUIRE(retrieved_elem2.get_data() == "data");
            REQUIRE(retrieved_elem3.get_tag() == "h4");
            REQUIRE(retrieved_elem3.get_data() == "data");
            REQUIRE(retrieved_elem4.get_tag() == "h5");
            REQUIRE(retrieved_elem4.get_data() == "data");
        };

        const auto test_handle_sections = []() {
            using namespace docpp::HTML;

            Section section{docpp::HTML::Tag::Html, {}};

            section.push_back(Element{docpp::HTML::Tag::H2, {}, "data"});
            section.push_back(Element{docpp::HTML::Tag::H3, {}, "data"});
            section.push_back(Element{docpp::HTML::Tag::H4, {}, "data"});

            Section new_section = section;

            new_section.set_tag(docpp::HTML::Tag::Div);
            section.push_back(new_section);

            REQUIRE(section.get() == "<html><h2>data</h2><h3>data</h3><h4>data</h4><div><h2>data</h2><h3>data</h3><h4>data</h4></div></html>");

            Section retrieved_section = section.get_sections().at(0);

            REQUIRE(retrieved_section.get_tag() == "div");

            Element retrieved_elem1 = retrieved_section.get_elements().at(0);
            Element retrieved_elem2 = retrieved_section.get_elements().at(1);
            Element retrieved_elem3 = retrieved_section.get_elements().at(2);

            REQUIRE(retrieved_elem1.get_tag() == "h2");
            REQUIRE(retrieved_elem1.get_data() == "data");
            REQUIRE(retrieved_elem2.get_tag() == "h3");
            REQUIRE(retrieved_elem2.get_data() == "data");
            REQUIRE(retrieved_elem3.get_tag() == "h4");
            REQUIRE(retrieved_elem3.get_data() == "data");
        };

        const auto the_test_to_end_all_tests = []() {
            using namespace docpp::HTML;

            Section base_section{docpp::HTML::Tag::Html, {}};

            base_section.push_back(Element{docpp::HTML::Tag::H2, {}, "data"});
            base_section.push_back(Element{docpp::HTML::Tag::H3, {}, "data"});
            base_section.push_back(Element{docpp::HTML::Tag::H4, {}, "data"});
            base_section.push_back(Element{docpp::HTML::Tag::H5, {}, "data"});

            REQUIRE(base_section.get() == "<html><h2>data</h2><h3>data</h3><h4>data</h4><h5>data</h5></html>");

            Section section{docpp::HTML::Tag::Html, {}};
            Section section_plus_plus{docpp::HTML::Tag::Html, {}};

            // just... why? because i can, that's why
            for (std::size_t i = 0; i < 10; ++i) {
                Section _section{docpp::HTML::Tag::Div, {}};

                _section.push_back(Element{docpp::HTML::Tag::P, {}, "Data " + std::to_string(i)});

                section_plus_plus += _section;
                section_plus_plus += section_plus_plus;

                REQUIRE(section_plus_plus.size() == (i + 1) * 2);
            }
        };

        test_get_and_set();
        test_copy_section();
        test_operators();
        test_constructors();
        test_iterators();
        test_find();
        test_insert();
        test_swap();
        test_front_and_back();
        test_size_empty_and_clear();
        test_push_front_and_back();
        test_string_get();
        test_constructors();
        test_handle_elements();
        test_handle_sections();
        the_test_to_end_all_tests();
    }

    void test_document() {
        const auto test_get_and_set = []() {
            using namespace docpp::HTML;

            Document document;

            document.set(Section {
                docpp::HTML::Tag::Html, {},
                {
                    Element{docpp::HTML::Tag::H1, {}, "data1"},
                    Element{docpp::HTML::Tag::H2, {}, "data2"},
                    Element{docpp::HTML::Tag::H3, {}, "data3"},
                    Element{docpp::HTML::Tag::H4, {}, "data4"},
                    Element{docpp::HTML::Tag::H5, {}, "data5"},
                    Element{docpp::HTML::Tag::H6, {}, "data6"}
                }
            });

            REQUIRE(document.get() == "<!DOCTYPE html><html><h1>data1</h1><h2>data2</h2><h3>data3</h3><h4>data4</h4><h5>data5</h5><h6>data6</h6></html>");
            REQUIRE(document.get<std::string>() == "<!DOCTYPE html><html><h1>data1</h1><h2>data2</h2><h3>data3</h3><h4>data4</h4><h5>data5</h5><h6>data6</h6></html>");
            REQUIRE(document.get<std::string>(docpp::HTML::Formatting::None) == "<!DOCTYPE html><html><h1>data1</h1><h2>data2</h2><h3>data3</h3><h4>data4</h4><h5>data5</h5><h6>data6</h6></html>");
            REQUIRE(document.get<std::string>(docpp::HTML::Formatting::Pretty) == "<!DOCTYPE html>\n<html>\n\t<h1>data1</h1>\n\t<h2>data2</h2>\n\t<h3>data3</h3>\n\t<h4>data4</h4>\n\t<h5>data5</h5>\n\t<h6>data6</h6>\n</html>");
            REQUIRE(document.get<std::string>(docpp::HTML::Formatting::Newline) == "<!DOCTYPE html>\n<html>\n<h1>data1</h1>\n<h2>data2</h2>\n<h3>data3</h3>\n<h4>data4</h4>\n<h5>data5</h5>\n<h6>data6</h6>\n</html>");

            REQUIRE(document.get_doctype() == "<!DOCTYPE html>");
            REQUIRE(document.get_section() == Section {
                docpp::HTML::Tag::Html, {},
                {
                    Element{docpp::HTML::Tag::H1, {}, "data1"},
                    Element{docpp::HTML::Tag::H2, {}, "data2"},
                    Element{docpp::HTML::Tag::H3, {}, "data3"},
                    Element{docpp::HTML::Tag::H4, {}, "data4"},
                    Element{docpp::HTML::Tag::H5, {}, "data5"},
                    Element{docpp::HTML::Tag::H6, {}, "data6"}
                }
            });

            REQUIRE(document.get_section().get() == "<html><h1>data1</h1><h2>data2</h2><h3>data3</h3><h4>data4</h4><h5>data5</h5><h6>data6</h6></html>");

            document.set_doctype("<!NEW_DOCTYPE html>");

            REQUIRE(document.get_doctype() == "<!NEW_DOCTYPE html>");
            REQUIRE(document.get() == "<!NEW_DOCTYPE html><html><h1>data1</h1><h2>data2</h2><h3>data3</h3><h4>data4</h4><h5>data5</h5><h6>data6</h6></html>");
        };

        const auto test_copy_document = []() {
            using namespace docpp::HTML;

            Document document;

            document.set(Section {
                docpp::HTML::Tag::Html, {},
                {
                    Element{docpp::HTML::Tag::H1, {}, "data1"},
                    Element{docpp::HTML::Tag::H2, {}, "data2"},
                    Element{docpp::HTML::Tag::H3, {}, "data3"},
                    Element{docpp::HTML::Tag::H4, {}, "data4"},
                    Element{docpp::HTML::Tag::H5, {}, "data5"},
                    Element{docpp::HTML::Tag::H6, {}, "data6"}
                }
            });

            Document new_document = document;

            REQUIRE(document == new_document);
            REQUIRE(document.empty() == false);

            document.clear();

            REQUIRE(document.empty() == true);

            document = std::move(new_document);

            REQUIRE(document.empty() == false);
        };

        const auto test_operators = []() {
            using namespace docpp::HTML;

            Document document1;
            Document document2;

            document1.set(Section {
                docpp::HTML::Tag::Html, {},
                {
                    Element{docpp::HTML::Tag::H1, {}, "data1"},
                    Element{docpp::HTML::Tag::H2, {}, "data2"},
                    Element{docpp::HTML::Tag::H3, {}, "data3"},
                    Element{docpp::HTML::Tag::H4, {}, "data4"},
                    Element{docpp::HTML::Tag::H5, {}, "data5"},
                    Element{docpp::HTML::Tag::H6, {}, "data6"}
                }
            });

            document2.set(Section {
                docpp::HTML::Tag::Html, {},
                {
                    Element{docpp::HTML::Tag::H1, {}, "data1"},
                    Element{docpp::HTML::Tag::H2, {}, "data2"},
                    Element{docpp::HTML::Tag::H3, {}, "data3"},
                    Element{docpp::HTML::Tag::H4, {}, "data4"},
                    Element{docpp::HTML::Tag::H5, {}, "data5"},
                    Element{docpp::HTML::Tag::H6, {}, "data6"}
                }
            });

            REQUIRE(document1 == document2);

            document2.set(Section {
                docpp::HTML::Tag::Html, {},
                {
                    Element{docpp::HTML::Tag::H6, {}, "data1"},
                    Element{docpp::HTML::Tag::H5, {}, "data2"},
                    Element{docpp::HTML::Tag::H4, {}, "data3"},
                    Element{docpp::HTML::Tag::H3, {}, "data4"},
                    Element{docpp::HTML::Tag::H2, {}, "data5"},
                    Element{docpp::HTML::Tag::H1, {}, "data6"}
                }
            });

            REQUIRE(document1 != document2);
        };

        const auto test_constructors = []() {
            using namespace docpp::HTML;

            Document document{};

            REQUIRE(document.get_doctype() == "<!DOCTYPE html>");
            REQUIRE(document.get_section().get_tag() == "");
            REQUIRE(document.get_section().get_sections().empty());
            REQUIRE(document.get_section().get_elements().empty());
            REQUIRE(document.get_section().get_properties().empty());

            Document document2(Section {
                docpp::HTML::Tag::Html, {},
                {
                    Element{docpp::HTML::Tag::H1, {}, "data1"},
                    Element{docpp::HTML::Tag::H2, {}, "data2"},
                    Element{docpp::HTML::Tag::H3, {}, "data3"},
                    Element{docpp::HTML::Tag::H4, {}, "data4"},
                    Element{docpp::HTML::Tag::H5, {}, "data5"},
                    Element{docpp::HTML::Tag::H6, {}, "data6"}
                }
            });

            REQUIRE(document2.get_doctype() == "<!DOCTYPE html>");
            REQUIRE(document2.get_section().get_tag() == "html");
            REQUIRE(document2.get_section().get_sections().empty());
            REQUIRE(document2.get_section().get_elements().size() == 6);
            REQUIRE(document2.get_section().get_properties().empty());

            Document document3(Section(docpp::HTML::Tag::Html, {}, {
                Section(docpp::HTML::Tag::Head, {}, {
                    Element(docpp::HTML::Tag::Title, {}, "Title")
                }),
                Section(docpp::HTML::Tag::Body, {}, {
                    Element(docpp::HTML::Tag::H1, {}, "Hello, World!")
                }),
            }), "<!NEW_DOCTYPE html>");

            REQUIRE(document3.get_doctype() == "<!NEW_DOCTYPE html>");
            REQUIRE(document3.get_section().get_tag() == "html");
            REQUIRE(document3.get_section().get_sections().size() == 2);
            REQUIRE(document3.get_section().get_elements().empty());
            REQUIRE(document3.get_section().get_properties().empty());
        };

        test_get_and_set();
        test_copy_document();
        test_operators();
        test_constructors();
    }

    void test_html() {
        test_tag();
        test_property();
        test_properties();
        test_element();
        test_section();
        test_document();
    }
} // namespace HTML

inline namespace CSS {
    void test_property() {
        const auto test_get_and_set = []() {
            using namespace docpp::CSS;

            Property property;

            property.set("key", "value");

            REQUIRE(property.get().first == "key");
            REQUIRE(property.get().second == "value");
            REQUIRE(property.get_key() == "key");
            REQUIRE(property.get_value() == "value");

            property.set_key("new_key");

            REQUIRE(property.get().first == "new_key");
            REQUIRE(property.get().second == "value");
            REQUIRE(property.get_key() == "new_key");
            REQUIRE(property.get_value() == "value");

            property.set_value("new_value");

            REQUIRE(property.get().first == "new_key");
            REQUIRE(property.get().second == "new_value");
            REQUIRE(property.get_key() == "new_key");
            REQUIRE(property.get_value() == "new_value");

            REQUIRE(property.get_key<std::string>() == "new_key");
            REQUIRE(property.get_value<std::string>() == "new_value");
        };

        const auto test_operators = []() {
            using namespace docpp::CSS;

            Property property1;
            Property property2;

            property1.set("key", "value");
            property2.set("key", "value2");

            REQUIRE(property1 == property1);
            REQUIRE(property1 != property2);

            property2 = property1;

            REQUIRE(property1 == property2);

            property2.set("key2", "value2");

            REQUIRE(property1 != property2);
        };

        test_get_and_set();
        test_operators();
    }

    void test_element() {
        const auto test_get_and_set = []() {
            using namespace docpp::CSS;

            Element element;

            element.set_tag("my_element");

            REQUIRE(element.get_tag() == "my_element");
            REQUIRE(element.get_properties().empty());

            element.set_properties({{Property{"key", "value"}, Property{"key2", "value2"}}});

            REQUIRE(element.get_properties().at(0).get().first == "key");
            REQUIRE(element.get_properties().at(0).get().second == "value");
            REQUIRE(element.get_properties().at(1).get().first == "key2");
            REQUIRE(element.get_properties().at(1).get().second == "value2");

            element.set("new_element", {{Property{"key", "value"}, Property{"key2", "value2"}}});

            REQUIRE(element.get_tag() == "new_element");
            REQUIRE(element.get_properties().at(0).get().first == "key");
            REQUIRE(element.get_properties().at(0).get().second == "value");
            REQUIRE(element.get_properties().at(1).get().first == "key2");
            REQUIRE(element.get_properties().at(1).get().second == "value2");

            element.set_properties({{Property{"key3", "value3"}, Property{"key4", "value4"}}});

            REQUIRE(element.get_properties().at(0).get().first == "key3");
            REQUIRE(element.get_properties().at(0).get().second == "value3");
            REQUIRE(element.get_properties().at(1).get().first == "key4");
            REQUIRE(element.get_properties().at(1).get().second == "value4");
        };

        const auto test_operators = []() {
            using namespace docpp::CSS;

            Element element1;
            Element element2;

            element1.set("my_element", {{Property{"key", "value"}, Property{"key2", "value2"}}});
            element2.set("my_element", {{Property{"key", "value"}, Property{"key2", "value2"}}});

            REQUIRE(element1 == element2);

            element2.set("new_element", {{Property{"key", "value"}, Property{"key2", "value2"}}});

            REQUIRE(element1 != element2);

            element2 = element1;

            REQUIRE(element1 == element2);
        };

        const auto test_constructors = []() {
            using namespace docpp::CSS;

            Element element{};

            REQUIRE(element.get_tag() == "");
            REQUIRE(element.get_properties().empty());
            REQUIRE(element.get().empty());

            Element element2{"my_element", {{Property{"key", "value"}, Property{"key2", "value2"}}}};

            REQUIRE(element2.get_tag() == "my_element");
            REQUIRE(element2.get_properties().at(0).get().first == "key");
            REQUIRE(element2.get_properties().at(0).get().second == "value");
            REQUIRE(element2.get_properties().at(1).get().first == "key2");
            REQUIRE(element2.get_properties().at(1).get().second == "value2");
        };

        const auto test_copy_section = []() {
            using namespace docpp::CSS;

            Element element;

            element.set("my_element", {{Property{"key", "value"}, Property{"key2", "value2"}}});

            Element element2 = element;

            REQUIRE(element == element2);

            element2.set("new_element", {{Property{"key", "value"}, Property{"key2", "value2"}}});

            REQUIRE(element != element2);

            element2 = std::move(element);

            REQUIRE(element2.get_tag() == "my_element");
        };

        const auto test_iterators = []() {
            using namespace docpp::CSS;

            Element element;

            element.set("my_element", {{Property{"key", "value"}, Property{"key2", "value2"}}});

            std::size_t index{0};
            for (Element::iterator it = element.begin(); it != element.end(); ++it) {
                Property property = *it;

                if (index == 0) {
                    REQUIRE(property.get().first == "key");
                    REQUIRE(property.get().second == "value");
                } else if (index == 1) {
                    REQUIRE(property.get().first == "key2");
                    REQUIRE(property.get().second == "value2");
                }

                ++index;
            }

            index = 0;
            for (Element::const_iterator it = element.cbegin(); it != element.cend(); ++it) {
                Property property = *it;

                if (index == 0) {
                    REQUIRE(property.get().first == "key");
                    REQUIRE(property.get().second == "value");
                } else if (index == 1) {
                    REQUIRE(property.get().first == "key2");
                    REQUIRE(property.get().second == "value2");
                }

                ++index;
            }

            index = 0;
            for (Element::reverse_iterator it = element.rbegin(); it != element.rend(); ++it) {
                Property property = *it;

                if (index == 0) {
                    REQUIRE(property.get().first == "key2");
                    REQUIRE(property.get().second == "value2");
                } else if (index == 1) {
                    REQUIRE(property.get().first == "key");
                    REQUIRE(property.get().second == "value");
                }

                ++index;
            }

            index = 0;
            for (Element::const_reverse_iterator it = element.crbegin(); it != element.crend(); ++it) {
                Property property = *it;

                if (index == 0) {
                    REQUIRE(property.get().first == "key2");
                    REQUIRE(property.get().second == "value2");
                } else if (index == 1) {
                    REQUIRE(property.get().first == "key");
                    REQUIRE(property.get().second == "value");
                }

                ++index;
            }
        };

        const auto test_find = []() {
            using namespace docpp::CSS;

            Element element;

            element.set("my_element", {{Property{"key", "value"}, Property{"key2", "value2"}}});

            REQUIRE(element.find(Property{"key", "value"}) == 0);
            REQUIRE(element.find("key") == 0);
            REQUIRE(element.find(Property{"key2", "value2"}) == 1);
            REQUIRE(element.find("key2") == 1);
            REQUIRE(element.find("key3") == Element::npos);
            REQUIRE(element.find(Property{"key3", "value3"}) == Element::npos);

            Property property = element.at(element.find("key2"));

            REQUIRE(property.get().first == "key2");
        };

        const auto test_insert = []() {
            using namespace docpp::CSS;

            Element element;

            element.set("my_element", {{Property{"key", "value"}, Property{"key2", "value2"}}});

            std::size_t pos = element.find("key");

            Property property = element.at(pos);

            std::size_t pos2 = element.find("key2");

            element.insert(pos2, property);

            REQUIRE(element.at(pos2) == property);
            REQUIRE(element.get_properties().at(pos2) == property);
            REQUIRE(element.get_properties().at(pos2).get().first == "key");
        };

        const auto test_swap = []() {
            using namespace docpp::CSS;

            Element element;

            element.set("my_element", {{Property{"key", "value"}, Property{"key2", "value2"}}});

            std::size_t pos1 = element.find("key");
            Property property1 = element.at(pos1);

            std::size_t pos2 = element.find("key2");
            Property property2 = element.at(pos2);

            element.swap(pos1, pos2);

            REQUIRE(element[pos1] == property2);
            REQUIRE(element[pos2] == property1);
        };

        const auto test_front_and_back = []() {
            using namespace docpp::CSS;

            Element element;

            element.set("my_element", {{Property{"key", "value"}, Property{"key2", "value2"}}});

            REQUIRE(element.front().get().first == "key");
            REQUIRE(element.back().get().first == "key2");
        };

        const auto test_size_empty_and_clear = []() {
            using namespace docpp::CSS;

            Element element;

            element.set("my_element", {{Property{"key", "value"}, Property{"key2", "value2"}}});

            REQUIRE(element.size() == 2);
            REQUIRE(element.empty() == false);

            element.clear();

            REQUIRE(element.size() == 0);
            REQUIRE(element.empty() == true);
        };

        const auto test_push_front_and_back = []() {
            using namespace docpp::CSS;

            Element element;

            element.push_front(Property{"key", "value"});
            element.push_back(Property{"key2", "value2"});

            REQUIRE(element.front().get().first == "key");
            REQUIRE(element.back().get().first == "key2");
        };

        const auto test_string_get = []() {
            using namespace docpp::CSS;

            Element element;

            element.set("my_element", {{Property{"key", "value"}, Property{"key2", "value2"}}});

            const std::string expected_1 = "my_element {key: value;key2: value2;}";
            const std::string expected_2 = "my_element {\nkey: value;\nkey2: value2;\n}\n";
            const std::string expected_3 = "my_element {\n\tkey: value;\n\tkey2: value2;\n}\n";

            REQUIRE(element.get() == expected_1);
            REQUIRE(element.get<std::string>() == expected_1);
            REQUIRE(element.get<std::string>(docpp::CSS::Formatting::None) == expected_1);
            REQUIRE(element.get<std::string>(docpp::CSS::Formatting::Newline) == expected_2);
            REQUIRE(element.get<std::string>(docpp::CSS::Formatting::Pretty) == expected_3);
        };

        const auto test_handle_elements = []() {
            using namespace docpp::CSS;

            Element element;

            element.set("my_element", {{Property{"key", "value"}, Property{"key2", "value2"}}});

            Property retrieved_prop1 = element.get_properties().at(0);
            Property retrieved_prop2 = element.get_properties().at(1);

            REQUIRE(retrieved_prop1.get().first == "key");
            REQUIRE(retrieved_prop1.get().second == "value");
            REQUIRE(retrieved_prop2.get().first == "key2");
            REQUIRE(retrieved_prop2.get().second == "value2");
        };

        test_get_and_set();
        test_operators();
        test_get_and_set();
        test_constructors();
        test_copy_section();
        test_iterators();
        test_find();
        test_insert();
        test_swap();
        test_front_and_back();
        test_size_empty_and_clear();
        test_push_front_and_back();
        test_string_get();
        test_handle_elements();
    }

    void test_stylesheet() {
        const auto test_get_and_set = []() {
            using namespace docpp::CSS;

            Stylesheet stylesheet;

            stylesheet.set({Element{"my_element", {{Property{"key", "value"}, Property{"key2", "value2"}}}}});

            REQUIRE(stylesheet.at(0).get_tag() == "my_element");
            REQUIRE(stylesheet.at(0).get_properties().at(0).get().first == "key");
            REQUIRE(stylesheet.at(0).get_properties().at(0).get().second == "value");
            REQUIRE(stylesheet.at(0).get_properties().at(1).get().first == "key2");
            REQUIRE(stylesheet.at(0).get_properties().at(1).get().second == "value2");

            stylesheet.set({Element{"my_element2", {{Property{"key3", "value3"}, Property{"key4", "value4"}}}}});

            REQUIRE(stylesheet.at(0).get_tag() == "my_element2");
            REQUIRE(stylesheet.at(0).get_properties().at(0).get().first == "key3");
            REQUIRE(stylesheet.at(0).get_properties().at(0).get().second == "value3");
            REQUIRE(stylesheet.at(0).get_properties().at(1).get().first == "key4");
            REQUIRE(stylesheet.at(0).get_properties().at(1).get().second == "value4");

            try {
                static_cast<void>(stylesheet.at(1));
            } catch (const docpp::out_of_range& e) {
                REQUIRE(true);
            }

            try {
                stylesheet.at(0).at(2);
            } catch (const docpp::out_of_range& e) {
                REQUIRE(true);
            }
        };

        const auto test_copy_section = []() {
            using namespace docpp::CSS;

            Stylesheet stylesheet;

            stylesheet.set({Element{"my_element", {{Property{"key", "value"}, Property{"key2", "value2"}}}}});

            Stylesheet new_stylesheet = stylesheet;

            REQUIRE(stylesheet == new_stylesheet);
            REQUIRE(stylesheet.empty() == false);

            stylesheet.clear();

            REQUIRE(stylesheet.empty() == true);

            stylesheet = std::move(new_stylesheet);

            REQUIRE(stylesheet.empty() == false);
        };

        const auto test_operators = []() {
            using namespace docpp::CSS;

            Stylesheet stylesheet1;
            Stylesheet stylesheet2;

            Element element{"my_element", {{Property{"key", "value"}, Property{"key2", "value2"}}}};
            Element element2{"my_element", {{Property{"key", "value"}, Property{"key2", "value2"}}}};

            stylesheet1.set({element});
            stylesheet2.set({element2});

            REQUIRE(stylesheet1 == stylesheet2);

            element2.set("my_element2", {{Property{"key3", "value3"}, Property{"key4", "value4"}}});
            stylesheet2.set({element2});

            REQUIRE(stylesheet1 != stylesheet2);
        };

        const auto test_constructors = []() {
            using namespace docpp::CSS;

            Stylesheet stylesheet{};

            REQUIRE(stylesheet.empty() == true);

            Stylesheet stylesheet2{{Element{"my_element", {{Property{"key", "value"}, Property{"key2", "value2"}}}}}};

            REQUIRE(stylesheet2.size() == 1);

            Stylesheet stylesheet3 = docpp::CSS::make_stylesheet(
                docpp::CSS::make_element(
                    "my_element", docpp::CSS::make_properties(Property{"property1", "data1"}, Property{"property2", "data2"})
                ),
                docpp::CSS::make_element(
                    "my_element_2", docpp::CSS::make_properties(Property{"property3", "data3"}, Property{"property4", "data4"})
                )
            );

            REQUIRE(stylesheet3.size() == 2);
            REQUIRE(stylesheet3.get<std::string>() == "my_element {property1: data1;property2: data2;}my_element_2 {property3: data3;property4: data4;}");
            REQUIRE(stylesheet3.at(1).at(1).get().first == "property4");
        };

        const auto test_push_front_and_back = []() {
            using namespace docpp::CSS;

            Stylesheet stylesheet;

            stylesheet.push_front(Element{"my_element", {{Property{"key", "value"}, Property{"key2", "value2"}}}});
            stylesheet.push_back(Element{"my_element2", {{Property{"key3", "value3"}, Property{"key4", "value4"}}}});

            REQUIRE(stylesheet.front().get_tag() == "my_element");
            REQUIRE(stylesheet.back().get_tag() == "my_element2");
        };

        const auto test_swap = []() {
            using namespace docpp::CSS;

            Stylesheet stylesheet;

            stylesheet.push_back(Element{"my_element", {{Property{"key", "value"}, Property{"key2", "value2"}}}});
            stylesheet.push_back(Element{"my_element2", {{Property{"key3", "value3"}, Property{"key4", "value4"}}}});

            std::size_t pos1 = stylesheet.find("my_element");
            Element element1 = stylesheet.at(pos1);

            std::size_t pos2 = stylesheet.find("my_element2");
            Element element2 = stylesheet.at(pos2);

            stylesheet.swap(pos1, pos2);

            REQUIRE(stylesheet.at(pos1) == element2);
            REQUIRE(stylesheet.at(pos2) == element1);

            stylesheet.swap(element1, element2);

            REQUIRE(stylesheet.at(pos1) == element1);
            REQUIRE(stylesheet.at(pos2) == element2);
        };

        const auto test_size_empty_and_clear = []() {
            using namespace docpp::CSS;

            Stylesheet stylesheet;

            stylesheet.push_back(Element{"my_element", {{Property{"key", "value"}, Property{"key2", "value2"}}}});
            stylesheet.push_back(Element{"my_element2", {{Property{"key3", "value3"}, Property{"key4", "value4"}}}});

            REQUIRE(stylesheet.size() == 2);
            REQUIRE(stylesheet.empty() == false);

            stylesheet.clear();

            REQUIRE(stylesheet.size() == 0);
            REQUIRE(stylesheet.empty() == true);
        };

        const auto test_insert = []() {
            using namespace docpp::CSS;

            Stylesheet stylesheet;

            stylesheet.push_back(Element{"my_element", {{Property{"key", "value"}, Property{"key2", "value2"}}}});
            stylesheet.push_back(Element{"my_element2", {{Property{"key3", "value3"}, Property{"key4", "value4"}}}});

            std::size_t pos = stylesheet.find("my_element");

            Element element = stylesheet.at(pos);

            std::size_t pos2 = stylesheet.find("my_element2");

            stylesheet.insert(pos2, element);

            REQUIRE(stylesheet.at(pos2) == element);
            REQUIRE(stylesheet.at(pos2).get_tag() == "my_element");
        };

        const auto test_iterators = []() {
            using namespace docpp::CSS;

            Stylesheet stylesheet;

            stylesheet.push_back(Element{"my_element", {{Property{"key", "value"}, Property{"key2", "value2"}}}});
            stylesheet.push_back(Element{"my_element2", {{Property{"key3", "value3"}, Property{"key4", "value4"}}}});
            stylesheet.push_back(Element{"my_element3", {{Property{"key5", "value5"}, Property{"key6", "value6"}}}});
            stylesheet.push_back(Element{"my_element4", {{Property{"key7", "value7"}, Property{"key8", "value8"}}}});

            std::size_t index{0};
            for (Stylesheet::iterator it = stylesheet.begin(); it != stylesheet.end(); ++it) {
                Element element = *it;

                if (index == 0) {
                    REQUIRE(element.get_tag() == "my_element");
                } else if (index == 1) {
                    REQUIRE(element.get_tag() == "my_element2");
                } else if (index == 2) {
                    REQUIRE(element.get_tag() == "my_element3");
                } else if (index == 3) {
                    REQUIRE(element.get_tag() == "my_element4");
                }

                ++index;
            }

            index = 0;
            for (Stylesheet::const_iterator it = stylesheet.cbegin(); it != stylesheet.cend(); ++it) {
                Element element = *it;

                if (index == 0) {
                    REQUIRE(element.get_tag() == "my_element");
                } else if (index == 1) {
                    REQUIRE(element.get_tag() == "my_element2");
                } else if (index == 2) {
                    REQUIRE(element.get_tag() == "my_element3");
                } else if (index == 3) {
                    REQUIRE(element.get_tag() == "my_element4");
                }

                ++index;
            }

            index = 0;
            for (Stylesheet::reverse_iterator it = stylesheet.rbegin(); it != stylesheet.rend(); ++it) {
                Element element = *it;

                if (index == 0) {
                    REQUIRE(element.get_tag() == "my_element4");
                } else if (index == 1) {
                    REQUIRE(element.get_tag() == "my_element3");
                } else if (index == 2) {
                    REQUIRE(element.get_tag() == "my_element2");
                } else if (index == 3) {
                    REQUIRE(element.get_tag() == "my_element");
                }

                ++index;
            }

            index = 0;
            for (Stylesheet::const_reverse_iterator it = stylesheet.crbegin(); it != stylesheet.crend(); ++it) {
                Element element = *it;

                if (index == 0) {
                    REQUIRE(element.get_tag() == "my_element4");
                } else if (index == 1) {
                    REQUIRE(element.get_tag() == "my_element3");
                } else if (index == 2) {
                    REQUIRE(element.get_tag() == "my_element2");
                } else if (index == 3) {
                    REQUIRE(element.get_tag() == "my_element");
                }

                ++index;
            }

            index = 0;

            for (const auto& it : stylesheet) {
                Element element = it;

                if (index == 0) {
                    REQUIRE(element.get_tag() == "my_element");
                } else if (index == 1) {
                    REQUIRE(element.get_tag() == "my_element2");
                } else if (index == 2) {
                    REQUIRE(element.get_tag() == "my_element3");
                } else if (index == 3) {
                    REQUIRE(element.get_tag() == "my_element4");
                }

                ++index;
            }
        };

        test_get_and_set();
        test_copy_section();
        test_operators();
        test_constructors();
        test_push_front_and_back();
        test_swap();
        test_size_empty_and_clear();
        test_insert();
        test_iterators();
    }

    void test_css() {
        test_property();
        test_element();
        test_stylesheet();
    }

} // namespace CSS

inline namespace General {
    void test_exceptions() {
        try {
            throw docpp::out_of_range{};
        } catch (const docpp::out_of_range& e) {
            REQUIRE(std::string(e.what()) == "Out of range");
        }

        try {
            throw docpp::out_of_range{"Out of range, very very out of range"};
        } catch (const docpp::out_of_range& e) {
            REQUIRE(std::string(e.what()) == "Out of range, very very out of range");
        }

        try {
            throw docpp::invalid_argument{};
        } catch (const docpp::invalid_argument& e) {
            REQUIRE(std::string(e.what()) == "Invalid argument");
        }

        try {
            throw docpp::invalid_argument{"Invalid, very very invalid argument"};
        } catch (const docpp::invalid_argument& e) {
            REQUIRE(std::string(e.what()) == "Invalid, very very invalid argument");
        }
    }

    void test_npos_values() {
        REQUIRE(docpp::HTML::Property::npos == -1);
        REQUIRE(docpp::HTML::Properties::npos == -1);
        REQUIRE(docpp::HTML::Element::npos == -1);
        REQUIRE(docpp::HTML::Section::npos == -1);
        REQUIRE(docpp::HTML::Document::npos == -1);
        REQUIRE(docpp::CSS::Property::npos == -1);
        REQUIRE(docpp::CSS::Element::npos == -1);
        REQUIRE(docpp::CSS::Stylesheet::npos == -1);
    }

    void test_version() {
        std::tuple<int, int, int> version = docpp::version();

        REQUIRE(std::get<0>(version) >= 0);
        REQUIRE(std::get<1>(version) >= 0);
        REQUIRE(std::get<2>(version) >= 0);
    }
}

/**
 * @brief Test cases for the docpp namespace.
 */
SCENARIO("Test general", "[GENERAL]") {
    General::test_exceptions();
    General::test_npos_values();
    General::test_version();
}

/**
 * @brief Test cases for the docpp namespace.
 */
SCENARIO("Test HTML", "[HTML]") {
    HTML::test_html();
}

/**
 * @brief Test cases for the docpp namespace.
 */
SCENARIO("Test CSS", "[CSS]") {
    CSS::test_css();
}

// NOLINTEND