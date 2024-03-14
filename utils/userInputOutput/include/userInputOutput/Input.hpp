#pragma once

#include <iostream>
#include <string>

namespace userInputOutput {

    constexpr int inputBufferLimit = 100;

    class Input {
    private:
        void clearInput();
    public:
        std::istream& input_stream = std::cin;
        virtual ~Input() = default;

        virtual void read(char& c);
        virtual void readNumerical(char& c);
        virtual void read(std::string& s);
        virtual void readNumerical(std::string& s);
        virtual void read(char* s);
        virtual void read(char* s, int);
    };

} // userInputOutput
