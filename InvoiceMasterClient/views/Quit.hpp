#pragma once
#include "../View.hpp"

namespace InvoiceMasterClient {

    class Quit : public View {
    public:
        std::unique_ptr<CommandStruct> run() override;
    };

} // InvoiceMasterClient
