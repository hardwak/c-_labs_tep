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

    std::set<Node*> vars;


    void printVars();
    float compile();
    void join();

    void create(std::string formula);

    std::vector<std::string> splitString(std::string formula);
    Node* createHelper(std::vector<std::string> *elements);
    bool isStringANumber(std::string string);
public:
    void enterFormula(std::string formula);
    void menu();
    void print(Node* root);
    Node* root = nullptr;
    void clear();
};

void mt_test();

#endif //TEPLABY_MATHTREE_H
