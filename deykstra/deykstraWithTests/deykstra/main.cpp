#include "stdafx.h"
#include "targetver.h"
#include "FileReader.h"

using namespace std;

struct Vertex {
	size_t distance = INT_MAX;
	size_t prevCityIndex = INT_MAX;
	size_t lastMustVizitedCityIndex = INT_MAX;
	bool isFinalDistance = false;
};

int main(int argc, char* argv[])
{
	if (argc < 2)
	{
		cout << "Program argument count error!" << endl
			<< "Usage: \"deykstra.exe\" <filename>";
		return EXIT_FAILURE;
	}

	string fileName(argv[1]);
	ifstream f(fileName);
	if (!f.is_open())
	{
		cout << "File with name " << '"' << fileName << '"' << " open error!" << endl;
		return EXIT_FAILURE;
	}

	string cityNamesStr;
	if (!getline(f, cityNamesStr) || cityNamesStr.length() == 0)
	{
		cout << "Cities reading error from file " << '"' << fileName << '"' << endl;
		return EXIT_FAILURE;
	};

	vector<string> cityNames;
	if (!ReadCityNames(cityNamesStr, cityNames) || cityNames.size() == 0)
	{
		cout << "City names reading error from string " << '"' << cityNamesStr << '"' << endl;
	};
	size_t citiesCount = cityNames.size();

	vector<vector<int>> citiesDistances;
	InitDistancesTable(citiesDistances, citiesCount);

	while (!f.eof())
	{
		string distancesStr;
		if (!getline(f, distancesStr) && !f.eof())
		{
			cout << "Distances between cities reading error from file "
				<< '"' << fileName << '"' << " line must be not empty!" << endl;
			return EXIT_FAILURE;
		};
		if (distancesStr.length() == 0)
		{
			break; // Выходим из цикла при первой найденной пустой строке
		}
		if (!AddCityDistancesToTable(citiesDistances, distancesStr, cityNames))
		{
			cout << "Addition distance to table error at string " <<
				'"' << distancesStr << '"' << '!' << endl;
			return EXIT_FAILURE;
		}
	}
	cout << "Entered graph have the following cities:" << endl
		<< "Index" << '\t' << "City name" << endl;
	for (size_t i = 0; i < citiesCount; ++i)
	{
		cout << i << '\t' << cityNames[i] << endl;
	}
	cout << "Please, enter source city index (0 to " << citiesCount - 1 << "): ";
	size_t sourceCityIndex = 0;
	if (!(cin >> sourceCityIndex) || sourceCityIndex > citiesCount - 1)
	{
		cout << "Error! Source city index must be between 0 and " << citiesCount - 1
			<< '!' << endl;
		return EXIT_FAILURE;
	}

	// инициализация вектора с вершинами
	auto getInitedVertexVector = [&](size_t count) {
		vector<Vertex> vertexes(count);
		for (size_t i = 0; i < count; ++i)
		{
			vertexes[i].prevCityIndex = i;
		}
		return vertexes;
	};

	vector<Vertex> vertexes = getInitedVertexVector(citiesCount);

	auto initSourceVertex = [&]() {
		vertexes[sourceCityIndex].distance = 0;
		vertexes[sourceCityIndex].lastMustVizitedCityIndex = sourceCityIndex;
		vertexes[sourceCityIndex].isFinalDistance = true;
	};
	initSourceVertex();

	auto setVertexesLastSourceCityIndex = [&]() {
		for (size_t j = 0; j < citiesCount; ++j)
		{
			for (int i = (int)citiesCount - 1; i >= 0; --i)
			{
				if (sourceCityIndex != j && citiesDistances[i][j] > 0 && citiesDistances[i][j] != INT_MAX)
				{
					vertexes[j].lastMustVizitedCityIndex = i;
					break;
				}
			}
		}
	};

	setVertexesLastSourceCityIndex();

	// крутим в цикле, заполняем вектор (поиск временных и постоянных меток, заполняем вектор кратчайшего пути)
	cout << "Dont worry, be happy!" << endl;
	return EXIT_SUCCESS;
}