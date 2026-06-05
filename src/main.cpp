#include <iostream>
#include "aggregator.h"
#include "collectors/system_metrics_collector.h"
int main() {
    Aggregator agg;

    agg.addCollector(new SMCollector());
    agg.run();
    std::cout << agg.getResultsAsJson() << std::endl;
    return 0;
}