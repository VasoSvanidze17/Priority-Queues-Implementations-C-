/*************************************************************
 * File: pqueue-doublylinkedlist.cpp
 *
 * Implementation file for the DoublyLinkedListPriorityQueue
 * class.
 */
 
#include "pqueue-doublylinkedlist.h"
#include "error.h"

DoublyLinkedListPriorityQueue::DoublyLinkedListPriorityQueue() {
	head = NULL;
	length = 0;
}

DoublyLinkedListPriorityQueue::~DoublyLinkedListPriorityQueue() {
	if(isEmpty()) return;

	Cell* temp;

	for(int i = 0; i < length; i++){
		temp = head;
		head = head->next;
		delete temp;
	}

	length = 0;
}

int DoublyLinkedListPriorityQueue::size() {
	
	return length;
}

bool DoublyLinkedListPriorityQueue::isEmpty() {
	
	return size() == 0;
}

void DoublyLinkedListPriorityQueue::enqueue(string value) {
	Cell* newCell = new Cell;
	newCell->value = value;

	if(isEmpty()){
		newCell->next = NULL;
		newCell->back = NULL;
		head = newCell;
	}else{
		newCell->next = head;
		newCell->back = NULL;
		head->back = newCell;
		head = newCell;
	}

	length++;
}

string DoublyLinkedListPriorityQueue::peek() {
	if(isEmpty()) error("Queue is empty");

	findMinElement();
	return currMinCell->value;
}

string DoublyLinkedListPriorityQueue::dequeueMin() {
	string result = peek();
	Cell* temp = currMinCell;
	currMinCell = NULL;

	if(temp->back != NULL && temp->next != NULL){
		temp->back->next = temp->next;
		temp->next->back = temp->back;
	}else if(temp->back == NULL && temp->next == NULL){ //this case happens when we have one element in queue
		head = NULL;
		//nothing
	} else if(temp->back == NULL){ //this case happens when we dequeue first elemet from queue
		head = temp->next;
		head->back = NULL;
	}else if(temp->next == NULL){ //this case happens when we dequeue last elemet from queue
		temp->back->next = NULL;
	}
	
	length--;
	delete temp;

	return result;
}


//private functions implementation
void DoublyLinkedListPriorityQueue::findMinElement(){
	Cell* temp = head;
	currMinCell = temp;
	
	while(true){
		if(currMinCell->value > temp->value) currMinCell = temp;

		if(temp->next == NULL) break;

		temp = temp->next;
	}
}