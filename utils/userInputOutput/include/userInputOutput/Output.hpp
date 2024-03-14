#pragma once
#include <memory>
#include <iostream>
#include "protocol/Response.hpp"

namespace userInputOutput {

    class Output {
    public:
        virtual void formatResponse(const std::unique_ptr<protocol::ResponseStructure>&);
        virtual void outputLine(const std::string&);
        virtual void output(const std::string&);
    protected:
        std::ostream& output_stream = std::cout;
    };

}