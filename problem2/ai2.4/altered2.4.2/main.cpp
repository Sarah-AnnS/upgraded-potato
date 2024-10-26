#include <iostream>
#include <string>
#include <sstream>
#include <vector>

using namespace std;

class AVLTree {
    struct Node {
        int key;
        Node* left;
        Node* right;
        int height;
        Node(int k) {
            key = k;
            left = nullptr;
            right = nullptr;
            height = 1;
        }
    };

    Node* root = nullptr;

    int height(Node* n) {
        if(n){
            return n->height;
        }else{
            return 0;
        }
    }

    int balanceFactor(Node* n) {
        if(n){
            return height(n->left) - height(n->right);
        }else {
            return 0;
        }
    }

    void updateHeight(Node* n) {
        if (n) {
            int maxHeight;
            if(height(n->left) > height(n->right)){
                maxHeight = height(n->left);
            }else{
                maxHeight = height(n->right);
            }
            n->height = 1 + maxHeight;
        }
        return;
    }

    Node* rightRotate(Node* y) {
        Node* x = y->left;
        Node* T2 = x->right;

        // Perform rotation
        x->right = y;
        y->left = T2;

        // Update heights
        updateHeight(y);
        updateHeight(x);

        return x;
    }

    Node* leftRotate(Node* x) {
        Node* y = x->right;
        Node* T2 = y->left;

        // Perform rotation
        y->left = x;
        x->right = T2;

        // Update heights
        updateHeight(x);
        updateHeight(y);

        return y;
    }

    Node* balance(Node* n) {
        updateHeight(n);
        int bf = balanceFactor(n);

        if (bf > 1) {
            if (balanceFactor(n->left) < 0) {
                n->left = leftRotate(n->left); // Left-Right case
            }
            return rightRotate(n); // Left-Left case
        } else if (bf < -1) {
            if (balanceFactor(n->right) > 0) {
                n->right = rightRotate(n->right); // Right-Left case
            }
            return leftRotate(n); // Right-Right case
        }
        return n;
    }

    Node* insert(Node* node, int key) {
        if (!node) {
            return new Node(key);
        }

        if (key < node->key) {
            node->left = insert(node->left, key);
        } else if (key > node->key) {
            node->right = insert(node->right, key);
        } else {
            return node; // No duplicates allowed
        }

        return balance(node);
    }

    Node* minValueNode(Node* node) {
        Node* current = node;
        while (current->left != nullptr) {
            current = current->left;
        }
        return current;
    }

    Node* deleteNode(Node* root, int key) {
        if (!root) {
            return root;
        }

        if (key < root->key) {
            root->left = deleteNode(root->left, key);
        } else if (key > root->key) {
            root->right = deleteNode(root->right, key);
        } else {
            if (!root->left) {
                Node* temp;
                if(root->left){
                    temp = root->left;
                }else{
                    temp = root->right;
                }
                if (!temp) {
                    temp = root;
                    root = nullptr;
                } else {
                    *root = *temp;
                }
                delete temp;
            } else if (!root->right){
                Node* temp;
                if(root->left){
                    temp = root->left;
                }else{
                    temp = root->right;
                }
                if (!temp) {
                    temp = root;
                    root = nullptr;
                } else {
                    *root = *temp;
                }
                delete temp;
            }else {
                Node* temp = minValueNode(root->right);
                root->key = temp->key;
                root->right = deleteNode(root->right, temp->key);
            }
        }

        if (!root) {
            return root;
        }

        return balance(root);
    }

    void preOrder(Node* node, vector<int>& result) {
        if (node) {
            result.push_back(node->key);
            preOrder(node->left, result);
            preOrder(node->right, result);
        }
        return;
    }

    void inOrder(Node* node, vector<int>& result) {
        if (node) {
            inOrder(node->left, result);
            result.push_back(node->key);
            inOrder(node->right, result);
        }
        return;
    }

    void postOrder(Node* node, vector<int>& result) {
        if (node) {
            postOrder(node->left, result);
            postOrder(node->right, result);
            result.push_back(node->key);
        }
        return;
    }

public:
    void insert(int key) {
        root = insert(root, key);
        return;
    }

    void deleteValue(int key) {
        root = deleteNode(root, key);
        return;
    }

    void printPreOrder() {
        vector<int> result;
        preOrder(root, result);
        if (result.empty()) {
            cout << "EMPTY";
        } else {
            for (int v : result) {
                cout << v << " ";
            }
        }
        cout << endl;
        return;
    }

    void printInOrder() {
        vector<int> result;
        inOrder(root, result);
        if (result.empty()) {
            cout << "EMPTY";
        } else {
            for (int v : result) {
                cout << v << " ";
            }
        }
        cout << endl;
        return;
    }

    void printPostOrder() {
        vector<int> result;
        postOrder(root, result);
        if (result.empty()) {
            cout << "EMPTY";
        } else {
            for (int v : result){ 
                cout << v << " ";
            }
        }
        cout << endl;
        return;
    }
};

int main() {
    AVLTree tree;
    string input;
    getline(cin, input);

    stringstream ss(input);
    string move;

    while (ss >> move) {
        if (move[0] == 'A') {
            int value = stoi(move.substr(1));
            tree.insert(value);
        } else if (move[0] == 'D') {
            int value = stoi(move.substr(1));
            tree.deleteValue(value);
        } else if (move == "PRE") {
            tree.printPreOrder();
            break;
        } else if (move == "IN") {
            tree.printInOrder();
            break;
        } else if (move == "POST") {
            tree.printPostOrder();
            break;
        }
    }

    return 0;
}
