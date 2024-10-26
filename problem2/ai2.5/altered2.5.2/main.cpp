#include <iostream>
#include <sstream>
#include <vector>
#include <string>
using namespace std;

// Node structure for AVL Tree
struct Node {
    int key;
    Node* left;
    Node* right;
    int height;
    Node(int k){
        key = k;
        left = nullptr;
        right = nullptr;
        height = 1;
    }
};

// Utility functions
int getHeight(Node* node) {
    if(node){
        return node->height;
    }else{
        return 0;
    }
}

int getBalance(Node* node) {
    if(node){
        return getHeight(node->left) - getHeight(node->right);
    } else{
        return 0;
    }
}

void updateHeight(Node* node) {
    if (node){
        int maxHeight;
        if(getHeight(node->left) > getHeight(node->right)){
            maxHeight = getHeight(node->left);
        }else {
            maxHeight = getHeight(node->right);
        }
        node->height = 1 + maxHeight;
    }
    return;
}

// Rotations
Node* rotateRight(Node* y) {
    Node* x = y->left;
    Node* T2 = x->right;

    x->right = y;
    y->left = T2;

    updateHeight(y);
    updateHeight(x);

    return x;
}

Node* rotateLeft(Node* x) {
    Node* y = x->right;
    Node* T2 = y->left;

    y->left = x;
    x->right = T2;

    updateHeight(x);
    updateHeight(y);

    return y;
}

// Insert a key
Node* insert(Node* node, int key) {
    if (!node) {
        return new Node(key);
    }

    if (key < node->key){
        node->left = insert(node->left, key);
    }else if (key > node->key){
        node->right = insert(node->right, key);
    }else{
        return node; // Duplicate keys not allowed
    }

    updateHeight(node);
    int balance = getBalance(node);

    if (balance > 1 && key < node->left->key){
        return rotateRight(node);
    }
    if (balance < -1 && key > node->right->key){
        return rotateLeft(node);
    }
    if (balance > 1 && key > node->left->key) {
        node->left = rotateLeft(node->left);
        return rotateRight(node);
    }
    if (balance < -1 && key < node->right->key) {
        node->right = rotateRight(node->right);
        return rotateLeft(node);
    }
    return node;
}

// Find minimum node in subtree
Node* minValueNode(Node* node) {
    while (node && node->left){
        node = node->left;
    }
    return node;
}

// Delete a key
Node* deleteNode(Node* root, int key) {
    if (!root) {
        return root;
    }

    if (key < root->key){
        root->left = deleteNode(root->left, key);
    }else if (key > root->key){
        root->right = deleteNode(root->right, key);
    }else {
        if (!root->left) {
            Node* temp = root->left ? root->left : root->right;
            delete root;
            return temp;
        } else if(!root->right){
            Node* temp = root->left ? root->left : root->right;
            delete root;
            return temp;
        } else {
            Node* temp = minValueNode(root->right);
            root->key = temp->key;
            root->right = deleteNode(root->right, temp->key);
        }
    }
    updateHeight(root);
    int balance = getBalance(root);

    if (balance > 1 && getBalance(root->left) >= 0){
        return rotateRight(root);
    }
    if (balance > 1 && getBalance(root->left) < 0) {
        root->left = rotateLeft(root->left);
        return rotateRight(root);
    }
    if (balance < -1 && getBalance(root->right) <= 0){
        return rotateLeft(root);
    }
    if (balance < -1 && getBalance(root->right) > 0) {
        root->right = rotateRight(root->right);
        return rotateLeft(root);
    }
    return root;
}

// Traversals
void preOrder(Node* root) {
    if (root) {
        cout << root->key << " ";
        preOrder(root->left);
        preOrder(root->right);
    }
}

void inOrder(Node* root) {
    if (root) {
        inOrder(root->left);
        cout << root->key << " ";
        inOrder(root->right);
    }
}

void postOrder(Node* root) {
    if (root) {
        postOrder(root->left);
        postOrder(root->right);
        cout << root->key << " ";
    }
}

// Driver function
int main() {
    Node* root = nullptr;
    string input;
    getline(cin, input);
    istringstream iss(input);
    vector<string> moves;
    string move;

    while (iss >> move){
        moves.push_back(move);
    }
    
    string traversal = moves.back();
    moves.pop_back();

    for (const string& m : moves) {
        if (m[0] == 'A') {
            int value = stoi(m.substr(1));
            root = insert(root, value);
        } else if (m[0] == 'D') {
            int value = stoi(m.substr(1));
            root = deleteNode(root, value);
        }
    }

    if (!root) {
        cout << "EMPTY";
    } else if (traversal == "PRE") {
        preOrder(root);
    } else if (traversal == "IN") {
        inOrder(root);
    } else if (traversal == "POST") {
        postOrder(root);
    }
    cout << endl;

    return 0;
}
