#pragma once
#include "stdafx.h"

bool ReadCityNames(std::string & inStr, std::vector<std::string> & cities);
void InitDistancesTable(std::vector<std::vector<int>> & distancesTable, size_t size);
int GetCityIndex(const std::vector<std::string> & cities, const std::string & city);
bool AddCityDistancesToTable(std::vector<std::vector<int>> & distancesTable,
	const std::string & distancesStr, const std::vector<std::string> & cities);