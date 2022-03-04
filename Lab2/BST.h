
namespace Lab2
{

	template <class Key, class Data> 
	class BST
	{
		class Node;

	public:
		class Iterator
		{
		public:
			Iterator();
			Iterator(BST& bst, Node& node);
		protected:
			BST* bst;
			Node* current;
			friend class BST;
		};

		class ReverseIterator : Iterator
		{
		public:
			ReverseIterator();
			ReverseIterator(BST& bst, Node& node);
			friend class BST;
		};

		BST();
		BST(const& BST);
		~BST();
		Iterator Begin();
		Iterator End();
	protected:
		int size;
		Node* root;

		class Node
		{
		public:
			Node(Key key, Data value);
			Key key;
			Data value;
			Node* left;
			Node* right;
		};

		friend class Iterator;
		friend class ReverseIterator;
	};
}
