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
		cout << "File with name " << fileName << " open error!" << endl;
		return false;
	}

	string citesStr;
	if (!getline(f, citesStr) || citesStr.length() == 0)
	{
		cout << "Cities reading error from file " << fileName << endl;
		return false;
	};
	
	return true;
}