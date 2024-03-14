#pragma once

#include "InvoiceMasterServer/entities/Invoice.hpp"
#include <xercesc/sax2/DefaultHandler.hpp>
#include <xercesc/sax2/Attributes.hpp>
#include <string>
#include <stack>


namespace InvoiceMasterServer {

class InvoiceSAX2Handler : public xercesc::DefaultHandler {
protected:
    std::shared_ptr<Invoice> invoicePtr;

    const std::string containerName = "Product";
    const std::string terminateContainer = "Products";
    std::stack<std::string> currentElement{};
    bool inContainer = false;
    bool saved = false;

    std::string itemName;
    unsigned int price = 0;
    unsigned int quantity = 0;

public:

    InvoiceSAX2Handler(const std::shared_ptr<Invoice>& newInvoicePtr);

    void startElement(
            const XMLCh* const uri,
            const XMLCh* const localname,
            const XMLCh* const qname,
            const xercesc::Attributes& attrs);

    void endElement(
            const XMLCh* const uri,
            const XMLCh* const localname,
            const XMLCh* const qname);

    void fatalError(const xercesc::SAXParseException&);

    void characters(
            const XMLCh* const chars,
            const XMLSize_t length);
    };

} // xml
