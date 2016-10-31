#include "stdafx.h"
#include <iostream>     
#include <iterator>     
#include <fstream>
#include <sstream>

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

void ReadLine(istream & file, char* str[])
{
	char ch;
	while ((ch = file.get()) != '\n')
	{
		str += ch;
	};
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

int main(int argc, char* argv[]) {

	ifstream inputFile(argv[1]);
	int listSize = GetListSize(inputFile);
	vector <Node*> heads(listSize);
	int currentListSize = 0;

	while (!inputFile.eof() && currentListSize < listSize)
	{
		char* strLine[256] = {};
		ReadLine(inputFile, strLine);
		Node *head = new Node;
		StrToLinkedList(strLine, head);
		heads.push_back(head);
		// convert it to linked list
		// insert it to array
		++currentListSize;
	}

	vector<int>::iterator it = heads.begin;
	//PrintNode(heads.*begin);
	cout << endl;

	return 0;
}