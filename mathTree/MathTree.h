//
// Created by ymher on 14.11.2023.
//

#ifndef TEPLABY_MATHTREE_H
#define TEPLABY_MATHTREE_H

#include <iostream>
#include <set>

class MathTree{
private:
    enum Operations{PLUS, MINUS, DIV, MULT, SIN, COS, NIL};
    class Node{
    public:
        Node* left = nullptr;
        Node* right = nullptr;
        float value = 0;
        std::string name;
        bool variable = false;
        Operations op = NIL;
        explicit Node(std::string name){
            this->name = std::move(name);
            variable = true;
        }
        explicit Node(float val){
            value = val;
        }
        explicit Node(Operations op){
            this->op = op;
        }
    };
    Node root;
    std::set<Node*> vars;

    void enterFormula();
    void printVars();
    float compile();
    void join();
    void printTree();

    bool isFormulaCorrect(std::string);
    void createTree(std::string);
    void clearTree();
public:
    void menu();
};

#endif //TEPLABY_MATHTREE_H
