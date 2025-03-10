#include <benchmark/benchmark.h>
#include "pcs/controller/controller.h"

#include <vector>

#include "pcs/topology/topology.h"
#include "pcs/lts/parsers/parsers.h"

static void HingeCompleteTopology(benchmark::State& state) {
	// The time to generate the complete topology alone
	pcs::Environment machine;
	try {
		machine.AddResource("../../data/hinge/Resource1.txt", false);
		machine.AddResource("../../data/hinge/Resource2.txt", false);
		machine.AddResource("../../data/hinge/Resource3.txt", false);
		machine.AddResource("../../data/hinge/Resource4.txt", false);
		machine.AddResource("../../data/hinge/Resource5.txt", false);
	} catch (const std::ifstream::failure& e) {
		throw;
	}

	for (auto _ : state) {
		machine.Complete();
		benchmark::DoNotOptimize(machine.topology());
		benchmark::ClobberMemory();
	}
}

BENCHMARK(HingeCompleteTopology)->Unit(benchmark::kMillisecond);

static void HingeControllerUsingComplete(benchmark::State& state) {
	// First generate the topology, then time how long the controller takes
	pcs::Environment machine;
	try {
		machine.AddResource("../../data/hinge/Resource1.txt", false);
		machine.AddResource("../../data/hinge/Resource2.txt", false);
		machine.AddResource("../../data/hinge/Resource3.txt", false);
		machine.AddResource("../../data/hinge/Resource4.txt", false);
		machine.AddResource("../../data/hinge/Resource5.txt", false);
	} catch (const std::ifstream::failure& e) {
		throw;
	}

	pcs::Recipe recipe;
	try {
		recipe.set_recipe("../../data/hinge/recipe.json");
	} catch (const std::ifstream::failure& e) {
		throw;
	}

	machine.Complete();

	for (auto _ : state) {
		pcs::Controller con(&machine, machine.topology(), &recipe);
		std::optional<const pcs::LTS<std::vector<std::string>, std::vector<std::string>, boost::hash<std::vector<std::string>>>*> controller_lts = con.Generate();
		benchmark::DoNotOptimize(controller_lts);
		benchmark::ClobberMemory();
	}
}

BENCHMARK(HingeControllerUsingComplete)->Unit(benchmark::kMillisecond);


static void HingeCompleteWithController(benchmark::State& state) {
	// Times complete + controller total time
	pcs::Environment machine;
	try {
		machine.AddResource("../../data/hinge/Resource1.txt", false);
		machine.AddResource("../../data/hinge/Resource2.txt", false);
		machine.AddResource("../../data/hinge/Resource3.txt", false);
		machine.AddResource("../../data/hinge/Resource4.txt", false);
		machine.AddResource("../../data/hinge/Resource5.txt", false);
	} catch (const std::ifstream::failure& e) {
		throw;
	}

	pcs::Recipe recipe;
	try {
		recipe.set_recipe("../../data/hinge/recipe.json");
	} catch (const std::ifstream::failure& e) {
		throw;
	}

	for (auto _ : state) {
		machine.Complete();
		pcs::Controller con(&machine, machine.topology(), &recipe);
		std::optional<const pcs::LTS<std::vector<std::string>, std::vector<std::string>, boost::hash<std::vector<std::string>>>*> controller_lts = con.Generate();
		benchmark::DoNotOptimize(controller_lts);
		benchmark::ClobberMemory();
	}
}

BENCHMARK(HingeCompleteWithController)->Unit(benchmark::kMillisecond);


static void HingeIncrementalWithController(benchmark::State& state) {
	// Controller generation time with incremental topology
	pcs::Environment machine;
	try {
		machine.AddResource("../../data/hinge/Resource1.txt", false);
		machine.AddResource("../../data/hinge/Resource2.txt", false);
		machine.AddResource("../../data/hinge/Resource3.txt", false);
		machine.AddResource("../../data/hinge/Resource4.txt", false);
		machine.AddResource("../../data/hinge/Resource5.txt", false);
	} catch (const std::ifstream::failure& e) {
		throw;
	}

	pcs::Recipe recipe;
	try {
		recipe.set_recipe("../../data/hinge/recipe.json");
	} catch (const std::ifstream::failure& e) {
		throw;
	}

	for (auto _ : state) {
		machine.Incremental();
		pcs::Controller con(&machine, machine.topology(), &recipe);
		std::optional<const pcs::LTS<std::vector<std::string>, std::vector<std::string>, boost::hash<std::vector<std::string>>>*> controller_lts = con.Generate();
		benchmark::DoNotOptimize(controller_lts);
		benchmark::ClobberMemory();
	}
}

BENCHMARK(HingeIncrementalWithController)->Unit(benchmark::kMillisecond);


