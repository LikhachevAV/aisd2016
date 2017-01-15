#include "stdafx.h"
#include "FileReader.h"
#include <algorithm>


bool ReadVertexNames(std::string & inStr, std::vector<std::string> & vertexNames)
{
	std::string name;
	if (inStr.length() == 0)
	{
		return false;
	}

	for (auto it = inStr.begin(); it < inStr.end(); ++it)
	{
		if ((name.length() != 0 || *it != ' ') && (*it != ';'))
		{
			name.push_back(*it);
		}
		if ((*it == ';') || (it == inStr.end() - 1))
		{
			vertexNames.push_back(name);
			name = "";
		}
	}
	return true;
}

void InitDistancesTable(std::vector<std::vector<size_t>> & distancesTable, size_t size)
{
	for (size_t i = 0; i < size; ++i)
	{
		std::vector<size_t> v(size, SIZE_MAX);
		distancesTable.push_back(v);
		distancesTable[i][i] = 0;
	}
}

int GetCityIndex(const std::vector<std::string>& cities, std::string & const city)
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

bool AddEdgeToTable(std::vector<std::vector<int>> & distancesTable,
	const std::string & distancesStr, const std::vector<std::string> & cities)
{
	auto it = distancesStr.begin();
	auto itEnd = distancesStr.end();
	int i = -1;

	auto getWord = [&](const char delimeter) {
		std::string word;
		for (;*it == ' '; ++it){}

		for (; it < itEnd && *it != delimeter; ++it)
		{
			word.push_back(*it);
		}

		if (it < itEnd && *it == delimeter)
		{
			++it;
		}
		return word;
	};

	auto getDistance = [&]() {
		std::string distStr = getWord(';');
		int distance = stoi(distStr);
		if (!distance)
		{
			return -1;
		}
		return distance;
	};

	std::string cityA = getWord('#');
	i = GetCityIndex(cities, cityA);

	if (i == -1)
	{
		std::cout << "Source name name reading error!" << std::endl;
		return false;
	}

	while (it < itEnd)
	{
		std::string cityB = getWord(':');
		int j = GetCityIndex(cities, cityB);
		if (j == -1)
		{
			std::cout << "Destination name name reading error!" << std::endl;
			return false;
		}
		int distance = getDistance();
		if (distance == -1)
		{
			return false;
		}
		distancesTable[i][j] = distance;
	}
	return true;
}
