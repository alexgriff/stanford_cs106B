/*
 * File: FleschKincaid.cpp
 * ----------------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file is the starter project for the Flesch-Kincaid problem.
 * [TODO: rewrite the documentation]
 */

#include <iostream>
#include <fstream>
#include <cctype>
#include "console.h"
#include "simpio.h"
#include "tokenscanner.h"
using namespace std;

void openFile(ifstream& in);
void readText(ifstream& in);

double numSentences;
double numWords;
double numSyllables;

const double C_ZERO = -15.59;
const double C_ONE = 0.39;
const double C_TWO = 11.8;

double FleschKinkaidFormula(double sentences, double words, double syllables);

int main() {
    ifstream in;
    double grade;
    openFile(in);
    readText(in);
    grade = FleschKinkaidFormula(numSentences, numWords, numSyllables);
    cout << "Grade: " << grade << endl;
    return 0;
}

void openFile(ifstream& in)
{
    while (true) {
        cout << "Enter a file name: ";
        string filename = getLine();
        in.open(filename.c_str());
        if (!in.fail()) break;
        cout << "Invalid filename" << endl;
        in.clear();
    }
}


bool isVowel(char ch)
{
    switch (ch) {
        case ('a') : case ('e') : case ('i') : case ('o') : case ('u') : case ('y') :
        case ('A') : case ('E') : case ('I') : case ('O') : case ('U') : case ('Y') : return true;
        default: return false;
    }
}

bool isSilentE(string word)
{
    char finalChar = tolower(word[word.length()-1]);
    char secondLastChar = tolower(word[word.length()-2]);
    char thirdLastChar = tolower(word[word.length()-3]);
    
    if (word.length() > 3) {
        if (finalChar == 'e') {
            if (secondLastChar == 'l') {
                if (!isVowel(thirdLastChar)) return false;
                return true;
            }
            return true;
        }
    } else if (word.length() > 1 && word.length() <= 3) {
        if (finalChar == 'e' && secondLastChar != 'h') {
            return true;
        }
    }
    return false;
}


int countSyllables(string word)
{
    int syllableCount = 0;
    for (int i = 0; i < word.length(); i++) {
        if (isVowel(word[i])) syllableCount++;
        if (i != 0) {
            if (isVowel(word[i]) && isVowel(word[i-1]))syllableCount--;
        }
    }
    if (isSilentE(word)) syllableCount --;
    if (syllableCount < 1) syllableCount = 1;
    return syllableCount;
}

void readText(ifstream& in)
{
    string text;
    int wordCount = 0;
    int sentenceCount = 0;
    int totalSyllCount = 0;
    int numSyll;
    while (getline(in, text)) {
        TokenScanner scanner(text);
        scanner.ignoreWhitespace();
        scanner.addWordCharacters("-");
        scanner.addWordCharacters("'");
        
        while (scanner.hasMoreTokens()) {
            string token = scanner.nextToken();
            if (isalpha(token[0])) {
                wordCount++;
                numSyll = countSyllables(token);
                totalSyllCount += numSyll;
                cout << "Token: [" << token << "] word; " <<  numSyll << " syllables" << endl;
            } else if (token[0] == '.' || token[0] == '?' || token[0] == '!') {
                sentenceCount++;
                cout << "Token: [" << token << "] end of sentence. "<< sentenceCount << " sentences." << endl;
            } else {
                cout << "Token: [" << token << "]" << endl;
            }
        }
    }
    numSentences = sentenceCount;
    numWords= wordCount;
    numSyllables = totalSyllCount;
    cout << "Sentences: " << numSentences << endl;
    cout << "Words: " << numWords << endl;
    cout << "Syllables: " << numSyllables << endl;
}



double FleschKinkaidFormula(double sentences, double words, double syllables)
{
    double grade = C_ZERO + (C_ONE * (words/sentences)) + (C_TWO *(syllables/words));
    return grade;
}



