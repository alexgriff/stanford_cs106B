/**********************************************
 * File: pqueue-heap.h
 *
 * A priority queue class backed by a binary
 * heap.
 * This file is my own work.
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
	int size() const;
	
	/* Returns whether or not the priority queue is empty. */
	bool isEmpty() const;
	
	/* Enqueues a new string into the priority queue. */
	void enqueue(string value);
	
	/* Returns, but does not remove, the lexicographically first string in the
	 * priority queue.
	 */
	string peek() const;
	
	/* Returns and removes the lexicographically first string in the
	 * priority queue.
	 */
	string dequeueMin();

private:
    
    /* Instance variables */
     
    string *heap;          /* Dynamic array will function as a binary heap */
    int capacity;          /* Allocated size of array */
    int count;             /* Current count of strings in array */
    
    /* Private method prototypes */
    
    void expandCapacity();
    void swap(int index1, int index2);
    int getParentI(int childI);
    void bubbleUp(int childI, int parentI);
    void bubbleDown(int parentI, int child1I, int child2I);
	
};

#endif
