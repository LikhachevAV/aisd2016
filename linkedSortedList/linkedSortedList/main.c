#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[])
{
	FILE *filePtr;
	char s[10];
	int listSize = 0;
	if (argc != 2)
	{
		printf("Argument count error!\nUsage: linkedSortedList.exe <fileName>\n");
		return 1;
	}
	
	if (!(filePtr = fopen(argv[1], "r")))
	{
		printf("Error! File %s %s", argv[1], "can't be open or not exists!\n");
		return 1;
	}
	fscanf(filePtr, "%s", s);
	printf("Main list size is: %s %c", s, '\n');

	fclose(filePtr);
	printf("Success!!!\n");
	return 0;
}