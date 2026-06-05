#pragma once
#include <string>
class Collector {
    public:
        virtual ~Collector() = default;
        virtual std::string getName() = 0;
        virtual std::string collect() = 0;
};