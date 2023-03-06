#ifndef TIMECODE_H
#define TIMECODE_H

#define COLOR_RED 0
#define COLOR_BLACK 1
#define COLOR_DOUBLE_BLACK 2

#include <iostream>
#include <stdexcept>
using namespace std;

struct RBTNode{
    int data;
    unsigned short int color; // black:0 red:1 double black:2
    RBTNode *left = nullptr;
    RBTNode *right = nullptr;
    RBTNode *parent = nullptr;
    bool temp = false;
    
};



class RedBlackTree
{
public:
    RedBlackTree(){};
    RedBlackTree(const RedBlackTree &rbt); // copy
    ~RedBlackTree();

    void Insert(int);
    void Remove(int data);
    bool Contains(int value);
    
    int GetMin();
    int GetMax();

    RBTNode* GetRoot()const {return TreeRoot;}
    unsigned long long int Size(){return numItems;}
    RBTNode* Recolor(RBTNode* looking_at);

    string ToInfixString() const {return ToInfixString(TreeRoot);}
    string ToPrefixString() const { return ToPrefixString(TreeRoot);}
    string ToPostfixString() const { return ToPostfixString(TreeRoot);}
private:
    void FixDB(RBTNode* node);
    RBTNode* GetNode(int data);
    RBTNode* GetSib(RBTNode* node);
    int GetColor(RBTNode* node); // prevents seg fault
    void SetColor(RBTNode* node, int color); // prevents seg fault
    bool IsLeftChild(RBTNode* node);
    void QuickRemove(RBTNode* node);
    RBTNode* GetIOS(RBTNode* node);
    RBTNode* CopyNode(RBTNode* node, RBTNode* parent=nullptr);
    void DestructorHelper(RBTNode* node);
    unsigned long long int numItems = 0;
    RBTNode *TreeRoot = nullptr;
    RBTNode* GetUncle(RBTNode* node) const;
    //void recolor();
    void RightRotate(RBTNode* node);
    void LeftRotate(RBTNode* node);

    string NodeToString(RBTNode* node) const;
    string ToInfixString(RBTNode* root) const;
    string ToPrefixString(RBTNode* root) const;
    string ToPostfixString(RBTNode* root) const;
};

#endif