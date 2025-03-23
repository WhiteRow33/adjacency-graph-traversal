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

// --- Function Declarations ---

void readEdges(vector<vector<int>>& edges, vector<string>& illegalEdges, int& vertexCount);
void bubbleSortEdges(vector<vector<int>>& edges);
void buildAdjacencyList(int vertexCount, const vector<vector<int>>& edges, LinkedList* adjList);

void addEdge(LinkedList* adjList, int vertexCount);
void removeEdge(LinkedList* adjList, int vertexCount);
void displayGraph(const LinkedList* adjList, int vertexCount);

void depthFirstSearch(const LinkedList* adjList, int vertexCount);
void breadthFirstSearch(const LinkedList* adjList, int vertexCount);

bool isVisited(int v, const vector<int>& visitedVertices);


// --- Main Menu Program ---

int main() {
    int vertexCount = 0;
    vector<vector<int>> edges;
    vector<string> illegalEdges;

    readEdges(edges, illegalEdges, vertexCount);
    bubbleSortEdges(edges);

    LinkedList* adjList = new LinkedList[vertexCount];
    buildAdjacencyList(vertexCount, edges, adjList);

    if (!illegalEdges.empty()) {
        cout << "\nThese edges are illegal or repeated:\n";
        for (const string& edge : illegalEdges) {
            cout << edge << endl;
        }
        cout << endl;
    }

    int choice = 0;
    do {
        cout << "   (1) Add edge\n"
             << "   (2) Remove edge\n"
             << "   (3) Display the graph\n"
             << "   (4) Depth-first search\n"
             << "   (5) Breadth-first search\n"
             << "   (6) Exit\n"
             << "Please enter a number (1-6):\n";

        do {
            cin >> choice;
            if (cin.fail() || choice < 1 || choice > 6) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid input! Please enter a valid number (1-6):\n";
                choice = 0;
            }
        } while (choice < 1 || choice > 6);

        switch (choice) {
            case 1: addEdge(adjList, vertexCount); break;
            case 2: removeEdge(adjList, vertexCount); break;
            case 3: displayGraph(adjList, vertexCount); break;
            case 4: depthFirstSearch(adjList, vertexCount); break;
            case 5: breadthFirstSearch(adjList, vertexCount); break;
            case 6: cout << "Program exiting...\n"; break;
        }

    } while (choice != 6);

    delete[] adjList;
    return 0;
}

// --- Input & Preprocessing ---

void readEdges(vector<vector<int>>& edges, vector<string>& illegalEdges, int& vertexCount) {
    string filename;
    ifstream file;

    // Try opening file until success
    do {
        cout << "Enter the input file name:\n";
        cin >> filename;
        file.open(filename);
        if (!file.is_open()) {
            cout << "Could not open the file " << filename << endl;
        }
    } while (!file.is_open());

    string line;
    while (getline(file, line)) {
        istringstream iss(line);
        int u, v;
        char extraChar;

        if ((iss >> u >> v) && !(iss >> extraChar)) {
            if (u < 0 || v < 0) {
                illegalEdges.push_back(line);
                continue;
            }

            bool isDuplicate = false;
            for (const auto& edge : edges) {
                if (edge[0] == u && edge[1] == v) {
                    isDuplicate = true;
                    break;
                }
            }

            if (!isDuplicate) {
                edges.push_back({u, v});
                vertexCount = max(vertexCount, max(u, v) + 1);
            } else {
                illegalEdges.push_back(line);
            }
        } else {
            illegalEdges.push_back(line);
        }
    }

    file.close();
}

void bubbleSortEdges(vector<vector<int>>& edges) {
    int n = edges.size();
    for (int i = 0; i < n - 1; ++i) {
        for (int j = 0; j < n - i - 1; ++j) {
            if (edges[j][0] > edges[j + 1][0]) {
                swap(edges[j], edges[j + 1]);
            }
        }
    }
}

void buildAdjacencyList(int vertexCount, const vector<vector<int>>& edges, LinkedList* adjList) {
    for (const auto& edge : edges) {
        int u = edge[0];
        int v = edge[1];
        if (!adjList[u].contains(v)) {
            adjList[u].insert(v);
        }
    }
}

// --- Graph Manipulation ---

void addEdge(LinkedList* adjList, int vertexCount) {
    int from, to;
    cout << "Enter two nodes as the endpoints of the new edge:\n";

    while (true) {
        cin >> from >> to;

        if (cin.fail() || from == to || from < 0 || from >= vertexCount || to < 0 || to >= vertexCount) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please enter two distinct valid node IDs:\n";
            continue;
        }

        if (adjList[from].contains(to)) {
            cout << "This edge already exists.\n";
            continue;
        }

        adjList[from].insert(to);
        cout << "Edge added successfully.\n\n";
        break;
    }
}

void removeEdge(LinkedList* adjList, int vertexCount) {
    int from, to;
    cout << "Enter two nodes as the endpoints of the edge to remove:\n";

    while (true) {
        cin >> from >> to;

        if (cin.fail() || from < 0 || from >= vertexCount || to < 0 || to >= vertexCount) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please enter valid node IDs:\n";
            continue;
        }

        if (!adjList[from].contains(to)) {
            cout << "Edge does not exist. Try again:\n";
            continue;
        }

        adjList[from].remove(to);
        cout << "Edge removed successfully.\n\n";
        break;
    }
}

void displayGraph(const LinkedList* adjList, int vertexCount) {
    cout << "Current graph structure:\n";
    for (int i = 0; i < vertexCount; ++i) {
        cout << i << " ->";
        Node* current = adjList[i].head;
        while (current) {
            cout << " " << current->value;
            if (current->next) cout << " ->";
            current = current->next;
        }
        cout << endl;
    }

    cout << "Press any key to continue...\n";
    while (!_kbhit()) {}
    _getch();
}

// --- Traversals ---

void breadthFirstSearch(const LinkedList* adjList, int vertexCount) {
    int start;
    cout << "Enter starting node for BFS:\n";
    while (!(cin >> start) || start < 0 || start >= vertexCount) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid input. Enter a valid node ID:\n";
    }

    Queue q;
    vector<int> visited;
    q.enqueue(start);
    visited.push_back(start);

    cout << "BFS traversal order:\n";
    while (!q.isEmpty()) {
        int current = q.frontElement();
        cout << current << " ";
        q.dequeue();

        Node* node = adjList[current].head;
        while (node) {
            if (!isVisited(node->value, visited)) {
                q.enqueue(node->value);
                visited.push_back(node->value);
            }
            node = node->next;
        }
    }
    cout << "\n\n";
}

void depthFirstSearch(const LinkedList* adjList, int vertexCount) {
    int start;
    cout << "Enter starting node for DFS:\n";
    while (!(cin >> start) || start < 0 || start >= vertexCount) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid input. Enter a valid node ID:\n";
    }

    DynamicIntStack stack;
    vector<int> visited;
    stack.push(start);
    visited.push_back(start);

    cout << "DFS traversal order:\n";
    while (!stack.isEmpty()) {
        int current;
        stack.pop(current);
        cout << current << " ";

        Node* node = adjList[current].head;
        while (node) {
            if (!isVisited(node->value, visited)) {
                stack.push(node->value);
                visited.push_back(node->value);
            }
            node = node->next;
        }
    }
    cout << "\n\n";
}

bool isVisited(int v, const vector<int>& visitedVertices) {
    for (int x : visitedVertices) {
        if (x == v) return true;
    }
    return false;
}
