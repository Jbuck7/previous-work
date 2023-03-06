#include "RedBlackTree.h"

using namespace std;

RedBlackTree::~RedBlackTree(){
    DestructorHelper(TreeRoot); // Function that deallocates memory used by the tree.
}

RedBlackTree::RedBlackTree(const RedBlackTree &rbt){ // Copy constructor.
    TreeRoot = CopyNode(rbt.TreeRoot); // Function that creates a new node and copies the data from another node.
    numItems = rbt.numItems; // Copy the number of elements in the tree.
}

bool RedBlackTree::Contains(int value){ // Function to check if the value is present in the tree.
    if(numItems == 0){return false;} // If there are no elements in the tree, the function returns false.
    RBTNode* looking_at = TreeRoot; // A pointer to the root of the tree.
    bool moved = true; // A boolean variable that indicates whether the node has moved to another node.
    while(moved){ // A loop that runs while the node is moving.
        moved = false;
        if(looking_at->right != nullptr){
            if(looking_at->data<value ){ // If the value is greater than the data in the current node, move to the right child.
                moved = true;
                looking_at = looking_at->right;
                }
            }
        if(looking_at->left != nullptr){
            if(looking_at->data > value){ // If the value is less than the data in the current node, move to the left child.
                moved = true;
                looking_at = looking_at->left;}
            }
            if(looking_at->data == value){return true;} // If the value is equal to the data in the current node, the function returns true.
    }

    return false; // If the value is not present in the tree, the function returns false.
}


void RedBlackTree::Insert(int data){ // Function to insert a value in the tree.
    
    if(Contains(data)){throw invalid_argument("Value already in tree.");} // If the value is already present in the tree, the function throws an exception.
    RBTNode *node = new RBTNode; // Create a new node.
    node->data = data; // Assign the value to the node.
   if(numItems ==0){ // If the tree is empty, the root node is set to black and the function returns.
        node->color = COLOR_BLACK;
        TreeRoot = node;
        numItems +=1;
        return;
    }

    node->color = COLOR_RED; // New nodes are initially set to red.
    
    RBTNode *looking_at = TreeRoot; // A pointer to the root of the tree.
    while(true){ // Find a place in the tree for the new node.
        if(node->data > looking_at->data){
            if(looking_at->right == nullptr){
                looking_at->right = node; // If the new node's value is greater than the current node, move to the right child.
                break;
                }
            looking_at = looking_at->right;
            }
        else{
            if(looking_at->left == nullptr){
                looking_at->left = node; // If the new node's value is less than the current node, move to the left child.
                break;
                }
            looking_at = looking_at->left;
            }
    }
    node->parent = looking_at; // Assign the parent of the new node.
    looking_at = node; // Set the new node as the current node.
    //clean up
    while(looking_at->parent != nullptr){
        if(looking_at->parent->color == COLOR_BLACK){break;} // Step 4: Parent is red
        if(looking_at->parent == looking_at->parent->parent->left){ // Left Left or Left Right case.
            RBTNode *unc = GetUncle(looking_at);
            unsigned short int uncColor;
            if(unc == nullptr){uncColor = COLOR_BLACK;}
            else{uncColor= unc->color;}
            if(uncColor == COLOR_RED){ // Step 6: Uncle is Red
                looking_at=Recolor(looking_at);
                continue;
                
            }
            else if(looking_at == looking_at->parent->right){ // Step 5: Uncle is black. Left right case.
                looking_at = looking_at->parent;
                LeftRotate(looking_at);
            }
            // Step 5 Left Left case:
            if(looking_at->parent == nullptr){continue;}
            else if(looking_at->parent->parent == nullptr){continue;}
            looking_at->parent->color = COLOR_BLACK;
            looking_at->parent->parent->color = COLOR_RED;
            RightRotate(looking_at->parent->parent);
        }
        else{ // Right Right or Right Left cases
            RBTNode *unc = GetUncle(looking_at);
            unsigned short int uncColor;
            if(unc == nullptr){uncColor = COLOR_BLACK;}
            else{uncColor= unc->color;}
            if(uncColor == COLOR_RED){ // Step 6: Uncle is Red
                looking_at=Recolor(looking_at);
                continue;
            }
            else if(looking_at == looking_at->parent->left){ // Step 5: Uncle is black. Right Left case.
               looking_at= looking_at->parent;
                RightRotate(looking_at);
            }
            // Step 5 Right Right case:
            if(looking_at->parent == nullptr){continue;}
            else if(looking_at->parent->parent == nullptr){continue;}
            looking_at->parent->color = COLOR_BLACK;
            looking_at->parent->parent->color = COLOR_RED;
            LeftRotate(looking_at->parent->parent);
        }
        
    }
    TreeRoot->color= COLOR_BLACK;
    numItems +=1;
    return;
    
}
RBTNode* RedBlackTree::Recolor(RBTNode* looking_at){
    // If the node being looked at is the root of the tree,
    // set its color to black and return it.
    if(looking_at == TreeRoot){
        looking_at->color = COLOR_BLACK;
        return looking_at;
    }

    // If the parent of the node being looked at is null,
    // return the node.
    if(looking_at->parent == nullptr){return looking_at;}

    // Set the color of the parent of the node being looked at to black.
    looking_at->parent->color = COLOR_BLACK;

    // If the grandparent of the node being looked at is null,
    // return the node.
    if(looking_at->parent->parent == nullptr){return looking_at;}

    // Set the color of the grandparent of the node being looked at to red.
    looking_at->parent->parent->color = COLOR_RED;

    // Get the uncle of the node being looked at and set its color to black.
    RBTNode *unc = GetUncle(looking_at);
    if(unc != nullptr){unc->color=COLOR_BLACK;}

    // Set the node being looked at to its grandparent.
    looking_at = looking_at->parent->parent;

    // If the parent of the node being looked at is not null and
    // the grandparent of the node being looked at is not null,
    // get the uncle of the node being looked at.
    if(looking_at->parent != nullptr){
        if(looking_at->parent->parent != nullptr)
        {unc = GetUncle(looking_at);}
    }

    // If the color of the uncle of the node being looked at is red,
    // recursively call Recolor() with the grandparent of the node being looked at.
    if(unc->color == COLOR_RED){looking_at = Recolor(looking_at);}

    // Return the node being looked at.
    return looking_at;
}



