/*
 * File: RandomSubsets.cpp
 * ----------------------
 * Name: [Alex]
 * This file is the starter project for the Random Subsets problem
 * on Assignment #3.
 */

#include <iostream>
#include "set.h"
#include "random.h"
#include "console.h"
using namespace std;

/* Given a set of integers, returns a uniformly-random subset of that
 * set.
 */
Set<int> randomSubsetOf(Set<int>& s);

int main() {
    
    Set<int> set;
    set += 1,2,3,4,5;
 
        
    cout << randomSubsetOf(set) << endl;
    
    return 0;
}


Set<int> randomSubsetOf(Set<int>& s) {
   
    /* Base case: The only subset of the empty set is the empty set. */
    if (s.isEmpty()) return s;
    
    /* Extract the first element from the set. */
    int n = s.first();
    
    /* Choose a random subset of what remains.  To do this, we will remove
     * the first element, compute the random subset, then put the element
     * back in.
     */
    s -= n;
    Set<int> result = randomSubsetOf(s);
    s += n;
    
    /* Randomly choose whether to add the element back in. */
    if (randomChance(0.5)) return result + n;
    return result;

}
