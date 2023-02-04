namespace Lab1
{

	const int NO_INDEX = -1; //��������, ���� ������� �� ����������

	template <class T>
	class List
	{
		class Node;

	public:
		class Iterator
		{
		public:
			Iterator() {};
			Iterator(List<T>& list, int pos);
			T& operator *() const; //���������� ������ �� �������� �������� ��������
			bool operator++(int value); //������� � ���������� ��������
			bool operator--(int value); //������� � ����������� ��������
			bool operator == (Iterator iter) const
			{
				return list == iter.list && current == iter.current;
			}
			bool operator != (Iterator iter) const
			{
				return !(*this == iter);
			}
		protected:
			List<T>* list = nullptr; //��������� �� ������
			Node* current = nullptr; //��������� �� ������� ������� ������

			friend class List;
		};

		List() : List(1) {}
		List(int capacity);
		List(const List<T>&);
		~List() { delete[] array; };
		int GetSize() const { return size; }
		void Clear();
		bool IsEmpty() const { return size == 0; }
		bool Contains(T value) const;
		T& operator[] (int pos); //������/��������� �������� � �������� ������� � ������
		int GetPos(T value) const;
		void Add(T value);
		bool Add(T value, int pos);
		bool RemoveByValue(T value);
		bool RemoveByPos(int pos);
		Iterator Begin() { return Iterator(*this, 0); }        //������ ������� ���������
		Iterator End() { return Iterator(*this, NO_INDEX); }   //������ ����������������� ������� ���������
		int GetReadElementsCount() const { return readElements; } //������ ����� ���������, ������������� ��������� ���������
		void Print();

	protected:
		int capacity;
		int size = 0;
		mutable int readElements = 0; //���������� ������������� ��������� ��������� ���������
		int startIndex = NO_INDEX; //������ ������� ��������
		int endIndex = NO_INDEX; //������ ���������� ��������
		int firstFreeIndex = NO_INDEX; //������ ��������� ������ � �������
		Node* array = nullptr; //�������. ������ ���������

		void CreateArrayWithFreeNodes(int capacity); //�������� ������� �� ���������� ���������� � ����������� ������
		void IncreaseArray(); //���������� ������� ������� �� 1
		void Remove(Node& node);
		Node& GetFreeNode(int& index); //���������� ��������� ������� � �������
		bool FindNodeByPos(int& index, int pos) const;
		bool FindNodeByValue(int& index, int& pos, T value) const;
		bool LinkAsPrevAndNext(int index1, int index2);	 //������ ��������� ��� ���������� � �����������

		class Node
		{
		public:
			int prevIndex = NO_INDEX; //������ ����������� ��������
			int index = NO_INDEX; //����������� ������ 
			int nextIndex = NO_INDEX; //������ ���������� ��������
			T value;

			Node() { }
			void ResetIndexes() { prevIndex = nextIndex = NO_INDEX; } //����� ��������
		};

	};

	//�������� ������ ������

	template<class T>
	inline List<T>::List(int capacity)
	{
		if (capacity <= 0)
			throw "Invalid capacity";

		firstFreeIndex = 0;
		CreateArrayWithFreeNodes(capacity);
	}

	template<class T>
	inline List<T>::List(const List<T>& list)
	{
		this->capacity = list.capacity;
		this->startIndex = list.startIndex;
		this->endIndex = list.endIndex;
		this->size = list.size;
		this->firstFreeIndex = list.firstFreeIndex;

		array = new Node[capacity];
		for (int i = 0; i < capacity; i++)
			array[i] = list.array[i];
	}

	template<class T>
	inline void List<T>::Clear()
	{
		delete[] array;
		size = firstFreeIndex = 0;
		capacity = 1;

		CreateArrayWithFreeNodes(capacity);

		startIndex = endIndex = NO_INDEX;
	}

	template<class T>
	inline bool List<T>::Contains(T value) const
	{
		int nodeIndex, pos;
		return FindNodeByValue(nodeIndex, pos, value);
	}

	template<class T>
	inline T& List<T>::operator[](int pos)
	{
		int nodeIndex;
		if (FindNodeByPos(nodeIndex, pos))
			return array[nodeIndex].value;
		else
			throw "Wrong pos";
	}

	template<class T>
	inline void List<T>::Add(T value)
	{
		if (size == capacity)
			IncreaseArray();

		int freeIndex;
		Node& node = GetFreeNode(freeIndex);
		node.value = value;

		if (IsEmpty())
			startIndex = freeIndex;
		else
			LinkAsPrevAndNext(endIndex, freeIndex);

		endIndex = freeIndex;

		size++;
	}

	template<class T>
	inline bool List<T>::Add(T value, int pos)
	{
		if (pos < 0 || pos > size)
			return false;

		if (size == capacity)
			IncreaseArray();

		if (pos == size)
		{
			Add(value);
			return true;
		}

		int nodeIndex;
		if (FindNodeByPos(nodeIndex, pos) == false)
			return false;

		Node& nextNode = array[nodeIndex];

		int prevIndex = nextNode.prevIndex;

		int newNodeIndex;
		Node& newNode = GetFreeNode(newNodeIndex);
		newNode.value = value;

		bool isFirst = prevIndex == NO_INDEX;

		if (isFirst)
			this->startIndex = newNodeIndex;
		else
			LinkAsPrevAndNext(prevIndex, newNodeIndex);

		LinkAsPrevAndNext(newNodeIndex, nextNode.index);
		size++;

		return true;
	}

	template<class T>
	inline int List<T>::GetPos(T value) const
	{
		int nodeIndex, pos;
		if (FindNodeByValue(nodeIndex, pos, value) == false)
			return NO_INDEX;

		return pos;
	}

	template<class T>
	inline bool List<T>::RemoveByValue(T value)
	{
		if (IsEmpty())
			return false;

		bool removedOnce = false;

		int curIndex = startIndex;

		while (curIndex != NO_INDEX)
		{
			int prevIndex = curIndex;
			curIndex = array[prevIndex].nextIndex;

			if (array[prevIndex].value == value)
			{
				Remove(array[prevIndex]);
				removedOnce = true;
			}
		}

		return removedOnce;
	}

	template<class T>
	inline bool List<T>::RemoveByPos(int pos)
	{
		int nodeIndex;
		if (FindNodeByPos(nodeIndex, pos) == false)
			return false;

		Remove(array[nodeIndex]);
		return true;
	}

	template<class T>
	inline void List<T>::Print()
	{
		if (IsEmpty())
		{
			std::cout << "List is empty" << std::endl;
			return;
		}

		Iterator iter = this->Begin();

		do
		{
			std::cout << "[" << *iter << "] ";
		} while (iter++);

		std::cout << std::endl;
	}

	//��������� ������ ������

	template<class T>
	inline void List<T>::CreateArrayWithFreeNodes(int capacity)
	{
		this->capacity = capacity;
		array = new Node[capacity];
		for (int i = 0; i < capacity - 1; i++)
		{
			array[i].index = i;
			array[i].nextIndex = i + 1; //��������� �������� (� ������ ������ ���) �������� ����������� ������
		}
		array[capacity - 1].index = capacity - 1;
	}

	template<class T>
	inline void List<T>::IncreaseArray()
	{
		capacity++;

		Node* newArray = new Node[capacity];
		for (int i = 0; i < capacity - 1; i++)
			newArray[i] = array[i];

		newArray[capacity - 1].index = capacity - 1;

		if (firstFreeIndex != NO_INDEX)
			array[firstFreeIndex].nextIndex = capacity - 1;
		else
			firstFreeIndex = capacity - 1;

		delete[] array;
		array = newArray;
	}

	template<class T>
	void List<T>::Remove(Node& node)
	{
		int prevIndex = node.prevIndex, nextIndex = node.nextIndex;

		if (size == 1)
		{
			this->startIndex = endIndex = NO_INDEX;
			goto addNodeToFree;
		}

		if (prevIndex != NO_INDEX && nextIndex != NO_INDEX)
		{
			LinkAsPrevAndNext(prevIndex, nextIndex);
		}
		else if (prevIndex == NO_INDEX)
		{
			this->startIndex = nextIndex;
			array[nextIndex].prevIndex = NO_INDEX;
		}
		else if (nextIndex == NO_INDEX)
		{
			this->endIndex = prevIndex;
			array[prevIndex].nextIndex = NO_INDEX;
		}

	addNodeToFree:

		node.ResetIndexes();
		node.nextIndex = this->firstFreeIndex;
		firstFreeIndex = node.index;
		size--;
	}

	template<class T>
	inline typename List<T>::Node& List<T>::GetFreeNode(int& index)
	{
		if (firstFreeIndex == NO_INDEX)
			throw "Where is no free node";

		index = firstFreeIndex;
		Node& freeNode = array[firstFreeIndex];
		firstFreeIndex = array[firstFreeIndex].nextIndex;
		freeNode.ResetIndexes();

		return freeNode;
	}

	template<class T>
	inline bool List<T>::LinkAsPrevAndNext(int index1, int index2)
	{
		if (index1 < 0 || index1 >= capacity || index2 < 0 || index2 >= capacity)
			return false;

		array[index1].nextIndex = index2;
		array[index2].prevIndex = index1;
		return true;
	}

	template<class T>
	inline bool List<T>::FindNodeByPos(int& index, int pos) const
	{
		if (pos < 0 || pos >= size)
			return false;

		bool reverseBypass = false;
		int curPos = 0;
		readElements = 1;
		int curIndex = startIndex;

		if (pos > size / 2)
		{
			curIndex = endIndex;
			curPos = size - 1;
			reverseBypass = true;
		}

		while (curPos != pos)
		{
			if (reverseBypass)
			{
				curIndex = array[curIndex].prevIndex;
				curPos--;
			}
			else
			{
				curIndex = array[curIndex].nextIndex;
				curPos++;
			}
			readElements++;
		}

		index = curIndex;
		return true;
	}

	template<class T>
	inline bool List<T>::FindNodeByValue(int& index, int& pos, T value) const
	{
		if (IsEmpty())
			return false;

		int curIndex = startIndex;
		int curPos = 0;
		readElements = 0;
		do
		{
			readElements++;
			if (array[curIndex].value == value)
			{
				index = curIndex;
				pos = curPos;
				return true;
			}
			curPos++;
			curIndex = array[curIndex].nextIndex;
		} while (curIndex != NO_INDEX);

		return false;
	}

	//������ ���������

	template<class T>
	inline List<T>::Iterator::Iterator(List<T>& list, int pos)
	{
		this->list = &list;
		int index;
		if (list.FindNodeByPos(index, pos))
		{
			current = &list.array[index];
		}
	}

	template<class T>
	inline T& List<T>::Iterator::operator*() const
	{
		if (current != nullptr)
			return current->value;
		else
			throw "Iterator is not installed";
	}

	template<class T>
	inline bool List<T>::Iterator::operator++(int)
	{
		if (current == nullptr)
			return false;

		if (current->nextIndex == NO_INDEX)
		{
			*this = list->End();
			return false;
		}

		current = &list->array[current->nextIndex];
		return true;
	}

	template<class T>
	inline bool List<T>::Iterator::operator--(int)
	{
		if (current == nullptr)
			return false;

		if (current->prevIndex == NO_INDEX)
			return false;

		current = &list->array[current->prevIndex];
		return true;
	}

}