#pragma once
#include "Graph.h"
#include <iostream>

template<class Vertex, class Edge>
inline Vertex* Graph<Vertex, Edge>::MatrixForm::AddVertex()
{
	IncreaseMatrix();
	Vertex* newVertex = new Vertex();
	GraphForm::vertexes++;
	newVertex->index = GraphForm::vertexes - 1;
	return newVertex;
}

template<class Vertex, class Edge>
inline void Graph<Vertex, Edge>::MatrixForm::RemoveVertex(Vertex* v)
{
	Edge*** newEdges = CreateMatrix(GraphForm::vertexes - 1);

	for (int i = 0; i < GraphForm::vertexes; i++)
	{
		if (i == v->index)
			continue;

		for (int j = 0; j < GraphForm::vertexes; j++)
		{
			if (j == v->index)
				continue;

			newEdges[i][j] = edges[i][j];
		}
	}

	GraphForm::vertexes--;
	delete[] edges;
	edges = newEdges;
}

template<class Vertex, class Edge>
inline Edge* Graph<Vertex, Edge>::MatrixForm::AddEdge(Vertex* v1, Vertex* v2)
{
	if (IsEdgeExists(v1, v2))
		return nullptr;

	Edge** edge1 = &edges[v1->index][v2->index];
	Edge** edge2 = &edges[v2->index][v1->index];

	*edge1 = new Edge(v1, v2, 1);

	if (GraphForm::isDirected == false)
	{
		*edge2 = (*edge1)->CreateReversedCopy();
	}

	GraphForm::edges++;
	return *edge1;
}

template<class Vertex, class Edge>
inline bool Graph<Vertex, Edge>::MatrixForm::RemoveEdge(Vertex* v1, Vertex* v2)
{
	if (IsEdgeExists(v1, v2) == false)
		return false;

	Edge* edge1 = edges[v1->index][v2->index];
	Edge* edge2 = edges[v2->index][v1->index];

	auto deletePtr = [](Edge** ptr) { delete* ptr; *ptr = nullptr; };

	deletePtr(&edge1);

	if (GraphForm::isDirected == false)
		deletePtr(&edge2);

	GraphForm::edges--;
	return true;
}

template<class Vertex, class Edge>
inline void Graph<Vertex, Edge>::MatrixForm::FindNextEdge(Vertex* v, Edge** current)
{
	if (v == nullptr) return;

	int startIndex = 0;

	if (*current != nullptr)
	{
		for (int i = 0; i < GraphForm::vertexes; i++)
		{
			if (*current == edges[v->index][i])
			{
				startIndex = i + 1;
				break;
			}
		}
	}

	*current = nullptr;

	for (int i = startIndex; i < GraphForm::vertexes; i++)
	{
		if (edges[v->index][i] != nullptr)
		{
			*current = edges[v->index][i];
			return;
		}
	}
}

template<class Vertex, class Edge>
inline void Graph<Vertex, Edge>::MatrixForm::Print(VertexesIterator& iter)
{
	if (iter == iter.End())
	{
		cout << "Graph is empty\n";
		return;
	}

	cout << "  ";

	for (int i = 0; i < GraphForm::vertexes; i++)
		cout << i << " ";

	cout << endl;

	while (iter != iter.End())
	{
		cout << (*iter).index << " ";

		for (int i = 0; i < GraphForm::vertexes; i++)
		{
			Edge* edge = edges[(*iter).index][i];
			if (edge == nullptr)
				cout << 0;
			else
				cout << 1;

			cout << " ";

		}

		cout << endl;
		iter++;
	}

	cout << "index-name | ";
	for (iter = iter.Begin(); iter != iter.End(); iter++)
	{
		cout << (*iter).index << "-" << (*iter).GetName() << " ";
	}
	cout << endl;
}

template<class Vertex, class Edge>
inline void Graph<Vertex, Edge>::MatrixForm::IncreaseMatrix()
{
	Edge*** newEdges = CreateMatrix(GraphForm::vertexes + 1);

	for (int i = 0; i < GraphForm::vertexes; i++)
	{
		for (int j = 0; j < GraphForm::vertexes; j++)
			newEdges[i][j] = edges[i][j];
	}

	DeleteMatrix();
	edges = newEdges;
}

template<class Vertex, class Edge>
inline Edge*** Graph<Vertex, Edge>::MatrixForm::CreateMatrix(int size)
{
	if (size <= 0) return nullptr;

	Edge*** newEdges = new Edge * *[size];

	for (int i = 0; i < size; i++)
	{
		newEdges[i] = new Edge * [size];

		for (int j = 0; j < size; j++)
			newEdges[i][j] = nullptr;
	}

	return newEdges;
}

