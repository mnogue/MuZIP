
#include "Compression.h"

// GETTERS: --------------------------------------------------------------------

GHT& Compression::ReferenceToGHT()
{
    return this->ght;
}

Huffman& Compression::ReferenceToHuffman()
{
    return this->huffman;
}

// COMPRESSION FUNCTION: -------------------------------------------------------

void Compression::CompressImage(Image& image)
{
    IO::OutputProgress("Compressing", 0);
    for (int i = 0; i < image.GetImageSizeI(); i += Block::P)
    {
        for (int j = 0; j < image.GetImageSizeJ(); j += Block::Q)
        {
            Block block = image.GetImageBlock(i,j);
            
            int similarIndex = this->GetSimilarBlockInC(block);
            
            if (similarIndex > -1)
            {
                this->ght.FoundSimilarBlock(similarIndex);
            }
            else
            {
                this->ght.NotFoundSimilarBlock(block);
            }
        }
        
        int percent = (int)((double)i/(double)image.GetImageSizeI()*100.0);
        IO::OutputProgress("Compressing", percent);
    }
    
    IO::OutputProgress("Compressing", 100, true);
    
    this->huffman.GenerateCodesFromIndex(this->ght);
}

// PRIVATE FUNCTIONS: ----------------------------------------------------------

int Compression::GetSimilarBlockInC(Block& block)
{
    int neighborIndex = -1;
    double distance = this->ght.GetNearestNeighbor(block, neighborIndex);
    
    return ((double)(distance) < Block::Alpha ? neighborIndex : -1);
}