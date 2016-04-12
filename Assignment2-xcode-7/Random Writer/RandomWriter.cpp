/*
 * File: RandomWriter.cpp
 * ----------------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file is the starter project for the Random Writer problem.
 * [TODO: rewrite the documentation]
 */

#include "vector.h"
#include "map.h"
#include "console.h"
#include "simpio.h"
#include "random.h"
#include <iostream>
#include <fstream>

using namespace std;

const int GENERATED_TEXT_LENGTH = 2000;


void openFile(ifstream &inf);
void readText(ifstream &inf);
string initSeed();
void randomWriter(string seed);

int order;
Map< string, Vector<char> > seedMap;

int main() {
    while (true) {
        seedMap.clear();
        ifstream input;
        openFile(input);
        readText(input);
        string seed = initSeed();
        randomWriter(seed);
    }
    
    return 0;
}

void getOrder()
{
    while (true) {
        cout << "Enter Markov order of analysis [1-10]: ";
        order = getInteger();
        if (order < 1 || order > 10) cout << "Must enter order between 1 and 10" << endl;
        else break;
    }
    
    cout << "Processing Text...\n\n\n" << endl;
    
}


void openFile(ifstream& inf)
{
    while (true) {
        cout << "Enter file name: ";
        string filename = getLine();
        inf.open(filename.c_str());
        if (!inf.fail()) break;
        cout << "Invalid filename" << endl;
        inf.clear();
    }
    getOrder();
}




void createSeedMap(string &text)
{
    for (int i = 0; i < text.length() - order; i++) {
        string seed = text.substr(i, order);
        if (i + order < text.length()) {
            char nextCh = text[i + order];
            Vector <char> followedByCh;
            if (!seedMap.containsKey(seed)) {
                followedByCh.add(nextCh);
                seedMap.put(seed, followedByCh);
            } else {
                followedByCh = seedMap.get(seed);
                followedByCh.add(nextCh);
                seedMap.put(seed, followedByCh);
            }
        }
    }
}


void readText(ifstream &inf)
{
    string text;
    char ch;
    while (inf.get(ch)) {
        text += ch;
    }
    
    createSeedMap(text);
}




string initSeed()
{   
    Vector <string> possSeed;
    int max = 0;
    
    foreach(string key in seedMap) {
        int size = seedMap.get(key).size();
        if (size > max) {
            max = size;
            possSeed.clear();
            possSeed.add(key);
        } else if (size == max) possSeed.add(key);
    }
    int indexOfSeed = randomInteger(0, possSeed.size()-1);
    return possSeed[indexOfSeed];
}



void randomWriter(string seed)
{
    Vector<char> possibleCh;
    cout << seed; 
    for (int i = 0; i < GENERATED_TEXT_LENGTH; i++) {
        if (!seedMap.containsKey(seed)) break;
        possibleCh = seedMap.get(seed);
        int size = possibleCh.size();
        if (size == 0) break;
        int index = randomInteger(0, size-1);
        char nextCh = possibleCh[index]; 
        cout << nextCh;
        seed.erase(0,1); 
        seed += nextCh; 
    }
    cout << endl << endl;
    
}







