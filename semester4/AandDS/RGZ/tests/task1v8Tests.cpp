#include "pch.h"
#include <gtest/gtest.h>
#include "graphSetup.h"
#include "../Task1v8.h"

template <class Vertex, class Edge>
class Task1v8Test
{
    public:

    static vector<vector<Vertex>> GetResult(Task1v8<Vertex, Edge>* task)
    {
        return task->result;
    }
};

TEST(Task1v8Test, WhenGraphIsUndirected_ShouldThrow) {
    auto graph = SetupUndirectedGraph(RGZGraph::Form::L);
    bool threw = false;

    try {
        auto task = Task1v8<_Vertex, _Edge>(*graph);
    }
    catch (const char* err)
    {
        threw = true;
    }

    ASSERT_TRUE(threw);
}

TEST(Task1v8Test, WhenGraphIsValid_ShouldBeCorrectResult) {
    auto graph = SetupDirectedGraph(RGZGraph::Form::L);
    auto e = graph->AddEdge(vertexMap.Get("3"), vertexMap.Get("0"));
    ASSERT_FALSE(e == nullptr);

    auto task = Task1v8<_Vertex, _Edge>(*graph);
    auto res = Task1v8Test<_Vertex, _Edge>::GetResult(&task);
    ASSERT_EQ(res.size(), 0);

    Input<string>::GetPredefinedValues().push("0");
    task.Restart();
    res = Task1v8Test<_Vertex, _Edge>::GetResult(&task);
    ASSERT_EQ(res.size(), 2);

    Input<string>::GetPredefinedValues().push("1");
    task.Restart();
    res = Task1v8Test<_Vertex, _Edge>::GetResult(&task);
    ASSERT_EQ(res.size(), 4);

    Input<string>::GetPredefinedValues().push("4");
    task.Restart();
    res = Task1v8Test<_Vertex, _Edge>::GetResult(&task);
    ASSERT_EQ(res.size(), 3);
}