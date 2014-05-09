
#include <iostream>
#include <vector>

#include "../data/Image.h"
#include "../data/Pixel.h"
#include "../data/Block.h"
#include "../data/GHT.h"
#include "../data/Huffman.h"
#include "../io/IO.h"

using namespace std;

#ifndef COMPRESSION_H
#define COMPRESSION_H

class Compression
{
    private:
        
    // PRIVATE VARIABLES: ------------------------------------------------------
    
    GHT ght;
    
    Huffman huffman;
    
    // PRIVATE FUNCTIONS: ------------------------------------------------------
    
    int GetSimilarBlockInC(Block& block);
        
    public:
        
        // GETTERS: ------------------------------------------------------------
        
        GHT& ReferenceToGHT();
        
        Huffman& ReferenceToHuffman();
        
        // COMPRESSION FUNCTION: -----------------------------------------------
        
        void CompressImage(Image& image);
};

#endif