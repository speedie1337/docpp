#ifndef ENDPOINT_HPP
#define ENDPOINT_HPP

#include <string>
#include <stdexcept>
#include <filesystem>
#include <fstream>

class Endpoint {
private:
    std::string endpoint{};
    bool endpoint_set{false};
    std::ofstream fs{};
public:
    Endpoint() = default;
    explicit Endpoint(const std::string& str) {
        set_endpoint(str);
    }
    void open() {
        if (endpoint.empty()) {
            throw std::runtime_error{"Empty endpoint"};
        } else if (endpoint.at(0) == '/' || endpoint.at(0) == '\\' || endpoint.at(0) == '.') {
            throw std::runtime_error{"Invalid endpoint"};
        }

        std::string dir{std::filesystem::path(this->endpoint).parent_path()};
        if (!std::filesystem::exists(dir) && dir.empty() == false) {
            if (!std::filesystem::create_directories(dir)) {
                throw std::runtime_error{"Failed to create directory '" + dir + "'."};
            }
        }

        std::string full_path{dir};
        full_path += !full_path.empty() ? "/" : ""; full_path += std::filesystem::path(this->endpoint).filename();
        this->fs.open(full_path);

        if (!this->fs.is_open()) {
            throw std::runtime_error{"Failed to open file '" + full_path + "'"};
        }
    }
    void close() {
        if (this->fs.is_open()) {
            this->fs.close();
        }
    }
    void touch() {
        this->open();
        this->close();
    }
    bool is_open() const {
        return this->fs.is_open();
    }
    void set_endpoint(const std::string& str) {
        this->endpoint = str;
        endpoint_set = true;
        this->touch();
    }
    void append_string(const std::string& str) {
        if (!this->fs.is_open()) {
            throw std::runtime_error{"File is not open"};
        }

        this->fs << str;
    }
};

#endif //ENDPOINT_HPP
