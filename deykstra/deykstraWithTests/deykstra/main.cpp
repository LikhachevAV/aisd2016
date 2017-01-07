#include "stdafx.h"
#include "targetver.h"
#include "FileReader.h"

using namespace std;

bool main(int argc, char* argv[])
{
	if (argc < 2)
	{
		cout << "Program argument count error!" << endl
			<< "Usage: \"deykstra.exe\" <filename>";
		return false;
	}

	string fileName(argv[1]);
	ifstream f(fileName);
	if (!f.is_open())
	{
		cout << "File with name " << '"' << fileName << '"' << " open error!" << endl;
		return false;
	}

	string cityNamesStr;
	if (!getline(f, cityNamesStr) || cityNamesStr.length() == 0)
	{
		cout << "Cities reading error from file " << '"' << fileName << '"' << endl;
		return false;
	};

	vector<string> cityNames;
	if (!ReadCityNames(cityNamesStr, cityNames) || cityNames.size() == 0)
	{
		cout << "City names reading error from string " << '"' << cityNamesStr << '"' << endl;
	};
	return true;
}