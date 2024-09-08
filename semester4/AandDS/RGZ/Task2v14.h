#pragma once
#include "Graph.h"
#include "Input.h"
#include "Task.h"
#include <algorithm>
#include <limits>
#include <climits>

#define SecondTask Task2v14

string task2Description = "Определение центра взвешенного орграфа на основе алгоритма Флойда";

template <class Vertex, class Edge>
class Task2v14 : public Task<Vertex, Edge>
{
public:
	Task2v14(Graph<Vertex, Edge>& graph) : Task<Vertex, Edge>(graph)
	{
		if (graph.IsDirected() == false)
			throw "Граф должен быть ориентированным";
		Restart();
	};
	virtual void Restart();
	virtual void Result();
protected:
	vector<Vertex> result;
	vector<vector<int>> GetWeightMatrix();
	vector<Vertex*> GetAllVertexes();
	void Floyd(vector<vector<int>>& weights);
	int GetEccentricity(vector<vector<int>>& weights, int vertexIndex);
	vector<Vertex> SaveVector(const vector<Vertex*>& v);
};

template<class Vertex, class Edge>
inline void Task2v14<Vertex, Edge>::Result()
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
inline void Task2v14<Vertex, Edge>::Restart()
{
	result.clear();
	int vertexes = Task<Vertex, Edge>::graph->GetVertexesCount();

	if (vertexes == 0)
		return;

	vector<vector<int>> weights = GetWeightMatrix();
	Floyd(weights);

	vector<int> mins(vertexes);
	int min = INT_MAX;
	for (int i = 0; i < vertexes; i++)
	{
		mins[i] = GetEccentricity(weights, i);
		min = std::min(min, mins[i]);
	}

	vector<Vertex*> graphVertexes = GetAllVertexes();

	vector<Vertex*> centers;

	for (int i = 0; i < mins.size(); i++)
	{
		if (min == mins[i])
			centers.push_back(graphVertexes[i]);
	}

	result = SaveVector(centers);
}

template<class Vertex, class Edge>
inline vector<vector<int>> Task2v14<Vertex, Edge>::GetWeightMatrix()
{
	int vertexes = Task<Vertex, Edge>::graph->GetVertexesCount();

	vector<vector<int>> weights;

	for (int i = 0; i < vertexes; i++)
	{
		weights.push_back(vector<int>());
		for (int j = 0; j < vertexes; j++)
			weights[i].push_back(numeric_limits<int>::max());
	}

	result.clear();
	typename Graph<Vertex, Edge>::EdgesIterator iter(*Task<Vertex, Edge>::graph);

	while (iter != iter.End())
	{
		Vertex* v1 = (*iter).V1();
		Vertex* v2 = (*iter).V2();

		if (!(*iter).HasWeight())
			throw "Граф не взвешен";

		weights[v1->index][v2->index] = (*iter).GetWeight();

		if (Task<Vertex, Edge>::graph->IsDirected() == false)
			weights[v2->index][v1->index] = (*iter).GetWeight();

		iter++;
	}

	return weights;
}

template<class Vertex, class Edge>
inline vector<Vertex*> Task2v14<Vertex, Edge>::GetAllVertexes()
{
	vector<Vertex*> vertexes;
	typename Graph<Vertex, Edge>::VertexesIterator iter(*Task<Vertex, Edge>::graph);

	while (iter != iter.End())
	{
		vertexes.push_back(&(*iter));
		iter++;
	}

	return vertexes;
}

template<class Vertex, class Edge>
inline void Task2v14<Vertex, Edge>::Floyd(vector<vector<int>>& weights)
{
	for (int i = 0; i < weights.size(); i++)
	{
		for (int j = 0; j < weights.size(); j++)
		{
			for (int s = 0; s < weights.size(); s++)
			{
				int possibleMin = weights[j][i] + weights[i][s];
				if (weights[j][i] == numeric_limits<int>::max() || weights[i][s] == numeric_limits<int>::max())
					possibleMin = numeric_limits<int>::max();

				weights[j][s] = std::min(weights[j][s], possibleMin);
			}
		}
	}
}

template<class Vertex, class Edge>
inline int Task2v14<Vertex, Edge>::GetEccentricity(vector<vector<int>>& weights, int vertexIndex)
{
	int max = (vertexIndex == 0 ? -1 : weights[0][vertexIndex]);
	if (weights.size() == 1) max = weights[0][0];

	for (int i = 0; i < weights.size(); i++)
	{
		if (i == vertexIndex) continue;

		max = std::max(max, weights[i][vertexIndex]);
	}

	return max;
}

template<class Vertex, class Edge>
inline vector<Vertex> Task2v14<Vertex, Edge>::SaveVector(const vector<Vertex*>& v)
{
	vector<Vertex> savedPath;

	for (auto elem : v)
		savedPath.push_back(*elem);

	return savedPath;
}