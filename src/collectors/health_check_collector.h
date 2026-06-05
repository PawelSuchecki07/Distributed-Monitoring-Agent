#pragma once
#include <string>
#include "collector.h"

class HealthCheckCollector : public Collector {
    public:
        std::string collect() override;
        std::string getName() override {
            return "HealthCheckCollector";
        }
};