
#include "Decompression.h"

// GETTERS: --------------------------------------------------------------------

GHT& Decompression::ReferenceToGHT()
{
    return this->ght;
}

Huffman& Decompression::ReferenceToHuffman()
{
    return this->huffman;
}

// DECOMPRESSION FUNCTIONS: ----------------------------------------------------

void Decompression::DecompressImage(Image& image)
{
    this->huffman.GenerateIndexFromCodes(this->ght, image);
    
    cout << endl;
    IO::OutputProgress("Decompressing", 100);
    cout << endl;
}

