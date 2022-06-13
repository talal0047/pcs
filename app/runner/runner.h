#pragma once

#include <array>
#include <filesystem>
#include "pcs/environment/environment.h"
#include "pcs/lts/lts.h"
#include "pcs/product/recipe.h"
#include "pcs/environment/environment.h"

struct RunnerOpts {
	bool incremental_topology;
	bool generate_images;
	bool only_highlighted_topology_image; // Exports the highlighted topology only, rather than topology & highlighted topology
};

void Run(const std::string& name, const RunnerOpts& opts);
pcs::Environment RunReturnMachine(const std::string&	name, const RunnerOpts& opts);
void AddResourceAdaptive(const std::string& name, const std::string& recipefolder, const RunnerOpts& opts, pcs::Environment &machine);

static size_t NumOfResources(const std::filesystem::path& data_folder);

static pcs::Environment LoadMachine(const std::string& data_folder, size_t num_resources);
static pcs::Recipe LoadRecipe(const std::string& data_folder);
static void CompleteTopology(pcs::Environment& machine);
static void IncrementalTopology(pcs::Environment& machine);
static void GraphVizSave(const std::string& export_folder, size_t num_resources, bool only_highlighted_topology);