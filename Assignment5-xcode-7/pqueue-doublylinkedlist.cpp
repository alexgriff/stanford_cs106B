/*************************************************************
 * File: pqueue-doublylinkedlist.cpp
 *
 * Implementation file for the DoublyLinkedListPriorityQueue
 * class.
 * This is my own work.
 */
 
#include "pqueue-doublylinkedlist.h"
#include "error.h"

/* Constructor
 * -----------
 * Initialize list to NULL and count to 0. You've got a list of nothing.
 */

DoublyLinkedListPriorityQueue::DoublyLinkedListPriorityQueue() {
	list = NULL;
    count = 0;
}




/* Destructor
 * ----------
 * Standard code to delete a linked-list. "list" points to end of
 * linked list so cycle backwards through list with ->prev.
 */
DoublyLinkedListPriorityQueue::~DoublyLinkedListPriorityQueue() {
	while (list != NULL) {
        Cell *next = list->prev;
        delete list;
        list = next;
    }
}




/* Function: size
 * --------------
 * Global variable "count" tracks size, no iteration through list is necessary.
 */
int DoublyLinkedListPriorityQueue::size() {
	return count;
}



/* Function: isEmpty
 * -----------------
 * If there is no list Cell, there is no list.
 */
bool DoublyLinkedListPriorityQueue::isEmpty() {
	return list == NULL;
}



/* Function: enqueue
 * -----------------
 * Allocates memory for a new Cell in the list and 
 * appends to end of list
 */
void DoublyLinkedListPriorityQueue::enqueue(string value) {
	/* Allocate memory for a new Cell, set it's value and increment count */
    Cell *newCell = new Cell;
    newCell->value = value;
    count ++;
    
    /* If the new Cell is the only cell in the list */
    if (list == NULL) {
        list = newCell;
        newCell->prev = NULL;
        newCell->next = NULL;
    }
    
    /* Else, append to end of list. */
    else {
        /* prev points to list, next to NULL. list's next points to new. */
        newCell->prev = list;
        newCell->next = NULL;
        
        list->next = newCell;
        
        /* Update list to point to new end of list. */
        list = newCell;
    }
}



/* Function: peek
 * --------------
 * Moves through list and finds minimum Cell. Expensive O(N).
 */
string DoublyLinkedListPriorityQueue::peek() {
	if(isEmpty()) error("Queue is empty.");
    
    /* Init a "minimum" value to the value of last Cell.
     * Use to test against. */
    string min = list->value;
    
    /* p is the pointer used to move backwards through list.
     * Must be a separate variable so "list" retains value as pointer
     * to end of list. */
    Cell *p = list;
    
    while(p != NULL) {
        if (p->value < min) {
            min = p->value;
        }
        p = p->prev;
    }
    
	return min;
}




/* Function: dequeueMin
 * --------------------
 * Moves through list and finds minimum Cell. Removes and 
 * deletes the min Cell and links the Cell before it to the
 * Cell after it & vice-versa.  Much of the conditional checking
 * in this function is just for special cases where min Cell
 * is either the first or last Cell in the linked list.
 * Expensive O(N).
 */
string DoublyLinkedListPriorityQueue::dequeueMin() {
    if(isEmpty()) error("Queue is empty.");
	
    /* Init a "minimum" value to the value of last Cell. 
     * Use to test against. */
    Cell *minCell = list;
    string min = minCell->value;
    
    /* p is the pointer used to move backwards through list.
     * Must be a separate variable so "list" retains value as pointer
     * to end of list. */
    Cell *p = list;

    
    while(p != NULL) {
        if (p->value < min) {
            min = p->value;
            minCell = p;
        }
        p = p->prev;
    }
    
    /* prevC points to Cell before minCell */
    Cell *prevC;
    if (minCell->prev != NULL) {
        prevC = minCell->prev;
    } else {
        prevC = NULL;
    }
    
    /* nextC points to Cell after minCell */
    Cell *nextC;
    if (minCell->next != NULL) {
        nextC = minCell->next;
    } else {
        nextC = NULL;
        /* Special case: If the Cell to be dequeued is the last Cell in list,
         * "list" should update to point to prevC before minCell gets deleted. */
        list = prevC;
    }
    
    /* "Cut" minCell out of list and patch up by pointing prevC to nextC... */
    if (prevC != NULL) {
        prevC->next = nextC;
    }
    /* ... and nextC back to prevC. */
    if (nextC != NULL) {
        nextC->prev = prevC;
    }
    

    /* Go ahead and delete and decrement */
    delete minCell;
    count --;
    
	return min;
}

