#include "FileHelper.hpp"
#include <fstream>
#include <vector>

namespace helpers {

    bool FileHelper::isFileExists(const std::string& fileName) {
        std::ifstream f(fileName.c_str());
        return f.good();
    }

    void FileHelper::readEntireFileToString(const std::string &fileName, std::string &content) {
        if (!helpers::FileHelper::isFileExists(fileName)) {
            throw std::invalid_argument("File doesn't exist: " + fileName);
        }
        std::ifstream inputFileStream(fileName);

        content.assign(
                (std::istreambuf_iterator<char>(inputFileStream) ),
                (std::istreambuf_iterator<char>()));
    }

    void FileHelper::readEntireFileToVector(const std::string& fileName, std::vector<unsigned char>& content) {
        if (!helpers::FileHelper::isFileExists(fileName)) {
            throw std::invalid_argument("File doesn't exist: " + fileName);
        }
        std::ifstream inputFileStream(fileName, std::ios::binary);
        content.assign(
                (std::istreambuf_iterator<char>(inputFileStream) ),
                (std::istreambuf_iterator<char>()));
    }

    void FileHelper::writeVectorToFile(const std::string& fileName, const std::vector<unsigned char> &content) {
        std::ofstream textout(fileName, std::ios::out | std::ios::binary);
        textout.write((const char*)&content[0], content.size());
        textout.close();
    }

    void FileHelper::writeStringToFile(const std::string &fileName, const std::string &content) {
        std::ofstream textout(fileName, std::ios::out | std::ios::binary);
        textout << content;
        textout.close();
    }

} // helpers
