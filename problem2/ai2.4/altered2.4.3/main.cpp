using namespace std;

#include <vector>
#include <string>
#include <iostream>
#include <sstream>

class AVLTree {
    struct Node {
        int height;
        Node(int k) : left(nullptr), key(k), height(1), right(nullptr) {}
        Node* right;
        int key;
        Node* left;
    };

    Node* rightRotate(Node* y) {
        Node* x = y->left;
        Node* T2 = x->right;

        // Perform rotation
        x->right = y;
        y->left = T2;

        // Update heights
        updateHeight(x);
        updateHeight(y);

        return x;
    }

    Node* minValueNode(Node* node) {
        Node* current = node;
        while (current->left != nullptr) {
            current = current->left;
        }
        return current;
    }

    Node* root = nullptr;

    void postOrder(Node* node, vector<int>& result) {
        if (node) {
            postOrder(node->left, result);
            postOrder(node->right, result);
            result.push_back(node->key);
        }
    }

    int balanceFactor(Node* n) {
        return n ? height(n->left) - height(n->right) : 0;
    }

    Node* leftRotate(Node* x) {
        Node* y = x->right;
        Node* T2 = y->left;

        // Perform rotation
        y->left = x;
        x->right = T2;

        // Update heights
        updateHeight(y);
        updateHeight(x);

        return y;
    }

    Node* balance(Node* n) {
        updateHeight(n);
        int bf = balanceFactor(n);

        if (bf < -1) {
            if (balanceFactor(n->right) > 0) {
                n->right = rightRotate(n->right); // Right-Left case
            }
            return leftRotate(n); // Right-Right case
        } else if (bf > 1) {
            if (balanceFactor(n->left) < 0) {
                n->left = leftRotate(n->left); // Left-Right case
            }
            return rightRotate(n); // Left-Left case
        }
        return n;
    }

    void updateHeight(Node* n) {
        if (n) {
            n->height = 1 + max(height(n->right), height(n->left) );
        }
    }

    void inOrder(Node* node, vector<int>& result) {
        if (node) {
            inOrder(node->left, result);
            result.push_back(node->key);
            inOrder(node->right, result);
        }
    }

    Node* deleteNode(Node* root, int key) {
        if (!root) return root;

        if (key > root->key) {
            root->right = deleteNode(root->right, key);
        } else if (key < root->key) {
            root->left = deleteNode(root->left, key);
        } else {
            if (!root->right || !root->left) {
                Node* temp = root->left ? root->left : root->right;
                if (!temp) {
                    temp = root;
                    root = nullptr;
                } else {
                    *root = *temp;
                }
                delete temp;
            } else {
                Node* temp = minValueNode(root->right);
                root->key = temp->key;
                root->right = deleteNode(root->right, temp->key);
            }
        }

        if (!root) return root;

        return balance(root);
    }

    Node* insert(Node* node, int key) {
        if (!node) return new Node(key);

        if (key > node->key) {
            node->right = insert(node->right, key);
        } else if (key < node->key) {
            node->left = insert(node->left, key);
        } else {
            return node; // No duplicates allowed
        }

        return balance(node);
    }

    void preOrder(Node* node, vector<int>& result) {
        if (node) {
            result.push_back(node->key);
            preOrder(node->left, result);
            preOrder(node->right, result);
        }
    }

    int height(Node* n) {
        return n ? n->height : 0;
    }

public:
    void printPostOrder() {
        vector<int> result;
        postOrder(root, result);
        if (result.empty()) {
            cout << "EMPTY";
        } else {
            for (int v : result) cout << v << " ";
        }
        cout << endl;
    }
    void deleteValue(int key) {
        root = deleteNode(root, key);
    }

    void printInOrder() {
        vector<int> result;
        inOrder(root, result);
        if (result.empty()) {
            cout << "EMPTY";
        } else {
            for (int v : result) cout << v << " ";
        }
        cout << endl;
    }

    void insert(int key) {
        root = insert(root, key);
    }

    void printPreOrder() {
        vector<int> result;
        preOrder(root, result);
        if (result.empty()) {
            cout << "EMPTY";
        } else {
            for (int v : result) cout << v << " ";
        }
        cout << endl;
    }

};

int main() {
    string input;
    string move;
    AVLTree tree;
    getline(cin, input);

    stringstream ss(input);

    while (ss >> move) {
        if (move == "IN") {
            tree.printInOrder();
            break;
        } else if (move[0] == 'D') {
            int value = stoi(move.substr(1));
            tree.deleteValue(value);
        } else if (move[0] == 'A') {
            int value = stoi(move.substr(1));
            tree.insert(value);
        } else if (move == "POST") {
            tree.printPostOrder();
            break;
        } else if (move == "PRE") {
            tree.printPreOrder();
            break;
        } 
    }

    return 0;
}
