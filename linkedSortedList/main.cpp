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

int main(int argc, char* argv[]) {

	ifstream inputFile(argv[1]);
	int listSize = GetListSize(inputFile);
	cout << endl;
	Node *head = new Node;
	char s[256];
	 //sstream;

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