RBTNode* RedBlackTree::GetUncle(RBTNode* node) const{
    // Get the grandparent node of the input node
    RBTNode* gparent = node->parent->parent;

    // Determine if the parent node is the left or right child of the grandparent,
    // and return the opposite child of the grandparent
    if(gparent->data > node->parent->data){
        return gparent->right;
    }
    return gparent->left;
}

void RedBlackTree::RightRotate(RBTNode* root){
    // Store the left child of the root node in a new pivot variable
    RBTNode *pivot = root->left;

    // Update the left child of the root node to be the right child of the pivot node
    root->left = pivot->right;

    // Update the parent pointer of the right child of the pivot node to point to the root node
    if(pivot->right!=nullptr){pivot->right->parent=root;}

    // Update the parent pointer of the pivot node's parent to point to the pivot node,
    // if the root node is a left or right child of its parent
    if(root->parent!=nullptr){if(root == root->parent->left){root->parent->left=pivot;}}
    if(root->parent!=nullptr){if(root == root->parent->right){root->parent->right=pivot;}}

    // Update the right child of the pivot node to be the root node
    pivot->right = root;

    // Update the parent pointer of the pivot node to point to the original parent of the root node
    pivot->parent = root->parent;

    // Update the parent pointer of the root node to point to the pivot node
    root->parent = pivot;

    // If the original root node was the root of the tree, update the TreeRoot pointer to point to the pivot node
    if(TreeRoot == root){TreeRoot=pivot;}

    // Return from the function
    return;
}

// Performs a left rotation on a Red Black Tree
void RedBlackTree::LeftRotate(RBTNode* root){
    RBTNode *pivot = root->right; // Set the pivot node to the right child of the root
    root->right = pivot->left; // Set the right child of the root to the left child of the pivot node
    if(pivot->left!=nullptr){pivot->left->parent=root;} // Update the parent of the left child of the pivot node
    if(root->parent!=nullptr){if(root == root->parent->left){root->parent->left=pivot;}} // Update the parent of the root node to point to the pivot node
    if(root->parent!=nullptr){if(root == root->parent->right){root->parent->right=pivot;}} // Update the parent of the root node to point to the pivot node
    pivot->left = root; // Set the left child of the pivot node to the root node
    pivot->parent = root->parent; // Set the parent of the pivot node to the parent of the root node
    root->parent = pivot; // Set the parent of the root node to the pivot node
    if(TreeRoot == root){TreeRoot=pivot;} // If the root node was the root of the entire tree, update the tree's root to be the pivot node

    return;
}


// Returns a string representation of the tree using infix traversal
string RedBlackTree::ToInfixString(RBTNode* root) const {
    string output="";
    if(root == nullptr){return output;} // If the root node is null, return an empty string
    if(root->left != nullptr){output +=ToInfixString(root->left);} // Traverse the left subtree recursively
    output +=NodeToString(root); // Add the current node to the output string
    if(root->right != nullptr){output +=ToInfixString(root->right);} // Traverse the right subtree recursively
    return output; // Return the output string
}


