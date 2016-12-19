#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

int const MAX_SIZE = 100;

bool ReadCitiesToVector(const string & filename, ifstream & f, vector<string> & cities, string & error)
{
	string citiesStr;
	if (!getline(f, citiesStr))
	{
		error.append("Cities from file ")
			.append(filename)
			.append(" reading error!");
		return false;
	}

	auto itBegin = citiesStr.begin();
	while (itBegin != citiesStr.end())
	{
		string s;
		while ((itBegin != citiesStr.end() && (*itBegin != ';')))
		{
			s.push_back(*itBegin);
			++itBegin;
		}
		if (s.length() != 0)
		{
			cities.push_back(s);
		}
		if ((itBegin != citiesStr.end() && (*(itBegin + 1) == ' ')))
		{
			++itBegin;
		}
	}
	if (cities.size() < 2)
	{
		error
			.append("Cities min count must be 2, but found ")
			.append(to_string(cities.size()));
		return false;
	}
	return true;
}

int GetCityIndex(vector<string> & cities, const string & city)
{
	for (size_t i = 0; i < cities.size(); ++i)
	{
		if (cities[i].compare(city) == 0)
		{
			return i;
		}
	}
	return -1;;
}

bool ReadFileToTable(const string & filename, vector<string> & cities, vector<vector<int>> & distanceBetweenCities, string & error)
{
	ifstream inFile(filename);
	if (!inFile.is_open())
	{
		error.append("File ")
			.append(filename)
			.append("open error!\n");
		return false;
	}
	if (!ReadCitiesToVector(filename, inFile, cities, error))
	{
		return false;
	}

	int i = 0;
	while (!inFile.eof())
	{
		vector<int> distances;
		string distancesStr;
		if (!getline(inFile, distancesStr) && (distancesStr.size() == 0))
		{
			error.append("Distances between cities at file ")
				.append(filename)
				.append(" reading error!");
			return false;
		}
		for (auto it = distancesStr.begin(); it != distancesStr.end(); ++it)
		{
			int cDist = 0;
			*it >> cDist;
			distances.push_back(cDist);
		}
		if (distances.size() != cities.size())
		{
			error.append("Cities distances reading error at line ")
				.append(to_string(i + 1))
				.append(" in file with name ")
				.append(filename);
			return false;
		}
		distanceBetweenCities.push_back(distances);
	}
	if (distanceBetweenCities.size() != cities.size())
	{
		error.append("Distances table size error!");
		return false;
	}
	return true;
}

bool main(int argc, char* argv[])
{
	if (argc < 4)
	{
		cout << "Program argument count error!" << endl
			<< "Usage: \"deykstra.exe\" <filename> <graph node A> <graph node B>";
		return false;
	}

	vector<string> cities;
	vector<vector<int>> distanceBetweenCities;
	string error;
	if (!ReadFileToTable(argv[1], cities, distanceBetweenCities, error))
	{
		cout << error << endl;
		return false;
	}
	cout << endl;
	return true;
}