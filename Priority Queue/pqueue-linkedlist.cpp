/*************************************************************
 * File: pqueue-linkedlist.cpp
 *
 * Implementation file for the LinkedListPriorityQueue
 * class.
 */
 
#include "pqueue-linkedlist.h"
#include "error.h"

LinkedListPriorityQueue::LinkedListPriorityQueue() {
	head = NULL;
	length = 0;
}

LinkedListPriorityQueue::~LinkedListPriorityQueue() {
	if(isEmpty()) return;

	Cell* temp;

	for(int i = 0; i < length; i++){
		temp = head;
		head = head->next;
		delete temp;
	}
	length = 0;
}

int LinkedListPriorityQueue::size() {
	
	return length;
}

bool LinkedListPriorityQueue::isEmpty() {
	
	return (size() == 0);
}

void LinkedListPriorityQueue::enqueue(string value) {
	//create new cell and value of cell will be inpute value
	Cell* newCell = new Cell;
	newCell->value = value;

	if(isEmpty()){ //when elements aren't in queue
		newCell->next = NULL;
		head = newCell;
		length++;
		return;
	}

	int index = findIndex(value);
	Cell* temp = head;

	int count = 0;
	while(count < index){
		count++;
		if(count == index) break;
		if(temp->next != NULL) temp = temp->next;
	}

	if(count == 0){ //add value as first element
		newCell->next = head;
		head = newCell;
	}else if(count == index){ //add element as last element
		if(temp->next == NULL){//if we have 1 elements in queue
			newCell->next = NULL;
		}else{ //if we have one more elements in queue
			newCell->next = temp->next;
		}

		temp->next = newCell;
	}else{ //for others case
		newCell->next = temp;
		temp = newCell;
	}
	
	length++;
}

string LinkedListPriorityQueue::peek() {
	if(isEmpty()) {
		error("Queue is empty");
	}

	return head->value;
}

string LinkedListPriorityQueue::dequeueMin() {
	string result = peek();
	Cell* temp = head;
	head = head->next;
	length--;
	delete temp;

	return result;
}



//private function implementation

 //sub function of enqueue, which find index where new element will add
int LinkedListPriorityQueue::findIndex(string newVal){
	int result = 0;
	Cell* temp = head;

	while(newVal > temp->value){
		result++;
		if(temp->next == NULL) break;
		temp = temp->next;		
	}
	
	return result;
}
