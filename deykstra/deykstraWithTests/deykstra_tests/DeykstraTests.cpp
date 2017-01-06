#include "stdafx.h"
#include "..\deykstra\FileReader.cpp"
#include <sstream>
#include <iostream>
#include <climits>

using namespace std;


BOOST_AUTO_TEST_SUITE(ReadCities_function)
	BOOST_AUTO_TEST_CASE(return_false_when_have_not_cities)
	{
		string s;
		vector<string> cities;
		BOOST_CHECK(!ReadCityNames(s, cities));
	}

	BOOST_AUTO_TEST_CASE(return_true_when_have_just_one_city)
	{
		string s = "New York";
		vector<string> cities;
		BOOST_CHECK(ReadCityNames(s, cities));
		BOOST_CHECK_EQUAL(s, cities[0]);
	}

	BOOST_AUTO_TEST_CASE(return_true_when_have_three_cities)
	{
		string s = "New York; Yorksir; Yoshkar-Ola";
		vector<string> cities;
		BOOST_CHECK(ReadCityNames(s, cities));
		vector<string> expectedCities = {"New York", "Yorksir", "Yoshkar-Ola"};
		auto comparer = [&](string s1, string s2) {return s1 == s2;};
			
		BOOST_CHECK(equal(cities.begin(), cities.end(), expectedCities.begin()));
	}
BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(InitDistancesVector_function)
	BOOST_AUTO_TEST_CASE(dont_change_empty_vector)
	{
		vector<vector<int>> v1;
		InitDistancesTable(v1, 0);
		vector<vector<int>> expectedVector;
		BOOST_CHECK(equal(v1.begin(), v1.end(), expectedVector.begin()));
	}

	BOOST_AUTO_TEST_CASE(can_initialize_vector_with_size_3X3)
	{
		vector<vector<int>> v1;
		InitDistancesTable(v1, 3);
		vector<vector<int>> expectedVector = { { 0, INT_MAX, INT_MAX},
												{INT_MAX, 0, INT_MAX },
												{INT_MAX, INT_MAX, 0}};
		BOOST_CHECK(equal(v1.begin(), v1.end(), expectedVector.begin()));
	}
BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(GetCityIndex_function)
	BOOST_AUTO_TEST_CASE(return_MINUS_ONE_when_city_not_found)
	{
		vector<string> cities = {"One", "Two", "Three"};
		int index = GetCityIndex(cities, "Four");
		BOOST_CHECK_EQUAL(index, -1);
	}

	BOOST_AUTO_TEST_CASE(return_city_index_when_vector_contain_it)
	{
		vector<string> cities = {"One", "Two Two", "Three Three"};
		int index = GetCityIndex(cities, "Two Two");
		BOOST_CHECK_EQUAL(index, 1);
	}
BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(AddCityDistancesToTable_function)
	BOOST_AUTO_TEST_CASE(add_cities_distances_to_table)
	{
		vector<string> cities = {"New York", "Yorksir", "Yoshkar-Ola"};
		string distancesStr = "Yorksir# New York: 2; Yoshkar-Ola: 10";
		vector<vector<int>> distancesTable;
		InitDistancesTable(distancesTable, 3);
		AddCityDistancesToTable(distancesTable, distancesStr, cities);
//		BOOST_CHECK(AddCityDistancesToTable(distancesTable, distancesStr, cities));
	}
BOOST_AUTO_TEST_SUITE_END()