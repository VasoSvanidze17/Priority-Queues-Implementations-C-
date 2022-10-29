/*************************************************************
 * File: pqueue-extra.cpp
 *
 * Implementation file for the ExtraPriorityQueue class.  You
 * do not need to implement this class, but we're happy to
 * give you extra credit if you do!
 */
 
#include "pqueue-extra.h"
#include "error.h"

ExtraPriorityQueue::ExtraPriorityQueue() 
{
	head = NULL;
	nodesNum = 0;
}

ExtraPriorityQueue::~ExtraPriorityQueue() 
{
	// TODO: Fill this in!
}

int ExtraPriorityQueue::size() 
{
	// TODO: Fill this in!
	
	return nodesNum;
}

bool ExtraPriorityQueue::isEmpty() 
{
	// TODO: Fill this in!
	
	return size() == 0;
}

void ExtraPriorityQueue::enqueue(string value) 
{
	// TODO: Fill this in!
	Node* node = new Node;
	node->child = NULL;
	node->data = value;
	node->degree = 0;
	node->parent = NULL;
	node->sibling = NULL;

	if (isEmpty())
	{
		nodesNum++;
		head = node;
		return;
	}

	nodesNum++;
	node->sibling = head->sibling;
	head->sibling = node;
	
	if (head->degree == 0)
	{
		if (head->data < head->sibling->data)
		{
			head->child = node;
			node->parent = head;
			head->sibling = node->sibling;
			node->sibling = NULL;
			head->degree = 1;
		}
		else
		{
			node->child = head;
			head->parent = node;
			head->sibling = NULL;
			head = node;
			node->degree = 1;
		}
	}
	else
	{
		head->sibling = node->sibling;
		node->sibling = head;
		head = node;
	}

	merge();
}

string ExtraPriorityQueue::peek() 
{
	// TODO: Fill this in!
	if (isEmpty() == true)
	{
		error("Queue is empty");
		return "";
	}
	
	Node* lexicoMinNode = NULL;
	lexicoMinValue(lexicoMinNode);
	string lexicoMin = lexicoMinNode->data;

	return lexicoMin;
}

string ExtraPriorityQueue::dequeueMin() 
{
	// TODO: Fill this in!
	if (isEmpty() == true)
	{
		error("Queue is empty");
		return "";
	}

	Node* lexicoMinNode = NULL;
	lexicoMinValue(lexicoMinNode);
	string lexicoMin = lexicoMinNode->data;

	if (lexicoMinNode->child != NULL)
	{	
		Node* heapHead = NULL;
		reverseHeap(lexicoMinNode->child, heapHead);
		lexicoMinNode->sibling = NULL;

		Node* temp = head;
		Node* temp1 = heapHead;
		if (heapHead->parent == head)
		{
			head->degree = 0;
		}

		Node* node = NULL;
		while (true)
		{
			if (temp1->degree <= temp->degree)
			{
				node = temp1->sibling;
				temp1->sibling = temp;
				head = temp1;
				if (node == NULL) break;
				temp1 = node;
			}

			if (temp->sibling == NULL) break;
			temp = temp->sibling;
		}
		
		if (temp->sibling == NULL && node != NULL)
		{
			while (true)
			{
				temp->sibling = node;
				temp = temp->sibling;
				node = node->sibling;
				if (node == NULL) break;
			}
		}
	}

	head = lexicoMinNode->sibling;
	delete lexicoMinNode;
	nodesNum--;
	merge();
	return lexicoMin;
}

