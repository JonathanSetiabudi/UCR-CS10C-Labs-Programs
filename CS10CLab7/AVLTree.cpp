#include "Node.h"
#include "AVLTree.h"

using namespace std;

AVLTree::AVLTree()
    : root(nullptr)
{}

AVLTree::~AVLTree() {
    // nodes recursively delete each other
    delete root;
}

int AVLTree::height(Node* node){
    if(node == nullptr){
        return -1;
    }
    else{
        //recursively find the height of the tree
        return max(height(node->left), height(node->right)) + 1;
    }
}

int AVLTree::balanceFactor(Node* target){
    if(target != nullptr){
        //left height - right height
        return height(target->left) - height(target->right);
    }
    return 0;
}

//SetChild will literally not work if the string is passed by reference
void AVLTree::SetChild(Node*parent, string whichChild, Node* child){
    //self explanatory
    if(whichChild == "left"){
        parent->left = child;
    }
    else if(whichChild == "right")
    {
        parent->right = child;
    }
    if(child != nullptr){
        child->parent = parent;
    }
}

void AVLTree::ReplaceChild(Node* parent, Node* currentChild, Node* newChild){
    if(parent->left == currentChild){
        //if the current child is the left child, replace it with the new child
        SetChild(parent, "left", newChild);
    }
    else if(parent->right == currentChild){
        //if the current child is the right child, replace it with the new child
        SetChild(parent, "right", newChild);
    }
}

void AVLTree::printBalanceFactors(){
    printBalanceFactors(root);
}

void AVLTree::printBalanceFactors(Node *tree){
    {
        // do left, print key, do right
        if(tree == nullptr) {
            return;
        }
        printBalanceFactors(tree->left);
        cout << tree->key << "(" << balanceFactor(tree) << "), ";
        printBalanceFactors(tree->right);
    }
}

void AVLTree::rotateLeft(Node* target){
    Node* rightLeftChild = target->right->left;
    if(target->parent != nullptr){
        //replace parent's child with the target's right child
        ReplaceChild(target->parent, target, target->right);
    }
    else
    {
        //change root and root's parent to nullptr
        root = target->right;
        root->parent = nullptr;
    }
    //changing around parent and child pointers using helper functions
    SetChild(target->right, "left", target);
    SetChild(target, "right", rightLeftChild);
}

void AVLTree::rotateRight(Node* target){
    Node* leftRightChild = target->left->right;
    if(target->parent != nullptr){
        //replace the parent's child with the target's left child
        ReplaceChild(target->parent, target, target->left);
    }
    else
    {   
        //change root nad root's parent to nullptr
        root = target->left;
        root->parent = nullptr;
    }
    //changing around parent and child pointers using helper functions
    SetChild(target->left, "right", target);
    SetChild(target, "left", leftRightChild);
}

void AVLTree::balance(Node* target){
    if(target != nullptr){
        //right heavy, rotate left
        if (balanceFactor(target) == -2) {
            if(balanceFactor(target->right) == 1) {
                // Double rotation case.
                rotateRight(target->right);
            }
            rotateLeft(target);
        }
        //left heavy, rotate right
        else if (balanceFactor(target) == 2) 
        {
            if (balanceFactor(target->left) == -1) {
                // Double rotation case.
                rotateLeft(target->left);
            }
            rotateRight(target);
        }       
    } 
}

void AVLTree::insert(const string &key) {
  // Edge case:  The tree is empty
  if(root == nullptr) {
    root = new Node(key, nullptr);
    //end function once new node is inserted
    return;
  }
  // Start at the root
  Node* currNode = root;
  while(currNode != nullptr) {
    // if the key is less than the current node's key, go left
    if(key < currNode->key){
      //if there is a hole in the tree, insert the new node
      if(currNode->left == nullptr) {
        currNode->left = new Node(key,currNode);
        while(currNode != nullptr){
            balance(currNode);
            currNode = currNode->parent;
        }
        //end the function once new node is inserted
        return;
      }
      //will move on further left if no hole is found
      currNode = currNode->left;
    // if the key is greater than the current node's key, go right
    } 
    else if(key > currNode->key) 
    {
      //if there is a hole in the tree, insert the new node
      if(currNode->right == nullptr) {
        currNode->right = new Node(key,currNode);
        while(currNode != nullptr){
            balance(currNode);
            currNode = currNode->parent;
        }
        //end the function once new node is inserted
        return;
      }
      currNode = currNode->right;
    } 
    //if the key is equal to the current node's key, increment the count
    //only executes if other options are not met meaning there is a node with the same key
    else
    {
      currNode->count++;
      return;
    }
  }
}

