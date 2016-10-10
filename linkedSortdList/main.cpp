#include <fstream>
#include <iostream>
#include <string>
using namespace std;

const unsigned ARR_SIZE = 12;
char POSSIBLE_SYMBOLS[ARR_SIZE] = { '+', '-', '0', '1', '2', '3', '4', '5', '6', '7', '8', '9' };

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

int main(int argc, char* argv[])
{
	if (argc != 2)
	{
		cout << "Invalid arguments count!" << endl
			<< "Usage: bin2dec.exe <binary number>" << endl;

		return 1;
	}


	return 0;
}