#pragma once
#include "../monitor/DataAggregator.h"
#include <string>

class ConsoleDisplay {
public:
    void render(const MonitorSnapshot& snap) const;

private:
    void showOrderSummary(const std::map<OrderStatus, int>& counts) const;
    void showStockTable(const std::vector<SampleStockInfo>& infos) const;
    static std::string stockStatusLabel(StockStatus s);
    void separator(char c = '=', int w = 60) const;
};
