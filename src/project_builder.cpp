#include "project_builder.hpp"

#include "json.hpp"

void build_project(std::experimental::filesystem::path const & path)
{
	auto config = json::parse(path / "project.json");
}
