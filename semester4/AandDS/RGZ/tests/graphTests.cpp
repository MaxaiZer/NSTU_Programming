#include "pch.h"
#include "../Graph.h"
#include "../VertexMap.h"
#include <gtest/gtest.h>

using _Vertex = Vertex<string, int>;
using _Edge = Edge<_Vertex, int, string>;
using RGZGraph = Graph<_Vertex, _Edge>;
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

class GraphTestFixture : public ::testing::TestWithParam<RGZGraph::Form> {

};

INSTANTIATE_TEST_CASE_P(
    DifferentFormsTest,
    GraphTestFixture,
    ::testing::Values(RGZGraph::Form::L, RGZGraph::Form::M)
);

TEST_P(GraphTestFixture, ReversedEdgeInDirectedGraphShouldNotExist) {
    auto form = GetParam();
    auto graph = SetupDirectedGraph(form);

    //vertexes of existing edge
    auto vertex1 = vertexMap.Get("0");
    auto vertex2 = vertexMap.Get("1");

    bool originalEdgeExists = graph->GetEdge(vertex1, vertex2) != nullptr;
    EXPECT_TRUE(originalEdgeExists);

    EXPECT_EQ(graph->GetEdge(vertex2, vertex1), nullptr);
    EXPECT_FALSE(graph->RemoveEdge(vertex2, vertex1));
}

TEST_P(GraphTestFixture, AddEdgeInDirectedGraphShouldBeCorrect) {
    auto form = GetParam();
    auto graph = SetupDirectedGraph(form);

    //vertexes of existing edge
    auto vertex1 = vertexMap.Get("0");
    auto vertex2 = vertexMap.Get("1");

    EXPECT_EQ(graph->AddEdge(vertex1, vertex2), nullptr);

    bool edgeAdded = graph->AddEdge(vertex2, vertex1) != nullptr;
    EXPECT_TRUE(edgeAdded);
}

TEST_P(GraphTestFixture, RemovingEdgeInUndirectedGraphShouldBeCorrect) {
    auto form = GetParam();
    auto graph = SetupUndirectedGraph(form);

    //vertexes of existing edge
    auto vertex1 = vertexMap.Get("2");
    auto vertex2 = vertexMap.Get("5");

    EXPECT_EQ(graph->GetEdgesCount(), 7);
    EXPECT_TRUE(graph->RemoveEdge(vertex1, vertex2));
    EXPECT_FALSE(graph->RemoveEdge(vertex1, vertex2));
    EXPECT_FALSE(graph->RemoveEdge(vertex2, vertex1));
    EXPECT_EQ(graph->GetEdgesCount(), 6);
}

TEST_P(GraphTestFixture, AddEdgeInUndirectedGraphShouldBeCorrect) {
    auto form = GetParam();
    auto graph = SetupUndirectedGraph(form);

    //vertexes of existing edge
    auto vertex1 = vertexMap.Get("2");
    auto vertex2 = vertexMap.Get("5");

    EXPECT_EQ(graph->AddEdge(vertex1, vertex2), nullptr);
    EXPECT_EQ(graph->AddEdge(vertex2, vertex1), nullptr);

    EXPECT_TRUE(graph->RemoveEdge(vertex1, vertex2));

    bool edgeAdded = graph->AddEdge(vertex1, vertex2) != nullptr;
    EXPECT_TRUE(edgeAdded);
}

TEST_P(GraphTestFixture, AlterEdgeInUndirectedGraphShouldAffectReversed) {
    auto form = GetParam();
    auto graph = SetupUndirectedGraph(form);

    //vertexes of existing edge
    auto vertex1 = vertexMap.Get("2");
    auto vertex2 = vertexMap.Get("5");

    auto edge = graph->GetEdge(vertex1, vertex2);
    auto reversed_edge = graph->GetEdge(vertex2, vertex1);

    edge->SetWeight(100);
    edge->SetData("new_data");

    EXPECT_EQ(edge->GetData(), reversed_edge->GetData());
    EXPECT_EQ(edge->GetWeight(), reversed_edge->GetWeight());
    EXPECT_EQ(edge->HasData(), reversed_edge->HasData());
    EXPECT_EQ(edge->HasWeight(), reversed_edge->HasWeight());

    reversed_edge->SetWeight(-100);
    reversed_edge->SetData("new_new_data");

    EXPECT_EQ(edge->GetData(), reversed_edge->GetData());
    EXPECT_EQ(edge->GetWeight(), reversed_edge->GetWeight());
    EXPECT_EQ(edge->HasData(), reversed_edge->HasData());
    EXPECT_EQ(edge->HasWeight(), reversed_edge->HasWeight());
}