// Returns a string representation of the tree using prefix traversal
string RedBlackTree::ToPrefixString(RBTNode* root) const{
    string output="";
    if(root == nullptr){return output;} // If the root node is null, return an empty string
    output += NodeToString(root); // Add the current node to the output string
    if(root->left != nullptr){output += ToPrefixString(root->left);} // Traverse the left subtree recursively
    if(root->right != nullptr){output += ToPrefixString(root->right);} // Traverse the right subtree recursively
    return output; // Return the output string
}


// Returns a string representation of the tree using postfix traversal
string RedBlackTree::ToPostfixString(RBTNode* root) const{
    string output ="";
    if(root == nullptr){return output;} // If the root node is null, return an empty string
    if(root->left != nullptr){output += ToPostfixString(root->left);} // Traverse the left subtree recursively
    if(root->right != nullptr){output += ToPostfixString(root->right);} // Traverse the right subtree recursively
    output += NodeToString(root); // Add the current node to the output string
    return output; // Return the output string
}

// This function converts a RBTNode's color and data to a string representation.
string RedBlackTree::NodeToString(RBTNode* node) const{
    string output =" ";
    if(node->color == COLOR_BLACK){output+="B";}
    else{output+="R";}
    return output + to_string(node->data)+" ";
}

// This function returns the minimum value in the tree.
// It traverses the leftmost path from the root until there is no left child.
int RedBlackTree::GetMin(){
    if(this->Size()==0){throw logic_error("Tree is empty");}
    RBTNode* looking_at = TreeRoot;
    while(looking_at->left != nullptr){looking_at = looking_at->left;}
    return looking_at->data;
}

// This function returns the maximum value in the tree.
// It traverses the rightmost path from the root until there is no right child.
int RedBlackTree::GetMax(){
    if(this->Size()==0){throw logic_error("Tree is empty");}
    RBTNode* looking_at = TreeRoot;
    while(looking_at->right != nullptr){looking_at = looking_at->right;}
    return looking_at->data;
}

// This function recursively deletes each node of the tree, starting from the root.
void RedBlackTree::DestructorHelper(RBTNode* node){
    if(node == nullptr){return;}
    if(node->left!= nullptr){DestructorHelper(node->left);}
    if(node->right!= nullptr){DestructorHelper(node->right);}
    delete node;
}

// This function recursively copies a node and its descendants.
// It creates a new node with the same data and color, but sets the parent and children pointers to new nodes.
RBTNode* RedBlackTree::CopyNode(RBTNode* node, RBTNode* parent){
    RBTNode* copy = new RBTNode;
    copy->data = node->data;
    copy->color = node->color;
    copy->parent = parent;
    if(node->left != nullptr){copy->left = CopyNode(node->left,copy);}
    if(node->right != nullptr){copy->right = CopyNode(node->right,copy);}
    return copy;
}

RBTNode* RedBlackTree::GetNode(int data){
    // Check if tree is empty, return nullptr
    if(numItems == 0){return nullptr;}
    // Start at the root
    RBTNode* looking_at = TreeRoot;
    bool moved = true;
    // Traverse down the tree, moving left or right based on the value of data
    while(moved){
        moved = false;
        if(looking_at->right != nullptr){
            if(looking_at->data< data ){
                moved = true;
                looking_at = looking_at->right;
                }
            }
        if(looking_at->left != nullptr){
            if(looking_at->data > data){
                moved = true;
                looking_at = looking_at->left;}
            }
        // If node with given data is found, return it
        if(looking_at->data == data){return looking_at;}
    }
    // Node with given data was not found in the tree, return nullptr
    return nullptr;
}

RBTNode* RedBlackTree::GetIOS(RBTNode* node){
    // Check if given node is nullptr
    if(node == nullptr){throw invalid_argument("Node is nullptr");}
    // Start at the right child of the given node
    RBTNode* looking_at = node->right;
    // If the right child is nullptr, there is no IOS
    if(looking_at == nullptr){return looking_at;}
    // Traverse down the left subtree of the right child to find the leftmost node
    while(looking_at->left != nullptr){looking_at = looking_at->left;}
    // Return the leftmost node as the IOS
    return looking_at;
}

RBTNode* RedBlackTree::GetSib(RBTNode* node){
    // If the node is a left child, return its sibling (the right child)
    if(node->parent->left == node){return node->parent->right;}
    // If the node is a right child, return its sibling (the left child)
    else{return node->parent->left;}
}

int RedBlackTree::GetColor(RBTNode* node){
    // If the node is nullptr, return BLACK
    if(node == nullptr){return COLOR_BLACK;}
    // Otherwise, return the color of the node
    else{return node->color;}
}

void RedBlackTree::SetColor(RBTNode* node, int color){
    // If the node is not nullptr, set its color to the specified color
    if(node != nullptr){node->color = color;}
    return;
}

