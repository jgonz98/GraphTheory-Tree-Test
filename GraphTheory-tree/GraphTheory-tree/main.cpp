#include <iostream>
#include <string>
#include <vector>

using namespace std;

void formatVertices(string, vector<string>&);
void formatEdges(string, vector<string>&);
void formatAdjacents(vector<string>, vector<string>, vector<vector<string>>&);
void fEdges(vector<string>, vector<int>*, string);
bool cycleCheck(int, bool[], int, vector<int>*);
bool isTree(vector<string>, vector<int>*);


void main() {
	string vertices, edges;
	vector<string> verticesData;
	vector<string> edgesData;
	vector<vector<string>> adjacentData;
	vector<int> *adj;
	cout << "Enter the vertices V(G) using {a,b,c} form: {";
	getline(cin, vertices);
	formatVertices(vertices, verticesData);
	adj = new vector<int>[verticesData.size()];
	
	cout << "Enter the edges E(G) using {ab,ac,be} form: {";
	getline(cin, edges);
	fEdges(verticesData,adj,edges);
	if (isTree(verticesData, adj)) {
		cout << "The graph is a tree!" << endl;
	}
	else {
		cout << "The graph is not a tree!" << endl;
	}

	system("pause");
}

void formatVertices(string vertices, vector<string> &verticesData) {
	string vt;
	int lcheck = 0;
	for (int i = 0; i < vertices.length(); i++) {
		if (vertices.substr(i, 1) == "}") {
			verticesData.push_back(vt);
			vt.clear();
		}
		else if (vertices.substr(i, 1) == ",") {
			verticesData.push_back(vt);
			vt.clear();
			lcheck = 0;
		}
		else {
			vt = vertices.substr(i, 1);
			lcheck++;
		}
		if (lcheck > 1) {
			i = vertices.length() + 1;
			cout << "ERROR: YOU CAN ONLY INPUT SINGLE LETTERS FOR VERTICES" << endl;
			terminate();
		}

	}
}

void fEdges(vector<string> verticesData, vector<int> *adj,string edges) {
	int o, t, c=0;
	for (int i = 0; i < edges.length(); i++) {
		for (int j = 0; j < verticesData.size(); j++) {
			if (verticesData[j] == edges.substr(i,1)) {
				if (c == 0) {
					o = j;
					c++;
				}
				else {
					t = j;
					c++;
				}

			}
		}
		if (c == 2) {
			adj[o].push_back(t);
			adj[t].push_back(o);
			c = 0;
		}
	}
}

bool cycleCheck(int v,bool visited[], int parent, vector<int> *adj)
{
	// Mark the current node as visited 
	visited[v] = true;

	// Recur for all the vertices adjacent to this vertex 
	vector<int>::iterator i;
	for (i = adj[v].begin(); i != adj[v].end(); ++i)
	{
		// If an adjacent is not visited, then recur for  
		// that adjacent 
		if (!visited[*i])
		{
			if (cycleCheck(*i, visited, v,adj)) {
				return true;
			}
		}

		// If an adjacent is visited and not parent of current 
		// vertex, then there is a cycle. 
		else if (*i != parent) {
			return true;
		}
	}
	return false;
}

bool isTree(vector<string> verticesData, vector<int> *adj)
{
	// Mark all the vertices as not visited and not part of  
	// recursion stack 
	bool *visited = new bool[verticesData.size()];
	for (int i = 0; i < verticesData.size(); i++)
		visited[i] = false;

	// The call to isCyclicUtil serves multiple purposes. 
	// It returns true if graph reachable from vertex 0  
	// is cyclcic. It also marks all vertices reachable  
	// from 0. 
	if (cycleCheck(0, visited, -1, adj))
		return false;

	// If we find a vertex which is not reachable from 0  
	// (not marked by isCyclicUtil(), then we return false 
	for (int u = 0; u < verticesData.size(); u++)
		if (!visited[u])
			return false;

	return true;
}