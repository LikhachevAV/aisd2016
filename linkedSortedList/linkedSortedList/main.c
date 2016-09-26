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
	
	//Read list size
	fscanf(filePtr, "%s", s);
	if(!(listSize = atoi(s)) || (listSize <= 0))
	{
		printf("List size must be digit, more, than 0, but found: %s\n", s);
		return 1;
	}
	printf("Int val listSize: %d %c", listSize, '\n');
	
	//Read string before end of line listSize
	do
	{
		fscanf(filePtr, "%s", s);
		
	}while(s[0] != '\n' &&  !EOF);
	
	printf("%s\n", s);
	
	fclose(filePtr);
	printf("Success!!!\n");
	return 0;
}
