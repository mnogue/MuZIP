
#include "Image.h"

// CONSTRUCTOR: ----------------------------------------------------------------

Image::Image() { }

// GETTERS: --------------------------------------------------------------------

int Image::GetImageSizeI()
{
    return this->image.size();
}

int Image::GetImageSizeJ()
{
    return this->image[0].size();
}

Pixel Image::GetImagePixel(int i, int j)
{
    return this->image[i][j];
}

Block Image::GetImageBlock(int si, int sj)
{
    Block block;
    
    for (int i = 0; i < Block::P; ++i)
    {
        for (int j = 0; j < Block::Q; ++j)
        {
            block.SetBlockPixel(i, j, this->image[si+i][sj+j]);
        }
    }
    
    return block;
}

// SETTERS: --------------------------------------------------------------------

void Image::SetImageSize(int m, int n)
{
    this->image = vector< vector<Pixel> >(m, vector<Pixel>(n));
}

void Image::SetImagePixel(int i, int j, Pixel pixel)
{
    this->image[i][j] = pixel;
}