#pragma once
#include <memory>
#include "InvoiceMasterClient/View.hpp"

namespace InvoiceMasterClient {

    class Licence : public View {
    public:
        explicit Licence(std::shared_ptr<BaseApplication> newContext) : View(newContext) {};
        std::unique_ptr<CommandStruct> run() override;
    };

} // InvoiceMasterClient