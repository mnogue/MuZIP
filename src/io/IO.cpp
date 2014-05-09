
#include "IO.h"

////////////////////////////////////////////////////////////////////////////////
// OUTER FUNCTIONS: ------------------------------------------------------------

void IO::OutputProgress(string text, int percent, bool end)
{
    cout << "\r  " << text << " ";
    int space =  57 - text.size();
    
    for (int i = 0; i < space; ++i)
    {
        if (i < percent*space/100) cout << ".";
        else cout << " ";
    }
    
    if (percent < 10)       cout << " [0" << percent << "]";
    else if (percent < 100) cout << " ["  << percent << "]";
    else                    cout << " [OK]";
    
    cout << (end == true ? "\n\n" : "");
}

////////////////////////////////////////////////////////////////////////////////
// INPUT: ----------------------------------------------------------------------

void IO::InputCompression(Image& image)
{
    string fname = "";
    unsigned char *charImage;
    char header [100], *ptr;
    ifstream file;
    
    cout << endl;
    cout << "  +-------------------------------------------------------------+";
    cout << endl;
    cout << "  | COMPRESSION                                                 |";
    cout << endl;
    cout << "  +-------------------------------------------------------------+";
    cout << endl << endl;
    
    cout << "  # Enter path to image (.ppm): ";
    cin  >> fname;
    
    file.open(fname.c_str(), ios::in);
    
    IO::fileName = fname;
    
    if (!file) 
    {
        cout << endl << endl;
        cout << "  ERROR: Cannot read/find file '" << fname << "'." << endl;
        cout << "  Check out the path or file permissions" << endl << endl;
        exit(-1);
    }
    
    file.getline(header,100,'\n');

    // Check P6 magic number:
    if ((header[0] != 80) || (header[1] != 54)) 
    {
          cout << endl << endl;
          cout << "  ERROR: Wrong header." << endl;
          cout << "  Expected: P6. Found: " << header[0] << header[1] << endl;
          cout << endl;
          exit(-1);
    }
    
    // Avoid all comments:
    file.getline(header, 100, '\n');
    while (header[0] == '#') file.getline(header, 100, '\n');
    
    // Get size:
    int M = strtol(header, &ptr, 0);
    int N = atoi(ptr);
    
    // If N value is in a different line than M, read it (Photoshop CS4 does it)
    if (N == 0) 
    {
        file.getline(header, 100, '\n');
        N = strtol(header, &ptr, 0);
    }
 
    file.getline(header,100,'\n');
    int range=strtol(header,&ptr,0);
    
    if (range != 255)
    {
        cout << endl << endl;
        cout << "  ERROR: Expecting RGB value range of 255 and found " << range;
        cout << endl << endl;
        exit(-1);
    }

    charImage = (unsigned char *) new unsigned char [3*M*N];
    
    file.read (reinterpret_cast<char *>(charImage), (3*M*N)*sizeof(unsigned char));

    if (file.fail()) 
    {
        cout << endl << endl;
        cout << "  ERROR: (.ppm) file has wrong image size." << endl;
        cout << "  Size found: M = " << M << " N = " << N << endl << endl;
        exit(-1);
    }
    
    file.close();
    
    if (M%Block::P != 0 or N%Block::Q != 0)
    {
        cout << endl << endl;
        cout << "  ERROR: P and/or Q values are not exact divisors of" << endl;
        cout << "  the current image size (M mod P != 0 or N mod Q != 0).";
        cout << endl << endl;
        exit(-1);
    }
    
    /* Convert the unsigned characters to integers */
    
    image.SetImageSize(M, N);
    
    cout << endl;
    cout << "  Reading image file ....................................... [OK]";
    cout << endl;
    
    for (int i = 0; i < M; i++)
    {
        int k = 0;
        for (int j = 0; j < 3*N; j += 3) 
        {
            int r = (int)charImage[i*3*N+j];
            int g = (int)charImage[i*3*N+j+1];
            int b = (int)charImage[i*3*N+j+2];
            
            Pixel pixel(r, g, b);
            image.SetImagePixel(i, k, pixel);
            
            ++k;
        }
    }
    
    delete [] charImage;
    
    cout << endl;
    cout << "  Saving data .............................................. [OK]";
    cout << endl << endl;
}

