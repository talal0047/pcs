#include <benchmark/benchmark.h>
#include "pcs/topology/topology.h"

#include <array>

#include "pcs/lts/parsers/string_string.h"

static void BM_TopologyWithTwoResources(benchmark::State& state) {
    std::array<pcs::LTS<std::string, std::string>, 2> ltss;
    for (size_t i = 0; i < 2; ++i) {
        pcs::ReadFromFile(ltss[i], "../../data/pad/Resource" + std::to_string(i + 1) + ".txt");
    }

    for (auto _ : state) {
        pcs::LTS<std::string, std::pair<size_t, std::string>> topology = pcs::Combine(ltss);
        benchmark::DoNotOptimize(topology);
        benchmark::ClobberMemory();
    }
}

BENCHMARK(BM_TopologyWithTwoResources); // 1600ns - 400,000 iterations


static void BM_TopoologyWithFiveResources(benchmark::State& state) {
    std::array<pcs::LTS<std::string, std::string>, 5> ltss;
    for (size_t i = 0; i < 5; ++i) {
        pcs::ReadFromFile(ltss[i], "../../data/pad/Resource" + std::to_string(i + 1) + ".txt");
    }
    
    for (auto _ : state) {
        pcs::LTS<std::string, std::pair<size_t, std::string>> topology = pcs::Combine(ltss);
        benchmark::DoNotOptimize(topology);
        benchmark::ClobberMemory();
    }
}

BENCHMARK(BM_TopoologyWithFiveResources); // 414915 ns - 1659 iterations