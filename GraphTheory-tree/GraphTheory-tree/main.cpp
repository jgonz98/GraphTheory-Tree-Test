#include <iostream>
#include <string>
#include <vector>

using namespace std;

void formatVertices(string, vector<string>&);
void formatEdges(string, vector<string>&);
void formatAdjacents(vector<string>, vector<string>, vector<vector<string>>);

void main() {
	string vertices, edges;
	vector<string> verticesData;
	vector<string> edgesData;
	vector<vector<string>> adjacentData;

	cout << "Enter the number of vertices V(G) using {a,b,c} form: {";
	getline(cin, vertices);
	formatVertices(vertices, verticesData);

	cout << "Enter the edges E(G) using {ab,ac,be} form: {";
	getline(cin, edges);
	formatEdges(edges, edgesData);
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

void formatEdges(string edges, vector<string>& edgesData) {
	string et;
	int lcheck = 0;
	for (int i = 0; i < edges.length(); i++) {
		if (edges.substr(i, 1) == "}") {
			edgesData.push_back(et);
			et.clear();
		}
		else if (edges.substr(i, 1) == ",") {
			edgesData.push_back(et);
			et.clear();
		}
		else {
			et += edges.substr(i, 1);
		}

	}

}

void formatAdjacent(vector<string> verticesData, vector<string> edgesData, vector<vector<string>>& adjacentData) {
	//Process edges into new array with first row as vertices and columns under it's adjacent vertices.
}