template<class Vertex, class Edge>
inline bool Graph<Vertex, Edge>::MatrixForm::IsEdgeExists(Vertex* v1, Vertex* v2)
{
	Edge* edge1 = edges[v1->index][v2->index];
	Edge* edge2 = edges[v2->index][v1->index];

	if (GraphForm::isDirected)
		return (edge1 != nullptr || edge2 != nullptr);
	else
		return (edge1 != nullptr && edge2 != nullptr);
}

template<class Vertex, class Edge>
inline Vertex* Graph<Vertex, Edge>::ListForm::AddVertex()
{
	vector<Edge*> newRow;
	edges.push_back(newRow);

	Vertex* newVertex = new Vertex();
	newVertex->index = GraphForm::vertexes;
	GraphForm::vertexes++;
	return newVertex;
}

template<class Vertex, class Edge>
inline void Graph<Vertex, Edge>::ListForm::RemoveVertex(Vertex* v)
{
	if (GraphForm::isDirected == false)
	{
		for (auto edge : edges[v->index])
		{
			auto& row = edges[edge->V2()->index];
			auto it = FindEdgeWithV2(row, v);
			row.erase(it);
		}
	}
	else
	{
		for (int i = 0; i < GraphForm::vertexes; i++)
		{
			if (i == v->index) continue;

			auto it = FindEdgeWithV2(edges[i], v);
			if (it != edges[i].end())
				edges[i].erase(it);
		}
	}

	edges.erase(edges.begin() + v->index);
	GraphForm::vertexes--;
}

template<class Vertex, class Edge>
inline bool Graph<Vertex, Edge>::ListForm::IsEdgeExists(Vertex* v1, Vertex* v2)
{
	if (FindEdgeWithV2(edges[v1->index], v2) != edges[v1->index].end())
		return true;

	if (GraphForm::isDirected)
	{
		return FindEdgeWithV2(edges[v2->index], v1) != edges[v2->index].end();
	}
	return false;
}

template<class Vertex, class Edge>
inline Edge* Graph<Vertex, Edge>::ListForm::AddEdge(Vertex* v1, Vertex* v2)
{
	vector<Edge*>& row = edges[v1->index];

	if (IsEdgeExists(v1, v2))
		return nullptr;

	Edge* newEdge = new Edge(v1, v2, 1);
	row.push_back(newEdge);

	if (GraphForm::isDirected == false)
	{
		edges[v2->index].push_back(newEdge->CreateReversedCopy());
	}

	GraphForm::edges++;
	return newEdge;
}

template<class Vertex, class Edge>
inline bool Graph<Vertex, Edge>::ListForm::RemoveEdge(Vertex* v1, Vertex* v2)
{
	auto it = FindEdgeWithV2(edges[v1->index], v2);

	if (it == edges[v1->index].end()) return false;

	edges[v1->index].erase(it);

	if (GraphForm::isDirected == false)
	{
		auto it = FindEdgeWithV2(edges[v2->index], v1);
		edges[v2->index].erase(it);
	}

	GraphForm::edges--;
	return true;
}

template<class Vertex, class Edge>
inline Edge* Graph<Vertex, Edge>::ListForm::GetEdge(Vertex* v1, Vertex* v2)
{
	auto it = FindEdgeWithV2(edges[v1->index], v2);
	if (it == edges[v1->index].end()) return nullptr;

	return *it;
}

template<class Vertex, class Edge>
inline void Graph<Vertex, Edge>::ListForm::FindNextEdge(Vertex* v, Edge** current)
{
	if (v == nullptr) return;

	if (*current == nullptr)
	{
		*current = (edges[v->index].size() == 0 ? nullptr : edges[v->index].front());
		return;
	}

	auto it = std::find(edges[v->index].begin(), edges[v->index].end(), *current);

	if (*it == edges[v->index].back())
		*current = nullptr;
	else
	{
		it++;
		*current = *it;
	}
}

template<class Vertex, class Edge>
inline void Graph<Vertex, Edge>::ListForm::Print(VertexesIterator& iter)
{
	if (iter == iter.End())
	{
		cout << "Graph is empty\n";
		return;
	}

	while (iter != iter.End())
	{
		if ((*iter).HasName())
			cout << (*iter).GetName() << ": ";
		else
			cout << "No name: ";

		for (int i = 0; i < edges[(*iter).index].size(); i++)
		{
			cout << edges[(*iter).index][i]->V2()->GetName() << " ";
		}

		cout << endl;
		iter++;
	}
}
