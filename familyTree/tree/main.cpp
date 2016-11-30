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
Tree *FindTree(Tree *treePtr, char* name); // поиск листа дерева по имени
int IsParent(Tree *parent, Tree *child); // возвращает 0, если parent - предок child
Tree *FindParent(Tree *first, Tree *second);

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
	char* nameOfFirst = argv[2];
	char* nameOfSecond = argv[3];

	Tree *first = 0, *second = 0;
	first = FindTree(root, nameOfFirst);
	if (first == 0 )
	{
		printf("Human with name %s not found in the tree\n", nameOfFirst);
	}
	second = FindTree(root, nameOfSecond);
	if (second == 0)
	{
		printf("Human with name %s not found in the tree\n", nameOfSecond);
	}

	if (first == second)
	{
		printf("Just one name entered: %s\n", first->name);
		return 1;
	}

	if (first && second == 0)
	{
		return 1;
	}

	if (IsParent(first, second) == 0)
	{
		printf("%s is parent of %s\n", first->name, second->name);
	} else
	if (IsParent(second, first) == 0)
	{
		printf("%s is parent of %s\n", second->name, first->name);
	}
	else
	{
		Tree *parent = FindParent(first, second);
		if (parent != 0)
		{
			printf("%s is parent of %s and %s\n", parent->name, first->name, second->name);
		}
		else
		{
			printf("%s and %s haven't common parents\n", first->name, second->name);
			return 1;
		}
	}
	return 0;
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

Tree  *FindTree(Tree *treePtr, char* name)
{
	Tree *result = 0;
	if (treePtr != 0)
	{
		if (strcmp(name, treePtr->name) == 0)
		{
			return treePtr;
		}
		result = FindTree(treePtr->right, name);
		if (result == 0)
			result = FindTree(treePtr->left, name);
	}
	return result;
}

int IsParent(Tree *parent, Tree *child)
{
	if (parent->urov >= child->urov)
	{
		return 1;
	}

	Tree *tmp = child;
	while (tmp->urov > parent->urov)
	{
		tmp = tmp->fath;
	}
	if (tmp == parent)
		return 0;
	return 1;
}

Tree *FindParent(Tree *first, Tree *second)
{
	Tree *tmp1 = first;
	Tree *tmp2 = second;
	if (tmp1->urov != tmp2->urov)
	{
		while (tmp1->urov > tmp2->urov)
		{
			tmp1 = tmp1->fath;
		}
		while (tmp2->urov > tmp1->urov)
		{
			tmp2 = tmp2->fath;
		}
	}
	while ((tmp1 != tmp2) && (tmp1 != 0))
	{
		tmp1 = tmp1->fath;
		tmp2 = tmp2->fath;
	}
	if (tmp1 == tmp2)
	{
		return tmp1;
	}
	else return 0;
}
