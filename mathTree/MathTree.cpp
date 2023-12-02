//
// Created by ymher on 14.11.2023.
//
#include "MathTree.h"

#include <utility>
#include <sstream>

void mt_test(){
    MathTree tree;
    tree.enterFormula("+ * 5 sin x * + a b 8 + 2 3");
    tree.printTree(tree.root);
}

void MathTree::enterFormula(std::string formula) {

    createTree(formula);
}

void MathTree::printVars() {

}

float MathTree::compile() {
    return 0;
}

void MathTree::join() {

}

void MathTree::printTree(Node* root) {
    if (root->op != NIL){
        switch (root->op) {
            case PLUS:
                std::cout << "+ ";
                break;
            case MINUS:
                std::cout << "- ";
                break;
            case DIV:
                std::cout << "/ ";
                break;
            case MULT:
                std::cout << "* ";
                break;
            case SIN:
                std::cout << "sin ";
                break;
            case COS:
                std::cout << "cos ";
                break;
            case NIL:
                break;
        }
    } else if (root->variable){
        std::cout << root->name << " ";
    } else{
        std::cout << root->value << " ";
    }
    for (int i = 0; i < root->nodes.size(); ++i) {
        printTree(root->nodes.at(i));
    }
}

bool MathTree::isFormulaCorrect(std::string formula) {
    return true;
}

void MathTree::createTree(std::string formula) {
    std::vector<std::string> elements = splitString(formula);

    root = createHelper(&elements);

    while (!elements.empty()){
        root->nodes.push_back(createHelper(&elements));
    }
}

MathTree::Node *MathTree::createHelper(std::vector<std::string> *elements) {
    std::string current = elements->front();
    elements->erase(elements->begin());
    Node* node;
    if (current == "+" || current == "-" || current == "*" || current == "/" || current == "sin" || current == "cos"){
        if (current == "+") node = new Node(Operations(PLUS));
        if (current == "-") node = new Node(Operations(MINUS));
        if (current == "*") node = new Node(Operations(MULT));
        if (current == "/") node = new Node(Operations(DIV));
        if (current == "sin") node = new Node(Operations(SIN));
        if (current == "cos") node = new Node(Operations(COS));

        node->nodes.push_back(createHelper(elements));
        if (current == "+" || current == "-" || current == "*" || current == "/")
            node->nodes.push_back(createHelper(elements));


    } else if (isStringANumber(current)){
        node = new Node(std::stof(current));
    } else {
        node = new Node(current);
    }
    return node;
}

bool MathTree::isStringANumber(std::string string) {
    for (int i = 0; i < string.size(); ++i) {
        if (string.at(i) > '9' || string.at(i) < '0' || string.at(i) != '.')
            return false;
    }
    return true;
}

void MathTree::menu() {

}

void MathTree::clearTree() {
    delete root;
}

std::vector<std::string> MathTree::splitString(std::string formula) {
    std::string token;
    std::stringstream ss(formula);
    std::vector<std::string> v;
    while (getline(ss, token, ' ')) {
        v.push_back(token);
    }
    return v;
}

