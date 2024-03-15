#include "Tree.h"
#include "Node.h"
#include <iostream>

using namespace std;

Tree::Tree() {
    root = nullptr;
}

Tree::~Tree()
{
    //utilize the recursive delete function to delete all nodes
    delete recurDelete(root);
}

Node * Tree::recurDelete(Node *node)
{
    if (node != nullptr)
    {
        //recursively deletes left, middle, and right children if they aren't nullptrs
        delete recurDelete(node->left);
        delete recurDelete(node->middle);
        delete recurDelete(node->right);
    }

    return node;
}

Node* Tree::getLeftsibling(Node* tree){
    //if node is the right child of the parent, return the middle child
    if(tree == tree->parent->right){
        return tree->parent->middle;
    }
    //if node is the middle child of the parent, return the left child
    else if(tree == tree->parent->middle){
        return tree->parent->left;
    }
    //if node is the left child of the parent, return nullptr
    else{
        return nullptr;
    }
}

Node* Tree::getRightsibling(Node* tree){
    //if node is the left child of the parent, return the middle child
    if(tree == tree->parent->left){
        return tree->parent->middle;
    }
    //if node is the middle child of the parent, return the right child
    else if(tree == tree->parent->middle){
        return tree->parent->right;
    }
    //if node is the right child of the parent, return nullptr
    else{
        return nullptr;
    }
}

string Tree::getParentKeyLeftOf(Node* tree){
    //if node is the right child of the parent, return the large key
    if(tree == tree->parent->right){
        return tree->parent->large;
    }
    //if node is the middle child of the parent, return the small key
    else if(tree == tree->parent->middle){
        return tree->parent->small;
    }
    //if node is the left child of the parent, return an empty string
    else{
        return "";
    }

}

Node* Tree::nodeSearch(const string& key) const{
    //start at the root
    Node* cur = root;
    while(cur != nullptr){
        //node found, return pointer to this node
        if(key == cur->small || key == cur->large){
            return cur;
        }
        //node not found, search
        else
        {   
            //cases if cur has 2 keys
            if(cur->numKeys == 2){
                //go left
                if(key < cur->small){
                    cur = cur->left;
                }
                //go middle
                else if(key > cur->small && key < cur->large){
                    cur = cur->middle;
                }
                //go right
                else
                {
                    cur = cur->right;
                }
            }
            //cur only has one key
            else
            {   //go left
                if(key < cur->small){
                    cur = cur->left;
                }
                //go right
                else
                {
                    cur = cur->middle;
                }
            }
        }
    }
    return nullptr;
}

