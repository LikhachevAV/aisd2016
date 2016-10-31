// istream_iterator example
#include <iostream>     // cin, cout
#include <iterator>     // istream_iterator

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

int main() {

	cout << "Please, insert  values: ";

	istream_iterator<double> eos;        // end-of-stream iterator
	istream_iterator<double> iit(cin);   // stdin iterator

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