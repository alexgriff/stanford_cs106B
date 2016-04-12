/**********************************************
 * File: pqueue-extra.h
 *
 * A Priority Queue class backed by a Binomial Heap.
 */
#ifndef PQueue_Extra_Included
#define PQueue_Extra_Included

#include <string>
using namespace std;

/* A class representing a priority queue backed by a
 * Binomial Heap.
 */
class ExtraPriorityQueue {
public:
	/* Constructs a new, empty priority queue. */
	ExtraPriorityQueue();
	
	/* Cleans up all memory allocated by this priority queue. */
	~ExtraPriorityQueue();
	
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
    
    struct Node {
        string value;
        Node *parent;
        Node *child;
        Node * sibling;
    };
    
    int count;
    Node *root;
	
};

#endif
