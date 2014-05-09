
#include <iostream>
#include <vector>
#include <cmath>

#include "Pixel.h"

using namespace std;

#ifndef BLOCK_H
#define BLOCK_H

class Block
{
    private:
        
        // PRIVATE VARIABLES: --------------------------------------------------
        
        vector< vector<Pixel> > block;
        
        // PRVATE FUNCTIONS: ---------------------------------------------------
    
    public:
        
        // PUBLIC VARIABLES: ---------------------------------------------------
        
        static int P;
        static int Q;
        
        static double Alpha;
        
        // CONSTRUCTOR: --------------------------------------------------------
        
        Block();
        
        // GETTERS: ------------------------------------------------------------
        
        Pixel GetBlockPixel(int i, int j);
        
        double GetDistanceTo(Block& block);
        
        // SETTERS: ------------------------------------------------------------
        
        void SetBlockPixel(int i, int j, Pixel pixel);
};

#endif