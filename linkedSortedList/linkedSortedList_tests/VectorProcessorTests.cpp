#include "stdafx.h"
#include <string> 
#include <iostream>
#include <sstream>

using namespace std;

enum struct ReadStatus {Error, Ok, Eoln, Eof};

ReadStatus ReadIntFromStream(istream & inpt, int & result, string & error)
{


	if (inpt.eof())
	{
		return ReadStatus::Eof;
	}

	if (inpt >> result, " ")
	{
		return ReadStatus::Ok;
	}

	if (inpt.get() == '\n')
	{
		return ReadStatus::Eoln;
	}

	error = "Input stream reading error!";
	return ReadStatus::Error;
}

// Функция ProcessVector
BOOST_AUTO_TEST_SUITE(ReadInt)

BOOST_AUTO_TEST_CASE(check_stream_reading)
{
	stringstream ss;
	ss.str("123 0 12");
	int result;
	string error;
	ReadStatus status;
	status = ReadStatus::Ok;

	while (status != ReadStatus::Error)
	{
		status = ReadIntFromStream(ss, result, error);
		cout << "result: " << result << ", error: " << error << endl;
	}

	BOOST_CHECK(true);
}

BOOST_AUTO_TEST_SUITE_END()
