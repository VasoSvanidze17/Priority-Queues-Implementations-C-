/**********************************************
 * File: pqueue-heap.h
 *
 * A priority queue class backed by a binary
 * heap.
 */
#ifndef PQueue_Heap_Included
#define PQueue_Heap_Included

#include <string>
using namespace std;

/* A class representing a priority queue backed by an
 * binary heap.
 */
class HeapPriorityQueue {
public:
	/* Constructs a new, empty priority queue backed by a binary heap. */
	HeapPriorityQueue();
	
	/* Cleans up all memory allocated by this priority queue. */
	~HeapPriorityQueue();
	
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
	string* arr; //pointer for array
	int length; //lenght of array
	int elemsN; //number of elements in array

	//functions
	void addFristElement(string value);
	void grow(); //this functions grow length of array when array is full
	void copyElements(string* newArr); //this function copy elements to new array
	void swap(int parentIndex, int childIndex); //if child elemet is less then parent elemet then program must swap place for this two elemets
	void bubbleUp();
	void bubbleDown();
};

#endif