void IO::InputDecompression(GHT& ght, Huffman& huffman, Image& image)
{
    cout << endl;
    cout << "+---------------------------------------------------------------+";
    cout << endl;
    cout << "| DECOMPRESSION                                                 |";
    cout << endl;
    cout << "+---------------------------------------------------------------+";
    cout << endl << endl;
    
    string fname = "";
    ifstream file;
    
    cout << "  # Enter path to image (.ppm.mz): ";
    cin  >> fname;
    
    file.open(fname.c_str(), ios::in);
    
    IO::fileName = fname;
    
    if (!file) 
    {
        cout << endl << endl;
        cout << "  ERROR: Cannot read/find file '" << fname << "'." << endl;
        cout << "  Check out the path or file permissions" << endl << endl;
        exit(-1);
    }
    
    string magic;
    file >> magic;

    // Check P6Mu magic number:
    if (magic != "P6Mu") 
    {
          cout << endl << endl;
          cout << "  ERROR: Wrong header." << endl;
          cout << "  Expected: P6Mu. Found: " << magic << endl;
          cout << endl;
          exit(-1);
    }
    
    int numberBlocks;
    int P, Q;
    file >> numberBlocks >> P >> Q;
    
    Block::P = P;
    Block::Q = Q;
    
    for (int i = 0; i < 8; ++i) IO::ReadBit(file);
    
    ght.SetCSize(numberBlocks);
    huffman.SetCodesSize(numberBlocks);
    
    int bCollSize = 3*numberBlocks*Block::P*Block::Q;
    unsigned char * bColl = (unsigned char *) new unsigned char[bCollSize];
    
    file.read(reinterpret_cast<char *>(bColl), (bCollSize)*sizeof(unsigned char));
    
    int iter = 0;
    
    for (int i = 0; i < ght.GetCSize(); ++i)
    {
        Block block;
        
        for (int u = 0; u < Block::P; ++u)
        {
            for (int v = 0; v < Block::Q; ++v)
            {
                Pixel pixel;
                
                pixel.SetR( (int)bColl[iter++] );
                pixel.SetG( (int)bColl[iter++] );
                pixel.SetB( (int)bColl[iter++] );
                
                block.SetBlockPixel(u, v, pixel);
            }
        }
        
        ght.SetC(i, block);
    }
    
    // huffman codes:
    if (numberBlocks > 1)
    {
        for (int i = 0; i < huffman.GetHuffmanCodesSize(); ++i)
        {
            string huffmanCode;
            file >> huffmanCode;
            huffman.SetCodeAt(i, huffmanCode);
        }
    }
    else
    {
        huffman.SetCodeAt(0, "0");
    }
    
    int imageWidth;
    int imageHeight;
    
    file >> imageWidth >> imageHeight;
    
    image.SetImageSize(imageWidth, imageHeight);
    ght.SetSSize((imageWidth*imageHeight) / (Block::P * Block::Q));
    
    for (int i = 0; i < 8; ++i) IO::ReadBit(file);
    
    // collection of encoded index:
    string indexCodes = "";
    while (file.good())
    {
        int num = IO::ReadBit(file);
        indexCodes += (num == 0) ? "0" : "1";
    }
    
    huffman.SetCompressedCode(indexCodes);
    
    cout << endl;
    cout << "  Reading .ppm.mz image file ............................... [OK]";
    cout << endl;
    
}

////////////////////////////////////////////////////////////////////////////////
// OUTPUT: ---------------------------------------------------------------------

/*
 *   COMPRESSION FORMAT:
 *     + Magic string "P6Mu"
 *     + Number of blocks
 *     + Width  of the blocks
 *     + Height of the blocks
 *     + [ Collection of blocks ]
 *     + [ Huffman codes ]
 *     + Width of the image
 *     + Height of the image
 *     + [ Collection of index to blocks encoded with Huffman algorithm ]
 */

