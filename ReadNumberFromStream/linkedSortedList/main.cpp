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

void StrToLinkedList(char* str[], Node * root)
{
	istream_iterator<int> eos;
	stringstream stringStream;
	stringStream << str;
	istream_iterator<int> iit(stringStream);
	while (iit != eos)
	{
		AddNode(root, *iit);
		++iit;
	}
}

void ReadLine(istream & file, char* str[])
{
	char ch;
	while ((ch = file.get()) != '\n')
	{
		str += ch;
	};
}

int main(int argc, char* argv[]) {

	ifstream inputFile(argv[1]);
	int listSize = GetListSize(inputFile);
	vector<Node*> heads(listSize);

	while (!inputFile.eof())
	{
		char * strLine[256];
		// read line
		ReadLine(inputFile, strLine);
		// convert it to linked list
		Node *head = new Node;
		StrToLinkedList(strLine, head);
		// insert it to array
		heads.push_back(head);
	}

	cout << "Inserted values: ";
	PrintNode(heads[0]);
	cout << endl;

	return 0;
}

