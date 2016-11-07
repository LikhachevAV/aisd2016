#include "stdafx.h"
#include <iostream>     
#include <iterator>     
#include <fstream>
#include <sstream>
#include "main.h"

using namespace std;

struct Node {
	int value;
	Node *next = NULL;
};

void AddNode(Node* node, int value)
{
	Node *tmpNode = node;
	while (node->next != NULL)
	{
		node = node->next;
	}
	node->next = new Node;
	node->next->next = NULL;
	node->value = value;
	cout << "value: " << value << endl; //debug
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
	return result;
}

int ReadLineToLinkedList(istream & file, Node * node)
{
	stringstream ss;
	string line;
	getline(file, line);
	ss.str(line);
	int val;
	while (ss >> val)
	{
		AddNode(node, val);
	}
	if (ss.bad())
	{
		return 1;
	}
	return 0;
}

int main(int argc, char* argv[]) {

	if (argc < 1)
	{
		cout << "Argument count error!";
		return 1;
	}

	ifstream inputFile(argv[1]);
	if (!inputFile)
	{
		cout << "File " << argv[1] << "reading error ";
		return 1;
	}

	int listSize = GetListSize(inputFile);
	int currentListSize = 0;
	vector<Node*> heads(listSize);

	while (!inputFile.eof() && currentListSize <= listSize)
	{
		Node *head = new Node;
		if (ReadLineToLinkedList(inputFile, head))
		{
			cout << "Input file reading error!";
			return 1;
		}
		heads.push_back(head);
		++currentListSize;
	}

	cout << "Inserted values: ";
	Node *tmpNode = heads[0];
	PrintNode(tmpNode);
	cout << endl;

	return 0;
}
