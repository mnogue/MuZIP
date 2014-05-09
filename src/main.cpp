
#include <iostream>

#include "gui/Gui.h"
#include "io/IO.h"
#include "data/Image.h"
#include "data/Block.h"
#include "algorithms/Compression.h"
#include "algorithms/Decompression.h"

using namespace std;

// INIT STATIC VARIABLES: ------------------------------------------------------

int    Block::P     = 10;
int    Block::Q     = 10;
double Block::Alpha = 1.0;

string IO::fileName   = " ";
int    IO::bitCounter = 0;
unsigned char IO::singleByte = ' ';

// COMPRESSION: ----------------------------------------------------------------

void Compress()
{
    Image image;
    Compression cmp;
    
    IO::InputCompression(image);
    
    cmp.CompressImage(image);
    
    IO::OutputCompression(cmp.ReferenceToGHT(), cmp.ReferenceToHuffman(), image);
}

// DECOMPRESSION: --------------------------------------------------------------

void Decompress()
{
    Image image;
    Decompression cmp;
    
    IO::InputDecompression(cmp.ReferenceToGHT(), cmp.ReferenceToHuffman(), image);
    
    cmp.DecompressImage(image);
    
    IO::OutputDecompression(image);
}

// MAIN FUNCTION: --------------------------------------------------------------

int main()
{
    int cmd = GUI::InitMuZIP();
    
    switch (cmd)
    {
        case 0 : Compress();   break;
        case 1 : Decompress(); break;
    }
}