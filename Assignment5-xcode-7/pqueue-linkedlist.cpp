/*************************************************************
 * File: pqueue-linkedlist.cpp
 *
 * Implementation file for the LinkedListPriorityQueue
 * class.
 * This is my own work.
 */

#include "pqueue-linkedlist.h"
#include "error.h"


/* Constructor
 * -----------
 * Initialize head to NULL and count to 0. You've got a list of nothing.
 */
LinkedListPriorityQueue::LinkedListPriorityQueue() {
	head = NULL;
    count = 0;
}




/* Destructor
 * ----------
 * Standard code to delete a linked-list. 
 */
LinkedListPriorityQueue::~LinkedListPriorityQueue() {
	while (head != NULL) {
        Cell *next = head->next;
        delete head;
        head = next;
    }
}




/* Function: size
 * --------------
 * Global variable "count" tracks size, no iteration through list is necessary.
 */
int LinkedListPriorityQueue::size() {
	return count;
}




/* Function: isEmpty
 * -----------------
 * If there is no head cell, there is no list.
 */
bool LinkedListPriorityQueue::isEmpty() {
	return head == NULL;
}




/* Function: enqueue
 * -----------------
 * Allocates memory for a new Cell in the list and does the
 * sorting to ensure each string is at the correct
 * positon.
 */
void LinkedListPriorityQueue::enqueue(string value) {
    /* Create a new Cell, set it's value and increment the count. */
    Cell *newCell = new Cell;
    newCell->value = value;
    count++;
    
    
    /* *** There are several possibilities: ***
     * ----------------------------------------
     * 1 -> The new Cell is the only element in the list. 
     * It can become the new head and point to NULL. */
    
    if (head == NULL) {
        head = newCell;
        newCell->next = NULL;
    }

    /* 2 -> The new Cell is the minimum element in the list.
     * It can become the new head and point to the old head. 
     * 3 -> The new Cell is equal to the head.
     * Go ahead and make it the new head. */
    
    else if (newCell->value <= head->value) {
        newCell->next = head;
        head = newCell;
    }
    
    
    /* 4 -> The new Cell must be inserted somewhere in the middle of the list.
     * To find the correct position, set a pointer to your current position
     * in the list and a trailing pointer to the previously looked at position.
     * Advance each pointer until correct position is found. 
     * ^Insert: Previous points to new and new points to current. */
    
    else {
        Cell *currentPos = head;
        Cell *previousPos = NULL;
        
        while (newCell->value > currentPos->value) {
            previousPos = currentPos;
            currentPos = currentPos->next;
            /* If you have reached the end of the line... */
            if (currentPos == NULL) break;
        }
        
        previousPos->next = newCell;
        newCell->next = currentPos;
    
    /* Note, the above will also account for:
     * 5 -> The new cell is the last in the list i.e. points to NULL */
    
    }
	 
}




/* Function: dequeueMin
 * --------------------
 * Returns value at head and re-points head to next element.
 * Frees memory (by storing "old" head value in a temp variable
 * and deleting after no longer needed)and decrements count.
 */
string LinkedListPriorityQueue::dequeueMin() {
    if(isEmpty()) error("Queue is empty.");
	
    string min = head->value;
    Cell *temp = head;
    head = head->next;
    delete temp;
    count--;
    
	return min;
}




/* Function: peek
 * --------------
 * Take a peek at the head value.
 */
string LinkedListPriorityQueue::peek() {
    if(isEmpty()) error("Queue is empty.");
	
    return head->value;
}





