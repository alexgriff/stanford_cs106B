/*************************************************************
 * File: pqueue-vector.cpp
 *
 * Implementation file for the VectorPriorityQueue
 * class.
 * This is my own work.
 */
 
#include "pqueue-vector.h"
#include "error.h"

/* Constructor */
VectorPriorityQueue::VectorPriorityQueue() {
    /* EMPTY */
}

/* Destructor */
VectorPriorityQueue::~VectorPriorityQueue() {
        /* EMPTY */
}



/* Implementation Notes:
 * ---------------------
 * Basically can use the features of the vector class.
 * Have to loop through the length of vector to find 
 * and store the index of the minimum element.
 * O(N) in best (and worst) case.
 */

int VectorPriorityQueue::size() {
	return vec.size();
}

bool VectorPriorityQueue::isEmpty() {
	return vec.isEmpty();
}

void VectorPriorityQueue::enqueue(string value) {
	vec.add(value);
}

string VectorPriorityQueue::peek() {
    string min;
    
    if (vec.isEmpty()) error("Queue is empty");
    
    else {
        int low = 0;
        for (int i = 0; i < vec.size(); i++) {
            if (vec[i] < vec[low])
                low = i;
        }
        min = vec[low];
    }
	
    return min;
}

string VectorPriorityQueue::dequeueMin() {
    string min;
    
    if (vec.isEmpty()) error("Queue is empty");
    
    else {
        int low = 0;
        for (int i = 0; i < vec.size(); i++) {
            if (vec[i] < vec[low])
                low = i;
        }
        min = vec[low];
        vec.remove(low);
    }
	
    return min;
}

