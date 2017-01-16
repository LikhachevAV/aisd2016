#include "stdafx.h"
#include "targetver.h"
#include "FileReader.h"

using namespace std;

struct Node {
	string vertexName;
	size_t index = 0;
	size_t distance = SIZE_MAX;
	size_t prevVertexIndex = SIZE_MAX;
	bool isFinal = false;
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

	string vertexNamesStr;
	if (!getline(f, vertexNamesStr) || vertexNamesStr.length() == 0)
	{
		cout << "Vertexes reading error from file " << '"' << fileName << '"' << endl;
		return EXIT_FAILURE;
	};

	vector<string> vertexNames;
	if (!ReadVertexNames(vertexNamesStr, vertexNames) || vertexNames.size() == 0)
	{
		cout << "Vertex names reading error from string " << '"' << vertexNamesStr << '"' << endl;
	};
	size_t vertexesCount = vertexNames.size();

	vector<vector<size_t>> edges;
	InitDistancesTable(edges, vertexesCount);

	while (!f.eof())
	{
		string edgesStr;
		if (!getline(f, edgesStr) && !f.eof())
		{
			cout << "Graph edges reading error from file "
				<< '"' << fileName << '"' << " line must be not empty!" << endl;
			return EXIT_FAILURE;
		};
		if (edgesStr.length() == 0)
		{
			break; // Выходим из цикла при первой найденной пустой строке
		}
		if (!AddEdgeToTable(edges, edgesStr, vertexNames))
		{
			cout << "Addition distance to table error at string " <<
				'"' << edgesStr << '"' << '!' << endl;
			return EXIT_FAILURE;
		}
	}
	cout << "Entered graph have the following vertexes:" << endl
		<< "Index" << '\t' << "vertex" << endl;
	for (size_t i = 0; i < vertexesCount; ++i)
	{
		cout << i << '\t' << vertexNames[i] << endl;
	}
	cout << "Please, enter source vertex index (0 to " << vertexesCount - 1 << "): ";
	size_t sourceVertexIndex = 0;
	if (!(cin >> sourceVertexIndex) || sourceVertexIndex > vertexesCount - 1)
	{
		cout << "Error! Source vertex index must be between 0 and " << vertexesCount - 1
			<< '!' << endl;
		return EXIT_FAILURE;
	}

	// инициализация вектора с вершинами
	auto getInitedNodesVector = [&](size_t count) {
		vector<Node> nodes(count);
		for (size_t i = 0; i < count; ++i)
		{
			nodes[i].index = i;
			nodes[i].vertexName = vertexNames[i];
		}
		return nodes;
	};

	vector<Node> nodes = getInitedNodesVector(vertexesCount);
	auto initSourceVertex = [&]() {
		nodes[sourceVertexIndex].distance = 0;
		nodes[sourceVertexIndex].prevVertexIndex = sourceVertexIndex;
		nodes[sourceVertexIndex].isFinal = true;
	};
	initSourceVertex();
	
	auto printNode = [&]() {
		for (size_t i = 0; i < vertexesCount; ++i)
		{
			cout << "vertex name:\t\t" << nodes[i].vertexName << endl
				<< "vertex distance:\t";
			if (nodes[i].distance < SIZE_MAX)
			{
				cout << nodes[i].distance << endl;
			} 
			else
			{
				cout << '-' << endl;
			}
			cout << "vertex is final:\t";
			if (nodes[i].isFinal)
			{
				cout << "true" << endl;
			} 
			else
			{
				cout << "false" << endl;
			}

			cout << "prev vertex:\t\t";
			if (nodes[i].prevVertexIndex < SIZE_MAX)
			{
				cout << nodes[nodes[i].prevVertexIndex].vertexName << endl;
			}
			else
			{
				cout << nodes[i].vertexName << endl;
			}
			cout << endl;
 		}
		cout << "###########################" << endl;
	};
	printNode();
	// add printing vector with source Node vertex only!

	auto getMinSourceNodeIndex = [&](size_t sourceNodeIndex, vector<Node> & nodes) {
		size_t minDistanceVal = SIZE_MAX;
		size_t index = SIZE_MAX;
		for (size_t j = 0; j < vertexesCount; ++j)
		{
			if (edges[sourceNodeIndex][j] < minDistanceVal && edges[sourceNodeIndex][j] > 0)
			{
				minDistanceVal = edges[sourceNodeIndex][j];
				index = j;
			}
		}
		if (minDistanceVal < SIZE_MAX)
		{
			nodes[index].prevVertexIndex = sourceNodeIndex;
			nodes[index].distance = minDistanceVal;
			nodes[index].prevVertexIndex = sourceNodeIndex;
			nodes[index].isFinal = true;
		}
	};	
	getMinSourceNodeIndex(sourceVertexIndex, nodes);
	// add printing vector with two Node vertex!

	// крутим в цикле, заполняем вектор (поиск временных и постоянных меток, заполняем вектор кратчайшего пути)
	cout << "Dont worry, be happy!" << endl;
	return EXIT_SUCCESS;
}