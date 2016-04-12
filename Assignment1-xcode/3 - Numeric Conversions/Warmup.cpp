/*
 * PROBELEM WITH FILE, STORED HERE IDK Y IS FUCKED UP ;?
 * SHOULD BE .....
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

const int ASCII_VALUE_OF_0 = 48;


/* Main program */

int main() {
    string s = intToString(getInteger("#?: "));
    cout <<  s + " as a string" << endl;
    while (true) {
        int n  = stringToInt(getLine("s?: "));
        cout << n << string(" as int") << endl;
    }
    return 0;
}



char singleIntToChar(int n)
{
    char ch = char(n + ASCII_VALUE_OF_0);
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
        return intToString(n/10) + (string() + singleIntToChar(n % 10));
    }
}


int singleCharToInt(char ch)
{
    return (int) ch - ASCII_VALUE_OF_0;
}


int stringToInt (string s)
{
    int len = s.length();
    if (len == 1) {
        return singleCharToInt(s[0]);
    } else if (s[0] == '-') {
        return -1 * stringToInt(s.substr(1));
    } else {
        return 10 * stringToInt(s.substr(0, len-1)) + singleCharToInt(s[len-1]) ;
    }
}





