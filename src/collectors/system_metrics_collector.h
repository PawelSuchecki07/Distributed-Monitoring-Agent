#pragma once
#include <string>
#include "collector.h"

class SMCollector : public Collector {
    private:
        std::string getCPU();
        std::string getRAM();
        std::string getDisk();
    public:
        std::string collect() override;
        std::string getName() override;
};