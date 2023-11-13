#pragma once

#include <vector>
#include <string>
#include "../View.hpp"

namespace InvoiceMasterClient {

    class AdminAccess: public View {
    public:
        std::unique_ptr<CommandStruct> run() override;
    };

} // InvoiceMasterClient
