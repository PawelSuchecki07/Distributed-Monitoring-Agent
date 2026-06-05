#pragma once
#include <vector>
#include <string>
#include "collectors/collector.h"

class Aggregator {
    public:
        void run();
        void addCollector(Collector* collector);
        std::vector<std::string> getResults();
        std::string getResultsAsJson();


    private:
        std::vector<Collector*> collectors;
        std::vector<std::string> results;
};