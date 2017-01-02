#pragma once
#include "stdafx.h"

bool ReadCities(std::string & inStr, std::vector<std::string> & cities);
void InitDistancesVector(std::vector<std::vector<int>> & distancesTable, size_t size);
int GetCityIndex(const std::vector<std::string> & cities, const std::string & city);