#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

int const MAX_SIZE = 100;

bool readFileToTable(const string & filename, vector<string> & cities, vector<vector<int>> & distanceBetweenCities, string & error)
{
	ifstream inFile(filename);
	if (!inFile.is_open())
	{
		error.append("File ")
			.append(filename)
			.append("open error!\n");
		return false;
	}
	string citiesStr;
	if (!getline(inFile, citiesStr))
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
	if (!readFileToTable(argv[1], cities, distanceBetweenCities, error))
	{
		cout << error << endl;
		return false;
	}
	cout << endl;
	return true;
}