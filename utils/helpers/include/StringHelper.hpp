#pragma once
#include <string>
#include <vector>
#include <set>

namespace helpers {

    class StringHelper {
    public:
        static void removeSpaces(std::string& line);
        static void trimSpaces(std::string& line);
        static void trim(std::string& line, const std::string& characters);
        static void split(std::string& line, std::vector<std::string>& result, char delimiter = ',');
        static void join(const std::set<std::string>& array, char c, std::string& line);
        static void join(const std::vector<std::string>& array, char c, std::string& line, bool quote = false);
        static void randomString(std::string& line, size_t length);
        static void randomBytes(std::string& line, int length);
        static void quoteString(std::string& line);
        static void unquoteString(std::string& line);
        static void splitQuoted(const std::string& line, char delimiter, std::vector<std::string>& quoted, bool unquote = false);
    };

} // helpers