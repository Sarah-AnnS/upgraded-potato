#include <iostream>
#include <string>
#include <sstream>
#include <vector>

using namespace std;

// AVL Tree Node class
class Node {
public:
    int key;
    Node* left;
    Node* right;
    int height;
    
    Node(int val) : key(val), left(nullptr), right(nullptr), height(1) {}
};

// AVL Tree class
class AVLTree {
public:
    Node* root;
    
    AVLTree() : root(nullptr) {}
    
    // Function to get the height of the node
    int height(Node* N) {
        if (N == nullptr)
            return 0;
        return N->height;
    }

    // Function to right rotate subtree rooted with y
    Node* rightRotate(Node* y) {
        Node* x = y->left;
        Node* T2 = x->right;
        
        x->right = y;
        y->left = T2;
        
        y->height = max(height(y->left), height(y->right)) + 1;
        x->height = max(height(x->left), height(x->right)) + 1;
        
        return x;
    }
    
    // Function to left rotate subtree rooted with x
    Node* leftRotate(Node* x) {
        Node* y = x->right;
        Node* T2 = y->left;
        
        y->left = x;
        x->right = T2;
        
        x->height = max(height(x->left), height(x->right)) + 1;
        y->height = max(height(y->left), height(y->right)) + 1;
        
        return y;
    }

    // Get balance factor of node N
    int getBalance(Node* N) {
        if (N == nullptr)
            return 0;
        return height(N->left) - height(N->right);
    }

    // Insert a node
    Node* insert(Node* node, int key) {
        if (node == nullptr)
            return new Node(key);
        
        if (key < node->key)
            node->left = insert(node->left, key);
        else if (key > node->key)
            node->right = insert(node->right, key);
        else
            return node; // Duplicate keys not allowed
        
        node->height = 1 + max(height(node->left), height(node->right));
        
        int balance = getBalance(node);
        
        // Left Left Case
        if (balance > 1 && key < node->left->key)
            return rightRotate(node);
        
        // Right Right Case
        if (balance < -1 && key > node->right->key)
            return leftRotate(node);
        
        // Left Right Case
        if (balance > 1 && key > node->left->key) {
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }
        
        // Right Left Case
        if (balance < -1 && key < node->right->key) {
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }
        
        return node;
    }

    // Find the node with the smallest value
    Node* minValueNode(Node* node) {
        Node* current = node;
        while (current->left != nullptr)
            current = current->left;
        return current;
    }

    // Delete a node
    Node* deleteNode(Node* root, int key) {
        if (root == nullptr)
            return root;
        
        if (key < root->key)
            root->left = deleteNode(root->left, key);
        else if (key > root->key)
            root->right = deleteNode(root->right, key);
        else {
            if (root->left == nullptr || root->right == nullptr) {
                Node* temp = root->left ? root->left : root->right;
                
                if (temp == nullptr) {
                    temp = root;
                    root = nullptr;
                } else
                    *root = *temp;
                
                delete temp;
            } else {
                Node* temp = minValueNode(root->right);
                root->key = temp->key;
                root->right = deleteNode(root->right, temp->key);
            }
        }

        if (root == nullptr)
            return root;
        
        root->height = 1 + max(height(root->left), height(root->right));
        
        int balance = getBalance(root);
        
        // Left Left Case
        if (balance > 1 && getBalance(root->left) >= 0)
            return rightRotate(root);
        
        // Left Right Case
        if (balance > 1 && getBalance(root->left) < 0) {
            root->left = leftRotate(root->left);
            return rightRotate(root);
        }
        
        // Right Right Case
        if (balance < -1 && getBalance(root->right) <= 0)
            return leftRotate(root);
        
        // Right Left Case
        if (balance < -1 && getBalance(root->right) > 0) {
            root->right = rightRotate(root->right);
            return leftRotate(root);
        }
        
        return root;
    }

    // Pre-order traversal
    void preOrder(Node* root) {
        if (root != nullptr) {
            cout << root->key << " ";
            preOrder(root->left);
            preOrder(root->right);
        }
    }
    
    // In-order traversal
    void inOrder(Node* root) {
        if (root != nullptr) {
            inOrder(root->left);
            cout << root->key << " ";
            inOrder(root->right);
        }
    }
    
    // Post-order traversal
    void postOrder(Node* root) {
        if (root != nullptr) {
            postOrder(root->left);
            postOrder(root->right);
            cout << root->key << " ";
        }
    }
};

int main() {
    AVLTree tree;
    string input;
    
    getline(cin, input);
    
    istringstream ss(input);
    vector<string> commands;
    string command;
    
    while (ss >> command) {
        commands.push_back(command);
    }
    
    // Process modification moves
    for (size_t i = 0; i < commands.size() - 1; ++i) {
        if (commands[i][0] == 'A') {
            int value = stoi(commands[i].substr(1));
            tree.root = tree.insert(tree.root, value);
        } else if (commands[i][0] == 'D') {
            int value = stoi(commands[i].substr(1));
            tree.root = tree.deleteNode(tree.root, value);
        }
    }
    
    // Process finishing move
    string finishingMove = commands.back();
    
    if (tree.root == nullptr) {
        cout << "EMPTY" << endl;
    } else {
        if (finishingMove == "PRE") {
            tree.preOrder(tree.root);
        } else if (finishingMove == "IN") {
            tree.inOrder(tree.root);
        } else if (finishingMove == "POST") {
            tree.postOrder(tree.root);
        }
        cout << endl;
    }

    return 0;
}
