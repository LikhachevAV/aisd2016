#include "stdafx.h"
#include "..\deykstra\FileReader.cpp"
#include <sstream>
#include <iostream>

using namespace std;


	BOOST_AUTO_TEST_SUITE(ReadCities_function)
		BOOST_AUTO_TEST_CASE(return_false_when_have_not_cities)
		{
			string s;
			vector<string> cities;
			BOOST_CHECK(!ReadCities(s, cities));
		}

		BOOST_AUTO_TEST_CASE(return_true_when_have_just_one_city)
		{
			string s = "New York";
			vector<string> cities;
			BOOST_CHECK(ReadCities(s, cities));
			cout << cities[0] << endl;
			BOOST_CHECK_EQUAL(s, cities[0]);
		}
	BOOST_AUTO_TEST_SUITE_END()
