#include "stdafx.h"
#include "VectorProcessor.h"
#include <algorithm>
#include <numeric>
#include <functional>
#include <boost/range/algorithm/transform.hpp>
#pragma warning (push, 3)
#include <boost/phoenix.hpp>
#pragma warning (pop)

using namespace std;
using namespace std::placeholders;
using namespace boost::phoenix::placeholders;
using namespace boost::phoenix;
using boost::transform;

double GetVectorsMinVal(std::vector<double> & numbers)
{
	return *min_element(numbers.begin(), numbers.end());
}

void SortVector(std::vector<double> & numbers)
{
	sort(numbers.begin(), numbers.end());
}

void ProcessVector(std::vector<double> & numbers)
{
	if (!numbers.empty())
	{
		double minVal = GetVectorsMinVal(numbers);
		boost::transform(numbers, numbers.begin(), arg1 * minVal);
	}
}