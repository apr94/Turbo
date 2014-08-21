#include <iostream>

using namespace std;


namespace Turbo{


	template<typename T>
		class PriorityQueue;

	template<typename T>

		class PriorityQueueNode{

			friend class PriorityQueue<T>;

			public:
			PriorityQueueNode(PriorityQueueNode<T>* parent, T val);
			~PriorityQueueNode();
			PriorityQueueNode<T>* getRightChild();
			PriorityQueueNode<T>* getLeftChild();
			PriorityQueueNode<T>* getParent();
			T getValue();

			private:
			PriorityQueueNode<T>* LeftChild;
			PriorityQueueNode<T>* RightChild;
			PriorityQueueNode<T>* parent;
			T value;

		};

	template<typename T>
		PriorityQueueNode<T>::PriorityQueueNode(PriorityQueueNode<T>* parent, T val): LeftChild(nullptr), RightChild(nullptr){
			this->parent = parent;
			this->value = val;
		}

	template<typename T>
		PriorityQueueNode<T>::~PriorityQueueNode(){
			delete LeftChild;
			delete RightChild;
		}

	template<typename T>
		PriorityQueueNode<T>* PriorityQueueNode<T>::getRightChild(){
			return this->RightChild;
		}

	template<typename T>
		PriorityQueueNode<T>* PriorityQueueNode<T>::getLeftChild(){
			return this->LeftChild;
		}

	template<typename T>
		PriorityQueueNode<T>* PriorityQueueNode<T>::getParent(){
			return this->parent;
		}

	template<typename T>
		T PriorityQueueNode<T>::getValue(){
			return this->value;
		}	

	template<typename T>

		class PriorityQueue{

			typedef int (*compFuncType)(T, T);

			public:

			PriorityQueue(compFuncType compFunc = &PriorityQueue<T>::defaultComparator);
			~PriorityQueue();
			T delete_min();
			PriorityQueueNode<T>* getRoot();
			static int defaultComparator(T o1, T o2);
			int insert(T v);
			int getSize();

			private:

			int size;
			int (*compare)(T o1, T o2);
			PriorityQueueNode<T>* root;

		};

	template<typename T>
		PriorityQueue<T>::PriorityQueue(compFuncType compFunc):size(0), root(nullptr){
			this->compare = compFunc;
		}

	template<typename T>
		PriorityQueue<T>::~PriorityQueue(){
			delete root;
		}

	template<typename T>
		PriorityQueueNode<T>* PriorityQueue<T>::getRoot(){
			return this->root;
		}

	template<typename T>
		int PriorityQueue<T>::defaultComparator(T o1, T o2){
			return o1 > o2 ? 1 : o1 < o2 ? -1 : 0;
		}

	template<typename T>
		int PriorityQueue<T>::getSize(){
			return this->size;
		}

	template<typename T>

		int PriorityQueue<T>::insert(T v){

			if (this->size == 0){
				PriorityQueueNode<T>* mhn = new PriorityQueueNode<T>(nullptr, v);
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
				PriorityQueueNode<T>* curr_ptr = this->root;

				for (char c: binary){

					if (c == '1' and !foundOne) foundOne = true;
					else if (foundOne) curr_ptr = (c == '1' ? curr_ptr->getRightChild() : curr_ptr->getLeftChild());
					else ;
				}

				PriorityQueueNode<T>* newNode = new PriorityQueueNode<T>(curr_ptr,v);
				if (lastDigit == '1') curr_ptr->RightChild = newNode;
				else curr_ptr->LeftChild = newNode;

				PriorityQueueNode<T>* child = newNode;
				PriorityQueueNode<T>* parent = curr_ptr;

				while(child != this->root){

					if (this->compare(child->getValue(),parent->value) == -1){

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
