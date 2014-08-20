#include <iostream>
#include <queue>
#include <stdlib.h>
#include "Turbo/MinHeap.hpp"

using namespace std;
using namespace Turbo;

int main(){

	Turbo::MinHeap<float> mh;

	for(int i = 0; i < 7; i++){
		mh.insert(float(rand()%100));
	}
	
	queue<MinHeapNode<float>* > q;
	q.push(mh.getRoot());

	while(!q.empty()){

		MinHeapNode<float>* mhn = q.front();
		q.pop();
		cout << mhn->getValue() << endl;
		if (mhn->getLeftChild() != nullptr)
		q.push(mhn->getLeftChild());
		
		if (mhn->getRightChild() != nullptr)
		q.push(mhn->getRightChild());

	}

	
	return 0;

}
