/*
 * File: WordLadder.cpp
 * ----------------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file is the starter project for the Word Ladder problem.
 * [TODO: rewrite the documentation]
 */

#include <iostream>
#include "simpio.h"
#include "lexicon.h"
#include "queue.h"
#include "vector.h"
#include "console.h"
using namespace std;

const string FILENAME = "EnglishWords.dat";


Lexicon lexicon;
Vector<string> ladder;
Queue <string> queue;


Lexicon initDatabase(string filename);
string enterStartWord();
string enterFinalWord(string start);
void findOneAwayWord(string word);
void findLadder(string dest);

int main() {
    lexicon = initDatabase(FILENAME);
    string start = enterStartWord();
    //string final = enterFinalWord(start);
    findOneAwayWord(start);
    //findLadder(final);
    return 0;
}


Lexicon initDatabase(string file) {
    Lexicon lex (file);
    return lex;
}



string enterStartWord() {
    string start;
    while (true) {
        cout << "Enter a starting word: ";
        string start = getLine();
        if (!lexicon.contains(start)) cout << "Not a standard english word." << endl;
        else break;
    }
    return start;
}




string enterFinalWord(string start) {
    string final;
    while (true) {
        cout << "Enter a destination word of same length as starting word: ";
        string temp = getLine();
        if (!lexicon.contains(temp)) cout << "Not a standard english word." << endl;
        else if (temp.length() != start.length())
            cout << "Destination word must be of the same length as starting word." << endl;
        else {
            final = temp;
            break;
        }
    }
    return final;
}




void findOneAwayWord(string word){
    string temp = word;
    for(int i = 0; i < word.length(); i++){
        temp = word;
        for(char tryCh = 'a'; tryCh < 'z'; tryCh++){
            temp[i] = tryCh;
            if (lexicon.contains(temp) && temp != word) queue.enqueue(temp);
        }
    }
}


void findLadder(string dest) {
    while (!queue.isEmpty()) {
        string word = queue.dequeue();
        cout << word << endl;
    }
}






