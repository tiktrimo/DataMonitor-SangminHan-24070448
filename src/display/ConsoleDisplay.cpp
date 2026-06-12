#include "ConsoleDisplay.h"
#include <iostream>
#include <iomanip>
#include <string>

void ConsoleDisplay::separator(char c, int w) const {
    std::cout << std::string(w, c) << "\n";
}

std::string ConsoleDisplay::stockStatusLabel(StockStatus s) {
    switch (s) {
    case StockStatus::SUFFICIENT: return "[여유]";
    case StockStatus::LOW:        return "[부족]";
    case StockStatus::DEPLETED:   return "[고갈]";
    default:                      return "[----]";
    }
}

void ConsoleDisplay::showOrderSummary(const std::map<OrderStatus, int>& counts) const {
    std::cout << "[ 주문량 현황 ]\n";
    separator('-');
    for (const auto& [status, count] : counts) {
        std::cout << "  " << std::left << std::setw(12)
                  << orderStatusToString(status)
                  << " : " << count << "건\n";
    }
}

void ConsoleDisplay::showStockTable(const std::vector<SampleStockInfo>& infos) const {
    std::cout << "\n[ 재고 현황 ]\n";
    separator('-');
    std::cout << std::left
              << std::setw(8)  << "ID"
              << std::setw(22) << "시료명"
              << std::setw(8)  << "재고"
              << std::setw(8)  << "대기"
              << "상태\n";
    separator('-');
    for (const auto& info : infos) {
        std::cout << std::left
                  << std::setw(8)  << info.sample.id
                  << std::setw(22) << info.sample.name
                  << std::setw(8)  << (std::to_string(info.sample.stock) + "ea")
                  << std::setw(8)  << (std::to_string(info.pendingQty) + "ea")
                  << stockStatusLabel(info.stockStatus) << "\n";
    }
}

void ConsoleDisplay::render(const MonitorSnapshot& snap) const {
    separator();
    std::cout << "   반도체 시료 생산주문관리 - 모니터링\n";
    separator();
    showOrderSummary(snap.orderCounts);
    showStockTable(snap.stockInfos);
    separator();
}
