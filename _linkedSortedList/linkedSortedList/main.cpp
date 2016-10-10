#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char* argv[])
{
	FILE *filePtr;
	char s[10] = "";
	char ch;
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
	if(!(fscanf(filePtr, "%s", s)) || !(listSize = atoi(s)) || (listSize <= 0))
	{
		printf("List size must be digit, more, than 0, but found: %s\n", s);
		return 1;
	}
	printf("Int val listSize: %d %c", listSize, '\n');
	
	//Read string before end of line listSize
	do
	{
		ch = fgetc(filePtr);
		
	}while((ch != '\n') &&  !feof(filePtr));

	while (!feof(filePtr))
	{
		while (fscanf(filePtr, "%s", s))
		{
			//TODO: добавить преобразование сроки в число и обработку ошибок
			printf("%s ", s);
			if ((getc(filePtr) == '\n') || feof(filePtr))
			{
				break;
			}
		}
		printf("%c", '\n');
	}
	
	//printf("%s\n", s); //debug
	
	fclose(filePtr);
	printf("Success!!!\n");
	return 0;
}