#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

int const MAX_SIZE = 100;

bool readFileToTable(const string & filename, vector<string> cities, int valuesTable[], string & error)
{
	ifstream inFile(filename);
	if (!inFile.is_open())
	{
		error.append("File ")
			.append(filename)
			.append("open error!\n");
		return false;
	}
	char ch = ' ';
	int i = 0;
	int j = 0;
	string s;
	while (ch != '\n')
	{
		ch = ' ';
		while ((ch != ';') && (ch != '\n'))
		{
			inFile.get(ch);
			if (ch != ' ' && ch != ';' && ch != '\n')
			{
				s.push_back(ch);
			}
		}
		if (s != "")
		{
			cities.push_back(s);
		}
		s = "";
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
	int size = cities.size();
	int valuesTable[MAX_SIZE][MAX_SIZE];
	string error;
	readFileToTable(argv[1], cities, *valuesTable, error);
	return true;
}