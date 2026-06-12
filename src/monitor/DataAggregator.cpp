#include "DataAggregator.h"
#include <fstream>
#include <sstream>

DataAggregator::DataAggregator(const std::string& samplesPath,
                                const std::string& ordersPath)
    : samplesPath_(samplesPath), ordersPath_(ordersPath) {}

Sample DataAggregator::parseSampleLine(const std::string& line) {
    std::istringstream ss(line);
    std::string tok;
    Sample s;
    std::getline(ss, s.id,   '|');
    std::getline(ss, s.name, '|');
    std::getline(ss, tok, '|'); s.avgProductionTimeMin = std::stod(tok);
    std::getline(ss, tok, '|'); s.yield  = std::stod(tok);
    std::getline(ss, tok, '|'); s.stock  = std::stoi(tok);
    return s;
}

Order DataAggregator::parseOrderLine(const std::string& line) {
    std::istringstream ss(line);
    std::string tok;
    Order o;
    std::getline(ss, o.orderId,      '|');
    std::getline(ss, o.sampleId,     '|');
    std::getline(ss, o.customerName, '|');
    std::getline(ss, tok, '|'); o.quantity = std::stoi(tok);
    std::getline(ss, tok, '|'); o.status   = stringToOrderStatus(tok);
    return o;
}

std::vector<Sample> DataAggregator::loadSamples() const {
    std::vector<Sample> result;
    std::ifstream f(samplesPath_);
    std::string line;
    while (std::getline(f, line))
        if (!line.empty()) result.push_back(parseSampleLine(line));
    return result;
}

std::vector<Order> DataAggregator::loadOrders() const {
    std::vector<Order> result;
    std::ifstream f(ordersPath_);
    std::string line;
    while (std::getline(f, line))
        if (!line.empty()) result.push_back(parseOrderLine(line));
    return result;
}

StockStatus DataAggregator::calcStockStatus(int stock, int pending) {
    if (stock == 0)            return StockStatus::DEPLETED;
    if (stock < pending)       return StockStatus::LOW;
    return StockStatus::SUFFICIENT;
}

MonitorSnapshot DataAggregator::buildSnapshot() const {
    MonitorSnapshot snap;
    auto samples = loadSamples();
    auto orders  = loadOrders();

    // Count orders by status (exclude REJECTED)
    for (auto status : {OrderStatus::RESERVED, OrderStatus::PRODUCING,
                        OrderStatus::CONFIRMED, OrderStatus::RELEASE}) {
        snap.orderCounts[status] = 0;
    }
    std::map<std::string, int> pendingBySample;
    for (const auto& o : orders) {
        if (o.status == OrderStatus::REJECTED) continue;
        snap.orderCounts[o.status]++;
        if (o.status == OrderStatus::RESERVED || o.status == OrderStatus::PRODUCING)
            pendingBySample[o.sampleId] += o.quantity;
    }

    // Build stock info per sample
    for (const auto& s : samples) {
        int pending = 0;
        auto it = pendingBySample.find(s.id);
        if (it != pendingBySample.end()) pending = it->second;
        snap.stockInfos.push_back({s, pending, calcStockStatus(s.stock, pending)});
    }
    return snap;
}
