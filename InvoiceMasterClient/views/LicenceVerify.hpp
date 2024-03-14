#pragma once
#include "InvoiceMasterClient/View.hpp"

namespace InvoiceMasterClient {

    class LicenceVerify : public View {
    public:
        explicit LicenceVerify(std::shared_ptr<BaseApplication> newContext) : View(newContext) {};
        std::unique_ptr<CommandStruct> run() override;
    };

} // InvoiceMasterClient
