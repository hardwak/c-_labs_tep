//
// Created by ymher on 14.11.2023.
//
#include "MathTree.h"

#include <cmath>
#include <sstream>
#include <utility>

void mt_test() {
    MathTree tree;
    tree.menu();
}

void MathTree::printVars() {
    if (empty()) {
        std::cout << "Tree is empty.\n";
        return;
    }

    if (vars.empty()) {
        std::cout << "Tree dont have variables.\n";
        return;
    }

    std::cout << "Variables: ";
    for (int i = 0; i < vars.size(); ++i) {
        std::cout << vars.at(i)->name << " ";
    }
    std::cout << std::endl;
}

float MathTree::compile(Node *root, std::vector<float> *values) {
    if (empty()) {
        std::cout << "Tree is empty.\n";
        return 0;
    }

    if (root->op != NIL) {
        switch (root->op) {
            case PLUS:
                return compile(root->left, values) + compile(root->right, values);
            case MINUS:
                return compile(root->left, values) - compile(root->right, values);
            case DIV: {
                float num = compile(root->right, values);
                if (num == 0) {
                    std::cout << "Division by 0 is not allowed!\n";
                    num = 1;
                }
                return compile(root->left, values) / num;
            }
            case MULT:
                return compile(root->left, values) * compile(root->right, values);
            case SIN:
                return std::sin(compile(root->left, values));
            case COS:
                return std::cos(compile(root->left, values));
            case NIL:
                break;
        }
    } else if (root->variable) {
        float currVal = values->front();
        values->erase(values->begin());
        return currVal;
    } else {
        return root->value;
    }
    return 0;
}

void MathTree::join(std::string formula) {
    printVars();

    if (empty() || vars.empty())
        return;

    std::cout << "Choose one of the variables to replace (1-" << vars.size() << ")\n";

    int option;
    std::cin >> option;

    if (option > vars.size() || option < 1) {
        std::cout << "Incorrect number\n";
        return;
    }

    std::vector<std::string> elements = splitString(std::move(formula));
    if (elements.empty()){
        std::cout << "Formula wasn't provided\n";
        return;
    }

    delete vars.at(option - 1);
    *vars.at(option - 1) = *createHelper(&elements);
    vars.erase(vars.begin() + option - 1);

    std::cout << "New tree: ";
    print(root);
    std::cout << std::endl;
}

void MathTree::print(Node *root) {
    if (empty()) {
        std::cout << "Tree is empty.\n";
        return;
    }

    if (root->op != NIL) {
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
    } else if (root->variable) {
        std::cout << root->name << " ";
    } else {
        std::cout << root->value << " ";
    }
    if (root->left != nullptr)
        print(root->left);
    if (root->right != nullptr)
        print(root->right);
}

void MathTree::create(std::string formula) {
    if (!empty()) {
        std::cout << "Delete current tree before creating new.\n";
        return;
    }

    std::vector<std::string> elements = splitString(std::move(formula));
    if (elements.empty()){
        std::cout << "Formula wasn't provided\n";
        return;
    }

    root = createHelper(&elements);

    std::cout << "Created tree: ";
    print(root);
    std::cout << std::endl;

    if (!elements.empty()) {
        std::cout << "Warning! Redundant elements was skipped: ";
        for (const auto &element: elements) {
            std::cout << element << " ";
        }
        std::cout << std::endl;
    }
}

MathTree::Node *MathTree::createHelper(std::vector<std::string> *elements) {
    std::string current = elements->front();
    elements->erase(elements->begin());
    Node *node;
    if (current == "+" || current == "-" || current == "*" || current == "/" || current == "sin" || current == "cos") {
        if (current == "+") node = new Node(Operations(PLUS));
        if (current == "-") node = new Node(Operations(MINUS));
        if (current == "*") node = new Node(Operations(MULT));
        if (current == "/") node = new Node(Operations(DIV));
        if (current == "sin") node = new Node(Operations(SIN));
        if (current == "cos") node = new Node(Operations(COS));

        if (elements->empty()) {
            elements->emplace_back("1");
            std::cout << "Missing variable replaced with 1\n";
        }
        node->left = createHelper(elements);

        if (current == "+" || current == "-" || current == "*" || current == "/") {
            if (elements->empty()) {
                elements->emplace_back("1");
                std::cout << "Missing variable replaced with 1\n";
            }
            node->right = createHelper(elements);
        }

    } else if (isStringANumber(current)) {
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

MathTree::Node *MathTree::findNodeInVectorByName(std::vector<Node *> *vector, std::string string) {
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
    bool exit = false;

    while (!exit) {
        std::string str;
        std::getline(std::cin, str);
        std::string command = str.substr(0, str.find(' '));
        if (command == "enter") {
            create(str.substr(5));
        } else if (command == "vars") {
            printVars();
        } else if (command == "print") {
            print(root);
            std::cout << std::endl;
        } else if (command == "comp") {
            std::vector<std::string> elements = splitString(str.substr(4));
            std::vector<float> values;

            int errors = 0;
            if (elements.size() < vars.size())
                errors++;
            else {
                for (int i = 0; i < elements.size(); ++i) {
                    if (!isStringANumber(elements.at(i))) {
                        errors++;
                    } else {
                        values.push_back(std::stof(elements.at(i)));
                    }
                }
            }

            if (errors != 0){
                std::cout << "Provided incorrect numbers\n";
            } else{
                std::cout << "Result: " << compile(root, &values) << std::endl;
            }
        } else if (command == "join") {
            join(str.substr(4));
        } else if (command == "clear") {
            clear();
        } else if (command == "exit") {
            exit = true;
            delete root;
            std::cout << "Stopping program...\n";
        } else if (command == "help"){
            std::cout << "Commands: \nenter <formula> \nvars \nprint \ncomp <var0> <var1> ... <varN> \njoin <formula> \nclear \nexit\n";
        }
    }
}

void MathTree::clear() {
    if (empty()) {
        std::cout << "Tree is empty.\n";
        return;
    }

    delete root;
    root = nullptr;
    std::cout << "Tree cleared.\n";
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