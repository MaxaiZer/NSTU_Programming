#pragma once
#include "Graph.h"
#include <map>
#include <string>

using namespace std;

template <class Vertex, class Edge>
class VertexMap
{
public:
	VertexMap(Graph<Vertex, Edge>& graph) : graph(&graph) {};
	bool AddVertex(string name);
	Vertex* GetVertex(string name);
	bool RemoveVertex(string name);
	void SetNamesToAllVertexes();

private:
	std::map<string, Vertex*> map;
	Graph<Vertex, Edge>* graph;
};

template<class Vertex, class Edge>
inline bool VertexMap<Vertex, Edge>::AddVertex(string name)
{
	auto it = map.find(name);
	if (it != map.end())
		return false;

	Vertex* vertex = graph->AddVertex();
	vertex->SetName(name);
	std::pair<string, Vertex*> p(name, vertex);
	map.insert(p);
	return true;
}

template<class Vertex, class Edge>
inline Vertex* VertexMap<Vertex, Edge>::GetVertex(string name)
{
	auto it = map.find(name);

	if (it == map.end())
		return nullptr;

	return (*it).second;
}

template<class Vertex, class Edge>
inline bool VertexMap<Vertex, Edge>::RemoveVertex(string name)
{
	auto it = map.find(name);
	if (it == map.end())
		return false;

	graph->RemoveVertex((*it).second);
	map.erase(it);

	return true;
}

template<class Vertex, class Edge>
inline void VertexMap<Vertex, Edge>::SetNamesToAllVertexes()
{
	typename Graph<Vertex, Edge>::VertexesIterator iter(*graph);

	vector<int> code;
	code.push_back(0);

	while (iter != iter.End())
	{
		string name;

		for (int i = 0; i < code.size(); i++)
			name.insert(name.end(), (char)(code[i] + 97));

		(*iter).SetName(name);

		std::pair<string, Vertex*> p(name, &(*iter));
		map.insert(p);

		if (code.back() == 26)
			code.push_back(0);
		else
			code.back()++;

		iter++;
	}
}
