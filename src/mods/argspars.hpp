#pragma once

#include <string>
#include <cstdint>
#include <stdexcept>
#include <cstdlib>
#include <cerrno>
#include <algorithm>
#include <cctype>

class ArgsParser {
public:
    struct Params {
        std::string mode;
        std::string file_name;
        uint32_t offset{0};
        uint16_t length{0};
    };

    static Params parse(int argc, char* argv[]) {
        if (argc < 3) {
            throw std::invalid_argument("Usage: <program> <mode> <file_name> [offset] [length]");
        }

        Params p;
        p.mode      = trim(argv[1]);
        p.file_name = trim(argv[2]);

        if (argc >= 4) {
            p.offset = parse_uint32(argv[3], "offset");
        }

        if (argc >= 5) {
            p.length = parse_uint16(argv[4], "length");
        }

        return p;
    }

private:
    static std::string trim(const std::string& s) {
        auto start = s.begin();
        while (start != s.end() && std::isspace(static_cast<unsigned char>(*start))) {
            ++start;
        }
        auto end = s.end();
        if (start == end) return "";
        do {
            --end;
        } while (end != start && std::isspace(static_cast<unsigned char>(*end)));
        return std::string(start, end + 1);
    }

    static uint32_t parse_uint32(const char* arg, const char* name) {
        std::string s = trim(arg);
        char* endptr = nullptr;
        errno = 0;
        unsigned long val = std::strtoul(s.c_str(), &endptr, 10);
        if (errno != 0 || *endptr != '\0' || val > UINT32_MAX) {
            throw std::invalid_argument(std::string("Invalid ") + name + " value: " + s);
        }
        return static_cast<uint32_t>(val);
    }

    static uint16_t parse_uint16(const char* arg, const char* name) {
        std::string s = trim(arg);
        char* endptr = nullptr;
        errno = 0;
        unsigned long val = std::strtoul(s.c_str(), &endptr, 10);
        if (errno != 0 || *endptr != '\0' || val > UINT16_MAX) {
            throw std::invalid_argument(std::string("Invalid ") + name + " value: " + s);
        }
        return static_cast<uint16_t>(val);
    }
};
