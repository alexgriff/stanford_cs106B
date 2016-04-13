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


bool playGame(Lexicon &lex);


int main() {
    Lexicon lexicon(FILENAME);
    
    cout << "Word Ladder.  Enter two words of equal length \nThis program will trace the jumps necessary \nto change one word into another one letter at a time.\n[hit enter to quit]" << endl;

    while(playGame(lexicon));
    
    cout << endl << "Thanks for playing." << endl;
    
    return 0;
}




void printVector(Vector<string> vect) {
    cout << endl;
    int last = vect.size()-1;
    for (int i = 0; i < vect.size(); i ++) {
        if (i != last) cout << vect[i] << "  -->  ";
        else cout << vect[i] << endl;
    }
}





Vector <string> oneHopWords(Lexicon &lex, string word) {
    Vector<string> list;
    string orig = word;
    for (int i= 0; i < word.length(); i++) {
        word = orig;
        for (char tryCh = 'a'; tryCh <= 'z'; tryCh++) {
            word[i] = tryCh;
            if (lex.contains(word)) list.add(word);
        }
    }
    return list;
}




void buildLadder(Lexicon &lex, string startWord, string endWord) {
    Lexicon usedWords;
    Queue<Vector<string> > queue;
    Vector<string> start(1,startWord), ladder, copy;
    
    usedWords.add(startWord);
    queue.enqueue(start);
    
    while (!queue.isEmpty()) {
        ladder = queue.dequeue();
        string last = ladder[ladder.size()-1];
        if (last == endWord) {
            
            printVector(ladder);
            
            return;
        }
        foreach(string word in oneHopWords(lex, last)) {
            if (!usedWords.contains(word)) {
                usedWords.add(word);
                copy = ladder;
                copy.add(word);
                queue.enqueue(copy);
            }
        }
    }
    if (queue.isEmpty()) cout << "There is no ladder between these words." << endl << endl;
}




bool playGame(Lexicon &lex) {
    string start, end;
    while (true) {
        cout << endl << "Enter a starting word: ";
        start = getLine();
        if (start == "") break;
        if (!lex.contains(start)) cout << "Not a standard english word." << endl;
        else break;
    }
    
    while (true) {
        if (start == "") break;
        cout << "Enter a destination word: ";
        end = getLine();
        if (end == "") break;
        if (!lex.contains(end)) cout << "Not a standard english word." << endl;
        else if (end.length() != start.length()) cout << "Must enter two words of the same length." << endl;
        else break;
    }
    if (start == "" || end == "") return false;
   
    
    buildLadder(lex, start, end);
    
    
    return true;
}




