# Distributed Monitoring Agent (DMA)

A C++ agent for monitoring system metrics (CPU, RAM, disk) and providing structured JSON output.

## Architecture

The project uses a modular collector pattern:

- **Collector Interface** — base class defining monitoring interface
- **Collectors** — implementations collecting specific metrics:
  - `SystemMetricsCollector` — CPU %, RAM %, Disk % usage
  - `LogsCollector` — system log monitoring (planned)
  - `HealthCheckCollector` — service health checks (planned)
- **Aggregator** — orchestrates collectors and formats results

## Build & Run

```bash
cd /home/ubuntu/projects/DMA
./build.sh
cd /build
./dma_agent
```

## Dependencies

- C++17
- CMake 3.15+
- nlohmann/json (auto-fetched)
- Linux (for /proc interface)

