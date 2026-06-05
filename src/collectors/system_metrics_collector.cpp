#include <fstream>
#include "system_metrics_collector.h"
#include <sstream>
#include <sys/statvfs.h>

std::string SMCollector::collect(){
    std::string cpu = getCPU();
    std::string ram = getRAM();
    std::string disk = getDisk();
    return cpu + "|" + ram + "|" + disk;
}

std::string SMCollector::getName() {
    return "SMCollector";
}

std::string SMCollector::getCPU() {
    int user, nice, system, idle, iowait, irq, softirq;
    int cpu_used = 0;
    int cpu_total = 0;
    std::ifstream file("/proc/stat");
    if (!file.is_open()) {
        return "Error: Unable to open /proc/stat";
    }
    std::string line;
    while (std::getline(file, line)) {
        if (line.find("cpu ") == 0) {
            std::stringstream ss(line);
            std::string cpu_label;
            ss >> cpu_label >> user >> nice >> system >> idle >> iowait >> irq >> softirq;
            cpu_used = user + nice + system;
            cpu_total = cpu_used + idle + iowait + irq + softirq;
            return std::to_string(float(cpu_used * 100) / cpu_total) + "%";
        }
    }
    return "Error: cpu metrics not found";

}

std::string SMCollector::getRAM() {
    std::ifstream file("/proc/meminfo");
    if (!file.is_open()) {
        return "Error: Unable to open /proc/meminfo";
    }
    std::string line;
    int mem_total = 0;
    int mem_available = 0;
    while (std::getline(file, line)) {
        if (line.find("MemTotal:") == 0) {
            std::stringstream ss(line);
            std::string ram_label;
            ss >> ram_label >> mem_total;
        } else if (line.find("MemAvailable:") == 0) {
            std::stringstream ss(line);
            std::string ram_label;
            ss >> ram_label >> mem_available;
        }
    }
    if (mem_total == 0) {
        return "Error: MemTotal not found";
    }
    return std::to_string(float((mem_total - mem_available) * 100) / mem_total) + "%";
}

std::string SMCollector::getDisk() {
    struct statvfs stat;
    if (statvfs("/", &stat) != 0) {
        return "Error: Unable to get disk metrics";
    }
    unsigned long long total = stat.f_blocks * stat.f_frsize;
    unsigned long long free = stat.f_bfree * stat.f_frsize;
    unsigned long long used = total - free;
    return std::to_string(float(used * 100) / total) + "%";

}