void Tree::shiftUp(Node *tree){
    //The tree parameter above needs to be moved into it's parent and the tree only has one key
    //If there is no parent, don't run the function
    if(tree->parent != nullptr){
        Node* parent = tree->parent;
        if(parent->numKeys == 1){
            //There's two subcases for this case, node coming form left or node coming from right of parent
            if(tree == parent->left){//node is coming from left
                parent->large = parent->small; // shift key in parent to take the "large" spot
                parent->small = tree->small;

                //Here we shift the pointers from the children to the parent. Since it is coming from the left, the node will look like it is sitting right next 
                parent->left = tree->left;
                parent->right = parent->middle;
                parent->middle = tree->middle;
                //increment the numKeys
                parent->numKeys = 2;
            }
            else
            //node is coming from the right of the parent(middle pointer)
            {
                //adding key to parent's large spot
                parent->large = tree->small;

                //Here we shift pointers from children to parent. Since it's coming from the right, the node will look like it is sitting directly right of the parent
                parent->middle = tree->left;
                parent->right = tree->middle;
                parent->numKeys = 2;
            }
            //change the parent pointers of tree's children
            tree->left->parent = parent;
            tree->middle->parent = parent;
            //tree is no longer needed, get rid of them 
            //             ⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢠⣾⢻⠋⡏⢛⢹⢹⢦⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
            // ⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⣀⣠⠤⠤⠤⠤⣄⣀⣀⠀⠀⢸⣿⢸⣀⡇⢸⣾⢸⢸⡇⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
            // ⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢠⡾⠋⠀⠀⠀⠀⠀⠀⠀⠀⠈⠉⠒⣮⣿⠛⠉⠉⠉⠉⢻⠟⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
            // ⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⡏⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢠⣶⠟⣩⣿⣶⢰⣖⠒⣶⣼⣀⣀⣠⣤⣄⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
            // ⠀⠀⠀⠀⠀⠀⠀⠀⠀⢺⠀⠀⠀⠀⠀⠀⣴⣖⣲⣦⠤⣿⣿⡞⠁⠙⠛⠛⢻⡿⠁⡼⠋⢀⣈⡬⠶⠛⠋⠉⠉⠉⠉⠉⠉⢉⣩⠽⠛⣛⣽⠿⣟⣛⣛⣛⡛⠲⢤⣀⠀⠀⠀⠀⠀
            // ⠀⠀⠀⠀⢀⣠⠤⣤⣀⡈⣇⠀⠀⠀⠀⢸⣿⣿⠶⠾⣿⡿⠋⢹⠀⠀⠀⣠⡏⢀⣞⡵⢞⡟⠁⠀⠀⠀⠀⠀⠀⠀⠀⣠⠖⠋⣠⢶⣻⠵⡞⣏⠁⠀⠀⠀⠉⠙⠲⣌⡑⢦⡀⠀⠀
            // ⠀⠀⠀⣼⢿⠵⢶⣼⣷⠛⠛⣧⣄⠀⠀⢸⣇⣿⣗⣊⣿⠖⠀⢸⠀⢶⢯⣭⠟⢋⡞⢠⠟⠀⠀⠀⠀⠀⠀⠀⠀⢀⡞⠁⣠⠞⡵⢻⡁⠀⢹⡼⡄⠀⠀⠀⠀⠀⠀⠀⠙⢦⡹⣄⠀
            // ⠀⠀⠀⣿⢸⠀⢾⠁⠈⣳⠞⢛⣿⣟⠶⣿⣿⣻⠿⢽⣿⣦⣀⡼⠀⢸⠶⡇⠀⢸⠀⣼⠀⠀⠀⠀⠀⠀⠀⠀⣠⠟⢀⡜⢡⡞⠁⠀⡇⠀⠀⡇⡇⠀⠀⠀⠀⠀⠀⠀⠀⠀⢳⡹⡄
            // ⠀⠀⠀⠙⠛⠒⢚⣷⠞⣡⢞⡉⠀⠹⣿⣮⠙⣿⠯⠟⠉⢹⡿⣤⣀⠸⡶⣧⣀⡸⡄⢹⠀⠀⠀⠀⠀⠀⠀⢠⡟⠀⡼⢠⠏⠀⠀⠀⣷⠀⠀⡇⡇⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢃⢻
            // ⠀⢀⣤⠶⢶⣴⠋⣠⢾⡇⠹⣷⣄⠀⠉⠻⣷⡼⣳⣤⣴⣿⣷⡇⢨⣽⣿⣿⠿⣝⣿⣾⣆⠀⠀⠀⠀⠀⠀⢸⠁⠀⡇⡞⠀⠀⠀⢰⠃⠀⢸⢳⠇⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢸⢸
            // ⠀⡸⠹⢾⣖⣛⣿⣅⠀⢧⠀⠈⢻⣧⡀⠀⠘⠻⣟⣻⣿⣿⣿⣿⣿⣿⣿⣿⣦⣬⡿⣿⣿⣦⡀⠀⠀⠀⠀⠘⡆⠀⡇⣇⠀⠀⣠⠋⠀⢠⢏⡟⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢸⢸
            // ⣶⠃⠀⠈⠋⢻⢴⣗⣻⣮⣷⡀⠀⢹⣟⣦⡄⠀⠈⠛⠉⡹⠉⠈⠓⢿⡿⣿⣿⣿⠷⣄⣹⡆⠙⠲⣄⡀⠀⠀⢿⠀⢧⠸⡶⠚⠁⢀⡴⢣⠞⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⡀⢸
            // ⠛⢦⡀⠀⠀⠀⢸⠋⠀⠀⢈⡿⡄⢸⣺⡀⠀⠀⠀⠀⢠⡇⡾⣦⡀⠀⠉⢿⣿⠻⣷⣮⠟⢁⣀⣀⣨⣿⣷⣤⡈⢧⠈⣇⠳⣤⠖⣩⠴⠃⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠠⢁⠇
            // ⠀⠀⠙⢦⡀⠀⡏⠀⠀⠀⡼⠀⠙⣎⠙⣿⣾⣷⡀⠀⠘⢧⢿⣻⡇⢠⣄⠘⠿⠿⠻⠿⣼⡟⢷⣿⣿⣾⠯⠿⠋⠛⠧⣈⢦⡙⣏⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣡⠊⠀
            // ⠀⠀⠀⠀⠈⠻⠥⠤⠤⠼⠁⠀⠀⠘⢿⣿⡿⣏⣹⣆⠀⠀⠻⣍⠀⢸⣏⠳⡄⠀⠀⠀⠀⠑⢤⣿⣙⣟⣄⠀⠀⢠⡤⠬⠿⢿⣌⡓⢦⣄⡀⠀⠀⠀⠀⠀⠀⠀⣀⠴⣣⠞⠁⠀⠀
            // ⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢸⡄⠈⢠⡾⣷⡀⠀⠈⠳⣜⢟⣾⠀⢰⣄⡀⠀⣴⣾⢿⣽⡿⣞⣆⠀⠀⢻⡋⠉⠙⢧⢻⡳⢦⣉⡑⠲⠶⠶⠶⢒⣫⠵⠛⠁⠀⠀⠀⠀
            // ⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠸⡇⠀⠀⠳⣝⢿⣦⠀⠀⠈⠳⣍⠀⣞⡇⢹⣶⡏⡇⠀⠙⢿⣹⣜⢦⠀⠀⠳⣄⣀⣬⣷⣷⡄⢳⡌⠉⠉⠉⠉⠁⠀⠀⠀⠀⠀⠀⠀⠀
            // ⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣧⠀⠀⠀⠈⢦⡙⣷⠀⠀⠀⠈⠳⣝⠓⣸⢠⢇⡇⠀⠀⠀⠀⠹⣎⢧⠀⠀⠻⣄⣀⣀⣹⡿⡄⠹⡄⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
            // ⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢸⣆⠀⠀⠀⠀⢻⠃⠀⠀⠀⠀⠀⠈⠣⡍⢸⢸⠀⠀⠀⠀⠀⠀⠘⣆⢣⡀⠀⠙⣧⠴⠛⢣⠘⣄⠙⣆⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
            // ⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢸⠘⣆⠀⠀⠀⢸⠀⠀⠀⠀⠀⠀⠀⠀⠈⠻⣼⡀⠀⠀⠀⠀⠀⢀⡼⣶⠗⠦⡄⠘⣆⠀⠀⣳⣸⡆⠘⣦⠀⣀⣀⣀⠀⠀⠀⠀⠀⠀
            // ⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢸⠀⠘⣦⠀⠀⠹⡄⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠙⣄⠀⠀⠀⢀⡏⢀⠘⡆⠀⠹⣶⢮⡉⠉⠀⠀⠀⠀⠈⢯⠉⠙⣎⢻⡉⠑⢦⠀⠀
            // ⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢸⠀⢸⠋⢧⠀⠀⠹⣆⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⢦⡀⠀⢸⢸⠋⡇⣷⠀⠀⣏⡇⣷⠤⣤⡤⠤⠤⠤⢤⡇⠀⠸⡄⢇⠀⠸⡄⠀
            // ⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢸⠀⢸⠀⠈⣧⠀⠀⢹⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠹⣄⠈⡞⠦⠇⡿⠀⠀⡿⡇⣹⣶⣾⡷⠖⠲⣶⣟⠀⠀⠀⡇⢸⠀⢠⠇⠀
            // ⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠘⡇⣸⠀⠀⡼⢳⡀⠈⡇⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⢦⡻⣄⣠⡇⣀⡴⠃⡇⢻⠀⠀⠳⣤⡤⠇⠈⢦⡀⠀⡇⢸⣧⠞⠀⠀
            // ⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢻⠀⠀⠀⡇⠀⢳⡀⢷⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠻⣄⠉⠉⠁⡀⠀⡇⢈⣀⣁⡀⢉⣀⣉⣉⣉⣷⡀⡇⢸⡇⠀⠀⠀
            // ⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⡇⠀⠀⡇⠀⠀⣿⡜⣆⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⢦⡀⠀⠙⢦⡇⠘⠒⠒⠒⠒⠒⠒⠒⠒⠺⠟⠃⢸⣇⠀⠀⠀
            // ⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢹⡀⢰⠇⠀⠀⢸⠻⡜⣧⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠱⣄⠀⠀⠉⠉⠉⠉⠉⠉⠉⠉⠉⠛⠛⠛⠉⠉⠁⠀⠀⠀
            // ⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣿⠉⠀⠀⠀⢸⠂⠙⡎⠷⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⢷⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⡀⣀⣀⣀⡈⠂
            delete tree;
        }
        //recursive case
        else if(parent->numKeys == 2){
            //There are three subcases, whether the node's string is smaller, larger or in between the parent's two strings
            if(tree == parent->left){ // means the node is the left child of parent
                //newLarge takes parent's large string, middle child, and right child
                //Don't forget to change parent pointers
                Node* newLarge = new Node(parent->large, parent);
                newLarge->left = parent->middle;
                newLarge->left->parent = newLarge;
                newLarge->middle = parent->right;
                newLarge->middle->parent = newLarge;
                parent->middle = newLarge;
                parent->right = nullptr;
                parent->large = "";
                parent->numKeys = 1;
                shiftUp(parent);
            }
            else if(tree == parent->right) // node is coming from the right
            {   
                //newSmall takes parent's small string, left child, and right child.
                //Don't forget to change parent pointers
                Node* newSmall = new Node(parent->small,parent);
                newSmall->left = parent->middle;
                newSmall->left->parent = newSmall;
                newSmall->middle = parent->middle;
                newSmall->middle->parent = newSmall;
                parent->left = newSmall;
                parent->middle = tree;
                parent->right = nullptr;
                parent->small = parent->large;
                newSmall->parent = parent;
                parent->numKeys = 1;
                shiftUp(parent);
            }
            else //Node coming from the middle
            {
                Node* newSmall = new Node(parent->small,parent);
                newSmall->left = parent->left;
                newSmall->left->parent = newSmall;
                newSmall->middle = tree->left;
                newSmall->middle->parent = newSmall;

                Node* newLarge = new Node(parent->large,parent);
                newLarge->left = tree->middle;
                newLarge->left->parent = newLarge;
                newLarge->middle = parent->right;
                newLarge->middle->parent = newLarge;

                //now change the child pointers of parent, and replace parent's key with tree's key
                parent->left = newSmall;
                parent->middle = newLarge;
                parent->right = nullptr;
                parent->small = tree->small;
                parent->large = "";
                parent->numKeys = 1;

                //Tree is now again no longer needed
                delete tree;
                shiftUp(parent);
            }
        }
    }
}

