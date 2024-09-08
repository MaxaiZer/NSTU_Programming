#include "pch.h"
#include "graphSetup.h"

VertexMap<string, _Vertex*> vertexMap;

unique_ptr<RGZGraph> SetupDirectedGraph(RGZGraph::Form form) {
    auto graph = make_unique<RGZGraph>(0, true, form);
    vertexMap.Clear();

    _Vertex* v0 = graph->AddVertex(); v0->SetName("0"); vertexMap.Add("0", v0);
    _Vertex* v1 = graph->AddVertex(); v1->SetName("1"); vertexMap.Add("1", v1);
    _Vertex* v2 = graph->AddVertex(); v2->SetName("2"); vertexMap.Add("2", v2);
    _Vertex* v3 = graph->AddVertex(); v3->SetName("3"); vertexMap.Add("3", v3);
    _Vertex* v4 = graph->AddVertex(); v4->SetName("4"); vertexMap.Add("4", v4);

    auto e = graph->AddEdge(v0, v1); e->SetWeight(1);
    e = graph->AddEdge(v1, v2); e->SetWeight(2);
    e = graph->AddEdge(v2, v3); e->SetWeight(2);
    e = graph->AddEdge(v3, v2); e->SetWeight(3);
    e = graph->AddEdge(v2, v4); e->SetWeight(4);
    e = graph->AddEdge(v4, v3); e->SetWeight(5);
    e = graph->AddEdge(v3, v1); e->SetWeight(1);

    return graph;
}

unique_ptr<RGZGraph> SetupUndirectedGraph(RGZGraph::Form form) {
    auto graph = std::make_unique<RGZGraph>(0, false, form);
    vertexMap.Clear();

    _Vertex* v0 = graph->AddVertex(); v0->SetName("0"); vertexMap.Add("0", v0);
    _Vertex* v1 = graph->AddVertex(); v1->SetName("1"); vertexMap.Add("1", v1);
    _Vertex* v2 = graph->AddVertex(); v2->SetName("2"); vertexMap.Add("2", v2);
    _Vertex* v3 = graph->AddVertex(); v3->SetName("3"); vertexMap.Add("3", v3);
    _Vertex* v4 = graph->AddVertex(); v4->SetName("4"); vertexMap.Add("4", v4);
    _Vertex* v5 = graph->AddVertex(); v4->SetName("5"); vertexMap.Add("5", v5);

    if (graph->AddEdge(v0, v1) == nullptr) throw "Error add edge";
    if (graph->AddEdge(v0, v4) == nullptr) throw "Error add edge";
    if (graph->AddEdge(v0, v3) == nullptr) throw "Error add edge";
    if (graph->AddEdge(v1, v4) == nullptr) throw "Error add edge";
    if (graph->AddEdge(v3, v4) == nullptr) throw "Error add edge";
    if (graph->AddEdge(v4, v5) == nullptr) throw "Error add edge";
    if (graph->AddEdge(v5, v2) == nullptr) throw "Error add edge";

    return graph;
}