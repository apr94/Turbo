#include <iostream>

using namespace std;

namespace Turbo{

	template<typename T>

		class MinHeapNode{

			public:
				MinHeapNode(T* parent);
				~MinHeapNode();
				T getRightChild();
				T getLeftChild();
				T getParent();
				int getSize();
				int getDepth();



			private:
				int size;
				int depth;
				MinHeapNode<T>* LeftChild;
				MinHeapNode<T>* RightChild;
				MinHeapNode<T>* parent;

		};

	
	template<typename T>
		MinHeapNode<T>::MinHeapNode(T* parent):size(0), LeftChild(nullptr), RightChild(nullptr){
			this->parent = parent;
			this->depth = parent->depth + 1;
		}
	
	template<typename T>
		MinHeapNode<T>::~MinHeapNode(){
			delete LeftChild;
			delete RightChild;
		}
	
	
	template<typename T>

		class MinHeap{

			public:
				
				MinHeap();
				~MinHeap();
				T delete_min();
				T getRoot();
				int insert(T v);
				int getSize();
				int getMaxDepth();


			private:
				
				int size;
				int maxDepth;
				MinHeapNode<T>* root;

		};


	template<typename T>
		MinHeap<T>::MinHeap():size(0), maxDepth(0), root(nullptr){
			
		}
	
	template<typename T>
		MinHeap<T>::~MinHeap(){
			delete root;
		}
}
