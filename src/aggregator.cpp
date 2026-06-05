#include "aggregator.h"

void Aggregator::addCollector(Collector* collector) {
    collectors.push_back(collector);
}

void Aggregator::run() {
    results.clear();
    for (Collector* collector : collectors) {
        results.push_back(collector->collect());
    }
}

std::vector<std::string> Aggregator::getResults() {
    return results;
}
std::string Aggregator::getResultsAsJson() {
    std::string json = "{";
    for (size_t i = 0; i < collectors.size(); ++i) {
        json += "\"" + collectors[i]->getName() + "\": \"" + results[i] + "\"";
        if (i < collectors.size() - 1) {
            json += ", ";
        }
    }
    json += "}";
    return json;
}