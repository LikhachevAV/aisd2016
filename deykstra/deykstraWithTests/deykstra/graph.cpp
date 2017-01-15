#include "stdafx.h"

struct  Graph
{
	//SIZE_MAX
	size_t size = 0;
	std::vector<std::string> vertexes;
	std::vector<std::vector<size_t>> edges;
	Graph(std::vector<std::string> & vertexNames, std::vector<std::vector<size_t>> & distances)
	{
		size = vertexNames.size();
		vertexes = vertexNames;
		edges = distances;
	}
};

size_t GetVertexIndexByName(std::string name)
{
	//...
	return 0;
}