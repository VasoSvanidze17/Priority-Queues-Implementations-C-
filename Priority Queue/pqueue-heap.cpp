/*************************************************************
 * File: pqueue-heap.cpp
 *
 * Implementation file for the HeapPriorityQueue
 * class.
 */
 
#include "pqueue-heap.h"
#include "error.h"

HeapPriorityQueue::HeapPriorityQueue() {
	length = 0;
	elemsN = 0;
	arr = new string[length];
}

HeapPriorityQueue::~HeapPriorityQueue() {

	delete[] arr;
}

int HeapPriorityQueue::size() {
	
	return elemsN;
}

bool HeapPriorityQueue::isEmpty() {
	
	return size() == 0;
}

void HeapPriorityQueue::enqueue(string value) {
	if(isEmpty()){ //if number of elements equals zero
		addFristElement(value);
		return;
	} 
	
	//When the array is full, the program will call the grow() function and the length will increase by 2 times
	if(elemsN == length) grow(); 
	
	//before adding new elemet, index of last elemet is (elemsN - 1) so that index of new elemet must be elemsN
	arr[elemsN] = value; //add new element
	elemsN++;

	if(value < arr[(elemsN - 1)/ 2]){ //buble up if child element is less then parent 
		bubbleUp();
	}
}

string HeapPriorityQueue::peek() {
	if(isEmpty()) error("Queue is empty");
	
	return arr[0];
}

string HeapPriorityQueue::dequeueMin() {
	string result = peek();
	swap(0, elemsN - 1); //swap place last and firs elemets
	elemsN--;
	if(elemsN > 1) bubbleDown();
	

	return result;
}



//private functions implementations

void HeapPriorityQueue::addFristElement(string value){
	length++;
	arr = new string[length];
	arr[0] = value;
	elemsN++;
}

void HeapPriorityQueue::grow(){
	length = length * 2;
	string* newArr = new string[length];
	
	copyElements(newArr);
	delete[] arr;
	arr = newArr;
}

void HeapPriorityQueue::copyElements(string* newArr){
	for(int i = 0; i < elemsN; i++){
		newArr[i] = arr[i];
	} 
}

void HeapPriorityQueue::swap(int parentIndex, int childIndex){
	string temp = arr[parentIndex];
	arr[parentIndex] = arr[childIndex];
	arr[childIndex] = temp;
}

void HeapPriorityQueue::bubbleUp(){
	string newValue = arr[elemsN - 1];
	int valueIndex = elemsN - 1;
	int parentIndex;

	if(valueIndex % 2 == 0){
		parentIndex = (valueIndex / 2) - 1;
	}else{
		parentIndex = (valueIndex / 2);
	}

	while(newValue < arr[parentIndex]){ 
		swap(parentIndex, valueIndex);
		valueIndex = parentIndex;

		if(valueIndex == 0) break;
		
		if(valueIndex % 2 == 0){
			parentIndex = (valueIndex / 2) - 1;
		}else{
			parentIndex = (valueIndex / 2);
		}
	}
}

void HeapPriorityQueue::bubbleDown(){
	string temp = arr[0];
	int childIndex;
	int tempIndex = 0;

	if(arr[1] < arr[2] || 2 > elemsN - 1){
		childIndex = 1;
	}else{
		childIndex = 2;
	}

	while(temp > arr[childIndex]){
		swap(tempIndex, childIndex);
		tempIndex = childIndex;

		if((childIndex * 2) + 1 > elemsN - 1) break;
		if((childIndex * 2) + 2 > elemsN - 1){ 
			childIndex = (childIndex * 2) + 1;
		}else {
			if(arr[(childIndex * 2) + 1] < arr[(childIndex * 2) + 2]){
				childIndex = (childIndex * 2) + 1;
			}else{
				childIndex = (childIndex * 2) + 2;
			}
		}
	}
}