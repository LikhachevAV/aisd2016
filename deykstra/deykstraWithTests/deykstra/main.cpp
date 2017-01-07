#include "stdafx.h"
#include "targetver.h"
#include "FileReader.h"

using namespace std;

int main(int argc, char* argv[])
{
	if (argc < 2)
	{
		cout << "Program argument count error!" << endl
			<< "Usage: \"deykstra.exe\" <filename>";
		return EXIT_FAILURE;
	}

	string fileName(argv[1]);
	ifstream f(fileName);
	if (!f.is_open())
	{
		cout << "File with name " << '"' << fileName << '"' << " open error!" << endl;
		return EXIT_FAILURE;
	}

	string cityNamesStr;
	if (!getline(f, cityNamesStr) || cityNamesStr.length() == 0)
	{
		cout << "Cities reading error from file " << '"' << fileName << '"' << endl;
		return EXIT_FAILURE;
	};

	vector<string> cityNames;
	if (!ReadCityNames(cityNamesStr, cityNames) || cityNames.size() == 0)
	{
		cout << "City names reading error from string " << '"' << cityNamesStr << '"' << endl;
	};

	vector<vector<int>> citiesDistances;
	InitDistancesTable(citiesDistances, cityNames.size());

	while (!f.eof())
	{
		string distancesStr;
		if (!getline(f, distancesStr) && !f.eof())
		{
			cout << "Distances between cities reading error from file " 
				<< '"' << fileName << '"' << " line must be not empty!" << endl;
			return EXIT_FAILURE;
		};
		if (distancesStr.length() == 0)
		{
			break; // Выходим из цикла при первой найденной пустой строке
		}
		if (!AddCityDistancesToTable(citiesDistances, distancesStr, cityNames))
		{
			cout << "Addition distance to table error at string " <<
				'"' << distancesStr << '"' << '!' << endl;
			return EXIT_FAILURE;
		}
	}
	return EXIT_SUCCESS;
}