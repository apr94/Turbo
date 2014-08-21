#include <iostream>
#include <queue>
#include <stdlib.h>
#include "Turbo/PriorityQueue.hpp"

using namespace std;
using namespace Turbo;

int compareFunc(float a, float b){
	return a > b ? -1 : a < b ? 1 : 0;
}

int main(){

	Turbo::PriorityQueue<float> pq(compareFunc);

	for(int i = 0; i < 7; i++){
		pq.insert(float(i));
	}
	
	queue<PriorityQueueNode<float>* > q;
	q.push(pq.getRoot());

	while(!q.empty()){

		PriorityQueueNode<float>* pqn = q.front();
		q.pop();
		cout << pqn->getValue() << endl;
		if (pqn->getLeftChild() != nullptr)
		q.push(pqn->getLeftChild());
		
		if (pqn->getRightChild() != nullptr)
		q.push(pqn->getRightChild());

	}
	
	return 0;
}
