#include "stdafx.h"
#include "FileReader.h"
#include <algorithm>


bool ReadCities(std::string & inStr, std::vector<std::string> & cities)
{
	std::string city;
	if (inStr.length() == 0)
	{
		std::cout << "Error! Empty cities string!" << std::endl;
		return false;
	}

	for (auto it = inStr.begin(); it != inStr.end(); ++it)
	{
		if ((city.length() != 0 || *it != ' ') && (*it != ';'))
		{
			city.push_back(*it);
		}
		if ((*it == ';') || ((it + 1) == inStr.end()))
		{
			cities.push_back(city);
			city = "";
		}
	}
	return true;
}

void InitDistancesVector(std::vector<std::vector<int>> & distancesTable, size_t size)
{
	for (size_t i = 0; i < size; ++i)
	{
		std::vector<int> v(size, INT_MAX);
		distancesTable.push_back(v);
		distancesTable[i][i] = 0;
	}
}

int GetCityIndex(const std::vector<std::string>& cities, const std::string & city)
{
	for (int i = 0; i < cities.size(); ++i)
	{
		if (cities[i].compare(city) == 0)
		{
			return i;
		}
	}
	return -1;
}
