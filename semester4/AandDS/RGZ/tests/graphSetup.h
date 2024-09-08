#pragma once
#include "../Graph.h"
#include "../VertexMap.h"

using _Vertex = Vertex<string, int>;
using _Edge = Edge<_Vertex, int, string>;
using RGZGraph = Graph<_Vertex, _Edge>;
extern VertexMap<string, _Vertex*> vertexMap;

unique_ptr<RGZGraph> SetupDirectedGraph(RGZGraph::Form form);
unique_ptr<RGZGraph> SetupUndirectedGraph(RGZGraph::Form form);