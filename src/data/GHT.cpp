
#include "GHT.h"

// CONSTRUCTOR: ----------------------------------------------------------------

GHT::GHT()
{
    this->root = new Node();
    this->root->index       = -1;
    this->root->parentIndex = -1;
    this->root->left        = NULL;
    this->root->right       = NULL;
    
    this->s = vector<int>(0);
    this->C = vector<Block>(0);
    this->frequency = vector<int>(0);
}

// PRIVATE FUNCTIONS: ----------------------------------------------------------

void GHT::AddBlockToGHTandC(Block& block, Node*& node, int parentIndex)
{
    if (node == NULL)
    {
        this->C.push_back(block);
        
        node = new Node();
        node->index = C.size() - 1;
        node->parentIndex = parentIndex;
        return;
    }
    
    Block current = this->C[node->index];
    Block parent  = this->C[node->parentIndex];
    
    double distanceToCurrent = block.GetDistanceTo(current);
    double distanceToParent  = block.GetDistanceTo(parent);
    
    if (distanceToCurrent < distanceToParent)
    {
        this->AddBlockToGHTandC(block, node->left, node->index);
    }
    else
    {
        this->AddBlockToGHTandC(block, node->right, node->index);
    }
}

void GHT::GetNearestNeighbor(Block& block, Node*& node, double& r, int& nn)
{
    if (node == NULL) return;
    
    Block current = this->C[node->index];
    Block parent  = this->C[node->parentIndex];
    
    double distanceToCurrent = block.GetDistanceTo(current);
    double distanceToParent  = block.GetDistanceTo(parent);
    
    if (distanceToCurrent <= r or r == -1)
    {
        r  = distanceToCurrent;
        nn = node->index;
    }
    
    if (distanceToCurrent < distanceToParent)
    {
        GetNearestNeighbor(block, node->left, r, nn);
        
        if (distanceToCurrent + r > distanceToParent - r)
        {
            GetNearestNeighbor(block, node->right, r, nn);
        }
    }
    else
    {
        GetNearestNeighbor(block, node->right, r, nn);
        
        if (distanceToCurrent - r < distanceToParent + r)
        {
            GetNearestNeighbor(block, node->left, r, nn);
        }
    }
}

// GETTERS: --------------------------------------------------------------------

double GHT::GetNearestNeighbor(Block& block, int& nn)
{
    nn = -1;
    double r = -1.0;
    
    if (this->root->parentIndex == -1) return Block::Alpha + 1;
    
    if (this->root->index == -1)
    {
        Block rootParent = this->C[root->parentIndex];
        double distanceToRootParent = block.GetDistanceTo(rootParent);
        
        r = distanceToRootParent;
        nn = this->root->parentIndex;
        
        return r;
    }
    
    this->GetNearestNeighbor(block, this->root, r, nn);
    
    if (this->root->parentIndex != -1)
    {
        Block rootParent = this->C[root->parentIndex];
        double distanceToRootParent = block.GetDistanceTo(rootParent);
        
        if (distanceToRootParent < r)
        {
            r = distanceToRootParent;
            nn = this->root->parentIndex;
        }
    }

    return r;
}

int GHT::GetS(int i)
{
    return this->s[i];
}

int GHT::GetSSize()
{
    return this->s.size();
}

Block GHT::GetBlockFromC(int i)
{
    return this->C[i];
}

int GHT::GetCSize()
{
    return this->C.size();
}

int GHT::GetFrequency(int i)
{
    return this->frequency[i];
}

vector<int> GHT::GetFrequencyArray()
{
    return this->frequency;
}

// SETTERS: --------------------------------------------------------------------

void GHT::NotFoundSimilarBlock(Block& block)
{
    if (this->root->parentIndex == -1)
    {
        this->C.push_back(block);
        this->root->parentIndex = C.size() - 1;
    }
    else if (this->root->index == -1)
    {
        this->C.push_back(block);
        this->root->index = C.size() - 1;
    }
    else
    {
        this->AddBlockToGHTandC(block, this->root, this->root->index);
    }
    
    this->frequency.push_back(1);
    this->s.push_back(C.size()-1);
}
        
void GHT::FoundSimilarBlock(int similarIndex)
{
    this->s.push_back(similarIndex);
    this->frequency[similarIndex] += 1;
}

void GHT::SetS(int i, int value)
{
    this->s[i] = value;
}

void GHT::SetSSize(int size)
{
    this->s = vector<int>(size);
}

void GHT::SetC(int i, Block block)
{
    this->C[i] = block;
}

void GHT::SetCSize(int size)
{
    this->C = vector<Block>(size);
}