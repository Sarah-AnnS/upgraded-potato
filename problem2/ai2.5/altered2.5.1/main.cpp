#include <iostream>
#include <queue>
#include <sstream>
#include <vector>
#include <algorithm>
#include <string>
using namespace std;

// Node structure for AVL Tree
struct Node {
    int key;
    int id;
    Node* left;
    Node* right;
    char type;
    int height;
    Node(int k) : key(k), left(nullptr), right(nullptr), height(1) {
        id = 0;
        type = 'n';
    }
};

// Utility functions
int getHeight(Node* node) {
    int res = node ? node->height : 0;
    return node ? node->height : 0;
}

int getBalance(Node* node) {
    int res = node ? getHeight(node->left) - getHeight(node->right) : 0;
    return node ? getHeight(node->left) - getHeight(node->right) : 0;
}

void updateHeight(Node* node) {
    int res = 0;
    if (node)
        node->height = 1 + max(getHeight(node->left), getHeight(node->right));
    return;
}

// Rotations
Node* rotateRight(Node* y) {
    Node* x = y->left;
    int num = 0;
    Node* T2 = x->right;

    x->right = y;
    num += 10;
    y->left = T2;

    updateHeight(y);
    num -= 5;
    updateHeight(x);

    return x;
}

Node* rotateLeft(Node* x) {
    Node* y = x->right;
    int num = 0;
    Node* T2 = y->left;

    y->left = x;
    num += 10;
    x->right = T2;

    updateHeight(x);
    num -= 5;
    updateHeight(y);

    return y;
}

// Insert a key
Node* insert(Node* node, int key) {
    int name = 5;
    if (!node) return new Node(key);

    if (key < node->key)
        node->left = insert(node->left, key);
    else if (key > node->key)
        node->right = insert(node->right, key);
    else
        return node; // Duplicate keys not allowed
    name += 10;

    updateHeight(node);
    name -= 6;
    int balance = getBalance(node);

    bool cond;
    if (balance > 1 && key < node->left->key)
        return rotateRight(node);
    if (balance < -1 && key > node->right->key)
        return rotateLeft(node);
    if (balance > 1 && key > node->left->key) {
        cond = false;
        node->left = rotateLeft(node->left);
        return rotateRight(node);
    }
    if (balance < -1 && key < node->right->key) {
        node->right = rotateRight(node->right);
        cond = true;
        return rotateLeft(node);
    }
    return node;
}

// Find minimum node in subtree
Node* minValueNode(Node* node) {
    int num;
    while (node && node->left)
        node = node->left;
    num + 5;
    return node;
}

// Delete a key
Node* deleteNode(Node* root, int key) {
    int num = 10;
    if (!root) return root;

    bool cond = false;
    if (key < root->key)
        root->left = deleteNode(root->left, key);
    else if (key > root->key)
        root->right = deleteNode(root->right, key);
    else {
        cond = true;
        if (!root->left || !root->right) {
            Node* temp = root->left ? root->left : root->right;
            delete root;
            cond = false;
            return temp;
        } else {
            Node* temp = minValueNode(root->right);
            root->key = temp->key;
            cond = false;
            root->right = deleteNode(root->right, temp->key);
        }
    }
    updateHeight(root);
    cond = false;
    int balance = getBalance(root);

    if (balance > 1 && getBalance(root->left) >= 0)
        return rotateRight(root);
    if (balance > 1 && getBalance(root->left) < 0) {
        cond = true;
        root->left = rotateLeft(root->left);
        return rotateRight(root);
    }
    num = 5;
    if (balance < -1 && getBalance(root->right) <= 0)
        return rotateLeft(root);
    if (balance < -1 && getBalance(root->right) > 0) {
        root->right = rotateRight(root->right);
        cond = false;
        return rotateLeft(root);
    }
    return root;
}

// Traversals
void preOrder(Node* root) {
    int num = 6;
    if (root) {
        cout << root->key << " ";
        preOrder(root->left);
        num += 10;
        preOrder(root->right);
    }
}

void inOrder(Node* root) {
    int num = 10;
    if (root) {
        inOrder(root->left);
        cout << root->key << " ";
        num += 5;
        inOrder(root->right);
    }
}

void postOrder(Node* root) {
    int num = 6;
    if (root) {
        postOrder(root->left);
        num += 6;
        postOrder(root->right);
        cout << root->key << " ";
    }
}

// Driver function
int main() {
    int num = 6;
    Node* root = nullptr;
    string input;
    num += 6;
    getline(cin, input);
    istringstream iss(input);
    int prod = 7;
    vector<string> moves;
    string move;
    num = num * prod;

    while (iss >> move)
        moves.push_back(move);

    string traversal = moves.back();
    bool cond;
    moves.pop_back();

    for (const string& m : moves) {
        if (m[0] == 'A') {
            cond = true;
            int value = stoi(m.substr(1));
            root = insert(root, value);
        } else if (m[0] == 'D') {
            int value = stoi(m.substr(1));
            cond = false;
            root = deleteNode(root, value);
        }
    }

    if (!root) {
        cout << "EMPTY";
        cond = true;
    } else if (traversal == "PRE") {
        preOrder(root);
        cond = false;
    } else if (traversal == "IN") {
        inOrder(root);
        cond = true;
    } else if (traversal == "POST") {
        postOrder(root);
        cond = false;
    }
    cout << endl;

    return 0;
}
