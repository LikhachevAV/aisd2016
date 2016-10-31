#include <iostream>     
#include <iterator>     
#include <fstream>
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

int main(int argc, char* argv[]) {

	cout << "Please, insert  values: ";

	ifstream inputFile(argv[1]);

	istream_iterator<int> eos;				 // end-of-stream iterator
	istream_iterator<int> iit(inputFile);     // stdin iterator

	Node *head = new Node;

	while (iit != eos)
	{
		AddNode(head, *iit);
		++iit;
	}
	cout << "Inserted values: ";
	PrintNode(head);
	cout << endl;

	return 0;
}