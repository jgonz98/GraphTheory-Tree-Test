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
		cout << "therefore graph is a tree." << endl;
	}
	else {
		cout << "therefore graph is not a tree." << endl;
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
	visited[v] = true;
	vector<int>::iterator i;
	for (i = adj[v].begin(); i != adj[v].end(); ++i)
	{
		if (!visited[*i])
		{
			if (cycleCheck(*i, visited, v,adj)) {
				return true;
			}
		}
		else if (*i != parent) {
			return true;
		}
	}
	return false;
}

bool isTree(vector<string> verticesData, vector<int> *adj)
{
	int cycle = 0,con = 0;
	bool *visited = new bool[verticesData.size()];
	for (int i = 0; i < verticesData.size(); i++)
		visited[i] = false;
	if (cycleCheck(0, visited, -1, adj)) {
		cycle = 1;
	}
	for (int u = 0; u < verticesData.size(); u++)
		if (!visited[u]) {
			con = 1;
		}
	if (con == 1 && cycle == 1) {
		cout << "The graph is disconnected and contains cycles, ";
		return false;
	}
	if (con == 1 && cycle == 0) {
		cout << "The graph is disconnected and acyclic, ";
		return false;
	}
	if (con == 0 && cycle == 1) {
		cout << "The graph is connected and contains cycles, ";
		return false;
	}
	if (con == 0 && cycle == 0) {
		cout << "The graph is connected and acyclic, ";
		return true;
	}
}