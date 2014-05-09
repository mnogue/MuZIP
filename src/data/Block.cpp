
#include "Block.h"

// CONSTRUCTOR: ----------------------------------------------------------------

Block::Block()
{
    this->block = vector< vector<Pixel> >(Block::P, vector<Pixel>(Block::Q));
}

// GETTERS: --------------------------------------------------------------------

Pixel Block::GetBlockPixel(int i, int j)
{
    return this->block[i][j];
}

double Block::GetDistanceTo(Block& block)
{
    double rDistance = 0.0;
    double gDistance = 0.0;
    double bDistance = 0.0;
    
    for (int i = 0; i < Block::P; ++i)
    {
        for (int j = 0; j < Block::Q; ++j)
        {
            rDistance += std::abs((double)(this->block[i][j].GetR() - block.GetBlockPixel(i,j).GetR()));
            gDistance += std::abs((double)(this->block[i][j].GetG() - block.GetBlockPixel(i,j).GetG()));
            bDistance += std::abs((double)(this->block[i][j].GetB() - block.GetBlockPixel(i,j).GetB()));
        }
    }
    
    /*cout << "rDist = " << rDistance << " / P=" << Block::P << " / Q=" << Block::Q << endl;
    cout << "gDist = " << gDistance << " / P=" << Block::P << " / Q=" << Block::Q << endl;
    cout << "bDist = " << bDistance << " / P=" << Block::P << " / Q=" << Block::Q << endl;*/
    
    rDistance /= (Block::P * Block::Q);
    gDistance /= (Block::P * Block::Q);
    bDistance /= (Block::P * Block::Q);
    
    //cout << "Distance is: " << (rDistance + gDistance + bDistance) / 3 << endl;
    
    return (rDistance + gDistance + bDistance) / 3;
}

// SETTERS: --------------------------------------------------------------------

void Block::SetBlockPixel(int i, int j, Pixel pixel)
{
    this->block[i][j] = pixel;
}
