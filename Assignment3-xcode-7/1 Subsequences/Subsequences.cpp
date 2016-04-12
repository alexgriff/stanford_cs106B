/*
 * File: Subsequences.cpp
 * ----------------------
 * Name: [Alex]
 * This file is the starter project for the Subsequences problem
 * on Assignment #3.
 */

#include <iostream>
#include <string>
#include "console.h"
using namespace std;

/* Given two strings, returns whether the second string is a
 * subsequence of the first string.
 */


/*Function Prototype */
bool isSubsequence(string text, string subsequence);


int main() {
    string text = "how does that lizard feel?";
    string sub = "hell";
    if (isSubsequence(text, sub))
        cout << "\"" << sub << "\" is a subsequence of \"" << text << "\"" << endl;
    else cout << "\"" << sub << "\" is NOT a subsequence of \"" << text << "\"" << endl;
    
    
    return 0;
}



bool isSubsequence(string text, string subsequence) {
    
    if (text == "")
        return subsequence == "";

    // if first letters match --> advance both words and check again
    if (text[0] == subsequence[0])
        return isSubsequence(text.substr(1), subsequence.substr(1));
    
    // if first letters dont match --> check next char in text, dont advance subsequence
    return isSubsequence(text.substr(1), subsequence);
}