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
	cout << endl;
	Node *head = new Node;
	char s[256];

	while (!inputFile.eof())
	{
		istream_iterator<int> eos;
		istream_iterator<int> iit;
		inputFile.getline(s, 256);
		stringstream sstream;
		sstream.str(s);
		 iit = sstream;
		while (iit != eos)
		{
			AddNode(head, *iit);
			++iit;
		}
		cout << endl;
	}

	cout << "Inserted values: ";
	PrintNode(head);
	cout << endl;

	return 0;
}