void Tree::insert(const string &key){
    //edge case:tree is empty
    if(root == nullptr){
        root = new Node(key,nullptr);
    }
    else
    {
        Node* target = root;
        //because of B-tree properties, a node must have children on both sides
        //or have no children at all, which means if I find a node with no left child, that means there isn't a right child either and thus a leaf node
        while(target->left != nullptr)
        {
            //In this case, we have to see if we go left, right, or middle
            if(target->numKeys == 2){
                //we go left
                if(key < target->small){
                    target = target->left;
                }
                //we go middle
                else if(key > target->small && key < target->large){
                    target = target->middle;
                }
                //go right
                else
                {
                    target = target->right;
                }
                
            }
            //if this else activates, it means target only has one key
            else
            {   
                //we go left
                if(key < target->small){
                    target = target->left;
                }
                //we go right(middle ptr)
                else
                {
                    target = target->middle;
                }
            }
        }
        //cases if the target leaf node has 2 keys
        if(target->numKeys == 2){
            string small;
            string middle;
            string large;
            //this case means key is the smallest
            if(key < target->small){
                small = key;
                middle = target->small;
                large = target->large;
            }
            //this case means key is in the middle
            else if(key > target->small && key < target-> large){
                small = target->small;
                middle = key;
                large = target->large;
            }
            //this case means key is the largest
            else
            {
                small = target->small;
                middle = target->large;
                large = key;
            }

            //now we split up the full leaf node into 3 separate nodes
            Node* smallNode = new Node(small,target);
            Node* largeNode = new Node(large,target);
            
            target->small = middle;
            target->large = "";
            target->left = smallNode;
            target->middle = largeNode;
            target->numKeys = 1;
            target->right = nullptr;//redundant but just to be safe
            //shifts up the middle node to fix the temporarily broken b tree rules
            shiftUp(target);
        }
        //this case means that the node has only one string and we can just insert it without shifting any nodes around
        else
        {
            if(key < target->small){
                target->large = target->small;
                target->small = key;
            }
            else
            {
                target->large = key;
            }
            target->numKeys = 2;
        }
    }
}

