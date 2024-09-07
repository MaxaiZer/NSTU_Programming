#pragma once
#include <memory>

template <class Vertex, class Weight, class Data>
class Edge
{
public:
	Edge();
	Edge(Vertex* v1, Vertex* v2, Weight weight) : Edge() { this->v1 = v1; this->v2 = v2; SetWeight(weight); }
	Edge(Vertex* v1, Vertex* v2, Weight weight, Data data) : Edge(v1, v1, weight) { SetData(data); }

	Weight GetWeight() const { return sharedData->weight; };
	void SetWeight(Weight newW) { sharedData->hasWeight = true; sharedData->weight = newW; }
	bool HasWeight() const { return sharedData->hasWeight; }
	Data GetData() const { return sharedData->data; };
	void SetData(Data newD) { sharedData->hasData = true; sharedData->data = newD; }
	bool HasData() const{ return sharedData->hasData; }
	Vertex* V1() const { return v1; };
	Vertex* V2() const { return v2; };
	Edge* CreateReversedCopy();
	void Print() const;
	void CopyDataWeight(const Edge& edge);

protected:

	class SharedData
	{
	public:
		Weight weight;
		Data data;
		bool hasWeight = false;
		bool hasData = false;
	};

	std::shared_ptr<SharedData> sharedData;

	Vertex* v1 = nullptr, * v2 = nullptr;
};

template<class Vertex, class Weight, class Data>
inline Edge<Vertex, Weight, Data>::Edge()
{
	sharedData = std::make_shared<SharedData>();
}

template<class Vertex, class Weight, class Data>
inline Edge<Vertex, Weight, Data>* Edge<Vertex, Weight, Data>::CreateReversedCopy()
{
	Edge* newEdge = new Edge();
	newEdge->v1 = this->v2;
	newEdge->v2 = this->v1;
	newEdge->sharedData = this->sharedData;
	return newEdge;
}

template<class Vertex, class Weight, class Data>
inline void Edge<Vertex, Weight, Data>::Print() const
{
	std::cout << v1->GetName() << "->" << v2->GetName() << ": ";

	if (sharedData->hasData)
		std::cout << "data:" << sharedData->data;
	else
		std::cout << "no data ";

	if (sharedData->hasWeight)
		std::cout << "weight:" << sharedData->weight;
	else
		std::cout << "no weight ";
}

template<class Vertex, class Weight, class Data>
inline void Edge<Vertex, Weight, Data>::CopyDataWeight(const Edge& edge)
{
	if (edge.HasData())
		SetData(edge.GetData());
	if (edge.HasWeight())
		SetWeight(edge.GetWeight());
}
