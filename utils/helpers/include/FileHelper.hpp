#pragma once
#include <string>

namespace helpers {

    class FileHelper {
    public:
        static bool isFileExists(const std::string& fileName);
        static void readEntireFileToString(const std::string& fileName, std::string& contents);
        static void readEntireFileToVector(const std::string& fileName, std::vector<unsigned char> &content);
        static void writeStringToFile(const std::string& fileName, const std::string &content);
        static void writeVectorToFile(const std::string& fileName, const std::vector<unsigned char> &content);
    };

} // helpers