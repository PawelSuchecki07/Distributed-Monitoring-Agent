#include <fstream>
#include "system_metrics_collector.h"
#include <sstream>
#include <sys/statvfs.h>
#include <unistd.h>

std::string SMCollector::collect(){
    std::string cpu = getCPU();
    std::string ram = getRAM();
    std::string disk = getDisk();
    return cpu + "|" + ram + "|" + disk;
}

std::string SMCollector::getName() {
    return "SMCollector";
}

std::pair<long,long> getCPUinfoFromLine(std::string line){
    int user, nice, system, idle, iowait, irq, softirq;
    long cpu_used, cpu_total;


    std::stringstream ss(line);
    std::string cpu_label;


    ss >> cpu_label >> user >> nice >> system >> idle >> iowait >> irq >> softirq;
    cpu_used = user + nice + system;
    cpu_total = cpu_used + idle + iowait + irq + softirq;
    return {cpu_used, cpu_total};
    
}


std::string SMCollector::getCPU() {
    std::pair<long,long> result1{0,0}, result2{0,0};
    std::string line;
    bool found = false;

    std::ifstream file("/proc/stat");
    if (!file.is_open()) {
        return "Error: Unable to open /proc/stat";
    }
    while (std::getline(file, line)) {
        if (line.find("cpu ") == 0) {
            result1 = getCPUinfoFromLine(line);
            found = true;
            break;
        }
    }
    file.close();

    if (!found) {
        return "Error: 'cpu' line not found in /proc/stat";
    }

    usleep(100000);

    found = false;
    file.open("/proc/stat");
    if (!file.is_open()) {
        return "Error: Unable to open /proc/stat";
    }
    while (std::getline(file, line)) {
        if (line.find("cpu ") == 0) {
            result2 = getCPUinfoFromLine(line);
            found = true;
            break;
        }
    }
    file.close();

    if (!found) {
        return "Error: 'cpu' line not found in /proc/stat";
    }

    long delta_used = result2.first - result1.first;
    long delta_total = result2.second - result1.second;

    if (delta_total == 0) {
        return "Error: delta_total is zero";
    }

    return std::to_string((delta_used * 100) / delta_total) + "%";
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
