#pragma once
#include "Graph.h"
#include "Input.h"
#include <algorithm>

#define FirstTask Task1v13
#define SecondTask Task2v14

template <class Vertex, class Edge>
class Task
{
public:
	Task(Graph<Vertex, Edge>& graph): graph(&graph) { }
	void Set(Graph<Vertex, Edge>& graph) { this->graph = &graph; Restart(); }
	virtual ~Task() = default;
	virtual void Restart() = 0;
	virtual void Result() = 0;
protected:
	Graph<Vertex, Edge>* graph;
};

#pragma region Task1

string task1Description = "����������� ������, ��������� �� ���������� d �� �������� ������� (d � ����� ����)";

template <class Vertex, class Edge>
class Task1v13: public Task<Vertex, Edge>
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
		cout << "������� �� �������\n";
		return;
	}

	int d = Input<int>::Get("d");

	if (d < 0)
	{
		cout << "�������� ��������\n";
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
		cout << "��� ����� ������\n";

	for (auto v : result)
	{
		v.Print();
		cout << endl;
	}
}

template<class Vertex, class Edge>
inline bool Task1v13<Vertex, Edge>::FindVertex(Vertex** vertex)
{
	typename Graph<Vertex, Edge>::VertexesIterator iter(*Task<Vertex,Edge>::graph);
	string name = Input<string>::Get("��� �������");

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
	typename Graph<Vertex, Edge>::OutputEdgesIterator iter(*Task<Vertex,Edge>::graph, vertex);

	while (iter != iter.End())
	{
		neighbors.push_back((*iter).V2());
		iter++;
	}
}

#pragma endregion

#pragma region Task2

string task2Description = "����������� ������ ����������� ������� �� ������ ��������� ������";

template <class Vertex, class Edge>
class Task2v14 : public Task<Vertex, Edge>
{
public:
	Task2v14(Graph<Vertex, Edge>& graph) : Task<Vertex, Edge>(graph) 
	{
		if (graph.IsDirected() == false) 
			throw "���� ������ ���� ���������������";  
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
		cout << "��� ����� ������\n";
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
			throw "���� �� �������";

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

#pragma endregion