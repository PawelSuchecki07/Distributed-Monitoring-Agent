#pragma once
#include <string>
#include "collector.h"

class LogsCollector : public Collector {
    public:
        std::string collect() override;
        std::string getName() override {
            return "LogsCollector";
        }
};