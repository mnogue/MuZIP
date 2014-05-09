
#include <iostream>
#include <vector>

#include "../data/Image.h"
#include "../data/Pixel.h"
#include "../data/Block.h"
#include "../data/GHT.h"
#include "../data/Huffman.h"
#include "../io/IO.h"

using namespace std;

#ifndef DECOMPRESSION_H
#define DECOMPRESSION_H

class Decompression
{
    private:
        
    // PRIVATE VARIABLES: ------------------------------------------------------
    
    GHT ght;
    
    Huffman huffman;
        
    public:
        
        // GETTERS: ------------------------------------------------------------
        
        GHT& ReferenceToGHT();
        
        Huffman& ReferenceToHuffman();
        
        // DECOMPRESSION FUNCTION: ---------------------------------------------
        
        void DecompressImage(Image& image);
};

#endif