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

int main(int artc, char* argv[])
{
	cout << isPossibleSymbol('s') << endl;


	return 0;
}