#pragma once
#include "Edge.h"
#include "Vertex.h"
#include <vector>

using namespace std;
#define IterOutOfRangeEx "Iterator out of range"

template <class Vertex, class Edge>
class Graph
{
	class GraphForm;

public:

	class VertexesIterator
	{
	public:
		VertexesIterator(Graph& graph) : vertexes(&graph.vertexes), graph(&graph) { it = vertexes->begin(); };
		Vertex& operator *() const
		{
			if (it == vertexes->end())
				throw IterOutOfRangeEx;
			return **it;
		}
		VertexesIterator Begin() { return VertexesIterator(*graph); }
		VertexesIterator End() { VertexesIterator iter(*graph); iter.it = graph->vertexes.end(); return iter; }
		bool operator++(int value)
		{
			if (it == vertexes->end())
				return false;
			it++;
			return it != vertexes->end();
		}
		bool operator==(VertexesIterator iter) { return graph == iter.graph && it == iter.it; }
		bool operator!=(VertexesIterator iter) { return !(*this == iter); }
	protected:
		Graph* graph;
		vector<Vertex*>* vertexes;
		typename vector<Vertex*>::iterator it;
	};

	class OutputEdgesIterator
	{
	public:
		OutputEdgesIterator(Graph& graph, Vertex* vertex) : graph(&graph), vertex(vertex) { graph.form->FindNextEdge(vertex, &curEdge); };
		Edge& operator *() const
		{
			if (curEdge == nullptr)
				throw IterOutOfRangeEx;
			return *curEdge;
		}
		OutputEdgesIterator Begin() { return OutputEdgesIterator(*graph, vertex); }
		OutputEdgesIterator End()
		{
			OutputEdgesIterator iter(*graph, vertex);
			iter.curEdge = nullptr;
			return iter;
		}
		bool operator++(int value)
		{
			graph->form->FindNextEdge(vertex, &curEdge);
			return curEdge != nullptr;
		}
		bool operator==(OutputEdgesIterator iter) { return graph == iter.graph && vertex == iter.vertex && curEdge == iter.curEdge; }
		bool operator!=(OutputEdgesIterator iter) { return !(*this == iter); }
	protected:
		Graph* graph;
		Vertex* vertex;
		Edge* curEdge = nullptr;
	};

	class EdgesIterator
	{
	public:
		EdgesIterator(Graph& graph) : iterVertex(graph), graph(&graph), iterOutEdge(graph, nullptr)
		{
			if (graph.vertexes.size() != 0)
			{
				iterOutEdge = OutputEdgesIterator(graph, &(*iterVertex));
				while (iterOutEdge == iterOutEdge.End())
				{
					if (!(iterVertex++))
						break;

					iterOutEdge = OutputEdgesIterator(graph, &(*iterVertex));
				}
			}
		};
		Edge& operator *() const
		{
			return *iterOutEdge;
		}
		EdgesIterator Begin() { return EdgesIterator(*graph); }
		EdgesIterator End() { EdgesIterator it(*graph);  it.iterVertex = iterVertex.End();  it.iterOutEdge = iterOutEdge.End(); return it; }
		bool operator++(int value)
		{
			if (graph->IsDirected())
				return FindNextEdge();

			//для неориентированного графа ищем ребро, которого до этого не было 
			//т.к. при создании ребра v1->v2  создаётся его копия v2->v1

			do
			{
				if (FindNextEdge() == false)
					return false;
			} while ((*iterOutEdge).V2()->index < (*iterVertex).index);

			return true;
		}
		bool operator==(EdgesIterator iter) { return graph == iter.graph && iterVertex == iter.iterVertex && iterOutEdge == iter.iterOutEdge; }
		bool operator!=(EdgesIterator iter) { return !(*this == iter); }
	protected:
		bool FindNextEdge()
		{
			if (iterOutEdge++)
				return true;

			do
			{
				if (!(iterVertex++))
					return false;

				iterOutEdge = OutputEdgesIterator(*graph, &(*iterVertex));
			} while (iterOutEdge == iterOutEdge.End());

			return true;
		}
		Graph* graph;
		VertexesIterator iterVertex;
		OutputEdgesIterator iterOutEdge;
	};

