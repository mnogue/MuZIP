
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

#include "../data/Image.h"
#include "../data/Pixel.h"
#include "../data/Block.h"
#include "../data/GHT.h"
#include "../data/Huffman.h"

using namespace std;

#ifndef IO_H
#define IO_H

class IO
{
    private:
    
    // PRIVATE VARIABLES: ------------------------------------------------------
    
    static string fileName;
    
    static unsigned char singleByte;
    static int bitCounter;    
    
    // PRIVATE FUNCTIONS: ------------------------------------------------------
    
    static void WriteBit(int bit, ofstream& file);
    
    static int ReadBit(ifstream& file);
    
    public:
        
        // INFORMATION: --------------------------------------------------------
        
        static void OutputProgress(string text, int percent, bool end = false);
        
        // INPUT FUNCTIONS: ----------------------------------------------------
        
        static void InputCompression(Image& image);
        static void InputDecompression(GHT& ght, Huffman& huffman, Image& image);
        
        // OUPUT: --------------------------------------------------------------
        
        static void OutputCompression(GHT& ght, Huffman& huffman, Image& image);
        static void OutputDecompression(Image& image);
};

#endif
