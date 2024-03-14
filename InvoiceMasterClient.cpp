#include "InvoiceMasterClient/Application.hpp"
#include <memory>

int main() {
    std::shared_ptr<InvoiceMasterClient::Application> app = std::make_shared<InvoiceMasterClient::Application>();
    app->run();
    return 0;
}