	enum class Form { L = 0, M = 1 };

	Graph() { form = new ListForm(); }
	Graph(int vertexes, bool isDirected, Form form);
	Graph(int vertexes, int randomEdges, bool isDirected, Form form);
	Graph(const Graph& graph);
	~Graph()
	{
		for (int i = 0; i < vertexes.size(); i++)
			delete vertexes[i];
		delete form;
	}
	int GetVertexCount() { return form->GetVertexCount(); }
	int GetEdgesCount() { return form->GetEdgesCount(); }
	bool IsDirected() { return form->IsDirected(); }
	Form GetForm() { return curForm; }
	void SetForm(Form newForm);
	Vertex* AddVertex() 
	{ 
		vertexes.push_back(form->AddVertex());
		return vertexes.back();
	}
	void RemoveVertex(Vertex* v) 
	{ 
		form->RemoveVertex(v);

		auto it = std::find(vertexes.begin(), vertexes.end(), v);

		for (auto it2 = it + 1; it2 != vertexes.end(); it2++)
			(*it2)->index--;

		vertexes.erase(it);
		delete v;
	}
	Edge* AddEdge(Vertex* v1, Vertex* v2) { return (v1 == v2 ? nullptr : form->AddEdge(v1, v2)  );  }
	bool RemoveEdge(Vertex* v1, Vertex* v2) { return form->RemoveEdge(v1, v2); }
	Edge* GetEdge(Vertex* v1, Vertex* v2) { return form->GetEdge(v1, v2); };
	void Print() { VertexesIterator it(*this);  form->Print(it); };

protected:

	Form curForm = Form::L;
	GraphForm* form;
	vector<Vertex*> vertexes;

	GraphForm* CreateForm(Form form, bool isDirected);

	class GraphForm
	{
	public:
		GraphForm(bool isDirected = false) : isDirected(isDirected) {};
		bool IsDirected() { return isDirected; }
		int GetVertexCount() { return vertexes; }
		int GetEdgesCount() { return edges; }
		virtual ~GraphForm() = default;
		virtual Vertex* AddVertex() = 0;
		virtual void RemoveVertex(Vertex* v) = 0;
		virtual Edge* AddEdge(Vertex* v1, Vertex* v2) = 0;
		virtual bool RemoveEdge(Vertex* v1, Vertex* v2) = 0;
		virtual Edge* GetEdge(Vertex* v1, Vertex* v2) = 0;
		virtual void FindNextEdge(Vertex* v, Edge** current) = 0;
		virtual void Print(VertexesIterator& iter) = 0;
	protected:
		int vertexes = 0;
		int edges = 0;
		bool isDirected = false;
	};

	class MatrixForm : public GraphForm
	{
	public:
		MatrixForm(bool isDirected = false) : GraphForm(isDirected) {};
		~MatrixForm() { DeleteMatrix(); }
		virtual Vertex* AddVertex();
		virtual void RemoveVertex(Vertex* v);
		virtual Edge* AddEdge(Vertex* v1, Vertex* v2);
		virtual bool RemoveEdge(Vertex* v1, Vertex* v2);
		virtual Edge* GetEdge(Vertex* v1, Vertex* v2) { return edges[v1->index][v2->index]; };
		virtual void FindNextEdge(Vertex* v, Edge** current);
		virtual void Print(VertexesIterator& iter);
	protected:
		Edge*** edges;
		void IncreaseMatrix();
		void DeleteMatrix() 
		{
			for (int i = 0; i < GraphForm::vertexes; i++)
				delete[] edges[i];
			delete edges;
		}
		Edge*** CreateMatrix(int size);
		bool IsEdgeExists(Vertex* v1, Vertex* v2);
	};

