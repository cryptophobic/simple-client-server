#pragma once
#include "userInputOutput/Input.hpp"
#include "userInputOutput/Output.hpp"
#include <memory>


namespace InvoiceMasterClient {

    class BaseApplication {
    public:
        explicit BaseApplication(
                std::unique_ptr<userInputOutput::Input> providedInput,
                std::unique_ptr<userInputOutput::Output> providedOutput
                )
        {
            userInputSystem = std::move(providedInput);
            userOutputSystem = std::move(providedOutput);
        }

        BaseApplication() {
            userInputSystem = std::make_unique<userInputOutput::Input>();
            userOutputSystem = std::make_unique<userInputOutput::Output>();
        }

        virtual bool isAuthorized();
        virtual bool isLicenceConfirmed();
        std::unique_ptr<userInputOutput::Input> userInputSystem;
        std::unique_ptr<userInputOutput::Output> userOutputSystem;
    protected:
        bool authorized = false;
        bool licenceConfirmed = false;
    };

} // InvoiceMasterClient
