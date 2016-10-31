#include <iostream>     
#include <iterator>     
#include <fstream>
using namespace std;

struct Node {
	double value;
	Node *next = NULL;
};

void addNode(Node* node, double value)
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

void printNode(Node* node)
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

	istream_iterator<double> eos;				 // end-of-stream iterator
	istream_iterator<double> iit(inputFile);     // stdin iterator

	Node *head = new Node;

	while (iit != eos)
	{
		addNode(head, *iit);
		++iit;
	}
	cout << "Inserted values: ";
	printNode(head);
	cout << endl;

	return 0;
}