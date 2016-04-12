/*************************************************************
 * File: pqueue-heap.cpp
 *
 * Implementation file for the HeapPriorityQueue
 * class.
 */
 
#include "pqueue-heap.h"
#include "error.h"

/* Constant */
static const int INITIAL_CAPACITY = 10;

/* Constructor
 * -----------
 * Allocates a Dynamic Array with some starting capacity.
 * Set count to zero.
 */
HeapPriorityQueue::HeapPriorityQueue() {
	capacity = INITIAL_CAPACITY;
    heap = new string[capacity];
    count = 0;
}

/* Destructor
 * ----------
 * Deletes "heap" array.
 */
HeapPriorityQueue::~HeapPriorityQueue() {
	delete[] heap;
}



/* Implementation Notes: size(), isEmpty(), peek()
 * -----------------------------------------------
 * Straight-forward. Use "count" variable since c array has no way to check size.
 */
int HeapPriorityQueue::size() const {
    return count;
}

bool HeapPriorityQueue::isEmpty() const {
    return count == 0;
}

string HeapPriorityQueue::peek() const {
    if(isEmpty()) error("Queue is empty.");
	return (heap[0]);
}

/* Implementation Notes: enqueue(value)
 * ------------------------------------
 * Controls the allocated capacity of the array. Appends
 * a value and conforms with the rules of a binary heap:
 * Each node of the heap can have 0, 1, or 2 "children"
 * nodes. Each row of nodes must fill up completely before
 * advancing to the next row. A child node cannot be of a 
 * lower value than it's parent.  The lowest node should
 * therefore be at the top. Order within a row is arbitrary.
 */

void HeapPriorityQueue::enqueue(string value) {
    /* When necessary, call expandCapacity to double 
     * allocated length of heap/array */
    if (count == capacity) expandCapacity();
    
    /* Increment count and append to end of array. This ensures 
     * that each row of nodes will be filled in order*/
    heap[count++] = value;
    
    
    /* Use the index of newly-appended value to find it's parent node. */
    int childI = count - 1;
    int parentI = getParentI(childI);
    string parent = heap[parentI];
    
    
    /* If it needs to be swapped with it's parent to meet the
     * criteria of descending children, call bubbleUp */
    if (value < parent) {
        bubbleUp(childI, parentI);
        }
}



/* Implementation Notes: dequeueMin()
 * ----------------------------------
 * Because dequeue-ing off the top of the heap would leave
 * two seperate heaps the first step is to swap the very top
 * value with the very last value and always dequeue from the end.
 * Since now the order is not intact, bubble your way down from the top
 * making the first call using the first two children at indexes 1 and 2.
 */
string HeapPriorityQueue::dequeueMin() {
    if(isEmpty()) error("Queue is empty.");

    swap(0, count-1);
    /* Decrement count, select the last value */
    string min = heap[--count];
    
    /* bubbleDown is a recursive function. The first call here takes
     * the indexes of the top parent node and the first two children. */
    bubbleDown(0, 1, 2);
    
    return min;
}


/* Implementation Notes: expandCapacity()
 * --------------------------------------
 * Called upon to allocate more space for the array/heap.
 * Copies old heap. Doubles the allocated capacity.
 * Copies contents of old heap into the larger heap.
 * Deletes old heap.
 */
void HeapPriorityQueue::expandCapacity() {
    string *oldHeap = heap;
    capacity *= 2;
    heap = new string[capacity];
    for (int i = 0; i < count; i++) {
        heap[i] = oldHeap[i];
    }
    delete[] oldHeap;
}



/* Implementation Notes: swap()
 * ----------------------------
 * Standard swap two variables code.
 */
void HeapPriorityQueue::swap(int index1, int index2) {
    string temp = heap[index1];
    heap[index1] = heap[index2];
    heap[index2] = temp;
}


/* Implementation Notes: getParentI(childI)
 * ----------------------------------------
 * Returns the INDEX of the parent node and takes an INDEX of a child node.
 * A little bit tricky because the indexes of the array/heap begin with 0,
 * while the relationship of parent to child (node at position N will have 
 * a parent node at position N/2 (rounded down)) holds for numbered nodes 
 * starting with 1.
 */
int HeapPriorityQueue::getParentI(int childI) {
    int parentI = ((childI + 1)/2) - 1;
    if (parentI < 0) return 0;
    return parentI;
}


/* Implementation Notes: bubbleUp(childI, parentI)
 * -----------------------------------------------
 * A recursive function. First swaps a child node up to it's
 * parent's position so a descending relationship will hold.
 * If the operation needs to be performed again because the 
 * next parent is still greater than the child node, bubbleUp
 * gets called again.
 */
void HeapPriorityQueue::bubbleUp(int childI, int parentI) {
    
    swap(childI, parentI);
    
    int nextParentI = getParentI(parentI);
    
    if (heap[parentI] < heap[nextParentI]) {
        bubbleUp(parentI, nextParentI);
    }

    
}



/* Implementation Notes: bubbleDown(parentI, child1I, child2I)
 * -----------------------------------------------------------
 * A recursive function that will always get called starting from
 * the very top of the heap.  Swaps a node down with it's lowest-value
 * child node until the proper position is found.
 */
void HeapPriorityQueue::bubbleDown(int parentI, int child1I, int child2I){

    /* Base Case: There are no children, their indexes are out of scope. 
     * Note that only the first child needs to be explicitly checked for.
     * If there is no first child there cannot be a second child. */
    if(child1I >= count) {
        return;
    }
    
    /* lowChildI will store the index of the lesser child, once we figure out
     * which child that is... */
    int lowChildI;
   
    /* If there is no second child, but the first child exists, that's the 
     * low child. Note that no symmetrical test is necessary. */
    if (child2I >= count && child1I < count) {
        lowChildI = child1I;
    /* Else, find the lowest. */
    } else {
        if (heap[child1I] < heap[child2I]) lowChildI = child1I;
        else lowChildI = child2I;
    }
    
    /* Before you swap make sure that nodes are in fact out of order. 
     * Occasionally when getting down to only a few elements in the 
     * heap this test is necessary */
    if (heap[parentI] > heap[lowChildI]) {
        swap(parentI, lowChildI);
    }
    
    /* The low child is the new parent, find it's children and recursively 
     * call bubbleDown. */
    child1I = ((lowChildI + 1) * 2) - 1;
    child2I = (child1I + 1);
    
    bubbleDown(lowChildI, child1I, child2I);
    
}





