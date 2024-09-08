#include "pch.h"
#include <gtest/gtest.h>
#include "graphSetup.h"
#include "../Task2v4.h"

template <class Vertex, class Edge>
class Task2v4Test
{
public:

    static vector<Vertex> GetResult(Task2v4<Vertex, Edge>* task)
    {
        return task->result;
    }
};

TEST(Task2v4Test, WhenGraphIsUndirected_ShouldThrow) {
    auto graph = SetupUndirectedGraph(RGZGraph::Form::L);
    bool threw = false;

    try {
        auto task = Task2v4<_Vertex, _Edge>(*graph);
    }
    catch (const char* err)
    {
        threw = true;
    }

    ASSERT_TRUE(threw);
}

TEST(Task2v4Test, WhenGraphIsNotCoherent_ShouldBeEmptyResult) {
    auto graph = SetupDirectedGraph(RGZGraph::Form::L);
    graph->RemoveEdge(vertexMap.Get("0"), vertexMap.Get("1"));

    auto task = Task2v4<_Vertex, _Edge>(*graph);
    auto res = Task2v4Test<_Vertex, _Edge>::GetResult(&task);
    ASSERT_EQ(res.size(), 0);
}

TEST(Task2v4Test, WhenGraphIsValid_ShouldBeCorrectResult) {
    auto graph = SetupDirectedGraph(RGZGraph::Form::L);

    auto task = Task2v4<_Vertex, _Edge>(*graph);
    auto res = Task2v4Test<_Vertex, _Edge>::GetResult(&task);
    ASSERT_EQ(res[0].GetName(), "0");

    auto e = graph->AddEdge(vertexMap.Get("3"), vertexMap.Get("0"));
    ASSERT_FALSE(e == nullptr);

    task.Restart();
    res = Task2v4Test<_Vertex, _Edge>::GetResult(&task);
    ASSERT_EQ(res[0].GetName(), "2");

    graph->GetEdge(vertexMap.Get("2"), vertexMap.Get("3"))->SetWeight(5);
    e = graph->AddEdge(vertexMap.Get("3"), vertexMap.Get("4"));
    ASSERT_FALSE(e == nullptr);
    e->SetWeight(-1);

    task.Restart();
    res = Task2v4Test<_Vertex, _Edge>::GetResult(&task);
    ASSERT_EQ(res[0].GetName(), "3");
}

TEST(Task2v4Test, WhenGraphHasNegativeCycle_ShouldThrowError) {
    auto graph = SetupDirectedGraph(RGZGraph::Form::L);
    auto e = graph->AddEdge(vertexMap.Get("3"), vertexMap.Get("0"));
    auto task = Task2v4<_Vertex, _Edge>(*graph);

    e = graph->AddEdge(vertexMap.Get("3"), vertexMap.Get("4"));
    e->SetWeight(-100);

    ASSERT_THROW(task.Restart(), const char*);
}