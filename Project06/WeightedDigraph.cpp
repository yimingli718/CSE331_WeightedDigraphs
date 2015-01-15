/**
 * A definition of a weighted digraph
 * used for CSE 331 Project 6
 * Written by James Daly
 * Completed by [Your Name]
 */

#include "WeightedDigraph.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <limits>

using namespace std;

/**
 * Constructs the digraph from a file.
 * You may add any additional construction to this section.
 */
WeightedDigraph::WeightedDigraph(const string& filename) : numVertices(0), numArcs(0) {
	ifstream in(filename);
	if(!in.is_open()) {
		cerr << "cannot open file!" << std::endl;
		exit(EXIT_FAILURE);
	}
	
	string line;
	getline(in, line);
	istringstream vertexStream(line);
	vertexStream >> numVertices;
	
	// TODO : You can initialize your data structure here.
	vector<double> v;
	for (int i = 0; i < numVertices; i++){
		v.push_back(-1.0);
	}
	for (int i = 0; i < numVertices; i++){
		matrix.push_back(v);
	}
	
	while(getline(in,line)) {
		istringstream iss(line);
		int u, v;
		float weight;
		iss >> u >> v >> weight;
		InsertArc(u, v, weight);
	}
}

/**
 * Destructor
 * You can do any needed cleanup here.
 */
WeightedDigraph::~WeightedDigraph() {
	// Intentionally left empty
	// You may do any needed cleanup here
}

/**
 * Inserts a weighted arc into the digraph.
 * This is the sole mutator of this class and it is private
 * so the digraph is immutable once created.
 */
void WeightedDigraph::InsertArc(int from, int to, double weight) {
	numArcs++;
	(matrix[from])[to] = weight;
}

/**
 * Finds the number of arcs leading out of the given vertex
 */
int WeightedDigraph::GetOutDegree(int vertex) const { 
	// TODO
	int count = 0;
	vector<double> v = matrix[vertex];
	for (int i = 0; i < v.size(); i++){
		if (v[i] >= 0 && v[i] < numVertices){
			count++;
		}
	}
	return count;;
}

/**
 * Finds the weight of the arc between the two vertices
 * Returns infinity if there is no such arc
 */
double WeightedDigraph::GetArcWeight(int from, int to) const {
	// TODO
	if (matrix[from][to] >= 0.0 && matrix[from][to] < double(numVertices)){
		return matrix[from][to];
	}
	else{
		return numeric_limits<double>::infinity();
	}
}

/**
 * Finds the sum weight of the given path.
 * Returns infinity if the path is broken.
 */
double WeightedDigraph::GetPathWeight(const list<int> & path) const {
	// TODO
	double count = 0;
	auto to = path.begin();
	auto from = to;
	to++;
	for (to; to != path.end(); to++){
		if (matrix[*from][*to] != -1.0){
			count += matrix[*from][*to];
		}
		else{
			return numeric_limits<double>::infinity();
		}
		from = to;
	}
	return count;
}

/**
 * Checks whether an arc exists between two vertices.
 */
bool WeightedDigraph::AreConnected(int from, int to) const {
	if (matrix[from][to] != -1.0){
		return true;
	}
	return false;
}

/**
 * Determines whether a path between the two vertices exists.
 */
bool WeightedDigraph::DoesPathExist(int from, int to) const {
	// TODO
	vector<int> vertices;
	for (int i = 0; i < numVertices; i++){
		vertices.push_back(0);
	}
	vertices[from] = 1;
	bool result = DoesPathExistHelper(from, to, vertices);
	return result;
}

bool WeightedDigraph::DoesPathExistHelper(int from, int to, vector<int> &vertices) const {
	if (from != to){
		vector<double> v = matrix[from];
		for (int i = 0; i < v.size(); i++){
			if (v[i] != -1.0 && i == to){
				return true;
			}

			else if (v[i] != -1.0 && i != to && vertices[i] == 0){
				vertices[i] = 1;
				bool result = DoesPathExistHelper(i, to, vertices);
				if (result){
					return true;
				}
			}
		}
		return false;
	}

	else{
		return true;
	}
}

/**
 * Checks whether the given path goes over existing arcs.
 */
bool WeightedDigraph::IsPathValid(const list<int> & path) const {
	auto to = path.begin();
	auto from = to;
	to++;
	for (to; to != path.end(); to++){
		if (matrix[*from][*to] == -1.0){
			return false;
		}
		from = to;
	}
	return true;
}

/**
 * Finds a path of minimum weight between the two nodes.
 * The behavior is undefined if no such path exists
 * (you may assume that such a path does exist).
 */
list<int> WeightedDigraph::FindMinimumWeightedPath(int from, int to) const {
	// TODO
	//double weight = 0;
	list<int> path;
	////bool truth = FindMinimumWeightedPathHelper(from, to, weight, path);
	//path.push_front(from);
	//return path;
	return 
}

//
//bool WeightedDigraph::FindMinimumWeightedPathHelper(int from, int to, double &weight, list<int> &p) const {
//	list<int> temp_path = p;
//	double temp_weight = 0;
//	double temp_weight2 = 0;
//	if (from != to){
//		vector<double> v = matrix[from];
//		for (int i = 0; i < v.size(); i++){
//			if (v[i] != -1.0 && i == to){
//				temp_path.clear();
//				temp_path.push_back(i);
//				p = temp_path;
//				temp_weight += this->GetArcWeight(from, i);
//				weight = temp_weight;
//				cout << "temp_weight: " << temp_weight << endl;
//				return true;
//			}
//
//			else if (v[i] != -1 && i != to){
//				temp_path.push_back(i);
//				bool result = FindMinimumWeightedPathHelper(i, to, temp_weight, temp_path);
//				if (result){
//					temp_path.push_front(i);
//					if (temp_weight2 == 0 || temp_weight < temp_weight2){
//						cout << "test" << temp_weight << temp_weight2 <<endl;
//						temp_weight2 = temp_weight;
//						weight += temp_weight;
//						p = temp_path;
//					}
//				}
//				else{
//					temp_path.clear();
//				}
//			}
//		}
//		return true;
//	}
//	else{
//		return true;
//	}
//}
