#include "stdafx.h"
#include "targetver.h"
#include "FileReader.h"

using namespace std;

struct Node {
	string vertexName;
	size_t index = 0;
	size_t distance = SIZE_MAX;
	size_t sourceIndex = SIZE_MAX;
	bool isVisited = false;
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
	auto printCititesWithIndexes = [&]() {
		cout << endl;
		cout << "Entered graph have the following vertexes:" << endl
			<< "Index" << '\t' << "vertex" << endl;
		for (size_t i = 0; i < vertexesCount; ++i)
		{
			cout << i << '\t' << vertexNames[i] << endl;
		}
	};
	printCititesWithIndexes();

	auto getVertexIndex = [&]() {
		size_t index = SIZE_MAX;
		while (index == SIZE_MAX)
		{
			if (!(cin >> index) || index > vertexesCount - 1)
			{
				cout << "Error! Vertex index must be between 0 and " << vertexesCount - 1
					<< '!' << endl;
			}
		}
		return index;
	};

	cout << endl;
	cout << "Please, enter source vertex index (0 to " << vertexesCount - 1 << "): ";
	size_t sourceVertexIndex = getVertexIndex();
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
		nodes[sourceVertexIndex].sourceIndex = sourceVertexIndex;
	};
	initSourceVertex();

	auto printNodesHeader = [&]() {
		cout << "vertex name\t" << "vertex distance\t\t" << "vertex is final\t\t" << "prev vertex" << endl;
	};
	printNodesHeader();
	
	auto printNodes = [&]() {
		
		for (size_t i = 0; i < vertexesCount; ++i)
		{
			cout << nodes[i].vertexName << "\t\t";

			if (nodes[i].distance < SIZE_MAX)
			{
				cout << nodes[i].distance;
			} 
			else
			{
				cout << '-';
			}
			cout << "\t\t\t";
			if (nodes[i].isVisited)
			{
				cout << "true";
			} 
			else
			{
				cout << "false";
			}
			cout << "\t\t\t";

			if (nodes[i].sourceIndex < SIZE_MAX)
			{
				cout << nodes[nodes[i].sourceIndex].vertexName;
			}
			else
			{
				cout << nodes[i].vertexName;
			}
			cout << endl;
 		}
		cout << endl;
	};
	printNodes();
	
	size_t minVal = SIZE_MAX;
	size_t index = SIZE_MAX;

	auto getUnwizitedNodeIndexWithMinVal = [&]() {
		for (size_t i = 0; i < vertexesCount; ++i)
		{
			if (!nodes[i].isVisited &&
				nodes[i].distance < minVal)
			{
				minVal = nodes[i].distance;
				index = i;
			}
		}
		return index;
	};

	auto findSourceChildrenDistances = [&] (size_t sourceIndex, bool & hasChanged) {
		for (size_t destIndex = 0; destIndex < vertexesCount; ++destIndex)
		{
			if (nodes[sourceIndex].distance < SIZE_MAX &&
				edges[sourceIndex][destIndex] < SIZE_MAX &&
				(nodes[destIndex].distance > nodes[sourceIndex].distance + edges[sourceIndex][destIndex]) &&
				edges[sourceIndex][destIndex] > 0)
			{
				nodes[destIndex].distance = nodes[sourceIndex].distance + edges[sourceIndex][destIndex];
				nodes[destIndex].sourceIndex = sourceIndex;
				printNodes();
			}
		}
		nodes[sourceIndex].isVisited = true;
		hasChanged = true;
	};

	bool wasChanged = true;;
	findSourceChildrenDistances(sourceVertexIndex, wasChanged);
	do
	{
		minVal = SIZE_MAX;
		index = SIZE_MAX;
		wasChanged = false;
		size_t nextIndex = getUnwizitedNodeIndexWithMinVal();
		if (nextIndex < SIZE_MAX)
		{
			findSourceChildrenDistances(nextIndex, wasChanged);
		}
	} while (wasChanged);
	
	for (size_t i = 0; i < vertexesCount; ++i)
	{
		if (!nodes[i].isVisited)
		{
			nodes[i].isVisited = true;
			printNodes;
		}
	}
	printNodes();

	auto printPathToDestVertex = [&](size_t dest) {
		if (nodes[dest].distance < SIZE_MAX)
		{
			size_t curIndex = dest;
			vector<string> path;
			do
			{
				path.push_back(nodes[curIndex].vertexName);
				curIndex = nodes[curIndex].sourceIndex;
				if (curIndex == dest)
				{
					break;
				}
			} while (curIndex != sourceVertexIndex);
			path.push_back(nodes[sourceVertexIndex].vertexName);
			for (size_t i = path.size() - 1; i != 0; --i)
			{
				cout << path[i] << "->";
			}
			cout << path[0] << endl;
		}
		else
		{
			cout << "Vertex " << nodes[sourceVertexIndex].vertexName << " have not path to " << nodes[dest].vertexName << endl;
		}
	};

	auto handleMenuCommand = [&]() {
		bool exit = false;
		do
		{
			cout << endl;
			cout << "The following actions are possible: " << endl
				<< "E - exit program" << endl
				<< "C - see cities table" << endl
				<< "D - enter destination city index to see path from source city" << endl << endl;
			cout << "Please, enter command : ";
			char answer = 'x';
			cin >> answer;
			if (cin.eof() || answer == 'E' || answer == 'e')
			{
				exit = true;
			} else
			if (answer == 'C' || answer == 'c')
			{
				printCititesWithIndexes();
			} else
			if (answer == 'D' || answer == 'd')
			{
				cout << "Please, enter destination city index: ";
				size_t destVertexIndex = getVertexIndex();
				printPathToDestVertex(destVertexIndex);
			}
			else
			{
				cout << "Incorrect command!" << endl;
			}
		} while (exit == false);
	};
	handleMenuCommand();
	return EXIT_SUCCESS;
}