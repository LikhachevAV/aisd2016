#include "stdafx.h"
#include "targetver.h"

using namespace std;

bool main(int argc, char* argv[])
{
	if (argc < 2)
	{
		cout << "Program argument count error!" << endl
			<< "Usage: \"deykstra.exe\" <filename> <graph node A> <graph node B>";
		return false;
	}
	return true;
}