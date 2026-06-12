#include <iostream>
#include <fstream>
#include <windows.h>
#include "src/monitor/DataAggregator.h"
#include "src/display/ConsoleDisplay.h"

static void writeSeedData() {
    std::ofstream sf("data/samples.dat");
    sf << "S-001|실리콘 웨이퍼-8인치|0.5|0.92|480\n"
       << "S-002|GaN 에피택셜-4인치|0.3|0.78|220\n"
       << "S-003|SiC 파워기판-6인치|0.8|0.92|30\n"
       << "S-004|산화막 웨이퍼-SiO2|0.6|0.88|0\n";

    std::ofstream of("data/orders.dat");
    of << "ORD-20260612-0001|S-005|LG이노텍|300|RESERVED\n"
       << "ORD-20260612-0002|S-001|SK하이닉스|150|RESERVED\n"
       << "ORD-20260612-0003|S-003|삼성전자|200|PRODUCING\n"
       << "ORD-20260612-0004|S-002|DB하이텍|400|CONFIRMED\n"
       << "ORD-20260612-0005|S-004|네패스|100|RELEASE\n"
       << "ORD-20260612-0006|S-001|앰코테크|50|REJECTED\n";
}

int main() {
    SetConsoleOutputCP(65001);
    SetConsoleCP(65001);

    writeSeedData();  // create test data files

    DataAggregator  aggregator("data/samples.dat", "data/orders.dat");
    ConsoleDisplay  display;

    MonitorSnapshot snap = aggregator.buildSnapshot();
    display.render(snap);

    return 0;
}
