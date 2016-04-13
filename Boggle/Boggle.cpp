/*
 * File: Boggle.cpp
 * ----------------
 * This is my own work.
 */
 
#include <iostream>
#include "gboggle.h"
#include "grid.h"
#include "gwindow.h"
#include "lexicon.h"
#include "random.h"
#include "simpio.h"
using namespace std;

/* Constants */

const int BOGGLE_WINDOW_WIDTH = 650;
const int BOGGLE_WINDOW_HEIGHT = 350;
const int STANDARD = 4;
const int BIG = 5;

const string STANDARD_CUBES[16]  = {
    "AAEEGN", "ABBJOO", "ACHOPS", "AFFKPS",
    "AOOTTW", "CIMOTU", "DEILRX", "DELRVY",
    "DISTTY", "EEGHNW", "EEINSU", "EHRTVW",
    "EIOSST", "ELRTTY", "HIMNQU", "HLNNRZ"
};
 
const string BIG_BOGGLE_CUBES[25]  = {
    "AAAFRS", "AAEEEE", "AAFIRS", "ADENNN", "AEEEEM",
    "AEEGMU", "AEGMNN", "AFIRSY", "BJKQXZ", "CCNSTW",
    "CEIILT", "CEILPT", "CEIPST", "DDLNOR", "DDHNOT",
    "DHHLOR", "DHLNOR", "EIIITT", "EMOTTT", "ENSSSU",
    "FIPRSY", "GORRVW", "HIPRRY", "NOOTUW", "OOOTTU"
};

struct cubeT {
    int row;
    int col;
    char face;
};

/* Function prototypes */

void welcome();
void giveInstructions();
void playBoggle();
int promptSize();
Vector<cubeT> configureBoard(int size);
Vector<cubeT> randomArrangeCubes(int size);
Vector<cubeT> manualEnterCubes(int size);
Vector<cubeT> randomLabelCubes(Vector<string> &vec, int size);


/* Main program */

int main() {
    GWindow gw(BOGGLE_WINDOW_WIDTH, BOGGLE_WINDOW_HEIGHT);
    initGBoggle(gw);
    welcome();
    giveInstructions();
    playBoggle();
    
    return 0;
}

/*
 * Function: welcome
 * Usage: welcome();
 * -----------------
 * Print out a cheery welcome message.
 */

void welcome() {
    cout << "Welcome!  You're about to play an intense game ";
    cout << "of mind-numbing Boggle.  The good news is that ";
    cout << "you might improve your vocabulary a bit.  The ";
    cout << "bad news is that you're probably going to lose ";
    cout << "miserably to this little dictionary-toting hunk ";
    cout << "of silicon.  If only YOU had a gig of RAM..." << endl << endl;
}

/*
 * Function: giveInstructions
 * Usage: giveInstructions();
 * --------------------------
 * Print out the instructions for the user.
 */

void giveInstructions() {
    cout << endl;
    cout << "The boggle board is a grid onto which I ";
    cout << "I will randomly distribute cubes. These ";
    cout << "6-sided cubes have letters rather than ";
    cout << "numbers on the faces, creating a grid of ";
    cout << "letters on which you try to form words. ";
    cout << "You go first, entering all the words you can ";
    cout << "find that are formed by tracing adjoining ";
    cout << "letters. Two letters adjoin if they are next ";
    cout << "to each other horizontally, vertically, or ";
    cout << "diagonally. A letter can only be used once ";
    cout << "in each word. Words must be at least four ";
    cout << "letters long and can be counted only once. ";
    cout << "You score points based on word length: a ";
    cout << "4-letter word is worth 1 point, 5-letters ";
    cout << "earn 2 points, and so on. After your puny ";
    cout << "brain is exhausted, I, the supercomputer, ";
    cout << "will find all the remaining words and double ";
    cout << "or triple your paltry score." << endl << endl;
    cout << "Hit return when you're ready...";
    getLine();
}



void playBoggle() {
    int size = promptSize();
    Vector<cubeT> board = configureBoard(size);
}



int promptSize() {
    cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n" << endl;
    cout << "You have the choice to play" << endl;
    cout << "Standard Boggle (4 x 4 grid)" << endl;
    cout << "\tor" << endl;
    cout<< "Big Boggle (5 x 5 grid)" << endl << endl;
    
    cout << "Would you like to play Big Boggle? [Y/N]: ";
    while (true) {
        string input = getLine();
        if (tolower(input[0] == 'y')) return BIG;
        if (tolower(input[0] == 'n')) return STANDARD;
        cout << "please enter yes or no" << endl;
    }
    
}


Vector<cubeT> configureBoard(int size) {
    drawBoard(size, size);
    cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n" << endl;
    cout << "You have the option to manually input the board configuration. ";
    cout << "This is mainly for testing the program." << endl << endl;
    
    cout<< "Would you prefer to take your chances with a random \"roll\"? [Y/N]: ";
    while (true) {
        string input = getLine();
        if (tolower(input[0] == 'y')) {
            return randomArrangeCubes(size);
        }
        if (tolower(input[0] == 'n')) {
            return manualEnterCubes(size);
        }
        cout << "please enter yes or no" << endl;
    }
}


Vector<cubeT> randomArrangeCubes(int size) {
    Vector <string> vec;
    
    /* Assures random arrangement of cubes by shuffling */
    if (size == STANDARD) {
        for (string cube : STANDARD_CUBES)
            vec += cube;
        for (int i = 0; i < vec.size(); i++) {
            int r = randomInteger(i, vec.size()-1);
            string temp = vec[i];
            vec[i] = vec[r];
            vec[r] = temp;
        }
    }
    
    else if (size == BIG) {
        for (string cube : BIG_BOGGLE_CUBES)
            vec += cube;
        for (int i = 0; i < vec.size(); i++) {
            int r = randomInteger(i, vec.size()-1);
            string temp = vec[i];
            vec[i] = vec[r];
            vec[r] = temp;
        }
    }
    
    /* Calls on randomLabelCubes to pick a "face" and display */
    Vector<cubeT> board = randomLabelCubes(vec, size);
    return board;
}




Vector<cubeT> randomLabelCubes(Vector<string> &vec, int size) {
    Vector<cubeT> board;
    
    
    return board;
}








