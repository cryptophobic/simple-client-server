#include "XMLImport.hpp"
#include "InvoiceSAX2Handler.hpp"
#include <xercesc/sax2/SAX2XMLReader.hpp>
#include <xercesc/sax2/XMLReaderFactory.hpp>
#include <xercesc/sax2/DefaultHandler.hpp>
#include <xercesc/util/XMLString.hpp>
#include <xercesc/util/SecurityManager.hpp>
#include <xercesc/framework/MemBufInputSource.hpp>
#include <memory>

namespace InvoiceMasterServer {
    void XMLImport::importInvoice(const std::shared_ptr<Invoice>& invoicePtr, const std::string& xmlContent) {
        auto parser = createReader();

        auto invoiceHandler = new InvoiceSAX2Handler(invoicePtr);
        parser->setContentHandler(invoiceHandler);
        parser->setErrorHandler(invoiceHandler);

        xercesc::MemBufInputSource xmlBuffer((const XMLByte* )xmlContent.c_str(), xmlContent.size(),"myxml (in memory)");
        try {
            parser->parse(xmlBuffer);
        }
        catch (const xercesc::XMLException& e) {
            finalise();
            throw std::invalid_argument(xercesc::XMLString::transcode(e.getMessage()));
        }
        catch (const xercesc::SAXParseException& e) {
            finalise();
            throw std::invalid_argument(xercesc::XMLString::transcode(e.getMessage()));
        }
        finalise();
    }

    void XMLImport::finalise() {
        xercesc::XMLPlatformUtils::Terminate();
    }

    std::unique_ptr<xercesc::SAX2XMLReader> XMLImport::createReader() {
        try {
            xercesc::XMLPlatformUtils::Initialize();
        }
        catch (const xercesc::XMLException& e) {
            throw std::invalid_argument(xercesc::XMLString::transcode(e.getMessage()));
        }
        auto parser = std::unique_ptr<xercesc::SAX2XMLReader>(xercesc::XMLReaderFactory::createXMLReader());
        auto securityManager = new xercesc::SecurityManager();
        securityManager->setEntityExpansionLimit(100);
        parser->setProperty(xercesc::XMLUni::fgXercesSecurityManager, securityManager);
        return parser;
    }

} // InvoiceMasterServer