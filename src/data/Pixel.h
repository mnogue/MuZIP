
#include <iostream>

using namespace std;

#ifndef PIXEL_H
#define PIXEL_H

class Pixel
{
    private:
    
    // PRIVATE VARIABLES: ------------------------------------------------------
    
    int r;
    int g;
    int b;
    
    public:
    
    // CONSTRUCTOR: ------------------------------------------------------------
    
    Pixel();
    
    Pixel(int r, int g, int b);
    
    // GETTERS: ----------------------------------------------------------------
    
    int GetR();
    int GetG();
    int GetB();
    
    // SETTERS: ----------------------------------------------------------------
    
    void SetR(int r);
    void SetG(int g);
    void SetB(int b);
};

#endif