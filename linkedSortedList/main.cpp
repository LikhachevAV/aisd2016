#include <iostream>
#include <fstream>
#include <string>

using namespace std;

const unsigned ARR_SIZE = 12;
char POSSIBLE_SYMBOLS[ARR_SIZE] = {'+', '-', '0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};
enum streamReadStatus { noSymbol, ok, eoln, eof, error };

bool isPossibleSymbol(const char c)
{
	for (int i = 0; i < ARR_SIZE; ++i)
	{
		if (c == POSSIBLE_SYMBOLS[i])
		{
			return 1;
		}
	}
	return 0;
}

enum streamReadStatus readNumber(const istream & stream, int & outNumber, string & errorMsg)
{	
	char ch;
	string s = "";
	while (1)
	{

	}
	return streamReadStatus::ok;
}

int main(int argc, char* argv[])
{
	if (argc != 3)
	{
		cout << "Invalid arguments count!" << endl
			<< "Usage: linkedSortedList.exe <input file> <output file>" << endl;

		return 1;
	}

	ifstream inputFile(argv[1]);
	if (!inputFile.is_open())
	{
		cout << "Error! Failed to open " << argv[1] << " for reading" << endl;
		return 1;
	}

	return 0;
}