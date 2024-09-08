#pragma once
#include "Graph.h"
#include "Input.h"
#include "Task.h"
#include <algorithm>
#include <limits>
#include <climits>

#define FirstTask Task1v13

inline string task1Description = "Определение вершин, отстоящих на расстоянии d от заданной вершины (d – число рёбер)";

template <class Vertex, class Edge>
class Task1v13 : public Task<Vertex, Edge>
{
public:
	Task1v13(Graph<Vertex, Edge>& graph) : Task<Vertex, Edge>(graph) { Restart(); };
	virtual void Restart();
	virtual void Result();

protected:
	vector<Vertex> result;

	bool FindVertex(Vertex** vertex);
	void GetAllNeighboringVertexes(Vertex* vertex, vector<Vertex*>& neighbors);
};

template<class Vertex, class Edge>
inline void Task1v13<Vertex, Edge>::Restart()
{
	result.clear();

	Vertex* v;
	if (!FindVertex(&v))
	{
		cout << "Вершина не найдена\n";
		return;
	}

	int d = Input<int>::Get("d");

	if (d < 0)
	{
		cout << "Неверный параметр\n";
		return;
	}

	vector<bool> viewed(Task<Vertex, Edge>::graph->GetVertexesCount(), false);

	vector<Vertex*> vertexes;
	vertexes.push_back(v);
	viewed[v->index] = true;

	int curD = 0;
	while (curD != d)
	{
		if (vertexes.empty())
			break;

		vector<Vertex*> nextVertexes;

		for (auto v : vertexes)
			GetAllNeighboringVertexes(v, nextVertexes);

		vertexes.clear();

		for (auto v : nextVertexes)
		{
			if (viewed[v->index] == false)
				vertexes.push_back(v);
		}

		for (auto v : vertexes)
			viewed[v->index] = true;

		curD++;
	}

	for (auto elem : vertexes)
		result.push_back(*elem);
}

template<class Vertex, class Edge>
inline void Task1v13<Vertex, Edge>::Result()
{
	if (result.empty())
		cout << "Нет таких вершин\n";

	for (auto v : result)
	{
		v.Print();
		cout << endl;
	}
}

template<class Vertex, class Edge>
inline bool Task1v13<Vertex, Edge>::FindVertex(Vertex** vertex)
{
	typename Graph<Vertex, Edge>::VertexesIterator iter(*Task<Vertex, Edge>::graph);
	string name = Input<string>::Get("Имя вершины");

	while (iter != iter.End())
	{
		if ((*iter).GetName() == name)
		{
			*vertex = &((*iter));
			return true;
		}
		iter++;
	}
	return false;
}

template<class Vertex, class Edge>
inline void Task1v13<Vertex, Edge>::GetAllNeighboringVertexes(Vertex* vertex, vector<Vertex*>& neighbors)
{
	typename Graph<Vertex, Edge>::OutputEdgesIterator iter(*Task<Vertex, Edge>::graph, vertex);

	while (iter != iter.End())
	{
		neighbors.push_back((*iter).V2());
		iter++;
	}
}