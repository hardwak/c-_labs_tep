//
// Created by ymher on 14.11.2023.
//
#include "MathTree.h"

#include <cmath>
#include <sstream>
#include <utility>

void mt_test() {
    MathTree<std::string> tree;
    tree.menu();
}

template<typename T>
std::string MathTree<T>::sGetKnownType() {
    return "Unknown";
}

template<>
std::string MathTree<int>::sGetKnownType() {
    return "int";
}

template<>
std::string MathTree<float>::sGetKnownType() {
    return "float";
}

template<>
std::string MathTree<std::string>::sGetKnownType() {
    return "string";
}

template<>
bool MathTree<float>::isStringANumber(std::string string) {
    for (int i = 0; i < string.size(); ++i) {
        if (string.at(i) > '9' || string.at(i) < '0' && string.at(i) != '.')
            return false;
    }
    return true;
}

template<>
bool MathTree<int>::isStringANumber(std::string string) {
    for (int i = 0; i < string.size(); ++i) {
        if (string.at(i) > '9' || string.at(i) < '0')
            return false;
    }
    return true;
}

template<typename T>
void MathTree<T>::printVars() {
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

template<>
float MathTree<float>::compile(Node *root, std::vector<float> *values) {
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

template<>
int MathTree<int>::compile(Node *root, std::vector<int> *values) {
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
        int currVal = values->front();
        values->erase(values->begin());
        return currVal;
    } else {
        return root->value;
    }
    return 0;
}

template<>
std::string MathTree<std::string>::compile(Node *root, std::vector<std::string> *values) {
    if (empty()) {
        std::cout << "Tree is empty.\n";
        return "";
    }

    if (root->op != NIL) {
        switch (root->op) {
            case PLUS: {
                return compile(root->left, values) + compile(root->right, values);
            }
            case MINUS: {
                std::string leftstr = compile(root->left, values);
                std::string rightstr = compile(root->right, values);

                for (int i = leftstr.length() - rightstr.length(); i >= 0; --i) {
                    if (leftstr.substr(i, rightstr.length()) == rightstr) {
                        leftstr.erase(i, rightstr.length());
                        i = -1;
                    }
                }
                return leftstr;
            }
            case DIV: {
                std::string leftstr = compile(root->left, values);
                std::string rightstr = compile(root->right, values);

                for (int i = leftstr.length() - rightstr.length(); i >= 0 ; --i) {
                    if (leftstr.substr(i, rightstr.length()) == rightstr) {
                        leftstr.erase(i, rightstr.length());
                    }
                }
                return leftstr;
            }
            case MULT: {
                std::string leftstr = compile(root->left, values);
                std::string rightstr = compile(root->right, values);

                for (int i = 0; i < leftstr.length(); ++i) {
                    if (leftstr.at(i) == rightstr.at(0)) {
                        leftstr.insert(i + 1, rightstr.substr(1, rightstr.length() - 1));
                        i += rightstr.length() - 1;
                    }
                }
                return leftstr;
            }
            case NIL:
                break;
        }
    } else
        return root->value;
    return "";
}

template<typename T>
void MathTree<T>::join(std::string formula) {
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
    if (elements.empty()) {
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

template<typename T>
void MathTree<T>::print(Node *root) {
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

template<typename T>
void MathTree<T>::create(std::string formula) {
    if (!empty()) {
        std::cout << "Delete current tree before creating new.\n";
        return;
    }

    std::vector<std::string> elements = splitString(std::move(formula));
    if (elements.empty()) {
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

template<>
typename MathTree<float>::Node *MathTree<float>::createHelper(std::vector<std::string> *elements) {
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
            node = new Node(current, true);
            vars.push_back(node);
        }
    }
    return node;
}

template<>
typename MathTree<int>::Node *MathTree<int>::createHelper(std::vector<std::string> *elements) {
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
        node = new Node(std::stoi(current));
    } else {
        node = findNodeInVectorByName(&vars, current);
        if (node == nullptr) {
            node = new Node(current, true);
            vars.push_back(node);
        }
    }
    return node;
}

template<>
typename MathTree<std::string>::Node *MathTree<std::string>::createHelper(std::vector<std::string> *elements) {
    std::string current = elements->front();
    elements->erase(elements->begin());
    Node *node;
    if (current == "+" || current == "-" || current == "*" || current == "/") {
        if (current == "+") node = new Node(Operations(PLUS));
        if (current == "-") node = new Node(Operations(MINUS));
        if (current == "*") node = new Node(Operations(MULT));
        if (current == "/") node = new Node(Operations(DIV));


        if (elements->empty()) {
            elements->emplace_back("a");
            std::cout << "Missing variable replaced with \"a\"\n";
        }
        node->left = createHelper(elements);

        if (current == "+" || current == "-" || current == "*" || current == "/") {
            if (elements->empty()) {
                elements->emplace_back("a");
                std::cout << "Missing variable replaced with \"a\"\n";
            }
            node->right = createHelper(elements);
        }

    } else {
        node = new Node(current);
    }
    return node;
}

template<typename T>
typename MathTree<T>::Node *MathTree<T>::findNodeInVectorByName(std::vector<Node *> *vector, std::string string) {
    for (int i = 0; i < vector->size(); ++i) {
        if (vector->at(i)->name == string)
            return vector->at(i);
    }
    return nullptr;
}

template<>
void MathTree<float>::precompile(std::string str) {
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

    if (errors != 0) {
        std::cout << "Provided incorrect numbers\n";
    } else {
        if (!empty())
            std::cout << "Result: " << compile(root, &values) << std::endl;
        else
            std::cout << "Tree is empty\n";
    }
}

template<>
void MathTree<int>::precompile(std::string str) {
    std::vector<std::string> elements = splitString(str.substr(4));
    std::vector<int> values;

    int errors = 0;
    if (elements.size() < vars.size())
        errors++;
    else {
        for (int i = 0; i < elements.size(); ++i) {
            if (!isStringANumber(elements.at(i))) {
                errors++;
            } else {
                values.push_back(std::stoi(elements.at(i)));
            }
        }
    }

    if (errors != 0) {
        std::cout << "Provided incorrect numbers\n";
    } else {
        if (!empty())
            std::cout << "Result: " << compile(root, &values) << std::endl;
        else
            std::cout << "Tree is empty\n";
    }
}

template<>
void MathTree<std::string>::precompile(std::string str) {
    if (!empty())
        std::cout << "Result: " << compile(root, nullptr) << std::endl;
    else
        std::cout << "Tree is empty\n";
}

template<typename T>
void MathTree<T>::menu() {
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
            precompile(str);
        } else if (command == "join") {
            join(str.substr(4));
        } else if (command == "clear") {
            clear();
        } else if (command == "exit") {
            exit = true;
            delete root;
            std::cout << "Stopping program...\n";
        } else if (command == "help") {
            std::cout
                    << "Commands: \nenter <formula> \nvars \nprint \ncomp <var0> <var1> ... <varN> \njoin <formula> \nclear \nexit\nhelp\n";
        }
    }
}

template<typename T>
void MathTree<T>::clear() {
    if (empty()) {
        std::cout << "Tree is empty.\n";
        return;
    }

    delete root;
    root = nullptr;
    vars.clear();
    std::cout << "Tree cleared.\n";
}

template<typename T>
std::vector<std::string> MathTree<T>::splitString(std::string formula) {
    std::string token;
    std::stringstream ss(formula);
    std::vector<std::string> v;
    while (getline(ss, token, ' ')) {
        if (!token.empty())
            v.push_back(token);
    }
    return v;
}

template<typename T>
bool MathTree<T>::empty() {
    return root == nullptr;
}