#include "StringHelper.hpp"
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
#include <openssl/rand.h>
#include <iomanip>
#include <regex>

namespace helpers {

    void StringHelper::unquoteString(std::string &line) {
        std::stringstream ss;
        ss << line;
        ss >> std::quoted(line);
    }

    void StringHelper::quoteString(std::string &line) {
        std::stringstream ss;
        ss << std::quoted(line);
        line = ss.str();
    }

    void StringHelper::splitQuoted(const std::string& line, char delimiter, std::vector<std::string>& quoted, bool unquote) {
        quoted.clear();
        if (line.empty()) {
            return;
        }

        std::string buff;
        size_t found, offset = 0;
        while ((found = line.find("\"" + std::string(1, delimiter) + "\"", offset)) != std::string::npos) {
            buff = (offset == 0)
                               ? line.substr(offset, found + 1 - offset)
                               : line.substr(offset + 1, found + 1 - offset);
            offset = found + 1;
            if (unquote) {
                unquoteString(buff);
            }
            quoted.push_back(buff);
        }
        buff = line.substr(offset == 0 ? offset : offset + 1);
        if (unquote) {
            unquoteString(buff);
        }
        quoted.push_back(buff);
    }

    void StringHelper::removeSpaces(std::string& line) {
        line.erase(std::remove_if(line.begin(), line.end(), ::isspace),line.end());
    }

    void StringHelper::trimSpaces(std::string& line) {
        line.erase(line.begin(), std::find_if(line.begin(), line.end(), [](unsigned char ch) {
            return !std::isspace(ch);
        }));

        line.erase(std::find_if(line.rbegin(), line.rend(), [](unsigned char ch) {
            return !std::isspace(ch);
        }).base(), line.end());
    }

    void StringHelper::trim(std::string& line, const std::string& characters) {
        std::size_t start = line.find_first_not_of(characters);
        std::size_t end = line.find_last_not_of(characters);
        line = start == end ? std::string() : line.substr(start, end - start + 1);
    }

    void StringHelper::split(std::string& line, std::vector<std::string>& result, char delimiter) {
        std::stringstream ss(line);
        result.clear();
        while (!ss.eof()) {
            std::getline(ss, line, delimiter);
            result.emplace_back(line);
        }
    }

    void StringHelper::join(const std::set<std::string>& array, char c, std::string& line) {
        line.clear();
        for (const auto & p : array) {
            line += p;
            line += c;
        }
        if(!line.empty()) {
            line.pop_back();
        }
    }

    void StringHelper::join(const std::vector<std::string>& array, char delimiter, std::string& line, bool quote) {
        line.clear();
        for (auto p : array) {
            if (quote) {
                quoteString(p);
            }
            line += p;
            line += delimiter;
        }
        if(!line.empty()) {
            line.pop_back();
        }
    }

    void StringHelper::randomBytes(std::string &line, int length) {
        auto* charArray = new unsigned char [length];
        RAND_bytes(charArray, length);
        line.clear();
        line.insert(line.end(), charArray, charArray + length);
    }

    void StringHelper::randomString(std::string& line, size_t length)
    {
        auto randchar = []() -> char
        {
            const char charset[] =
                    "0123456789"
                    "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
                    "abcdefghijklmnopqrstuvwxyz";
            const size_t max_index = (sizeof(charset) - 1);
            return charset[ rand() % max_index ];
        };
        line = std::string(length, 0);
        std::generate_n( line.begin(), length, randchar );
    }

} // helpers
