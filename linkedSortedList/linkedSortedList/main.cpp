#include "stdafx.h"
#include <iostream>     
#include <iterator>     
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

struct Node {
	int value;
	Node *next = NULL;
};

void AddValueToNode(Node* node, int value)
{
	Node *tmpNode = node;
	while (node->next != NULL)
	{
		node = node->next;
	}
	node->next = new Node;
	node->next->next = NULL;
	node->value = value;
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
	while (file.get() != '\n') {} // Пропускаем символы до конца строки
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
	int currentListSize = 0;
	while (!file.eof() && currentListSize <= listSize)
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

	cout << "Inserted values: ";
	
	PrintNode(heads[0]);
	cout << endl;
	PrintNode(heads[1]);
	cout << endl;
	return 0;
}
