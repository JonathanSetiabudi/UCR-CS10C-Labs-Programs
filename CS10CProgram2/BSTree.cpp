#include "BSTree.h"

#include <iostream>
#include <stdexcept>

using namespace std;

void BSTree::insert(const string& key) {
  // Edge case:  The tree is empty
  if(root == nullptr) {
    root = new Node(key);
    //end function once new node is inserted
    return;
  }
  // Start at the root
  Node* currNode = root;
  while(currNode != nullptr) {
    // if the key is less than the current node's key, go left
    if(key < currNode->key) {
      //if there is a hole in the tree, insert the new node
      if(currNode->left == nullptr) {
        currNode->left = new Node(key);
        //end the function once new node is inserted
        return;
      }
      //will move on further left if no hole is found
      currNode = currNode->left;
    // if the key is greater than the current node's key, go right
    } else if(key > currNode->key) {
      //if there is a hole in the tree, insert the new node
      if(currNode->right == nullptr) {
        currNode->right = new Node(key);
        //end the function once new node is inserted
        return;
      }
      currNode = currNode->right;
    //if the key is equal to the current node's key, increment the count
    //only executes if other options are not met meaning there is a node with the same key
    } else {
      currNode->count++;
      return;
    }
  }
}
bool BSTree::search(const string& key) const {
  Node* currNode = root;
  while(currNode != nullptr) {
    //if the key is less than the current node's key, go left
    if(key < currNode->key) {
      currNode = currNode->left;
    //if the key is greater than the current node's key, go right
    } else if(key > currNode->key) {
      currNode = currNode->right;
    //if the key is equal to the current node's key, return true
    } else {
      return true;
    }
  }
  //if we reach here, it means the key was not found
  return false;
}

string BSTree::largest() const {
  // Edge case: Tree is empty
  if(root == nullptr) {
    return "";
  }
  //start at the root
  Node* currNode = root;
  //keep going right until there are no more right nodes
  while(currNode->right != nullptr) {
    currNode = currNode->right;
  }
  //once we reach here, it means we are at the furthest right we can possibly be
  //return the key of the current node
  return currNode->key;
}

string BSTree::smallest() const {
  // Edge case: Tree is empty
  if(root == nullptr) {
    return "";
  }
  //start at the root
  Node* currNode = root;
  //keep going left until there are no more left nodes
  while(currNode->left != nullptr) {
    currNode = currNode->left;
  }
  //once we reach here, it means we are at the furthest left we can possibly be
  //return the key of the current node
  return currNode->key;
}

int BSTree::height(const string& key) const {
  // First find the node with this key, then run "height_of" to get
  // the height that zybooks wants
  Node* currNode = root;
  while(currNode != nullptr) {
    //if the key is less than the current node's key, go left
    if(key < currNode->key) {
      currNode = currNode->left;
    //if the key is greater than the current node's key, go right
    } else if(key > currNode->key) {
      currNode = currNode->right;
    //if the key is equal to the current node's key, return true
    } else {
      return height_of(currNode);
    }
  }
  //if we reach here, it means the key was not found
  return -1;
}

void BSTree::preOrder() const {
  preOrder(root);
}

void BSTree::postOrder() const {
  postOrder(root);
}

void BSTree::inOrder() const {
  inOrder(root);
}

void BSTree::remove(const string& key) {
  remove(nullptr, root, key);
}

void BSTree::remove(Node* parent, Node* tree, const string& key) {
  //while loop to find where the node with key is
  while(tree != nullptr) {
    //if the key is less than the current node's key, go left
    if(key < tree->key) {
      parent = tree;
      tree = tree->left;
    //if the key is greater than the current node's key, go right
    }else if(key > tree->key) {
      parent = tree;
      tree = tree->right;
    //this only runs if we find the node with the key
    }else if(tree->key == key){
      //if count is greater than 1, decrement count and return
      if(tree->count > 1) {
        tree->count--;
        return;
      }
      //CASES FOR IF COUNT IS 1
      //case if the node has no children
      else if(tree->left == nullptr && tree->right == nullptr){
        //if parent is nullptr, it means we are removing the root
        if(tree == root) {
          delete root;
          root = nullptr;
          return;
        }
        //if the node is the left child, delete and set left to nullptr
        else if(parent->left == tree) {
          delete tree;
          parent->left = nullptr;
          return;
        }
        //if the node is the right child, delete and set right to nullptr
        else if(parent->right == tree) {
          delete tree;
          parent->right = nullptr;
          return;
        }
      }
      else if(tree->left != nullptr) {
        //node to be removed/changed
        Node* shapeShifter = tree;
        Node* parentOfLargest = tree;
        Node* largest = tree->left;
        //get the largest key in the left subtree
        while(largest->right != nullptr) {
          parentOfLargest = largest;
          largest = largest->right;
        }
        //shapeShifter takes the place of the node to be removed
        shapeShifter->key = largest->key;
        shapeShifter->count = largest->count;
        //change node to be removed to have count 1 so it will actually be removed
        largest->count = 1;
        //recursively remove the node that was moved
        remove(parentOfLargest, largest, largest->key);
        return;
      }
      else if(tree->right != nullptr) {
        //node to be removed/changed
        Node* shapeShifter = tree;
        Node* parentOfSmallest = tree;
        Node* smallest = tree->right;
        //get the smallest key in the right subtree
        while(smallest->left != nullptr) {
          parentOfSmallest = smallest;
          smallest = smallest->left;
        }
        //shapeShifter takes the place of the node to be removed
        shapeShifter->key = smallest->key;
        shapeShifter->count = smallest->count;
        //change node to be removed to have count 1 so it will actually be removed
        smallest->count = 1;
        //recursively remove the node that was moved
        remove(parentOfSmallest, smallest, smallest->key);
        return;
      }
    } 
  }
  if(tree == nullptr) {
    //if we reach here, it means the key was not found
    return;
  }
}



int BSTree::height_of(Node* tree) const {
  // Base case:  If the tree is empty, the height is -1
  if (tree == nullptr) {
    return -1;
  }
  //recursive cases
  int leftHeight = height_of(tree->left);
  int rightHeight = height_of(tree->right);
  return 1 + max(leftHeight, rightHeight);
}

void BSTree::preOrder(Node* tree) const {
  // print key, do left, do right
  if(tree == nullptr) {
    return;
  }
  cout << tree->key << "(" << tree->count << "), ";
  preOrder(tree->left);
  preOrder(tree->right);
}

void BSTree::postOrder(Node* tree) const {
  // do left, do right, print key
  if(tree == nullptr) {
    return;
  }
  postOrder(tree->left);
  postOrder(tree->right);
  cout << tree->key << "(" << tree->count << "), ";
}

void BSTree::inOrder(Node* tree) const {
  // do left, print key, do right
  if(tree == nullptr) {
    return;
  }
  inOrder(tree->left);
  cout << tree->key << "(" << tree->count << "), ";
  inOrder(tree->right);
}