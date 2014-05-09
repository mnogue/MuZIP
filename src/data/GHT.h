
#include <iostream>
#include <vector>

#include "Block.h"
#include "Pixel.h"

using namespace std;

#ifndef GHT_H
#define GHT_H

class GHT
{
    private:
    
    // STRUCT: -----------------------------------------------------------------
    
    struct Node
    {
        int index;
        int parentIndex;
        
        Node *left;
        Node *right;
        
        Node()
        {
            this->index  = -1;
            this->parentIndex = -1;
            
            this->left       = NULL;
            this->right      = NULL;
        }
    };
    
    // PRIVATE VARIABLES: ------------------------------------------------------
    
    Node *root;
    
    vector<int> s;
    
    vector<Block> C;
    vector<int> frequency;
    
    // PRIVATE FUNCTIONS: ------------------------------------------------------
    
    void AddBlockToGHTandC(Block& block, Node*& node, int parentIndex);
    
    void GetNearestNeighbor(Block& block, Node*& node, double& r, int& nn);
    
    public:
    
        // CONSTRUCTOR: --------------------------------------------------------
    
        GHT();
    
        // GETTERS: ------------------------------------------------------------
    
        double GetNearestNeighbor(Block& block, int& nearestIndex);
        
        int GetS(int i);
        int GetSSize();
        
        Block GetBlockFromC(int i);
        int GetCSize();
        
        int GetFrequency(int i);
        
        vector<int> GetFrequencyArray();
        
        // SETTERS: ------------------------------------------------------------
        
        void NotFoundSimilarBlock(Block& block);
        
        void FoundSimilarBlock(int similarIndex);
        
        void SetS(int i, int value);
        void SetSSize(int size);
        
        void SetC(int i, Block block);
        void SetCSize(int size);
};

#endif