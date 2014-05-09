
#include <iostream>

#include <vector>
#include <string>
#include <queue>
#include <stack>

#include "GHT.h"
#include "Block.h"
#include "Pixel.h"
#include "Image.h"

using namespace std;

#ifndef HUFFMAN_H
#define HUFFMAN_H

class Huffman
{
    private:
    
    // STRUCT: -----------------------------------------------------------------
    
    struct Node
    {
        int index;
        
        Node *left;
        Node *right;
        
        Node(int i = -1)
        {
            index = i;
            left  = NULL;
            right = NULL;
        }
        
        ~Node()
        {
            if (left  != NULL) delete left;
            if (right != NULL) delete right;
        }
    };
    
    struct Element
    {
        int frequency;
        Node *tree;
        
        Element()
        {
            frequency = 0;
            tree = new Node();
        }
        
    };
    
    struct Comparator
    {
        bool operator() (Element& a, Element& b)
        {
            return a.frequency > b.frequency;
        }
    };
    
    // PRIVATE VARIABLES: ------------------------------------------------------
    
    priority_queue<Element, vector<Element>, Comparator> pqueue;
    
    string codeTrace;       // Auxiliar variable which is used as a stack
                            // to hold the generated huffman code for a certain
                            // index.
                            
    vector<string> codes;   // The same variable as C (collection of blocks) but
                            // identifies a block with the huffman code.
    
    string compressedCode;  // a string which contains all the huffman code
                            // readed from a compressed .mz file. There are no
                            // cuts, so a huffman tree is needed to split 
                            // sequences of code.
    
    // PRIVATE FUNCTIONS: ------------------------------------------------------
    
    string GetTraceCode();
    void PushTraceCode(char c);
    void PopTraceCode();
    
    // compression: ------------------------------------------------------------
    void CreateHuffmanTreeFromIndex(GHT& ght);
    void GetHuffmanCodes(Node *node);
    
    // decompression: ----------------------------------------------------------
    void CreateHuffmanTreeFromCodes(Node*& node, int codeIndex, int it);
    void GetHuffmanIndex(Node*& node, int& codeIter, int sIter, GHT& ght);
    
    public:
    
        // CONSTRUCTOR: --------------------------------------------------------
        
        Huffman();
        
        // HUFFMAN: ------------------------------------------------------------
        
        void GenerateCodesFromIndex(GHT& ght);
        
        void GenerateIndexFromCodes(GHT& ght, Image& image);
        
        // GETTERS: ------------------------------------------------------------
        
        string GetHuffmanCode(int i);
        int GetHuffmanCodesSize();
        
        // SETTERS: ------------------------------------------------------------
        
        void SetCodesSize(int size);
        void SetCodeAt(int i, string code);
        
        void SetCompressedCode(string code);
};

#endif
