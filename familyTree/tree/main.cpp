// TreeObhod.cpp: определяет точку входа для консольного приложения.
//
/*
В файле дерево в виде
Ann
.Boris
..Cat
..Dora
...Eva
...Fred
..Goga
...Helmut
....Marta
.....Bred
.....Stiv
.....Jon
......Tom
...Nata
.Nina
Построить бинарное дерево. Обеспечить выдачу бинарного дерева в
3 порядках обхода. Выдать исходное дерево из бинарного.
Имя входного файла - через командную строку. */


#include "stdafx.h"   
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const int DL = 20;          // максимальная длина

using namespace std;

struct Tree
{
	char name[DL];
	int urov;
	Tree *fath;         // отец в исходном дереве
	Tree *left;
	Tree *right;
};

int ReadTreeFromFile(FILE *F, Tree **r);  // чтение из файла, формирование дерева
int FindTree(Tree *treePtr, Tree **result, char* name); // поиск листа дерева по имени
void back_from_bin(Tree *p);            // выдача исходное дерева из бинарного 
void print_down_bin(Tree *p, int lev);  // выдача бинарного сверху вниз
void print_up_bin(Tree *p, int lev);    // выдача бинарного снизу вверх
void print_right_bin(Tree *p, int lev); // выдача бинарного слева направо

int main(int argc, char* argv[])
{
	Tree *root = 0;
	FILE *Fin;
	setlocale(LC_ALL, "rus");
	if (argc < 4)
	{
		printf("\nProgram input data error!\nUsage: familyTree.exe <filename> <name1> <name2>\n");
		getchar();
		return -1;
	}
	errno_t err = fopen_s(&Fin, argv[1], "r");
	if (err)
	{
		printf("\nCan not open file %s", argv[1]);
		getchar();
		return -1;
	}
	ReadTreeFromFile(Fin, &root);
	printf("Binary tree setup completed!\n");
	//getchar();
	char* nameOfFirst = argv[2];
	char* nameOfSecond = argv[3];

	Tree *first = 0, *second = 0;
	if (FindTree(root, &first, nameOfFirst) != 0 )
	{
		printf("Human with name %s not found in the tree\n", nameOfFirst);
	}
	if (FindTree(root, &second, nameOfSecond) != 0)
	{
		printf("Human with name %s not found in the tree\n", nameOfSecond);
	}
	//getchar();
}

int ReadTreeFromFile(FILE *F, Tree **r)
{
	char buf[DL];
	int i, k, m, len;
	Tree *p, *q, *t;       // *root = 0 
	m = 0;                 // уровень вершины
	t = 0;
	while (!feof(F))
	{
		k = fscanf_s(F, "%s", buf, _countof(buf));
		len = strlen(buf);
		if (len == 0) break;            // если конец файла в следующей строке
		k = 0;
		while (buf[k] == '.') k++;     // k-уровень вершины
		p = new Tree;
		strncpy_s(p->name, &buf[k], len - k + 1);  // 0-(k-1) - точки, (k-1)-(len-1) - имя, \0 - конец строки
		buf[0] = '\0';                  // если конец файла в следующей строке
		p->urov = k;
		p->left = 0;
		p->right = 0;
		if (k == 0)                    // корень
		{
			*r = p;
			t = *r;
			continue;
		}
		if (k > m)                  // переход на следующий уровень
		{
			t->left = p;
			p->fath = t;
		}
		else if (k == m)            // тот же уровень
		{
			t->right = p;
			p->fath = t->fath;  // отец тот же
		}
		else        // подъем по дереву на m-k уровней
		{
			q = t;
			for (i = 0; i < m - k; i++) q = q->fath;
			// q - предыдущая вершина того же уровня
			p->fath = q->fath;   // отец тот же, что у брата
			q->right = p;
		}
		m = k;      // текущий уровень
		t = p;      // текущая вершина
	}
	fclose(F);
	return 0;
}

int FindTree(Tree *treePtr, Tree **result, char* name)
{
	int find = 1;
	if (treePtr != 0)
	{
		find *= FindTree(treePtr->right, result, name);
		find *= FindTree(treePtr->left, result, name);
		if (strcmp(name, treePtr->name) == 0)
		{
			result = &treePtr;
			return 0;
		}
	}
	return find;
}

void back_from_bin(Tree *p)
{
	int i, j;
	char st[DL];
	if (p)
	{
		for (i = 0; i < p->urov; i++) st[i] = '.';
		j = 0;
		while (st[i++] = (p->name)[j++]);
		printf("%s\n", st);
		back_from_bin(p->left);
		back_from_bin(p->right);
	}
}
