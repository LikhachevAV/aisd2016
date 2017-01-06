#include "stdafx.h"
#include "FileReader.h"
#include <algorithm>


bool ReadCityNames(std::string & inStr, std::vector<std::string> & cities)
{
	std::string city;
	if (inStr.length() == 0)
	{
		std::cout << "Error! Empty cities string!" << std::endl;
		return false;
	}

	for (auto it = inStr.begin(); it < inStr.end(); ++it)
	{
		if ((city.length() != 0 || *it != ' ') && (*it != ';'))
		{
			city.push_back(*it);
		}
		if ((*it == ';') || (it == inStr.end() - 1))
		{
			cities.push_back(city);
			city = "";
		}
	}
	return true;
}

void InitDistancesTable(std::vector<std::vector<int>> & distancesTable, size_t size)
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

bool AddCityDistancesToTable(std::vector<std::vector<int>> & distancesTable,
	const std::string & distancesStr, const std::vector<std::string> & cities)
{
	auto it = distancesStr.begin();
	auto itEnd = distancesStr.end();
	int i = -1;

	auto getWord = [&](const char delimeter) {
		std::string city;
		for (; it < itEnd && *it == ' '; ++it) {} // пропускаем пробелы в начале слова.

		for (; it < itEnd && *it != delimeter; ++it)
		{
			city.push_back(*it);	
		}
		return city;
	};

	std::string cityA = getWord('#');
	i = GetCityIndex(cities, cityA);

	if (i == -1)
	{
		std::cout << "Source city name reading error!" << std::endl;
		return false;
	}
	if (it < itEnd && *it == '#')
	{
		++it;
	}
	else
	{
		std::cout << "Distances between cities reading error" << std::endl;
	}
	
	auto getDistance = [&]() {
		if (it < itEnd && *it == ':')
		{
			++it;
		}
		else
		{
			std::cout << "Distance value between cities reading error!" << std::endl;
		}
		std::string distStr = getWord(';');
		int distance = stoi(distStr);
		if (!distance)
		{
			return -1;
		}
		return distance;
	};

	for (; it < itEnd; ++it)
	{
		std::string cityB = getWord(':');
		int j = GetCityIndex(cities, cityB);
		if (j == -1)
		{
			std::cout << "Destination city name reading error!" << std::endl;
			return false;
		}
		int val = getDistance();
		if (val == -1)
		{
			std::cout << "Distance between cities " << cityA << "and  " << cityB 
				<< " reading error!" << std::endl;
			return false;
		}
		distancesTable[i][j] = val;
	}
	return true;
}
