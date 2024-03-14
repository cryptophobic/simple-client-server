#include "InvoiceSAX2Handler.hpp"
#include "database/schema/InvoiceItem.hpp"

namespace InvoiceMasterServer {

    InvoiceSAX2Handler::InvoiceSAX2Handler(const std::shared_ptr<Invoice>& newInvoicePtr) {
        invoicePtr = newInvoicePtr;
    }

    void InvoiceSAX2Handler::startElement(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const xercesc::Attributes& attrs)
    {
        std::string elementName{xercesc::XMLString::transcode(localname)};
        if (!saved && elementName == containerName && currentElement.size() == 2) {
            inContainer = true;
        }
        currentElement.push(elementName);
    }

    void InvoiceSAX2Handler::endElement(const XMLCh *const uri, const XMLCh *const localname, const XMLCh *const qname)
    {
        currentElement.pop();
        std::string elementName{xercesc::XMLString::transcode(localname)};
        if (elementName == containerName && currentElement.size() == 2) {
            inContainer = false;
            invoicePtr->addItem(itemName, price, quantity);
            itemName = "";
            price = 0;
            quantity = 0;
        } else if (elementName == terminateContainer && currentElement.size() == 1) {
            invoicePtr->save();
            saved = true;
            inContainer = false;
        }
    }

    void InvoiceSAX2Handler::characters(const XMLCh* const chars, const XMLSize_t length)
    {
        if (inContainer) {
            std::string fieldValue{xercesc::XMLString::transcode(chars)};
            auto fieldName = currentElement.top();
            if (fieldName == database::InvoiceItem::itemName) {
                itemName = fieldValue;
            } else if (fieldName == database::InvoiceItem::price) {
                price = std::stoi(fieldValue);
            } else if (fieldName == database::InvoiceItem::quantity) {
                quantity = std::stoi(fieldValue);
            }
        }
    }

    void InvoiceSAX2Handler::fatalError(const xercesc::SAXParseException& exception)
    {
        throw std::invalid_argument(xercesc::XMLString::transcode(exception.getMessage()));
    }

} // InvoiceMasterServer