	class ListForm : public GraphForm
	{
	public:
		ListForm(bool isDirected = false) : GraphForm(isDirected) {};
		~ListForm()
		{
			for (int i = 0; i < edges.size(); i++)
			{
				for (int j = 0; j < edges[i].size(); j++)
					delete edges[i][j];
			}
		}
		virtual Vertex* AddVertex();
		virtual void RemoveVertex(Vertex* v);
		virtual Edge* AddEdge(Vertex* v1, Vertex* v2);
		virtual bool RemoveEdge(Vertex* v1, Vertex* v2);
		virtual Edge* GetEdge(Vertex* v1, Vertex* v2);
		virtual void FindNextEdge(Vertex* v, Edge** current);
		virtual void Print(VertexesIterator& iter);
	protected:
		vector<vector<Edge*>> edges;
		bool IsEdgeExists(Vertex* v1, Vertex* v2);
		typename vector<Edge*>::iterator FindEdgeWithV2(vector<Edge*>& row, Vertex* v2)
		{   return std::find_if(row.begin(), row.end(), [v2](Edge* edge) { return edge->V2() == v2; });   }
	};

	friend class VertexesIterator;
};

template<class Vertex, class Edge>
inline Graph<Vertex, Edge>::Graph(int vertexes, bool isDirected, Form form)
{
	curForm = form;
	this->form = CreateForm(form, isDirected);

	for (int i = 0; i < vertexes; i++)
		AddVertex();
}

template<class Vertex, class Edge>
inline Graph<Vertex, Edge>::Graph(int vertexes, int randomEdges, bool isDirected, Form form): Graph(vertexes, isDirected, form)
{
	if (vertexes <= 1)
		return;

	int maxEdges = vertexes * (vertexes - 1);
	if (randomEdges > maxEdges)
		randomEdges = maxEdges;

	int addedEdges = 0;

	while (addedEdges < randomEdges)
	{
		int i = rand() % this->vertexes.size();

		int j = i;
		while (j == i)
			j = rand() % this->vertexes.size();

		if (AddEdge(this->vertexes[i], this->vertexes[j]) != nullptr)
			addedEdges++;
	}
}

template<class Vertex, class Edge>
inline Graph<Vertex, Edge>::Graph(const Graph& graph)
{
	if (graph.vertexes == 0)
		return;

	VertexesIterator it(graph);
	while (it != it.End())
	{
		Vertex* vertex = AddVertex();
		*vertex = *(it);
	}

	EdgesIterator it2(graph);

	while (it2 != it2.End())
	{
		Edge* edge = (*it2);

		Vertex* v1 = vertexes[edge->V1()->index];
		Vertex* v2 = vertexes[edge->V2()->index];

		Edge* newEdge = AddEdge(v1, v2);

		newEdge = edge;
	}

}

template<class Vertex, class Edge>
inline void Graph<Vertex, Edge>::SetForm(Form newForm)
{
	if (newForm == curForm)
		return;

	curForm = newForm;

	GraphForm* _form;
	if (newForm == Form::L)
		_form = new ListForm();
	else
		_form = new MatrixForm();


	EdgesIterator it(*this);

	if (vertexes.size() == 0)
		goto swap;

	while (it != it.End())
	{
		Edge& edge = *it;

		Vertex* v1 = vertexes[edge.V1()->index];
		Vertex* v2 = vertexes[edge.V2()->index];

		Edge* edgeCopy = _form->AddEdge(v1, v2);

		*edgeCopy = edge;
		it++;
	}

	swap:
	delete this->form;
	form = _form;
}

template<class Vertex, class Edge>
inline typename Graph<Vertex, Edge>::GraphForm* Graph<Vertex, Edge>::CreateForm(Form form, bool isDirected)
{
	if (form == Form::L)
		return new ListForm(isDirected);
	else
		return new MatrixForm(isDirected);
}

#include "GraphForm.h"