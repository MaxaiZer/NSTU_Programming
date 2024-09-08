#pragma once
#include "Graph.h"
#include "Input.h"
#include <algorithm>
#include <limits>
#include <climits>

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