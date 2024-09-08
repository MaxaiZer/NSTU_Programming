#include "pch.h"
#include <gtest/gtest.h>
#include "graphSetup.h"

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