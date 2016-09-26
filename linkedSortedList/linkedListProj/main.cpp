#include <iostream>
#include <fstream>
#include <stdio.h>

using namespace std;
int main(int argc, char** argv) {
//	//Read list size
//	fscanf(filePtr, "%s", s);
//	if(!(listSize = atoi(s)) || (listSize <= 0))
//	{
//		printf("List size must be digit, more, than 0, but found: %s\n", s);
//		return 1;
//	}
//	printf("Int val listSize: %d %c", listSize, '\n');
//	
//	//Read string before end of line listSize
//	do
//	{
//		fscanf(filePtr, "%s", s);
//		
//	}while(s[0] != '\n' &&  !EOF);
//	
//	printf("%s\n", s);
//	
//	fclose(filePtr);
//	printf("Success!!!\n");
//	return 0;
	int listSize = 0;
	if (argc != 2)
	{
		cout << "Argument count error!\nUsage: " << argv[0] << " <fileName>\n";
		return 1;
	}
	ifstream readFile (argv[1]);
	if (!(readFile.is_open()))
	{
		cout << "File open error or file not erxists!\n";
		return 1;
	}
	cout << "Success!\n";
	return 0;
}
