#include <iostream>

using namespace std;

void main()
{
	auto enterCityNameInCycle = [&]() {
	bool exit = false;
	do
	{
		cout << endl;
		cout << "The following actions are possible: " << endl
			<< "E - exit program" << endl
			<< "C - see cities table" << endl
			<< "D - enter destination city index to see path from source city" << endl << endl;
		cout << "Please, enter command : ";
		char answer = 'x';
		cin >> answer;
		if (cin.eof() || answer == 'E' || answer == 'e')
		{
			cout << "Exit" << endl; //TODO: delete this
			exit = true;
		}
		else
			if (answer == 'C' || answer == 'c')
			{
				cout << "See cities table" << endl; //TODO: delete this
													//TODO print cities table
			}
			else
				if (answer == 'D' || answer == 'd')
				{
					cout << "Print path" << endl; //TODO: delete this
												  //TODO print path
				}
				else
				{
					cout << "Incorrect command!" << endl;
				}
	} while (exit == false);
	};
	enterCityNameInCycle();
}