void ExtraPriorityQueue::merge()
{
	Node* node = NULL;
	isMergeable(node, head);

	if (node == NULL)
	{
		return;
	}

	if (node == head)
	{
		if (node->degree == node->sibling->degree)
		{
			if (node->data < node->sibling->data)
			{
				node->sibling->parent = node;
				Node* newChild = node->sibling;

				if (node->sibling->sibling != NULL)
				{
					node->sibling = node->sibling->sibling;
				}
				else
				{
					node->sibling = NULL;
				}

				newChild->sibling = node->child;
				node->child = newChild;
				node->degree += (1 + node->child->degree);
			}
			else
			{
				node->parent = node->sibling;
				node->sibling->degree += (1 + node->degree);
				head = node->sibling;
				node->sibling = head->child;
				head->child = node;
			}
		}
		else
		{
			if (node->sibling->data < node->sibling->sibling->data)
			{
				node->sibling->sibling->parent = node->sibling;
				Node* newChild = node->sibling->sibling;
				node->sibling->degree += (1 + node->sibling->sibling->degree);
				
				if (node->sibling->sibling->sibling != NULL) 
				{
					node->sibling->sibling = node->sibling->sibling->sibling;
				}
				else
				{
					node->sibling->sibling = NULL;
				}

				newChild->sibling = node->sibling->child;
				node->sibling->child = newChild;
			}
			else
			{
				node->sibling->parent = node->sibling->sibling;
				Node* newChild = node->sibling;
				node->sibling->sibling->child = newChild;
				node->sibling->sibling->degree += (1 + node->sibling->degree);
				node->sibling = node->sibling->sibling;
				newChild->sibling = node->sibling->child;
			}
		}

		return;
	}

	if (node->sibling->data < node->sibling->sibling->data)
	{
		node->sibling->sibling->parent = node->sibling;
		Node* newCild = node->sibling->sibling;
		node->sibling->degree += (1 + node->sibling->sibling->degree);

		if (node->sibling->sibling->sibling != NULL)
		{
			node->sibling->sibling = node->sibling->sibling->sibling;
		}
		else
		{
			node->sibling->sibling = NULL;
		}

		newCild->sibling = node->sibling->child;
		node->sibling->child = newCild;
	}
	else
	{
		node->sibling->parent = node->sibling->sibling;
		Node* newChild = node->sibling;
		node->sibling->sibling->degree += (1 + node->sibling->degree);

		node->sibling->sibling->child = newChild;
		node->sibling = newChild->sibling;
		newChild->sibling = node->sibling->child;
	}

	merge();
}

void ExtraPriorityQueue::isMergeable(Node*& emptyNode, Node* currNode)
{
	emptyNode = NULL;

	if (currNode->sibling == NULL) 
	{ 
		return;
	}
	else if (currNode->sibling->sibling == NULL)
	{
		if (currNode == head && currNode->degree == currNode->sibling->degree)
		{
			emptyNode = currNode;
		}
		return;
	}

	isMergeable(emptyNode, currNode->sibling);
	if (emptyNode != NULL) return;
	if (currNode->sibling->degree == currNode->sibling->sibling->degree)
	{
		emptyNode = currNode;
	}
	else if (currNode == head && emptyNode == NULL && 
		currNode->degree == currNode->sibling->degree)	
	{
		emptyNode = currNode;
	}
	
	/*
	if (head->degree == head->sibling->degree)
	{
		emptyNode = temp;
		return;
	}

	while (true)
	{
		if (temp->sibling->sibling == NULL) break;

		if (temp->sibling->degree == temp->sibling->sibling->degree)
		{	
			emptyNode = temp;
			return;
		}

		temp = temp->sibling;
	}
	*/
}


void ExtraPriorityQueue::lexicoMinValue(Node*& emptyNode)
{
	string lexicoMin = head->data;
	Node* lexicoMinNode = head;
	Node* temp = head;

	while (true)
	{
		if (lexicoMin > temp->data)
		{
			lexicoMin = temp->data;
			lexicoMinNode = temp;
		}

		temp = temp->sibling;
		if (temp == NULL) break;
	}

	emptyNode = lexicoMinNode;
}

void ExtraPriorityQueue::reverseHeap(Node* leftLastSiblingNode, Node*& heapHead)
{
	if (leftLastSiblingNode->sibling == NULL)
	{
		heapHead = leftLastSiblingNode;
		return;
	}

	Node* node = leftLastSiblingNode->sibling;
	reverseHeap(node, heapHead);
	node->sibling = leftLastSiblingNode;
}