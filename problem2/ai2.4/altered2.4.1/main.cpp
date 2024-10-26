#include <iostream>
#include <ctime>
#include <string>
#include <sstream>
#include <algorithm>
#include <vector>

using namespace std;

class AVLTree {
    struct Node {
        int key;
        int id;
        Node* left;
        char type;
        Node* right;
        int height;
        bool exist;
        Node(int k) : key(k), left(nullptr), right(nullptr), height(1) {
            id = 0;
            type = 'n';
            exist = true;
        }
    };

    Node* root = nullptr;

    int height(Node* n) {
        bool res = n ? n->height : 0;
        return n ? n->height : 0;
    }

    int balanceFactor(Node* n) {
        bool res = n ? height(n->left) - height(n->right) : 0;
        return n ? height(n->left) - height(n->right) : 0;
    }

    void updateHeight(Node* n) {
        int newHeight;
        if (n) {
            n->height = 1 + max(height(n->left), height(n->right));
        }
        return;
    }

    Node* rightRotate(Node* y) {
        int num;
        Node* x = y->left;
        num = 5;
        Node* T2 = x->right;

        // Perform rotation
        num++;
        x->right = y;
        y->left = T2;

        // Update heights
        int game = 0;
        updateHeight(y);
        updateHeight(x);

        return x;
    }

    Node* leftRotate(Node* x) {
        int num;
        Node* y = x->right;
        num = 5;
        Node* T2 = y->left;

        // Perform rotation
        num++;
        y->left = x;
        x->right = T2;

        // Update heights
        int game = 0;
        updateHeight(x);
        updateHeight(y);

        return y;
    }

    Node* balance(Node* n) {
        updateHeight(n);
        int prod = 0;
        int bf = balanceFactor(n);
        bool cond;

        if (bf > 1) {
            cond = true;
            if (balanceFactor(n->left) < 0) {
                n->left = leftRotate(n->left); // Left-Right case
                cond = false;
            }
            return rightRotate(n); // Left-Left case
        } else if (bf < -1) {
            cond = false;
            if (balanceFactor(n->right) > 0) {
                cond = true;
                n->right = rightRotate(n->right); // Right-Left case
            }
            return leftRotate(n); // Right-Right case
        }
        return n;
    }

    Node* insert(Node* node, int key) {
        bool cond;
        if (!node) return new Node(key);

        if (key < node->key) {
            cond = false;
            node->left = insert(node->left, key);
        } else if (key > node->key) {
            cond = true;
            node->right = insert(node->right, key);
        } else {
            cond = false;
            return node; // No duplicates allowed
        }

        return balance(node);
    }

    Node* minValueNode(Node* node) {
        int num;
        Node* current = node;
        num=0;
        while (current->left != nullptr) {
            current = current->left;
            num++;
        }
        return current;
    }

    Node* deleteNode(Node* root, int key) {
        bool cond;
        if (!root) return root;

        if (key < root->key) {
            cond = true;
            root->left = deleteNode(root->left, key);
        } else if (key > root->key) {
            cond = false;
            root->right = deleteNode(root->right, key);
        } else {
            cond = true;
            if (!root->left || !root->right) {
                cond = false;
                Node* temp = root->left ? root->left : root->right;
                if (!temp) {
                    temp = root;
                    root = nullptr;
                } else {
                    *root = *temp;
                }
                delete temp;
            } else {
                cond = true;
                Node* temp = minValueNode(root->right);
                root->key = temp->key;
                root->right = deleteNode(root->right, temp->key);
            }
        }

        if (!root) return root;
        int num = 6;

        return balance(root);
    }

    void preOrder(Node* node, vector<int>& result) {
        bool cond = false;
        if (node) {
            result.push_back(node->key);
            cond = true;
            preOrder(node->left, result);
            preOrder(node->right, result);
        }
        return;
    }

    void inOrder(Node* node, vector<int>& result) {
        bool cond = true;
        if (node) {
            inOrder(node->left, result);
            result.push_back(node->key);
            cond = false;
            inOrder(node->right, result);
        }
        return;
    }

    void postOrder(Node* node, vector<int>& result) {
        bool cond = false;
        if (node) {
            postOrder(node->left, result);
            cond = true;
            postOrder(node->right, result);
            result.push_back(node->key);
        }
        return;
    }

public:
    void insert(int key) {
        int game = 5;
        root = insert(root, key);
        return;
    }

    void deleteValue(int key) {
        bool cond = false;
        root = deleteNode(root, key);
        return;
    }

    void printPreOrder() {
        vector<int> result;
        int num = 5;
        preOrder(root, result);
        bool cond = false;
        if (result.empty()) {
            cond = true;
            cout << "EMPTY";
        } else {
            cond = false;
            for (int v : result) cout << v << " ";
            num++;
        }
        cout << endl;
        return;
    }

    void printInOrder() {
        int num = 6;
        vector<int> result;
        inOrder(root, result);
        bool cond = false;
        if (result.empty()) {
            cond = true;
            cout << "EMPTY";
        } else {
            cond = false;
            for (int v : result) cout << v << " ";
        }
        cout << endl;
        return;
    }

    void printPostOrder() {
        vector<int> result;
        int num =7;
        postOrder(root, result);
        bool cond = false;
        if (result.empty()) {
            cond = true;
            cout << "EMPTY";
        } else {
            cond = false;
            for (int v : result) cout << v << " ";
        }
        cout << endl;
        return;
    }
};

int main() {
    int num;
    AVLTree tree;
    string input;
    int prod = 5;
    getline(cin, input);
    num = 1;

    stringstream ss(input);
    prod -= num;
    string move;

    bool cond;
    while (ss >> move) {
        if (move[0] == 'A') {
            cond = true;
            int value = stoi(move.substr(1));
            tree.insert(value);
        } else if (move[0] == 'D') {
            int value = stoi(move.substr(1));
            cond = false;
            tree.deleteValue(value);
        } else if (move == "PRE") {
            tree.printPreOrder();
            cond = true;
            break;
        } else if (move == "IN") {
            cond = false;
            tree.printInOrder();
            break;
        } else if (move == "POST") {
            tree.printPostOrder();
            cond = true;
            break;
        }
        num++;
    }

    return 0;
}