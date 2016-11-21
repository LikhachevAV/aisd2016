#include <iostream>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

const int DL = 200;

struct Tree
{
	char name[DL];
	int urov;
	Tree *fath, *left, *right;
};

int ReadFromFile(FILE *f, Tree **r)
{
	char buf[DL];
	int i=0, k=0, m=0, len=0;
	Tree *p = NULL, *q = NULL, *t = NULL;
	t = 0;
	while (!feof(f))
	{
		fscanf_s(f, "%s", buf, _countof(buf));
		len = strlen(buf);
		if (len == 0)
		{
			break;
		}
		k = 0;
		while (buf[i] == '-')
		{

			++k;
		}
		p = new Tree;
		strcpy_s(p->name, len-k+1, &buf[k]);
		buf[0] = '\0';
		p->urov = k;
		p->left = NULL;
		p->right = NULL;

		if (k == 0)
		{
			*r = p;
			t = *r;
			continue;
		}

		if (k > m)
		{
			t->left = p;
			p->fath = t;
		}
		else if (k == m)
		{
			t->right = p;
			p->fath = t->fath;
		}
		else
		{
			q = q->fath;
			q->right = p;
		}	
	}
	m = k;
	t = p;
	fclose(f);
	return 0;
}

int main(int argc, char *argv[])
{
	if (argc < 2)
	{
		cout << "Program call error! \n" << "Usage: familyTree.exe <filename>";
		return 1;
	}
	
	FILE *fIn;
	errno_t err = fopen_s(&fIn, argv[1], "r");
	if (err)
	{
		cout << "File " << argv[1] << "open error!\n";
		return 1;
	}
	Tree ** root = 0;
	ReadFromFile(fIn, root);
	return 0;
}