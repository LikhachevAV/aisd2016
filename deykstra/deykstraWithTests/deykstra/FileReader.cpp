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

	//for (auto it = inStr.begin(); it != inStr.end(); ++it)
	auto it = inStr.begin();
	while(it != inStr.end())
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
		++it;
	}
	return true;
}