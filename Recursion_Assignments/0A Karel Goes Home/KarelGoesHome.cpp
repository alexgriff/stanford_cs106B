/*
 * File: KarelGoesHome.cpp
 * ----------------------
 * Name: Alex
 * This file is the starter project for the Karel Goes Home
 * warmup problem for Assignment #3.
 * 
 */

#include <iostream>
#include "console.h"
using namespace std;

/* Given a street number and avenue number, which are 1-indexed,
 * returns the number of paths Karel can take back home that only
 * moves left or down.
 */
int numPathsHome(int street, int avenue);
    
    

int main() {
    cout << numPathsHome(2,3) << endl;
    return 0;
}
int numPathsHome(int street, int avenue) {
	/* Base case 1: If we're not on the map, there's no way back. */
	if (street < 1 || avenue < 1)
		return 0;
	/* Base case 2: If we're home, there's exactly one path back. */
	else if (street == 1 && avenue == 1)
		return 1;
	/* Recursive step: Take a step in each direction and sum up the
	 * number of paths.
	 */
	
    return numPathsHome(street - 1, avenue) + numPathsHome(street, avenue - 1);
}
