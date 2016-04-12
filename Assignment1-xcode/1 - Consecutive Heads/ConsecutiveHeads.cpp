/*
 * File: ConsecutiveHeads.cpp
 * --------------------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file is the starter project for the Consecutive Heads problem.
 */

#include <iostream>
#include "console.h"
#include "random.h"
#include "vector.h"

using namespace std;

void FlipCoin();

int main() {
    cout << "Flip a Coin:" << endl;
    FlipCoin();
    return 0;
}

void FlipCoin()
{
    int flipcount = 0;
    Vector<int> headcount;
    while (headcount.size() != 3) {
        bool flip = randomChance(0.5);
        if (flip == true) {
            cout << "heads" << endl;
            headcount.add(1);
        } else {
            cout << "tails" << endl;
            headcount.clear();
        }
        flipcount++;
    }
    cout << "It took " << flipcount << " flips to get 3 consecutive heads" << endl;
}
