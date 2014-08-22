#include <iostream>
#include <queue>
#include <stdlib.h>
#include "Turbo/priority_queue.hpp"
#include <ctime>


int compareFunc(float& a, float& b){
	return a > b ? -1 : a < b ? 1 : 0;
}

int main(){

	Turbo::priority_queue<float> pq;

	//priority_queue<float> pq;
	
	clock_t begin = clock();
	for(int i = 3432; i < 100000; i++){
		pq.push(float(i));
	}
	clock_t end = clock();
	double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;

	std::cout << "Time: " << elapsed_secs << "\n";
//	std::cout << "Top: " << pq.top() << "\n";
/*	queue<PriorityQueueNode<float>* > q;
	q.push(pq.root());

	while(!q.empty()){

		PriorityQueueNode<float>* pqn = q.front();
		q.pop();
		cout << pqn->value() << endl;
		if (pqn->left_child() != nullptr)
		q.push(pqn->left_child());
		
		if (pqn->right_child() != nullptr)
		q.push(pqn->right_child());

	}
*/	
	return 0;
}