void IO::OutputCompression(GHT& ght, Huffman& huffman, Image& image)
{
    ofstream file;
    string fname = (IO::fileName+".mz");
    file.open(fname.c_str(), ios::out);
    
    file << "P6Mu" << endl;
    
    file << ght.GetCSize() << endl;
    
    file << Block::P << " " << Block::Q << endl;
    
    for (int i = 0; i < ght.GetCSize(); ++i)
    {
        Block block = ght.GetBlockFromC(i);
        
        for (int u = 0; u < Block::P; ++u)
        {
            for (int v = 0; v < Block::Q; ++v)
            {
                Pixel pixel = block.GetBlockPixel(u, v);
                
                file << (unsigned char)pixel.GetR();
                file << (unsigned char)pixel.GetG();
                file << (unsigned char)pixel.GetB();
            }
        }
    }
    
    file << endl;
    
    for (int i = 0; i < huffman.GetHuffmanCodesSize(); ++i)
    {
        if (i != 0) file << " ";
        
        file << huffman.GetHuffmanCode(i);
    }
    
    file << endl;
    
    file << image.GetImageSizeI() << " " << image.GetImageSizeJ() << endl;
    
    for (int i = 0; i < ght.GetSSize(); ++i)
    {
        int index = ght.GetS(i);
        string huffmanCode = huffman.GetHuffmanCode(index);
        
        for (int j = 0; j < huffmanCode.size(); ++j)
        {
            if (huffmanCode[j] == '1') IO::WriteBit(1, file);
            else if (huffmanCode[j] == '0') IO::WriteBit(0, file);
        }
    }
    
    while (IO::bitCounter != 0) IO::WriteBit(0, file);
    
    file.close();
    
    cout << "  Creating compressed file ................................. [OK]";
    cout << endl << endl;
}

/*
 *   UNCOMPRESSED FORMAT:
 *     + Magic string "P6"
 *     + Width  of the image
 *     + Height of the image
 *     + Range of 1 pixel
 *     + [ Collection of Pixels ]
 */

void IO::OutputDecompression(Image& image)
{
    ofstream file;
    string fname = IO::fileName;
    fname.erase(fname.end()-7, fname.end());
    fname += "_mz.ppm";
    file.open(fname.c_str(), ios::out);
    
    file << "P6" << endl;
    file << "# This image was compressed using MuZIP." << endl;
    
    file << image.GetImageSizeI() << endl << image.GetImageSizeJ() << endl;
    file << "255" << endl;
    
    for (int i = 0; i < image.GetImageSizeI(); ++i)
    {
        for (int j = 0; j < image.GetImageSizeJ(); ++j)
        {
            Pixel pixel = image.GetImagePixel(i,j);
            
            file << (unsigned char)pixel.GetR();
            file << (unsigned char)pixel.GetG();
            file << (unsigned char)pixel.GetB();
        }
    }
    
    file.close();
    
    cout << endl;
    IO::OutputProgress("Creating .ppm file", 100);
    cout << endl << endl;
}

// PRIVATE FUNCTIONS: ----------------------------------------------------------

void IO::WriteBit(int bit, ofstream& file)
{
    IO::singleByte |= (bit << IO::bitCounter);
    if (++IO::bitCounter == 8)
    {
        file << singleByte;
        IO::singleByte = 0;
        IO::bitCounter = 0;
    }
}

int IO::ReadBit(ifstream& file)
{
   if (IO::bitCounter == 0)
   {
       IO::bitCounter = 8;
       
       int size = sizeof(unsigned char);
       unsigned char * reader = (unsigned char *) new unsigned char[size];
       file.read(reinterpret_cast<char *>(reader), sizeof(unsigned char));
       
       IO::singleByte = reader[0];
   }
   --IO::bitCounter;
   
   return (IO::singleByte >> (7 - IO::bitCounter)) & 1;
}