/*******************************************************
 * File: pqueue-linkedlist.h
 *
 * A priority queue class backed by a sorted, singly-linked
 * list.
 * This file is my own work.
 */
#ifndef PQueue_LinkedList_Included
#define PQueue_LinkedList_Included

#include <string>
using namespace std;

/* A class representing a priority queue backed by a sorted,
 * singly-linked list.
 */
class LinkedListPriorityQueue {
public:
	/* Constructs a new, empty priority queue backed by a sorted linked list. */
	LinkedListPriorityQueue();
	
	/* Cleans up all memory allocated by this priority queue. */
	~LinkedListPriorityQueue();
	
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
	/* Individual Cell of a Linked List */
    struct Cell {
		string value;
		Cell *next;
	};
	
    /* Instance Variables */
	Cell *head;
    int count;
    
};

#endif
