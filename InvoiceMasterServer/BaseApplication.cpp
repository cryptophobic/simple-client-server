#include "BaseApplication.hpp"

namespace InvoiceMasterServer {

    void BaseApplication::setDisconnected()
    {
        disconnected = true;
    }

    void BaseApplication::setQuit()
    {
        quit = true;
    }

    bool BaseApplication::isDisconnected()
    {
        return disconnected;
    }

} // InvoiceMasterServer
