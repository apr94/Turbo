#ifndef TURBO_PRIORITYQUEUE_HPP
#define TURBO_PRIORITYQUEUE_HPP

namespace Turbo{

	template<typename T>
		class priority_queue;

	template<typename T>
		class priority_queue_node{

			friend class priority_queue<T>;

			public:
			priority_queue_node(priority_queue_node<T>* parent, T val);
			~priority_queue_node();
			priority_queue_node<T>* right_child();
			priority_queue_node<T>* left_child();
			priority_queue_node<T>* parent();
			T value();

			private:
			priority_queue_node<T>* m_LeftChild;
			priority_queue_node<T>* m_RightChild;
			priority_queue_node<T>* m_parent;
			T m_value;

		};

	template<typename T>
		priority_queue_node<T>::priority_queue_node(priority_queue_node<T>* parent, T val): m_value(val){
			this->m_parent = parent;
			this->m_LeftChild = nullptr;
			this->m_RightChild = nullptr;
		}

	template<typename T>
		priority_queue_node<T>::~priority_queue_node(){
			delete m_LeftChild;
			delete m_RightChild;
		}

	template<typename T>
		priority_queue_node<T>* priority_queue_node<T>::right_child(){
			return this->m_RightChild;
		}

	template<typename T>
		priority_queue_node<T>* priority_queue_node<T>::left_child(){
			return this->m_LeftChild;
		}

	template<typename T>
		priority_queue_node<T>* priority_queue_node<T>::parent(){
			return this->m_parent;
		}

	template<typename T>
		T priority_queue_node<T>::value(){
			return this->m_value;
		}	

	template<typename T>

		class priority_queue{

			typedef int (*compFuncType)(T, T);
			typedef int size_type;

			public:

			priority_queue(compFuncType compFunc = &priority_queue<T>::defaultComparator);
			~priority_queue();
			
			priority_queue_node<T>* root() const;
			static int defaultComparator(T o1, T o2);
			
			bool empty() const;
			size_type size() const;
			T top() const;
			void push(T v);
			void pop();
			
			private:

			int m_size;
			int (*compare)(T o1, T o2);
			priority_queue_node<T>* m_root;

		};

	template<typename T>
		priority_queue<T>::priority_queue(compFuncType compFunc):m_size(0), m_root(nullptr){
			this->compare = compFunc;
		}

	template<typename T>
		priority_queue<T>::~priority_queue(){
			delete m_root;
		}

	template<typename T>
		priority_queue_node<T>* priority_queue<T>::root() const{
			return this->m_root;
		}

	template<typename T>
		int priority_queue<T>::defaultComparator(T o1, T o2){
			return o1 > o2 ? 1 : o1 < o2 ? -1 : 0;
		}

	template<typename T>
		bool priority_queue<T>::empty() const{
			return (this->m_size == 0);
		}

	template<typename T>
		typename priority_queue<T>::size_type priority_queue<T>::size() const{
			return this->m_size;
		}

	template<typename T>
		T priority_queue<T>::top() const{ 
			return this->root()->value();
		}

	template<typename T>

		void priority_queue<T>::push(T v){

			if (this->m_size == 0){
				priority_queue_node<T>* mhn = new priority_queue_node<T>(nullptr, v);
				this->m_root = mhn;
				this->m_size++;
			}
			else{
				int newsize = ++this->m_size;

				std::string bigbinary;
				std::string binary;
				int count = 0;

				while (count < 31){

					bigbinary += newsize < 0 ? '1' : '0';
					newsize = newsize << 1;
					count++;

				}

				bool foundOne = false;
				
				for (char c: bigbinary){
					if (c == '1' && !foundOne) foundOne = true;
					else if (foundOne) binary += c;
					else;
				}


				char lastDigit = newsize < 0 ? '1' : '0';

				priority_queue_node<T>* curr_ptr = this->m_root;

				for (char c: binary){
					curr_ptr = (c == '1' ? curr_ptr->right_child() : curr_ptr->left_child());
				}

				priority_queue_node<T>* newNode = new priority_queue_node<T>(curr_ptr,v);
				if (lastDigit == '1') curr_ptr->m_RightChild = newNode;
				else curr_ptr->m_LeftChild = newNode;
				
				priority_queue_node<T>* child = newNode;
				priority_queue_node<T>* parent = curr_ptr;

				while(child != this->m_root){

					if (this->compare(child->value(),parent->value()) == -1){

						T temp = child->value();
						child->m_value = parent->m_value;
						parent->m_value = temp;

						child = parent;
						parent = parent->parent();
					}
					else break;
				}
			}
		}

	template <typename T>
		void priority_queue<T>::pop(){



		}
}

#endif
