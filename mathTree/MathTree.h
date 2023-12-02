//
// Created by ymher on 14.11.2023.
//

#ifndef TEPLABY_MATHTREE_H
#define TEPLABY_MATHTREE_H

#include <iostream>
#include <set>
#include <vector>

class MathTree{
private:
    enum Operations{PLUS, MINUS, DIV, MULT, SIN, COS, NIL};
    class Node{
    public:
        std::vector<Node*> nodes;
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
        ~Node(){
            while (!nodes.empty()){
                Node* current = nodes.front();
                nodes.erase(nodes.begin());
                delete current;
            }
        }
    };
    Node* root;
    std::set<Node*> vars;

    void enterFormula(std::string formula);
    void printVars();
    float compile();
    void join();
    void printTree(Node* root);

    bool isFormulaCorrect(std::string formula);
    void createTree(std::string formula);
    void clearTree();
    std::vector<std::string> splitString(std::string formula);
    Node* createHelper(std::vector<std::string> *elements);
    bool isStringANumber(std::string string);
public:
    void menu();
};

void mt_test();

#endif //TEPLABY_MATHTREE_H
