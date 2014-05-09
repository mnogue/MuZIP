
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <stdlib.h>

#include "Pixel.h"
#include "Block.h"

using namespace std;

#ifndef IMAGE_H
#define IMAGE_H

class Image
{
    private:
    
    // PRIVATE VARIABLES: ------------------------------------------------------
    
    vector< vector<Pixel> > image;
    
    // PRIVATE FUNCTIONS: ------------------------------------------------------
    
    public: 
        
        // CONSTRUCTOR: --------------------------------------------------------
        
        Image();
        
        // GETTERS: ------------------------------------------------------------
        
        int GetImageSizeI();
        int GetImageSizeJ();
        
        Pixel GetImagePixel(int i, int j);
        Block GetImageBlock(int si, int sj);
        
        // SETTERS: ------------------------------------------------------------
        
        void SetImageSize(int m, int n);
        void SetImagePixel(int i, int j, Pixel pixel);
};

#endif