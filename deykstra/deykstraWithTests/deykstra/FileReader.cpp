#include "stdafx.h"
#include "FileReader.h"
#include <algorithm>


bool ReadVertexNames(const std::string & inStr, std::vector<std::string> & vertexNames)
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

size_t GetVertexIndex(std::vector<std::string>& vertexNames, std::string & vertexName)
{
	for (size_t i(0); i < vertexNames.size(); ++i)
	{
		if (vertexNames[i].compare(vertexName) == 0)
		{
			return i;
		}
	}
	return SIZE_MAX;
}

bool AddEdgeToTable(std::vector<std::vector<size_t>> & distancesTable,
	std::string & distancesStr, std::vector<std::string> & vertexNames)
{
	auto it = distancesStr.begin();
	auto itEnd = distancesStr.end();

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
	size_t i = SIZE_MAX;
	i = GetVertexIndex(vertexNames, cityA);

	if (i == SIZE_MAX)
	{
		std::cout << "Source name name reading error!" << std::endl;
		return false;
	}

	while (it < itEnd)
	{
		std::string cityB = getWord(':');
		size_t j = GetVertexIndex(vertexNames, cityB);
		if (j == SIZE_MAX)
		{
			std::cout << "Destination vertex name name reading error!" << std::endl;
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
