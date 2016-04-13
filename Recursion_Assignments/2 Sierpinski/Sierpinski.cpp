/*
 * File: Sierpinski.cpp
 * --------------------------
 * This file is the starter project for the Sierpinski problem
 * on Assignment #3.
 * [TODO: extend the documentation]
 */

#include <iostream>
#include "gwindow.h"
using namespace std;

const double EDGE_LENGTH = 600;
const double BUFFER = 30;
const int DELAY = 5;

/* For drawing to have correct result, there is one instance
 * where drawTriangle is called that must return a GPoint.
 * From that point the top points of subsequent triangles are derived.
 * In the other cases the value of that point is not needed. In those
 * cases, the value is stored in instance var "unused", for consistency.
 */
GPoint unused;

GPoint drawTriangle(GWindow& gw, GPoint& top, double edge, int order) {
    
    GPoint p1,p2,p3;
    p1 = gw.drawPolarLine(top, edge, -120);
    pause(DELAY);
    
    p2 = gw.drawPolarLine(p1, edge, 0);
    pause(DELAY);
    
    p3 = gw.drawPolarLine(p2, edge, 120);
    pause(DELAY);

    if (order != 0) {
        GPoint leftP = drawTriangle(gw, p3, edge/2, order-1);
        GPoint rightP (leftP.getX() + edge/2, leftP.getY());
        
        unused = drawTriangle(gw, leftP, edge/2, order-1);
        unused = drawTriangle(gw, rightP, edge/2, order-1);
    }
    
    return p1;
}


int main() {
    GWindow gw(800,600);
    GPoint top (gw.getWidth()/2, BUFFER);
    int order = 8;
    
    unused = drawTriangle(gw, top, EDGE_LENGTH, order);
    
    return 0;
}





