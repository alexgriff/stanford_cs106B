/*
 * File: NumericConversions.cpp
 * ---------------------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file is the starter project for the Numeric Conversions problem.
 * [TODO: rewrite the documentation]
 */

#include <iostream>
#include <string>
#include "console.h"
#include "simpio.h"

using namespace std;

/* Function prototypes */

string intToString(int n);
int stringToInt(string str);
char singleIntToChar(int n);

/* Main program */

int main() {
    cout << "hi" << endl;
    return 0;
}


char singleIntToChar(int n)
{
    char ch = char(n + 48);
    return ch;
}

string intToString(int n)
{
    if (n == 0) {
        return "0";
    } else if (n < 0) {
        return "-" + intToString(abs(n));
    } else if (n < 10) {
        return string() + singleIntToChar(n);
    } else {
        return ((string() + singleIntToChar(n % 10)) + intToString(n/10));
    }
}


