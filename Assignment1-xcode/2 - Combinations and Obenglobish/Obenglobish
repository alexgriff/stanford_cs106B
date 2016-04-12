/*
 * File: Obenglobish.cpp
 * ----------------------
 */

#include <iostream>
#include <string>
#include "console.h"
#include "simpio.h"
using namespace std;


string obenglobish(string word);

int main() {
    while (true) {
        string word = getLine("Enter a word: ");
        if (word == "") break;
        string trans = obenglobish(word);
        cout << word << " -> " << trans << endl;
    }
    return 0;
}

bool IsVowel(char ch) {
    if (ch == 'a') return true;
    if (ch == 'e') return true;
    if (ch == 'i') return true;
    if (ch == 'o') return true;
    if (ch == 'u') return true;
    return false;
    
}

bool EndsInE (string word, char ch) {
    int finalCh = word.length()-1;
    ch = word[finalCh];
    if (ch == 'e') return true;
    return false;
}



string obenglobish(string word) {
    string ob = "ob";
    for (int i = 0; i < word.length(); i ++) {
        if (i == 0 && IsVowel(word[i])) {
            word = word.insert(i, ob);
            i += ob.length();
        } else if (IsVowel(word[i]) && !IsVowel(word[i-1])) {
            word = word.insert(i, ob);
            i += ob.length();
            if (EndsInE(word, word[i])) break;
        }
    }
    return word;
}