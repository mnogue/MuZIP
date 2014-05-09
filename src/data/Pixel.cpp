
#include "Pixel.h"

// CONSTRUCTORS: ---------------------------------------------------------------

Pixel::Pixel()
{
    this->r = 0;
    this->g = 0;
    this->b = 0;
}

Pixel::Pixel(int r, int g, int b)
{
    this->r = r;
    this->g = g;
    this->b = b;
}

// GETTERS: --------------------------------------------------------------------

int Pixel::GetR() { return this->r; }
int Pixel::GetG() { return this->g; }
int Pixel::GetB() { return this->b; }

// SETTERS: --------------------------------------------------------------------

void Pixel::SetR(int r) { this->r = r; }
void Pixel::SetG(int g) { this->g = g; }
void Pixel::SetB(int b) { this->b = b; }