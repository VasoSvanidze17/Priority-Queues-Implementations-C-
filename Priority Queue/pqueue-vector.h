/**********************************************
 * File: pqueue-vector.h
 *
 * A priority queue class backed by an unsorted
 * vector.
 */
#ifndef PQueue_Vector_Included
#define PQueue_Vector_Included

#include <string>
#include "vector.h"
using namespace std;

/* A class representing a priority queue backed by an
 * unsorted Vector.
 */
class VectorPriorityQueue {
public:
	/* Constructs a new, empty priority queue backed by a vector. */
	VectorPriorityQueue();
	
	/* Cleans up all memory allocated by this priority queue. */
	~VectorPriorityQueue();
	
	/* Returns the number of elements in the priority queue. */
	int size();
	
	/* Returns whether or not the priority queue is empty. */
	bool isEmpty();
	
	/* Enqueues a new string into the priority queue. */
	void enqueue(string value);
	
	/* Returns, but does not remove, the lexicographically first string in the
	 * priority queue.
	 */
	string peek();
	
	/* Returns and removes the lexicographically first string in the
	 * priority queue.
	 */
	string dequeueMin();

private:
	//variables
	Vector<string>* v; //this variable is main data structure for queue

	//functions
	int findMinElement(Vector<string>* v, int low, int high); //this function returns index of min(priority) element
	int partion(Vector<string>* v, int low, int high); //this fun returns index of pivot element after swap index
	void swap(Vector<string>* v, int index1, int index2); //this fun swap place two elements
};

#endif
