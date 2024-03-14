#include "Invoice.hpp"
#include "database/Tables.hpp"
#include <fmt/core.h>

namespace InvoiceMasterServer {
    void Invoice::validateLineTotals(unsigned int lineTotals) {
        if (lineTotals > 0 && total > UINT_MAX - lineTotals) {
            throw std::invalid_argument(fmt::format("Invoice totals limit {} exceeded, try to break into several invoices.", UINT_MAX));
        }
    }

    void Invoice::validateLine(unsigned int price, unsigned int quantity) {
        validateQuantity(quantity);

        auto result = static_cast<unsigned long>(quantity) * static_cast<unsigned long>(price);
        if ((result >> std::numeric_limits<unsigned int>::digits) > 0) {
            throw std::invalid_argument(fmt::format("Invoice totals line limit {} exceeded, try to break into several invoices.", UINT_MAX));
        }
    }

    void Invoice::validateQuantity(unsigned int quantity) {
        if (quantity > invoiceMaxQuantityPerLine) {
            throw std::invalid_argument(fmt::format("Invoice quantity perl line limit {} exceeded, try to break into several invoices.", invoiceMaxQuantityPerLine));
        }
    }

    unsigned int Invoice::validateAndCalculateFee(unsigned int fee) {

        if (fee > overdueInvoiceMaxFee) {
            throw std::invalid_argument(fmt::format("Fee limit {} exceeded.", overdueInvoiceMaxFee));
        }

        auto percentage = static_cast<float>(fee) / 100.;
        auto calculatedFee = static_cast<unsigned int>(percentage * total);

        if (calculatedFee > 0 && total > UINT_MAX - calculatedFee) {
            throw std::invalid_argument(fmt::format("Overdue invoice totals with fee limit {} exceeded, try to break into several invoices.", UINT_MAX));
        }

        return calculatedFee;
    }

    void Invoice::addItem(const std::string& itemName, unsigned int price, unsigned int quantity) {
        validateLine(price, quantity);
        unsigned int lineTotals = price * quantity;
        validateLineTotals(lineTotals);
        total += lineTotals;
        auto item = std::make_shared<database::InvoiceItem>();
        item->setFields(
                {
                        {database::InvoiceItem::price, std::to_string(price)},
                        {database::InvoiceItem::quantity, std::to_string(quantity)},
                        {database::InvoiceItem::invoiceNumber, invoiceNumber},
                        {database::InvoiceItem::itemName, itemName}
                });

        items.emplace_back(item);
    }

    void Invoice::save(unsigned int chargedFee) {
        if (items.empty()) {
            throw std::invalid_argument("Cannot place invoice without items");
        }
        for (auto& item: items) {
            item->saveRecord();
        }

        if (chargedFee > 0) {
            this->saveOverdueInvoiceStrict(newOverdueInvoice(), chargedFee);
        } else {
            this->saveInvoiceStrict(newInvoice());
        }
    }

    void Invoice::saveInvoiceStrict(std::shared_ptr<database::Invoice> invoice) {
        invoice->setFields(
                {
                        {database::Invoice::invoiceNumber, invoiceNumber},
                        {database::Invoice::totals, std::to_string(total)},
                        {database::Invoice::userId, userId},
                });
        invoice->saveRecord(invoiceNumber);
    }

    [[deprecated("Use saveInvoiceStrict() instead.")]]
    void Invoice::saveInvoice(std::shared_ptr<database::Entity> invoice) {
        std::dynamic_pointer_cast<database::Invoice>(invoice)->setFields(
                {
                        {database::Invoice::invoiceNumber, invoiceNumber},
                        {database::Invoice::totals, std::to_string(total)},
                        {database::Invoice::userId, userId},
                });
        std::dynamic_pointer_cast<database::Invoice>(invoice)->saveRecord(invoiceNumber);
    }

    void Invoice::saveOverdueInvoiceStrict(std::shared_ptr<database::OverdueInvoice> invoice, unsigned int feeCharged) {
        total += validateAndCalculateFee(feeCharged);

        invoice->setFields(
                {
                        {database::OverdueInvoice::invoiceNumber, invoiceNumber},
                        {database::OverdueInvoice::totals, std::to_string(total)},
                        {database::OverdueInvoice::userId, userId},
                        {database::OverdueInvoice::feeCharged, std::to_string(feeCharged)}
                });
        invoice->saveRecord(invoiceNumber);
    }

    [[deprecated("Use saveOverdueInvoiceStrict() instead.")]]
    void Invoice::saveOverdueInvoice(std::shared_ptr<database::Entity> invoice, unsigned int feeCharged) {
        total += validateAndCalculateFee(feeCharged);

        std::dynamic_pointer_cast<database::OverdueInvoice>(invoice)->setFields(
                {
                        {database::OverdueInvoice::invoiceNumber, invoiceNumber},
                        {database::OverdueInvoice::totals, std::to_string(total)},
                        {database::OverdueInvoice::userId, userId},
                        {database::OverdueInvoice::feeCharged, std::to_string(feeCharged)}
                });
        std::dynamic_pointer_cast<database::OverdueInvoice>(invoice)->saveRecord(invoiceNumber);
    }

    std::shared_ptr<database::Invoice> Invoice::newInvoice() {
        return std::make_shared<database::Invoice>();
    }

    std::shared_ptr<database::OverdueInvoice> Invoice::newOverdueInvoice() {
        return std::make_shared<database::OverdueInvoice>();
    }

    Invoice::Invoice(std::string newUserId) : userId(std::move(newUserId)) {
        invoiceNumber = database::invoiceTable.getNewId();
    }

    std::string Invoice::getInvoiceNumber() {
        return invoiceNumber;
    }

    std::string Invoice::dump() {
        std::string result;

        result = fmt::format("Current invoice with id: {}; {}: {}\n", invoiceNumber, database::Invoice::userId, userId);

        for (const auto& item: items) {
            result += fmt::format("{}\n", item->toString());
        }
        result += fmt::format("{}: {}", database::Invoice::totals, std::to_string(total));
        return result;
    }
} // InvoiceMasterServer
