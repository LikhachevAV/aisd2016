#include "stdafx.h"
#include "..\linkedSortedList\VectorProcessor.h"

using namespace std;

bool VectorsAreEqual(vector<double> const& x, vector<double> const& y)
{
	return x == y;
}

// Функция ProcessVector
BOOST_AUTO_TEST_SUITE(ProcessVector_function)

	// Создает пустой вектор из пустого вектора
	BOOST_AUTO_TEST_CASE(dont_change_empty_vector)
	{
		vector<double> emptyVector;
		ProcessVector(emptyVector);
		BOOST_CHECK(emptyVector.empty());
	}

BOOST_AUTO_TEST_CASE(squaring_vector_from_just_one_element)
{
	vector<double> myVector = { -7.0 };
	vector<double> expectedVector = { 49.0 };
	ProcessVector(myVector);
	BOOST_CHECK(VectorsAreEqual(myVector, expectedVector));
}

	BOOST_AUTO_TEST_CASE(multiply_every_vectors_element_on_min_element)
	{
		vector<double> myVector = { 0.0, 1.0, -5.0 };
		vector<double> expectedVector = { 0.0, -5.0, 25.0 };
		ProcessVector(myVector);
		BOOST_CHECK(VectorsAreEqual(myVector, expectedVector));
	}

BOOST_AUTO_TEST_SUITE_END()