TEST(GraphTestFixture, VertexIteratorInDirectedGraphShouldWorkCorrect) {
    auto graph = SetupDirectedGraph(RGZGraph::Form::L);

    RGZGraph::VertexesIterator vIterator(*graph);
    vIterator = vIterator.Begin();

    int vertexes = 1;
    while (vIterator++) vertexes++;
    
    EXPECT_EQ(vertexes, 5);
}

TEST_P(GraphTestFixture, OutputEdgesIteratorInDirectedGraphShouldWorkCorrect) {
    auto form = GetParam();
    auto graph = SetupDirectedGraph(form);

    RGZGraph::OutputEdgesIterator eIterator(*graph, vertexMap.Get("0"));
    eIterator = eIterator.Begin();

    int edges = 1;
    while (eIterator++) edges++;

    EXPECT_EQ(edges, 1);

    eIterator = RGZGraph::OutputEdgesIterator(*graph, vertexMap.Get("3"));
    eIterator = eIterator.Begin();

    edges = 1;
    while (eIterator++) edges++;

    EXPECT_EQ(edges, 2);
}

TEST_P(GraphTestFixture, EdgesIteratorInDirectedGraphShouldWorkCorrect) {
    auto form = GetParam();
    auto graph = SetupDirectedGraph(form);

    RGZGraph::EdgesIterator eIterator(*graph);
    eIterator = eIterator.Begin();

    int edges = 1;
    while (eIterator++) edges++;

    EXPECT_EQ(edges, 7);
}

TEST(GraphTestFixture, VertexIteratorInUndirectedGraphShouldWorkCorrect) {
    auto graph = SetupUndirectedGraph(RGZGraph::Form::L);

    RGZGraph::VertexesIterator vIterator(*graph);
    vIterator = vIterator.Begin();

    int vertexes = 1;
    while (vIterator++) vertexes++;

    EXPECT_EQ(vertexes, 6);
}

TEST_P(GraphTestFixture, OutputEdgesIteratorInUndirectedGraphShouldWorkCorrect) {
    auto form = GetParam();
    auto graph = SetupUndirectedGraph(form);

    RGZGraph::OutputEdgesIterator eIterator(*graph, vertexMap.Get("0"));
    eIterator = eIterator.Begin();

    int edges = 1;
    while (eIterator++) edges++;

    EXPECT_EQ(edges, 3);

    eIterator = RGZGraph::OutputEdgesIterator(*graph, vertexMap.Get("3"));
    eIterator = eIterator.Begin();

    edges = 1;
    while (eIterator++) edges++;

    EXPECT_EQ(edges, 2);
}

TEST_P(GraphTestFixture, EdgesIteratorInUndirectedGraphShouldWorkCorrect) {
    auto form = GetParam();
    auto graph = SetupUndirectedGraph(form);

    RGZGraph::EdgesIterator eIterator(*graph);
    eIterator = eIterator.Begin();

    int edges = 1;
    while (eIterator++) edges++;

    EXPECT_EQ(edges, 7);
}

TEST(GraphTestFixture, AlterEdgeShouldWorkCorrect) {
    auto graph = SetupUndirectedGraph(RGZGraph::Form::L);

    auto e = graph->GetEdge(vertexMap.Get("0"), vertexMap.Get("1"));
    
    EXPECT_FALSE(e->HasData());
    EXPECT_TRUE(e->HasWeight()); //because graph creates edge with default weight: 1

    e->SetData("what");
    e->SetWeight(12);

    EXPECT_TRUE(e->HasData());
    EXPECT_TRUE(e->HasWeight());
}