void Tree::remove(const string& key){
    //zybooks only tests cases of height 1
    Node* target = nodeSearch(key);
    //edge case:target is root
    if(target == root){
        //case if root has only 1 key
        if(root->numKeys == 1 && root->left == nullptr){
            delete root;
            root = nullptr;
        }
        //case if root has 2 keys
        else if(root->numKeys == 2 && root->left == nullptr)
        {   //key is the small key
            if(key == root->small){
                root->small = root->large;
                root->large = "";
                root->numKeys = 1;
            }
            //key is the large key
            else
            {
                root->large = "";
                root->numKeys = 1;
            }
        }
        else
        {
            //case if there are only 3 nodes in the tree, and removing one requires the fusing of a node
            root->small = root->left->small;
            root->large = root->middle->small;
            root->numKeys = 2;
            delete target->left;
            delete target->middle;
            delete target->right;
            target->left = nullptr;
            target->middle = nullptr;
            target->right = nullptr;
        }
    }
    //zybooks only tests cases with height 1
    //cases if target isn't the root
    else
    {   
        //case if target has 2 keys
        //case if target is a leaf node with 2 keys
        if(target->numKeys == 2 && target->left == nullptr)
        {
            //case if key is the small key
            if(key == target->small){
                target->small = target->large;
                target->large = "";
                target->numKeys = 1;
            }
            //case if key is the large key
            else
            {
                target->large = "";
                target->numKeys = 1;
            }
        }
        else if(target->parent->numKeys == 1 && target->numKeys == 1)
        {
            //case if target is the left child of the parent
            if(target == target->parent->left){
                //if sibling has 2 keys
                Node* rightSibling = getRightsibling(target);
                if(rightSibling->numKeys == 2){
                    string parentTarget = getParentKeyLeftOf(rightSibling);
                    target->small  = parentTarget;
                    target->parent->small = rightSibling->small;
                    rightSibling->small = rightSibling->large;
                    rightSibling->large = "";
                    rightSibling->numKeys = 1;
                }
                //if sibling has 1 key
                else
                {
                    target->parent->large = rightSibling->small;
                    target->parent->right = nullptr; // might be redundant
                    target->parent->numKeys = 2;
                    target->parent->left = nullptr;
                    target->parent->middle = nullptr;
                    target->parent->right = nullptr; // might be redundant
                    delete rightSibling;
                    delete target;
                }
            }
            //case if target is the right (middle) child of the parent
            else if(target == target->parent->middle){
                //if sibling has 2 keys
                Node* leftSibling = getLeftsibling(target);
                if(leftSibling->numKeys == 2){
                    string targetParent = getParentKeyLeftOf(target);
                    target->small = targetParent;
                    target->parent->small = leftSibling->large;
                    leftSibling->large = "";
                    leftSibling->numKeys = 1;
                }
                //if sibling has 1 key
                else
                {
                    target->parent->large = target->parent->small;
                    target->parent->small = leftSibling->small;
                    target->parent->numKeys = 2;
                    target->parent->left = nullptr;
                    target->parent->middle = nullptr;
                    target->parent->right = nullptr; // might be redundant
                    delete leftSibling;
                    delete target;
                }
            }
        }
        //cases if it has one key and parent has 2 keys
        else if(target->numKeys == 1 && target->parent->numKeys == 2)
        {
            //subcases include whether or not it's sibling has 2 keys, or sibling has 1 key
            Node* rightSibling = getRightsibling(target);
            Node* leftSibling = getLeftsibling(target);
            //if right sibling has 2 keys
            if(rightSibling != nullptr && rightSibling->numKeys == 2){
                string parentTarget = getParentKeyLeftOf(rightSibling);
                target->small  = parentTarget;
                //check if target is the left child of the parent
                if(target == target->parent->left){
                    target->parent->small = rightSibling->small;
                    rightSibling->small = rightSibling->large;
                }
                //else the target is the middle child of the parent
                else
                {
                    target->parent->large = rightSibling->small;
                    rightSibling->small = rightSibling->large;
                }
                rightSibling->large = "";
                rightSibling->numKeys = 1;
            }
            //if left sibling has 2 keys
            else if(leftSibling != nullptr && leftSibling->numKeys == 2)
            {
                string parentTarget = getParentKeyLeftOf(target);
                //if left sibling has 2 keys
                target->small = parentTarget;
                //check if target is the right child of the parent
                if(target == target->parent->right){
                    target->parent->large = leftSibling->large;
                    leftSibling->large = "";
                }
                //else the target is the middle child of the parent
                else
                {
                    target->parent->small = leftSibling->large;
                    leftSibling->large = "";
                }
                leftSibling->numKeys = 1;
            }
            //if we get here, that means neither sibling has 2 keys
            else
            {   
                Node* leftSibling = getLeftsibling(target);
                Node* rightSibling = getRightsibling(target);
                //if target is left child of parent
                if(target == target->parent->left){
                    target->parent->large = rightSibling->small;
                    target->parent->left = nullptr;
                    target->parent->middle = nullptr;
                    target->parent->right = nullptr; // might be redundant
                    delete target;
                    delete rightSibling;
                }
                //case if target is the middle child
                else
                {
                    target->parent->large = target->parent->small;
                    target->parent->small = leftSibling->small;
                    target->parent->left = nullptr;
                    target->parent->middle = nullptr;
                    target->parent->right = nullptr;//might be redundant
                    delete target;
                    delete leftSibling;
                }
            }
        }
    }
}

