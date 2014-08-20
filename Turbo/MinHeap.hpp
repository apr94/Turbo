#include <iostream>

using namespace std;

namespace Turbo{
	
	template<typename T>
		class MinHeap;

	template<typename T>

		class MinHeapNode{

			friend class MinHeap<T>;

			public:
				MinHeapNode(MinHeapNode<T>* parent, T val);
				~MinHeapNode();
				MinHeapNode<T>* getRightChild();
				MinHeapNode<T>* getLeftChild();
				MinHeapNode<T>* getParent();
				T getValue();

			private:
				MinHeapNode<T>* LeftChild;
				MinHeapNode<T>* RightChild;
				MinHeapNode<T>* parent;
				T value;

		};

	template<typename T>
		MinHeapNode<T>::MinHeapNode(MinHeapNode<T>* parent, T val): LeftChild(nullptr), RightChild(nullptr){
			this->parent = parent;
			this->value = val;
		}

	template<typename T>
		MinHeapNode<T>::~MinHeapNode(){
			delete LeftChild;
			delete RightChild;
		}

	template<typename T>
		MinHeapNode<T>* MinHeapNode<T>::getRightChild(){
			return this->RightChild;
		}

	template<typename T>
		MinHeapNode<T>* MinHeapNode<T>::getLeftChild(){
			return this->LeftChild;
		}
	
	template<typename T>
		MinHeapNode<T>* MinHeapNode<T>::getParent(){
			return this->parent;
		}
	
	template<typename T>
		T MinHeapNode<T>::getValue(){
			return this->value;
		}	
	
	template<typename T>

		class MinHeap{

			public:

				MinHeap();
				~MinHeap();
				T delete_min();
				MinHeapNode<T>* getRoot();
				int insert(T v);
				int getSize();

			private:

				int size;
				MinHeapNode<T>* root;

		};

	template<typename T>
		MinHeap<T>::MinHeap():size(0), root(nullptr){

		}

	template<typename T>
		MinHeap<T>::~MinHeap(){
			delete root;
		}

	template<typename T>
		MinHeapNode<T>* MinHeap<T>::getRoot(){
			return this->root;
		}

	template<typename T>
		int MinHeap<T>::getSize(){
			return this->size;
		}

	template<typename T>

		int MinHeap<T>::insert(T v){

			if (this->size == 0){
				MinHeapNode<T>* mhn = new MinHeapNode<T>(nullptr, v);
				this->root = mhn;
				this->size++;
				return 1;
			}
			else{
				int newsize = ++this->size;

				std::string binary;
				int count = 0;

				while (count < 31){

					binary += newsize < 0 ? '1' : '0';
					newsize = newsize << 1;
					count++;

				}

				char lastDigit = newsize < 0 ? '1' : '0';

				bool foundOne = false;
				MinHeapNode<T>* curr_ptr = this->root;

				for (char c: binary){

					if (c == '1' and !foundOne) foundOne = true;
					else if (foundOne) curr_ptr = (c == '1' ? curr_ptr->getRightChild() : curr_ptr->getLeftChild());
					else ;
				}

				MinHeapNode<T>* newNode = new MinHeapNode<T>(curr_ptr,v);
				if (lastDigit == '1') curr_ptr->RightChild = newNode;
				else curr_ptr->LeftChild = newNode;

				MinHeapNode<T>* child = newNode;
				MinHeapNode<T>* parent = curr_ptr;

				while(child != this->root){

					if (child->getValue() < parent->value){

						T temp = child->getValue();
						child->value = parent->value;
						parent->value = temp;

						child = parent;
						parent = parent->getParent();

					}

					else break;

				}

				return 1;
			}

		}
}
