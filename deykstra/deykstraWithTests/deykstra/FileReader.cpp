#include "stdafx.h"
#include "FileReader.h"
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
		if (city.length() != 0 || *it != ' ')
		{
			city.push_back(*it);
		}
		if (*it == ';' || it == inStr.end())
		{
			cities.push_back(city);
			city = "";
		}
	}
	return true;
}