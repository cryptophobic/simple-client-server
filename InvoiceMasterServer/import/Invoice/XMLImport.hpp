#pragma once
#include <string>
#include "InvoiceMasterServer/entities/Invoice.hpp"
#include <xercesc/sax2/SAX2XMLReader.hpp>


namespace InvoiceMasterServer {

    class XMLImport {
    protected:
        virtual std::unique_ptr<xercesc::SAX2XMLReader> createReader();
        virtual void finalise();
    public:
        virtual void importInvoice(const std::shared_ptr<Invoice>& invoicePtr, const std::string& newXmlContent);
    };

} // InvoiceMasterServer