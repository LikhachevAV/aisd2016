#pragma once
#include "stdafx.h"

bool ReadVertexNames(const std::string & inStr, std::vector<std::string> & vertexNames);
void InitDistancesTable(std::vector<std::vector<size_t>> & distancesTable, size_t size);
size_t GetVertexIndex(std::vector<std::string>& vertexNames, std::string & vertexName);
bool AddEdgeToTable(std::vector<std::vector<size_t>> & distancesTable,
	std::string & distancesStr, std::vector<std::string> & vertexNames);