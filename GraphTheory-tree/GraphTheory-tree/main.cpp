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
	string vt; //Used as placeholder to assign vertices to
	int lcheck = 0; //letter check used to ensure character per vertex is 1
	for (int i = 0; i < vertices.length(); i++) {
		if (vertices.substr(i, 1) == "}") {
			verticesData.push_back(vt); //Add vertex to vector
			vt.clear(); //Clear string placeholde
		}
		else if (vertices.substr(i, 1) == ",") {
			verticesData.push_back(vt); //Add vertex to vector
			vt.clear(); //Clear string placeholder
			lcheck = 0; //Reset character count to 0
		}
		else {
			vt = vertices.substr(i, 1); //Set vt equal to point in vertex string 
			lcheck++; //Increase character count by 1
		}
		if (lcheck > 1) { //Character check
			i = vertices.length() + 1;
			cout << "ERROR: YOU CAN ONLY INPUT SINGLE CHARACTERS FOR VERTICES" << endl;
			terminate();
		}

	}
}

void fEdges(vector<string> verticesData, vector<int> *adj,string edges) {
	int o, t, c = 0; 
	//Go through edge string
	for (int i = 0; i < edges.length(); i++) { 
		//Compare edge string to vertices
		for (int j = 0; j < verticesData.size(); j++) { 
			if (verticesData[j] == edges.substr(i,1)) {
				//Set 1st match of edge equal to o 
				if (c == 0) { 
					o = j;
					c++;
				}
				//Set 2nd match of edge equal to t
				else { 
					t = j;
					c++;
				}

			}
		}
		//Pushing o and t to each others adjacent vector
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
	//Initialize vertices to not visited
	bool *visited = new bool[verticesData.size()];
	for (int i = 0; i < verticesData.size(); i++)
		visited[i] = false;
	//Run cycleCheck from vertex 0
	if (cycleCheck(0, visited, -1, adj)) {
		cycle = 1;
	}
	//Do connected and disconnected check by checking for unvisited vertex
	for (int u = 0; u < verticesData.size(); u++)
		if (!visited[u]) {
			con = 1;
		}
	//Output Result
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