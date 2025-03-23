#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <conio.h>  // For _kbhit() and _getch()
#include "LinkedList.h"
#include "Queue.h"
#include "DynamicIntStack.h"

using namespace std;

// Read inputs from file to the vector
void readEdges(vector<vector<int>>& edges, vector<string>& illegalEdges, int& vertexCount);
void bubbleSortEdges(vector<vector<int>>& edges);
// Build vector of LinkedLists using the input vector
void buildAdjacencyList(int vertexCount, const vector<vector<int>>& edges, LinkedList* adjList);
void addEdge(LinkedList* adjList, int vertexCount);
void removeEdge(LinkedList* adjList, int vertexCount);
void displayGraph(const LinkedList* adjList, int vertexCount);
void depthFirstSearch(const LinkedList* adjList, int vertexCount);
void breadthFirstSearch(const LinkedList* adjList, int vertexCount);
// Helper function for DFS and BFS
bool isVisited(int v, vector<int>& visitedVertices);

int main() {
	int vertexCount = 0;
	vector<vector<int>> edges;
	vector<string> illegalEdges; // Vector to store illegal edges

	// Read edges from the file
	readEdges(edges, illegalEdges, vertexCount);

	// Sort edges by the first vertex using bubble sort
	bubbleSortEdges(edges);

	// Build adjacency list from sorted edges
	LinkedList* adjList = new LinkedList[vertexCount];
	buildAdjacencyList(vertexCount, edges, adjList);

	// Print illegal edges if any
	if (!illegalEdges.empty()) {
		cout << endl << "These edges are illegal or repeated:" << endl;
		for (const string& edge : illegalEdges) {
			cout << edge << endl;
		}
		cout << endl;
	}

	// Menu loop
	int choice = 0;
	do {
		// Display menu options
		cout << "   (1) Add edge" << endl;
		cout << "   (2) Remove edge" << endl;
		cout << "   (3) Display the graph" << endl;
		cout << "   (4) Depth-first search" << endl;
		cout << "   (5) Breadth-first search" << endl;
		cout << "   (6) Exit" << endl;

		cout << "Please enter a number (1-6):" << endl;

		do {
			cin >> choice;
			// Check for invalid input (non-integer values)
			if (cin.fail()) {
				cin.clear(); // Clear the error flag
				cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
				cout << "The entered number is not valid! Make another choice:" << endl;
				choice = 0; // Reset choice to continue the loop
			}
			else if (choice < 1 || choice > 6) {
				cout << "The entered number is not valid! Make another choice:" << endl;
			}
		} while (choice < 1 || choice > 6);

		switch (choice) {
		case 1:
			addEdge(adjList, vertexCount); // Function to add an edge
			break;
		case 2:
			removeEdge(adjList, vertexCount); // Function to remove an edge
			break;
		case 3:
			displayGraph(adjList, vertexCount); // Function to display the graph
			break;
		case 4:
			depthFirstSearch(adjList, vertexCount); // Function for DFS
			break;
		case 5:
			breadthFirstSearch(adjList, vertexCount); // Function for BFS
			break;
		case 6:
			cout << "Program Exiting..." << endl;
			break;
		default:
			cout << "The entered number is not valid! Make another choice:" << endl;
			break;
		}
	} while (choice != 6);

	return 0;
}

// Read inputs from file to the vector
void readEdges(vector<vector<int>>& edges, vector<string>& illegalEdges, int& vertexCount) {
	string filename;
	ifstream file;

	// Prompt for the file name until it is opened successfully
	do {
		cout << "Enter the input file name:" << endl;
		cin >> filename;
		file.open(filename);
		if (!file.is_open()) {
			cout << "Could not open the file " << filename << endl;
		}
	} while (!file.is_open());

	// Read edges from the file
	string line;
	while (getline(file, line)) {
		istringstream iss(line);
		int u, v;
		char extraChar;

		// Read exactly two integers
		if ((iss >> u >> v) && !(iss >> extraChar)) {
			if (u < 0 || v < 0) {
				illegalEdges.push_back(line); // Add illegal edge to the list
				continue; // Ignore negative vertices
			}

			// Check for duplicates in the edge list
			bool isDuplicate = false;
			for (int i = 0; i < edges.size(); ++i) {
				if (edges[i][0] == u && edges[i][1] == v) {
					isDuplicate = true;
					break;
				}
			}

			if (!isDuplicate) {
				edges.push_back({ u, v }); // Add unique edges only
				vertexCount = max(vertexCount, max(u, v) + 1); // Find and update the max vertex count
			}
			else {
				illegalEdges.push_back(line); // Add duplicate edge to the illegal list
			}
		}
		else {
			illegalEdges.push_back(line); // Add illegal edge to the list for invalid input
		}
	}

	file.close();
}


// Function to perform bubble sort on the edges
void bubbleSortEdges(vector<vector<int>>& edges) {
	int n = edges.size();
	for (int i = 0; i < n - 1; ++i) {
		for (int j = 0; j < n - i - 1; ++j) {
			// Compare the first elements of the pairs
			if (edges[j][0] > edges[j + 1][0]) {
				vector<int> temp = edges[j];
				edges[j] = edges[j + 1];
				edges[j + 1] = temp;
			}
		}
	}
}

// Build vector of LinkedLists using the sorted input vector
void buildAdjacencyList(int vertexCount, const vector<vector<int>>& edges, LinkedList* adjList) {
    for (int i = 0; i < edges.size(); ++i) {
        int u = edges[i][0];
        int v = edges[i][1];
        if (!adjList[u].contains(v)) {
            adjList[u].insert(v);
        }
    }
}

