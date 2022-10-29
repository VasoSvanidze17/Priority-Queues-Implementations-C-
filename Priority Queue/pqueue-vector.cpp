/*************************************************************
 * File: pqueue-vector.cpp
 *
 * Implementation file for the VectorPriorityQueue
 * class.
 */
 
#include "pqueue-vector.h"
#include "error.h"

VectorPriorityQueue::VectorPriorityQueue() {
	v = new Vector<string>;
}

VectorPriorityQueue::~VectorPriorityQueue() {
	delete v;
}

int VectorPriorityQueue::size() {
	
	return v->size();
}

bool VectorPriorityQueue::isEmpty() {
	
	return v->isEmpty();
}

void VectorPriorityQueue::enqueue(string value) {
	v->add(value);
}

string VectorPriorityQueue::peek() {
	string result = v->get(findMinElement(v, 0, v->size() - 1));

	return result;
}

string VectorPriorityQueue::dequeueMin() {
	int index = findMinElement(v, 0, v->size() - 1);
	string result = v->get(index);
	v->remove(index);

	return result;
}



//private functions implementation

//this function returns index of priority word
int VectorPriorityQueue::findMinElement(Vector<string>* v, int low, int high){
	if(low >= high) return low;

	int partitionPoint;

	while(low < high){
		partitionPoint = partion(v, low, high);
		high = partitionPoint - 1;
	}

	return low;
}

//this fun returns index of pivot element after swap index
int VectorPriorityQueue::partion(Vector<string>* v, int low, int high){
	string pivot = v->get(low);
	int left = low + 1;
	int right = high;

	while(left < right){
		while(left < right && pivot <= v->get(right)) right--;

		while(left < right && pivot > v->get(left)) left++;

		if(left < right) swap(v, left, right);
	}
	
	if(pivot <= v->get(right)) return low;

	swap(v, low, right);
	return right;
}

//this fun swap place two elements
void VectorPriorityQueue::swap(Vector<string>* v, int index1, int index2){
	string temp = v->get(index1);
	v->set(index1, v->get(index2));
	v->set(index2, temp);
}


