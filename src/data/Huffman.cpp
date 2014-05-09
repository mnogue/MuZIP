
#include "Huffman.h"

// CONSTRUCTOR: ----------------------------------------------------------------

Huffman::Huffman() { }

// PRIVATE FUNCTIONS: ----------------------------------------------------------

string Huffman::GetTraceCode()
{
    return this->codeTrace;
}

void Huffman::PushTraceCode(char c)
{
    this->codeTrace.push_back(c);
}

void Huffman::PopTraceCode()
{
    this->codeTrace.erase(this->codeTrace.end()-1);
}

////////////////////////////////////////////////////////////////////////////////
// COMPRESSION: ----------------------------------------------------------------

void Huffman::CreateHuffmanTreeFromIndex(GHT& ght)
{
    for (int i = 0; i < ght.GetCSize(); ++i)
    {
        Element *element = new Element();
        element->frequency = ght.GetFrequency(i);
        element->tree = new Node(i);
        
        this->pqueue.push(*element);
    }
    
    while (pqueue.size() > 1)
    {
        Element elem1 = pqueue.top(); pqueue.pop();
        Element elem2 = pqueue.top(); pqueue.pop();
        
        Element *elem = new Element();
        elem->tree->left  = elem1.tree;
        elem->tree->right = elem2.tree;
        elem->frequency = elem1.frequency + elem2.frequency;
        
        this->pqueue.push(*elem);
    }
}

void Huffman::GetHuffmanCodes(Node *node)
{
    if (node == NULL) return;
    
    if (node->index != -1)
    {
        this->codes[node->index] = this->GetTraceCode();
        return;
    }
    
    PushTraceCode('0');
    this->GetHuffmanCodes(node->left);
    
    PopTraceCode();
    PushTraceCode('1');
    this->GetHuffmanCodes(node->right);
    
    PopTraceCode();
}

////////////////////////////////////////////////////////////////////////////////
// DECOMPRESSION: --------------------------------------------------------------

void Huffman::CreateHuffmanTreeFromCodes(Node*& node, int codeIndex, int it)
{
    if (node == NULL)
    {
        if (it == this->codes[codeIndex].size())
        {
            node = new Node(codeIndex);
            return;
        }
        else
        {
            node = new Node();
        }
    }
    
    if (this->codes[codeIndex][it] == '0')
    {
        CreateHuffmanTreeFromCodes(node->left, codeIndex, it+1);
    }
    else
    {
        CreateHuffmanTreeFromCodes(node->right, codeIndex, it+1);
    }
}

void Huffman::GetHuffmanIndex(Node*& node, int& codeIter, int sIter, GHT& ght)
{
    if (node->index != -1)
    {
        ght.SetS(sIter, node->index);
        return;
    }
    
    if (this->compressedCode[codeIter] == '0')
    {
        GetHuffmanIndex(node->left, ++codeIter, sIter, ght);
    }
    else
    {
        GetHuffmanIndex(node->right, ++codeIter, sIter, ght);
    }
}

////////////////////////////////////////////////////////////////////////////////
// GENERATE HUFFMAN CODES FROM A COLLECTION OF INDEX: --------------------------

void Huffman::GenerateCodesFromIndex(GHT& ght)
{
    this->CreateHuffmanTreeFromIndex(ght);
    
    this->codes = vector<string>(ght.GetCSize(), "$");
    this->codeTrace = "";
    
    Node *root = this->pqueue.top().tree; this->pqueue.pop();
    
    this->GetHuffmanCodes(root);
}

////////////////////////////////////////////////////////////////////////////////
// GENERATE BLOCK INDEX FROM HUFFMAN CODES: ------------------------------------

void Huffman::GenerateIndexFromCodes(GHT& ght, Image& image)
{
    Node *root = new Node();
    
    for (int i = 0; i < this->codes.size(); ++i)
    {
        this->CreateHuffmanTreeFromCodes(root, i, 0);
    }
    
    int sIterator = 0;
    int codeIterator = 0;
    while (codeIterator < this->compressedCode.size())
    {
        this->GetHuffmanIndex(root, codeIterator, sIterator, ght);
        ++sIterator;
    }
    
    int sIndex = 0;
    for (int imageX = 0; imageX < image.GetImageSizeI(); imageX += Block::P)
    {
        for (int imageY = 0; imageY < image.GetImageSizeJ(); imageY += Block::Q)
        {
            int blockIndex = ght.GetS(sIndex++);
            Block block = ght.GetBlockFromC(blockIndex);
            
            for (int u = 0; u < Block::P; ++u)
            {
                for (int v = 0; v < Block::Q; ++v)
                {
                    Pixel pixel = block.GetBlockPixel(u,v);
                    image.SetImagePixel(imageX + u, imageY + v, pixel);
                }
            }
        }
    }
    
    delete root;
}

// GETTERS: --------------------------------------------------------------------

string Huffman::GetHuffmanCode(int i)
{
    return this->codes[i];
}

int Huffman::GetHuffmanCodesSize()
{
    return this->codes.size();
}

// SETTERS: --------------------------------------------------------------------

void Huffman::SetCodesSize(int size)
{
    this->codes = vector<string>(size);
}

void Huffman::SetCodeAt(int i, string code)
{
    this->codes[i] = code;
}

void Huffman::SetCompressedCode(string code)
{
    this->compressedCode = code;
}