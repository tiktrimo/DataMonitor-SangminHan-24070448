#pragma once
#include <vector>
#include <map>
#include <string>
#include "../model/Sample.h"
#include "../model/Order.h"

enum class StockStatus { SUFFICIENT, LOW, DEPLETED };

struct SampleStockInfo {
    Sample sample;
    int    pendingQty;   // total quantity in active orders
    StockStatus stockStatus;
};

struct MonitorSnapshot {
    std::map<OrderStatus, int> orderCounts;
    std::vector<SampleStockInfo> stockInfos;
};

class DataAggregator {
public:
    DataAggregator(const std::string& samplesPath,
                   const std::string& ordersPath);

    MonitorSnapshot buildSnapshot() const;

private:
    std::string samplesPath_;
    std::string ordersPath_;

    std::vector<Sample> loadSamples() const;
    std::vector<Order>  loadOrders()  const;

    static Sample      parseSampleLine(const std::string& line);
    static Order       parseOrderLine(const std::string& line);
    static StockStatus calcStockStatus(int stock, int pending);
};
