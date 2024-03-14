#include "userInputOutput/Input.hpp"
#include <cctype>
#include <regex>

namespace userInputOutput {
    void Input::clearInput()
    {
        if (input_stream) {
            input_stream.clear();
            input_stream.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }

    void Input::read(char &c)
    {
        input_stream.get(c);
        clearInput();
    }

    void Input::readNumerical(char &c)
    {
        input_stream.get(c);
        clearInput();
        if (!std::isdigit(c)) {
            throw std::invalid_argument("Must be numerical");
        }
    }

    void Input::read(char *s, int buf_size)
    {
        input_stream.getline(s, static_cast<std::streamsize>(buf_size));
    }

    void Input::read(std::string &s)
    {
        std::getline(input_stream, s);
    }

    void Input::readNumerical(std::string &s) {
        std::getline(input_stream, s);

        std::regex regex("^\\d+$");
        if (!std::regex_match(s, regex)) {
            throw std::invalid_argument("Must be numerical");
        }
    }

    void Input::read(char *s)
    {
        read(s, static_cast<std::streamsize>(inputBufferLimit));
    }
} // userInputOutput
