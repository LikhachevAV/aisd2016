// istream_iterator example
#include <iostream>     // cin, cout
#include <iterator>     // istream_iterator

using namespace std;

int main() {
	double value1, value2;
	cout << "Please, insert  values: ";

	istream_iterator<double> eos;              // end-of-stream iterator
	istream_iterator<double> iit(cin);   // stdin iterator

	cout << "Inserted values: ";

	while (iit != eos)
	{
		cout << *iit << " ";
		++iit;
	}
	cout << endl;

	return 0;
}