void addEdge(LinkedList* adjList, int vertexCount) {
	int from, to;
	cout << "Enter two nodes as two endings of the new edge" << endl;

	while (true) {
		cin >> from >> to;

		// If the input is invalid
		if (cin.fail()) {
			cin.clear(); // Clear the error flag on cin
			cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
			cout << "Invalid input! Please enter integer values for node IDs." << endl;
			continue;
		}

		// Check if the nodes are within the valid range
		if (from < 0 || from >= vertexCount || to < 0 || to >= vertexCount) {
			cout << "The entered node IDs are out of range. Please enter two valid IDs:" << endl;
			continue;
		}

		// Check if from and to are the same
		if (from == to) {
			cout << "The entered node IDs are same. Please enter two valid IDs:" << endl;
			continue;
		}

		// Check if the edge already exists
		if (adjList[from].contains(to)) {
			cout << "This edge already exists." << endl;
			continue;
		}

		// Insert the edge into the adjacency list
		adjList[from].insert(to);
		cout << "The new edge is added." << endl;
		break;
	}
	cout << endl;
}


void removeEdge(LinkedList* adjList, int vertexCount) {
	int from, to;
	cout << "Enter two nodes as two endings of the edge" << endl;



	while (true) {
		cin >> from >> to;

		// If the input is invalid
		if (cin.fail()) {
			cin.clear(); // Clear the error flag on cin
			cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
			cout << "Invalid input! Please enter integer values for node IDs." << endl;
			continue;
		}

		// Check if the nodes are within the valid range
		if (from < 0 || from >= vertexCount || to < 0 || to >= vertexCount) {
			cout << "The entered node IDs are out of range, Enter two other IDs:" << endl;
			continue;
		}

		// Check if the edge exists
		Node* current = adjList[from].head;
		bool edgeExists = false;
		while (current != nullptr) {
			if (current->value == to) {
				edgeExists = true;
				break;
			}
			current = current->next;
		}

		if (!edgeExists) {
			cout << "The entered edge does not exist in the graph! Enter two other node IDs:" << endl;
			continue;
		}

		adjList[from].remove(to);
		cout << "The entered edge is removed." << endl;
		break;
	}
	cout << endl;
}

void displayGraph(const LinkedList* adjList, int vertexCount) {
	cout << "The graph has this structure:" << endl;
	for (int i = 0; i < vertexCount; ++i) {
		cout << i << " ->"; // Print the vertex number followed by "->"
		Node* current = adjList[i].head;
		if (current) { // Only print the arrows for connected nodes
			while (current) {
				cout << " " << current->value;
				current = current->next;
				if (current) {
					cout << " ->";
				}
			}
		}
		cout << endl;
	}

	cout << "Press any key to continue..." << endl;

	while (true) {
		if (_kbhit()) {  // Check if a key is pressed
			char ch = _getch();  // Get the pressed key without waiting for Enter
			break;
		}
	}
}

void breadthFirstSearch(const LinkedList* adjList, int vertexCount) {
	int v = 0;
	Queue Q;
	vector<int> visitedVertices;
	cout << "Please enter starting node:" << endl;

	//Check if the input is in the range
	while (true) {
		cin >> v;

		if (v < 0 || v >= vertexCount) {
			cout << "The entered node number is out of range, enter a valid one:" << endl;
			continue;
		}
		break;
	}

	cout << "Breadth - first search starting from node " << v << ":" << endl;

	Q.enqueue(v);
	visitedVertices.push_back(v); // Mark the starting node as visited

	Node* current = adjList[v].head;

	while (!(Q.isEmpty())) {
		int currentVertex = Q.frontElement();
		cout << currentVertex << " ";
		Q.dequeue();

		Node* current = adjList[currentVertex].head;

		while (current != nullptr) {
			if (!isVisited(current->value, visitedVertices)) {
				Q.enqueue(current->value);
				visitedVertices.push_back(current->value); // Mark the node as visited
			}
			current = current->next;
		}
	}
	cout << endl << endl;

}

void depthFirstSearch(const LinkedList* adjList, int vertexCount) {
	int startVertex;
	cout << "Please enter starting node:" << endl;

	//Check if the input is in the range
	while (true) {
		cin >> startVertex;

		if (startVertex < 0 || startVertex >= vertexCount) {
			cout << "The entered node number is out of range, enter a valid one:" << endl;
			continue;
		}
		break;
	}

	DynamicIntStack stack;
	vector<int> visitedVertices;

	cout << "Depth-first search starting from node " << startVertex << ":" << endl;

	stack.push(startVertex);
	visitedVertices.push_back(startVertex); // Mark the starting node as visited

	while (!stack.isEmpty()) {
		int currentVertex;
		stack.pop(currentVertex);

		cout << currentVertex << " ";

		Node* current = adjList[currentVertex].head;

		while (current != nullptr) {
			if (!isVisited(current->value, visitedVertices)) {
				stack.push(current->value);
				visitedVertices.push_back(current->value); // Mark the node as visited
			}
			current = current->next;
		}
	}
	cout << endl << endl;
}

// Helper function for DFS and BFS
bool isVisited(int v, vector<int>& visitedVertices) {
	for (int i = 0; i < visitedVertices.size(); i++) {
		if (visitedVertices[i] == v) {
			return true;
		}
	}
	return false;
}
