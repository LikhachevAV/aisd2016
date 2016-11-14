#include "stdafx.h"
#include <iostream>     
#include <iterator>     
#include <fstream>
#include <sstream>
#include <vector>
#include <climits>

using namespace std;

struct Node {
	int value;
	Node *next = NULL;
};

void AddValueToNode(Node * & node, int value)
{
	Node *tmpNode = node;
	while (node->next != NULL)
	{
		node = node->next;
	}
	node->value = value;
	node->next = new Node;
	node = tmpNode;
}

void PrintNode(Node* node)
{
	Node *tmpNode = node;
	while (node->next != NULL)
	{
		cout << " " << node->value;
		node = node->next;
	}
	node = tmpNode;
}

int GetListSize(istream & file)
{
	int result = -1;
	file >> result;	
	while (file.get() != '\n') {} // Пропускаем символы до конца текущей строки
 	return result;
}

bool ReadLineToLinkedList(istream & file, Node * node)
{
	stringstream ss;
	string line;
	getline(file, line);
	ss.str(line);
	int val;
	while (ss >> val)
	{
		AddValueToNode(node, val);
	}
	if (ss.bad())
	{
		return false;
	}
	return true;
}

bool ReadFileToLinkedListsVector(istream & file, vector<Node*> & nodes, string & error)
{
	int listSize = GetListSize(file);
	if (listSize < 1)
	{
		error = "List size must be more, than 0!";
		return false;
	}
	int currentListSize = 0;
	while (!file.eof() && currentListSize < listSize)
	{
		Node *node = new Node;
		if (!ReadLineToLinkedList(file, node))
		{
			error = "Input file reading error!";
			return false;
		}
		nodes.push_back(node);
		++currentListSize;
	}
	return true;
}

void MergeVectorToSortedList(vector<Node*> & const list, Node *sortedList)
{
	bool sorted = false;
	int minValIndex = 0;
	while (!sorted) // Из цикла выходим, когда все элементы вектора NULL
	{
		int minVal = INT_MAX;
		sorted = true;
		for (int i = 0; i < list.size(); ++i)
		{
			if ((list[i]->next != NULL) && (list[i]->value < minVal))
			{
				minValIndex = i;
				minVal = list[i]->value;
			}
			sorted = sorted && (list[i]->next == NULL);
		}
		AddValueToNode(sortedList, minVal);
		Node * tmpNode = list[minValIndex];
		if (list[minValIndex] != NULL)
		{
			list[minValIndex] = list[minValIndex]->next;
		}
		delete tmpNode;
	}
}

int main(int argc, char* argv[]) {

	if (argc < 2)
	{
		cout << "Argument count error!";
		return 1;
	}
	
	ifstream inputFile(argv[1]);
	if (!inputFile.is_open())
	{
		cout << "File " << argv[1] << " reading error!";
		return 1;
	}

	vector<Node*> heads;
	string error;
	if (!ReadFileToLinkedListsVector(inputFile, heads, error))
	{
		cout << error;
		return 1;
	}

	cout << "Sorted values: ";
	Node *sortedList = new Node;
	MergeVectorToSortedList(heads, sortedList);
	PrintNode(sortedList);
	//PrintNode(heads[0]);
	//cout << endl;
	//PrintNode(heads[1]);
	//cout << endl;
	return 0;
}
