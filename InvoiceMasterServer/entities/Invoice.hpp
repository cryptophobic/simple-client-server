#pragma once
#include <utility>
#include <vector>
#include <memory>
#include "database/schema/InvoiceItem.hpp"
#include "database/schema/Invoice.hpp"
#include "database/schema/OverdueInvoice.hpp"
#include <limits>

namespace InvoiceMasterServer {

    constexpr unsigned int invoiceMaxQuantityPerLine = 1000;
    constexpr unsigned int overdueInvoiceMaxFee = 99;

    class Invoice {
    protected:
        std::string invoiceNumber;
        std::string userId;
        std::vector<std::shared_ptr<database::InvoiceItem>> items;
        void validateLineTotals(unsigned int lineTotals);
        void validateLine(unsigned int price, unsigned int quantity);
        void validateQuantity(unsigned int quantity);
        unsigned int validateAndCalculateFee(unsigned int fee);
        unsigned int total = 0;
    public:
        Invoice(std::string newLoginId);
        virtual void addItem(const std::string& itemName, unsigned int price, unsigned int quantity);
        virtual std::string getInvoiceNumber();
        virtual std::string dump();
        virtual void save(unsigned int chargedFee = 0);
        virtual void saveInvoice(std::shared_ptr<database::Entity> invoice);
        virtual void saveInvoiceStrict(std::shared_ptr<database::Invoice> invoice);
        virtual void saveOverdueInvoice(std::shared_ptr<database::Entity> invoice, unsigned int chargedFee);
        virtual void saveOverdueInvoiceStrict(std::shared_ptr<database::OverdueInvoice> invoice, unsigned int chargedFee);
        virtual std::shared_ptr<database::Invoice> newInvoice();
        virtual std::shared_ptr<database::OverdueInvoice> newOverdueInvoice();
    };

} // InvoiceMasterServer