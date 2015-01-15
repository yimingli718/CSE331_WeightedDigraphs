/**
 * \file WeightedDigraph.cpp
 *
 * \author Yiming Li
 */

/**
 * A definition of a weighted digraph
 * used for CSE 331 Project 6
 * Written by James Daly
 * Completed by Yiming Li
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
	unordered_map<int, double> vertice;
	for (int i = 0; i < numVertices; i++){
		map.push_back(vertice);
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
	map[from][to] = weight;
}

/**
 * Finds the number of arcs leading out of the given vertex
 */
int WeightedDigraph::GetOutDegree(int vertex) const { 
	// TODO
	return map[vertex].size();
}

/**
 * Finds the weight of the arc between the two vertices
 * Returns infinity if there is no such arc
 */
double WeightedDigraph::GetArcWeight(int from, int to) const {
	// TODO
	unordered_map<int, double>::const_iterator got = map[from].find(to);
	if (got != map[from].end()){
		return map[from].at(to);
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
		if (GetArcWeight(*from, *to) != numeric_limits<double>::infinity()){
			count += GetArcWeight(*from, *to);
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
	unordered_map<int, double>::const_iterator got = map[from].find(to);
	if (got != map[from].end()){
		return true;
	}
	else{
		return false;
	}
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

/**
* Helper function to determine wherther a path between the two vertices exists.
*/
bool WeightedDigraph::DoesPathExistHelper(int from, int to, vector<int> &vertices) const {
	if(from != to){
		for (auto arc = map[from].begin(); arc != map[from].end(); arc++){
			if (arc->first == to){
				return true;
			}

			else if (arc->first != to && map[arc->first].size() != 0 && vertices[arc->first] == 0){
				vertices[arc->first] = 1;
				bool result = DoesPathExistHelper(arc->first, to, vertices);
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
		if (!AreConnected(*from, *to)){
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
	std::list<int> path;
	double infinity = numeric_limits<double>::infinity();
	vector<double> minimum;
	for (int i = 0; i < numVertices; i++){
		minimum.push_back(infinity);
	}
	minimum[from] = 0;

	vector<int> vertices;
	for (int i = 0; i < numVertices; i++){
		vertices.push_back(-1);
	}

	std::set<std::pair<int, double> > v_queue;
	v_queue.insert(std::make_pair(from, minimum[from]));

	if (from == to)
	{
		path.push_front(from);
		return path;
	}

	while (!v_queue.empty())
	{
		double distance = v_queue.begin()->second;
		int u = v_queue.begin()->first;
		v_queue.erase(v_queue.begin());
		auto neighbors = map[u];
		for (auto i = neighbors.begin(); i != neighbors.end(); i++)
		{
			int vertex = i->first;
			double weight = i->second;
			double total_distence = distance + weight;
			if (total_distence < minimum[vertex])
			{
				v_queue.erase(std::make_pair(vertex, minimum[vertex]));
				minimum[vertex] = total_distence;
				vertices[vertex] = u;
				v_queue.insert(std::make_pair(vertex, minimum[vertex]));
			}
		}
	}

	for (int vertex = to; vertex != -1; vertex = vertices[vertex])
		path.push_front(vertex);
	return path;
}