bool Tree::search(const string &key) const {
    if(root != nullptr){
        return search(root, key);
    }
    return false;
}

bool Tree::search (Node* point, const string &key) const{
    //start at the point, won't execute if point is nullptr
   if (point != nullptr) {
        Node* cur = point;
        //keep going until we find the key or we reach a nullptr
        while(cur != nullptr)
        {
            //key is found
            if(key == cur->small || key == cur->large){
                return true;
            }
            //key is smaller than this node
            if (key < cur->small) {
                cur = cur->left;
            }
            //key is larger than this node or in between the two keys
            else if (cur->numKeys == 1 || key < cur->large) {
                cur = cur->middle;
            }
            //cur is larger than both keys
            else if (key > cur->large) {
                cur = cur->right;
            }
        }
   }
   return false;
}

void Tree::inOrder( ) const{
    inOrder(root);
}

void Tree::inOrder(Node *tree) const{
    if (tree != nullptr) {
        inOrder(tree->left);
        cout << tree->small << ", ";
        inOrder(tree->middle);
        //will print large key if node has 2 keys
        if(tree->numKeys == 2){
            cout << tree->large << ", ";
            inOrder(tree->right);
        }
    }
}

void Tree::preOrder( ) const{
    preOrder(root);
}

void Tree::preOrder(Node *tree) const{
    if (tree != nullptr) {
        //case if node has 2 keys
        if(tree->numKeys == 2){
            cout << tree->small << ", ";
            preOrder(tree->left);
            cout << tree->large << ", ";
            preOrder(tree->middle);
            preOrder(tree->right);
        }
        //case if node has 1 key
        else
        {
            cout << tree->small << ", ";
            preOrder(tree->left);
            preOrder(tree->middle);
        }
    }
}

void Tree::postOrder( ) const{
    postOrder(root);
}

void Tree::postOrder(Node *tree) const{
    if (tree != nullptr) {
        //case if node has 2 keys
        if(tree->numKeys == 2){
            postOrder(tree->left);
            postOrder(tree->middle);
            cout << tree->small << ", ";
            postOrder(tree->right);
            cout << tree->large << ", ";
        }
        //case if node has 1 key
        else
        {
            postOrder(tree->left);
            postOrder(tree->middle);
            cout << tree->small << ", ";
        }
    }
}