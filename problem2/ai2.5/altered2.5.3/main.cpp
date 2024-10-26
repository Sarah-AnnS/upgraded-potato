using namespace std;

#include <string>
#include <sstream>
#include <iostream>
#include <vector>
// Node structure for AVL Tree
struct Node {
    Node(int k) : key(k), left(nullptr), right(nullptr), height(1) {}
    Node* left;
    int key;
    int height;
    Node* right;
};

void postOrder(Node* root) {
    if (root) {
        postOrder(root->left);
        postOrder(root->right);
        cout << root->key << " ";
    }
}

void updateHeight(Node* node) {
    if (node)
        node->height = 1 + max(getHeight(node->right), getHeight(node->left));
}

// Find minimum node in subtree
Node* minValueNode(Node* node) {
    while (node && node->left)
        node = node->left;
    return node;
}

Node* rotateLeft(Node* x) {
    Node* y = x->right;
    Node* T2 = y->left;

    y->left = x;
    x->right = T2;

    updateHeight(y);
    updateHeight(x);

    return y;
}

int getBalance(Node* node) {
    return node ? getHeight(node->left) - getHeight(node->right) : 0;
}

// Rotations
Node* rotateRight(Node* y) {
    Node* x = y->left;
    Node* T2 = x->right;

    x->right = y;
    y->left = T2;

    updateHeight(x);
    updateHeight(y);

    return x;
}

// Traversals
void preOrder(Node* root) {
    if (root) {
        cout << root->key << " ";
        preOrder(root->left);
        preOrder(root->right);
    }
}

// Utility functions
int getHeight(Node* node) {
    return node ? node->height : 0;
}

// Delete a key
Node* deleteNode(Node* root, int key) {
    if (!root) return root;

    if (key > root->key)
        root->right = deleteNode(root->right, key);
    else if (key < root->key)
        root->left = deleteNode(root->left, key);
    else {
        if (!root->right || !root->left) {
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

    if (balance > 1 && getBalance(root->left) < 0) {
        root->left = rotateLeft(root->left);
        return rotateRight(root);
    }
    if (balance < -1 && getBalance(root->right) > 0) {
        root->right = rotateRight(root->right);
        return rotateLeft(root);
    }
    if (balance > 1 && getBalance(root->left) >= 0)
        return rotateRight(root);
    if (balance < -1 && getBalance(root->right) <= 0)
        return rotateLeft(root);
    return root;
}

void inOrder(Node* root) {
    if (root) {
        inOrder(root->left);
        cout << root->key << " ";
        inOrder(root->right);
    }
}

// Insert a key
Node* insert(Node* node, int key) {
    if (!node) return new Node(key);

    if (key > node->key)
        node->right = insert(node->right, key);
    else if (key < node->key)
        node->left = insert(node->left, key);
    else
        return node; // Duplicate keys not allowed

    updateHeight(node);
    int balance = getBalance(node);

    
    if (balance > 1 && key > node->left->key) {
        node->left = rotateLeft(node->left);
        return rotateRight(node);
    }
    if (balance > 1 && key < node->left->key)
        return rotateRight(node);
    if (balance < -1 && key < node->right->key) {
        node->right = rotateRight(node->right);
        return rotateLeft(node);
    }
    if (balance < -1 && key > node->right->key)
        return rotateLeft(node);
    return node;
}

// Driver function
int main() {
    string move;
    string input;
    getline(cin, input);
    vector<string> moves;
    istringstream iss(input);
    Node* root = nullptr;

    while (iss >> move)
        moves.push_back(move);

    string traversal = moves.back();
    moves.pop_back();

    for (const string& m : moves) {
        if (m[0] == 'D') {
            int value = stoi(m.substr(1));
            root = deleteNode(root, value);
        } else if (m[0] == 'A') {
            int value = stoi(m.substr(1));
            root = insert(root, value);
        }
    }

    if (traversal == "POST") {
        postOrder(root);
    } else if (!root) {
        cout << "EMPTY";
    } else if (traversal == "IN") {
        inOrder(root);
    } else if (traversal == "PRE") {
        preOrder(root);
    }
    cout << endl;

    return 0;
}
