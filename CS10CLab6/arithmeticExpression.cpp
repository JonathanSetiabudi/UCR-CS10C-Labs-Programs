#include <iostream>
#include <cstdlib>
#include <stack>
#include <fstream>
#include <sstream>

#include "arithmeticExpression.h"

using namespace std;

//contructor
arithmeticExpression::arithmeticExpression(const string &value):infixExpression(value),root(nullptr){}

void arithmeticExpression::buildTree(){
    //get the postfix string
    string postfix = infix_to_postfix();
    //declare a stack and pointers to TreeNodes
    stack<TreeNode*> s;
    TreeNode* t;
    TreeNode* t1;
    TreeNode* t2;
    //starting key
    char key = 'a';
    //for each character in the postfix string
    for(unsigned i = 0; i < postfix.size(); ++i){
        //if the character is an operator, create a new subtree with the operator as root/head
        //take top two nodes from the stack and attach to new substree and push it to the stack
        if(postfix.at(i) == '+' || postfix.at(i) == '-' || postfix.at(i) == '*' || postfix.at(i) == '/'){
            t = new TreeNode(postfix.at(i), key);
            t1 = s.top();
            s.pop();
            t2 = s.top();
            s.pop();
            t->right = t1;
            t->left = t2;
            s.push(t);
            key++;
        }
        //if the character is a regular operand, create a new node and push it to the stack
        else{
            t = new TreeNode(postfix.at(i), key);
            s.push(t);
            key++;
        }
    }
    //when we reach here, the stack should only have one node, the root
    root = s.top();
    //clear nodes from the stack
    s.pop();
}

int arithmeticExpression::priority(char op){
    int priority = 0;
    //Follows PEMDAS rules
    if(op == '('){
        priority =  3;
    }
    else if(op == '*' || op == '/'){
        priority = 2;
    }
    else if(op == '+' || op == '-'){
        priority = 1;
    }
    return priority;
}

//given to use from zybooks, no need to change or comment
//name is self-explanatory
string arithmeticExpression::infix_to_postfix(){
    stack<char> s;
    ostringstream oss;
    char c;
    for(unsigned i = 0; i< infixExpression.size();++i){
        c = infixExpression.at(i);
        if(c == ' '){
            continue;
        }
        if(c == '+' || c == '-' || c == '*' || c == '/' || c == '(' || c == ')'){ //c is an operator
            if( c == '('){
                s.push(c);
            }
            else if(c == ')'){
                while(s.top() != '('){
                    oss << s.top();
                    s.pop();
                }
                s.pop();
            }
            else{
                while(!s.empty() && priority(c) <= priority(s.top())){
                    if(s.top() == '('){
                        break;
                    }
                    oss << s.top();
                    s.pop();
                }
                s.push(c);
            }
        }
        else{ //c is an operand
            oss << c;
        }
    }
    while(!s.empty()){
        oss << s.top();
        s.pop();
    }
    return oss.str();
}


void arithmeticExpression::prefix(){
    prefix(root);
}

void arithmeticExpression::prefix(TreeNode *tree){
    if(tree != nullptr){//check if tree isn't empty, otherwise this causes a segmentation fault
        //print itself
        cout<<tree->data;
        //print left
        prefix(tree->left);
        //print right
        prefix(tree->right);
    }
}

void arithmeticExpression::infix(){
    infix(root);
}

void arithmeticExpression::infix(TreeNode *tree){
    if(tree != nullptr){//check if tree isn't empty, otherwise this causes a segmentation fault
        //check if it's an operator, if so, print a parenthesis
        if(tree->data == '+' || tree->data == '-' || tree->data == '*' || tree->data == '/'){
            cout<<"(";
        }
        //print left
        infix(tree->left);
        //print itself
        cout<<tree->data;
        //print right
        infix(tree->right);
        //check if it's an operator, if so, print a parenthesis
        if(tree->data == '+' || tree->data == '-' || tree->data == '*' || tree->data == '/'){
            cout<<")";
        }
    }
}

void arithmeticExpression::postfix(){
    postfix(root);
}

void arithmeticExpression::postfix(TreeNode *tree){
    if(tree != nullptr){//check if tree isn't empty, otherwise this causes a segmentation fault
        //print left
        postfix(tree->left);
        //print right
        postfix(tree->right);
        //print itself
        cout<<tree->data;
    }
}