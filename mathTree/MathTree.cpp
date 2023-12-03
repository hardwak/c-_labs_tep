//
// Created by ymher on 14.11.2023.
//
#include "MathTree.h"

#include <cmath>
#include <sstream>
#include <utility>

void mt_test(){
    MathTree tree;
    tree.create("+ * 5 cos x * + a b 8");
    std::vector<float> values;
    values.push_back(1);
    values.push_back(2.2);
    values.push_back(3.4);
    std::cout << tree.compile(tree.root, &values) << "\n";
    std::cout << "\n";
    tree.printVars();
    std::cout << "\n";
    tree.join("+ 5 1");
    tree.clear();
    tree.create("3 - 3 5.5");

}

void MathTree::printVars() {
    if (empty()){
        std::cout << "Tree is empty.\n";
        return;
    }

    if (vars.empty()){
        std::cout << "Tree dont have variables.\n";
        return;
    }

    std::cout << "Variables: ";
    for (int i = 0; i < vars.size(); ++i) {
        std::cout << vars.at(i)->name << " ";
    }
    std::cout << std::endl;
}

float MathTree::compile(Node* root, std::vector<float> *values) {
    if (empty()){
        std::cout << "Tree is empty.\n";
        return 0;
    }

    if (root->op != NIL){
        switch (root->op) {
            case PLUS:
                return compile(root->nodes.at(0), values) + compile(root->nodes.at(1), values);
            case MINUS:
                return compile(root->nodes.at(0), values) - compile(root->nodes.at(1), values);
            case DIV: {
                float num = compile(root->nodes.at(1), values);
                if (num == 0){
                    std::cout << "Division by 0 is not allowed!\n";
                    num = 1;
                }
                return compile(root->nodes.at(0), values) / num;
            }
            case MULT:
                return compile(root->nodes.at(0), values) * compile(root->nodes.at(1), values);
            case SIN:
                return std::sin(compile(root->nodes.at(0), values));
            case COS:
                return std::cos(compile(root->nodes.at(0), values));
            case NIL:
                break;
        }
    } else if (root->variable){
        float currVal = values->front();
        values->erase(values->begin());
        return currVal;
    } else{
        return root->value;
    }
    return 0;
}

void MathTree::join(std::string formula) {
    if (vars.empty()){
        std::cout << "Impossible to join another tree (no available variables)\n";
        return;
    }

    printVars();
    std::cout << "Choose one of the variables to replace (1-" << vars.size() << ")\n";

    int option;
    std::cin >> option;

    if (option > vars.size() || option < 1) {
        std::cout << "Incorrect number\n";
        return;
    }

    std::vector<std::string> elements = splitString(std::move(formula));
    delete vars.at(option - 1);
    *vars.at(option - 1) = *createHelper(&elements);

    std::cout << "New tree: ";
    print(root);
    std::cout << std::endl;
}

void MathTree::print(Node* root) {
    if (empty()){
        std::cout << "Tree is empty.\n";
        return;
    }

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
        print(root->nodes.at(i));
    }
}

void MathTree::create(std::string formula) {
    if (!empty()){
        std::cout << "Delete current tree before creating new.\n";
        return;
    }

    std::vector<std::string> elements = splitString(std::move(formula));

    root = createHelper(&elements);

    std::cout << "Created tree: ";
    print(root);
    std::cout << std::endl;

    if (!elements.empty()){
        std::cout << "Warning! Redundant elements was skipped: ";
        for (const auto & element : elements) {
            std::cout << element << " ";
        }
        std::cout << std::endl;
    }
}

MathTree::Node *MathTree::createHelper(std::vector<std::string> *elements) {
    std::string current = elements->front();
    elements->erase(elements->begin());
    Node *node;
    if (current == "+" || current == "-" || current == "*" || current == "/" || current == "sin" || current == "cos"){
        if (current == "+") node = new Node(Operations(PLUS));
        if (current == "-") node = new Node(Operations(MINUS));
        if (current == "*") node = new Node(Operations(MULT));
        if (current == "/") node = new Node(Operations(DIV));
        if (current == "sin") node = new Node(Operations(SIN));
        if (current == "cos") node = new Node(Operations(COS));

        if (elements->empty()){
            elements->emplace_back("1");
            std::cout << "Missing variable replaced with 1\n";
        }
        node->nodes.push_back(createHelper(elements));

        if (current == "+" || current == "-" || current == "*" || current == "/") {
            if (elements->empty()){
                elements->emplace_back("1");
                std::cout << "Missing variable replaced with 1\n";
            }
            node->nodes.push_back(createHelper(elements));
        }

    } else if (isStringANumber(current)){
        node = new Node(std::stof(current));
    } else {
        node = findNodeInVectorByName(&vars, current);
        if (node == nullptr) {
            node = new Node(current);
            vars.push_back(node);
        }
    }
    return node;
}

MathTree::Node* MathTree::findNodeInVectorByName(std::vector<Node *> *vector, std::string string) {
    for (int i = 0; i < vector->size(); ++i) {
        if (vector->at(i)->name == string)
            return vector->at(i);
    }
    return nullptr;
}

bool MathTree::isStringANumber(std::string string) {
    for (int i = 0; i < string.size(); ++i) {
        if (string.at(i) > '9' || string.at(i) < '0' && string.at(i) != '.')
            return false;
    }
    return true;
}

void MathTree::menu() {
    std::cout << "Choose option: \n"
                 "1. Create tree;\n";
}

void MathTree::clear() {
    if (empty()){
        std::cout << "Tree is empty.\n";
        return;
    }

    delete root;
    root = nullptr;
}

std::vector<std::string> MathTree::splitString(std::string formula) {
    std::string token;
    std::stringstream ss(formula);
    std::vector<std::string> v;
    while (getline(ss, token, ' ')) {
        if (!token.empty())
            v.push_back(token);
    }
    return v;
}

bool MathTree::empty() {
    return root == nullptr;
}