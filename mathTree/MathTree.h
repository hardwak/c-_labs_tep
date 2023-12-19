//
// Created by ymher on 14.11.2023.
//

#ifndef TEPLABY_MATHTREE_H
#define TEPLABY_MATHTREE_H

#include <iostream>
#include <vector>

template<typename T>
class MathTree {
private:
    enum Operations {
        PLUS, MINUS, DIV, MULT, SIN, COS, NIL
    };

    class Node {
    public:
        Node *left = nullptr;
        Node *right = nullptr;
        T value;
        std::string name;
        bool variable = false;
        Operations op = NIL;

        explicit Node(T val) {
            value = val;
        }

        explicit Node(std::string name, bool isVar) {
            this->name = std::move(name);
            variable = isVar;
        }

        explicit Node(Operations op) {
            this->op = op;
        }

        ~Node() {
            if (left)
                delete left;
            if (right)
                delete right;
        }
    };

    Node *root = nullptr;
    std::vector<Node *> vars;

    void printVars();

    T compile(Node *root, std::vector<T> *values);

    void join(std::string formula);

    void clear();

    void print(Node *root);

    void create(std::string formula);

    bool empty();

    std::vector<std::string> splitString(std::string formula);

    Node *createHelper(std::vector<std::string> *elements);

    bool isStringANumber(std::string string);

    Node *findNodeInVectorByName(std::vector<Node *> *vector, std::string string);

    void precompile(std::string str);

    static std::string sGetKnownType();

public:
    void menu();


};

void mt_test();

#endif //TEPLABY_MATHTREE_H
