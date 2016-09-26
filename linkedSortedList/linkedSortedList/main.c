#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[])
{
	FILE *filePtr;
	if (argc != 2)
	{
		printf("Argument count error!\nUsage: linkedSortedList.exe <fileName>\n");
		return 1;
	}
	printf("fileName:  %s %c", argv[1], '\n');
	if (!(filePtr = fopen(argv[1], "r")))
	{
		printf("Error! File %s %s", argv[1], "can't be open!\n");
		return 1;
	}

	printf("Success!!!\n");
	return 0;
}