void RedBlackTree::QuickRemove(RBTNode* node){
    // If the node has a parent, update its parent's left or right child pointer to nullptr
    if(node->parent != nullptr){
        if(node == node->parent->left){node->parent->left = nullptr;}
        else{node->parent->right = nullptr;}
    }
    // Delete the node
    delete node;
    return;
}

bool RedBlackTree::IsLeftChild(RBTNode* node){
    // If the node has no parent, return false
    if(node->parent == nullptr){return false;}
    // If the node is a left child, return true
    if(node->parent->left == node){return true;}
    // Otherwise, return false
    return false;
}




void RedBlackTree::Remove(int data){
    if(!Contains(data)){throw invalid_argument("Value not in tree.");}
    RBTNode* D = GetNode(data);
    RBTNode* R = nullptr;
    int newval;
    // Check if node is a red leaf
    if(D->color == COLOR_RED && D->left == nullptr && D->right == nullptr){
        QuickRemove(D); // Remove node quickly
        return;
    }
    // Node has only one child
    if(D->left == nullptr && D->right != nullptr){R = D->right;}
    else if(D->left != nullptr && D->right == nullptr){R = D->left;}

    if(R != nullptr){
        D->data = R->data;
        D->left = R->left;
        D->right = R->right;
        delete R;
        return;
    }
    // Node has two children or black zero child case (double black)
    R = GetIOS(D);
    
    if(R != nullptr){
        newval = R->data;
        Remove(R->data);
        D->data = newval;
    }
    else{
        D->temp = true; // Mark node as temporary
        D->color = COLOR_DOUBLE_BLACK;
        FixDB(D); // Fix the double black node
    }
    return;
}

void RedBlackTree::FixDB(RBTNode* node){
    // Root case
    if(node == TreeRoot){
        node->color = COLOR_BLACK; // Set the root color to black
        return;
    }
    RBTNode* sibling = GetSib(node); // Get the sibling of the node
    RBTNode* parent = node->parent;
    RBTNode* rightChild = sibling->right;
    RBTNode* leftChild = sibling->left;
    // Black sibling cases
    if(GetColor(sibling) == COLOR_BLACK){
        // Both children are black
        if(GetColor(sibling->left) == COLOR_BLACK && GetColor(sibling->right) == COLOR_BLACK){
            RBTNode* parent = node->parent;
            SetColor(sibling, COLOR_RED); // Set the sibling color to red
            SetColor(parent, parent->color + 1); // Increase the parent color (red->black->double black)
            if(node->temp == true){QuickRemove(node);}
            else{SetColor(node,COLOR_BLACK);}
            if(parent->color == COLOR_DOUBLE_BLACK){FixDB(parent);} // Recursively fix the parent
        }
        // At least one red child
        if(GetColor(sibling->left) == COLOR_RED || GetColor(sibling->right) == COLOR_RED){
            // LL case
            if(IsLeftChild(sibling) && GetColor(leftChild) == COLOR_RED){
                RightRotate(parent);
                SetColor(leftChild, sibling->color);
                SetColor(sibling, parent->color);
                SetColor(parent, COLOR_BLACK);
                if(node->temp == true){QuickRemove(node);}
                else{SetColor(node,COLOR_BLACK);}
                return;
            }
            // LR case
            else if(IsLeftChild(sibling) && GetColor(rightChild) == COLOR_RED){
                LeftRotate(sibling);
                RightRotate(parent);
                SetColor(rightChild,parent->color);
                SetColor(parent,COLOR_BLACK);
                if(node->temp == true){QuickRemove(node);}
                else{SetColor(node,COLOR_BLACK);}
                return;
            }
            // RR CASE
            if(!IsLeftChild(sibling) && GetColor(rightChild) == COLOR_RED){
                LeftRotate(parent);
                SetColor(rightChild, sibling->color);
                SetColor(sibling, parent->color);
                SetColor(parent, COLOR_BLACK);
                if(node->temp == true){QuickRemove(node);}
                else{SetColor(node,COLOR_BLACK);}
                return;
            }
            // RL CASE
            else if(!IsLeftChild(sibling) && GetColor(leftChild) == COLOR_RED){
                RightRotate(sibling);
                LeftRotate(parent);
                SetColor(leftChild,parent->color);
                SetColor(parent,COLOR_BLACK);
                if(node->temp == true){QuickRemove(node);}
                else{SetColor(node,COLOR_BLACK);}
                return;
            }
        }
    }
    // Red sibling case
    else{
        SetColor(parent, COLOR_RED);
        SetColor(sibling, COLOR_BLACK);
        if(IsLeftChild(sibling)){RightRotate(parent);}
        else{LeftRotate(parent);}
        FixDB(node);
    }
    return;
}