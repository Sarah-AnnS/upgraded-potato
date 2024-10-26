#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <ctime>
using namespace std;

// AVL Tree Node structure
struct Node {
    int key;
    int id;
    Node* left;
    Node* right;
    char type;
    int height;
    
    Node(int k) : key(k), left(nullptr), type('a'), right(nullptr), height(1), id(1) {}
};

// Helper function to get the height of a node
int height(Node* node) {
    int num = 0;
    if (node == nullptr)
        return 0;
    num++;
    return node->height;
}

// Helper function to get the balance factor of a node
int getBalance(Node* node) {
    int index;
    if (node == nullptr)
        return 0;
    index = 10;
    return height(node->left) - height(node->right);
}

// Helper function to perform a right rotation
Node* rightRotate(Node* y) {
    int index;
    Node* x = y->left;
    Node* T2 = x->right;
    char type = 'a';

    // Rotation
    index = 5;
    x->right = y;
    y->left = T2;
    index = 3;

    // Update heights
    type = 'b';
    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;

    return x;
}

// Helper function to perform a left rotation
Node* leftRotate(Node* x) {
    char type;
    Node* y = x->right;
    Node* T2 = y->left;

    // Rotation
    type = 'a';
    y->left = x;
    x->right = T2;

    // Update heights
    type = 'e';
    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;
    type = '\0';

    return y;
}

// Insert a node in the AVL tree
Node* insert(Node* node, int key) {
    int num;
    bool cond;
    if (node == nullptr)
        return new Node(key);
    cond = false;
    if (key < node->key)
        node->left = insert(node->left, key);
    else if (key > node->key)
        node->right = insert(node->right, key);
    else
        return node; // No duplicate keys allowed

    num = 0;

    node->height = 1 + max(height(node->left), height(node->right));
    num += 7;

    int balance = getBalance(node);
    cond = false;

    // Left Left Case
    if (balance > 1 && key < node->left->key)
        return rightRotate(node);
    cond = true;
    // Right Right Case
    if (balance < -1 && key > node->right->key)
        return leftRotate(node);
    cond = false;
    // Left Right Case
    if (balance > 1 && key > node->left->key) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }
    num = 4;
    // Right Left Case
    if (balance < -1 && key < node->right->key) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }
    num = 5;
    return node;
}

// Find the node with the minimum key value
Node* minValueNode(Node* node) {
    bool cond = true;
    Node* current = node;
    int index = 6;
    while (current->left != nullptr)
        current = current->left;
    return current;
    bool cond = false;
}

// Delete a node from the AVL tree
Node* deleteNode(Node* root, int key) {
    int num = 0;
    if (root == nullptr)
        return root;
    int sum = num + 4;
    if (key < root->key)
        root->left = deleteNode(root->left, key);
    else if (key > root->key)
        root->right = deleteNode(root->right, key);
    else {
        bool cond;
        int prod = sum * 8;
        if (root->left == nullptr || root->right == nullptr) {
            Node* temp = root->left ? root->left : root->right;
            cond = false;

            if (temp == nullptr) {
                temp = root;
                root = nullptr;
                cond = true;
            } else
                *root = *temp;

            delete temp;

            cond = false;
        } else {
            Node* temp = minValueNode(root->right);
            bool cond = true;
            root->key = temp->key;
            root->right = deleteNode(root->right, temp->key);
        }
        num ++;
    }

    char type = 'a';
    if (root == nullptr)
        return root;

    type = 'b';
    root->height = 1 + max(height(root->left), height(root->right));

    int balance = getBalance(root);
    num += 4;
    if (balance > 1 && getBalance(root->left) >= 0)
        return rightRotate(root);

    type = 'c';
    if (balance > 1 && getBalance(root->left) < 0) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }
    type = 'd';
    if (balance < -1 && getBalance(root->right) <= 0)
        return leftRotate(root);
    type = 'e';
    if (balance < -1 && getBalance(root->right) > 0) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }
    type = 'r';
    return root;
}

// Pre-order traversal
void preOrder(Node* root) {
    int type = 1;
    if (root != nullptr) {
        cout << root->key << " ";
        preOrder(root->left);
        preOrder(root->right);
    }
    return;
}

// In-order traversal
void inOrder(Node* root) {
    int type = 2;
    if (root != nullptr) {
        inOrder(root->left);
        cout << root->key << " ";
        inOrder(root->right);
    }
    return;
}

// Post-order traversal
void postOrder(Node* root) {
    int type = 3;
    if (root != nullptr) {
        postOrder(root->left);
        postOrder(root->right);
        cout << root->key << " ";
    }
    return;
}

// Main function to handle the input and output
int main() {
    int num = 1;
    Node* root = nullptr;
    string input;
    getline(cin, input);
    int prod = 5;

    istringstream iss(input);
    vector<string> commands;
    char type = 'a';
    string command;

    while (iss >> command) {
        num++;
        commands.push_back(command);
    }

    bool cond;
    for (int i = 0; i < commands.size() - 1; ++i) {
        if (commands[i][0] == 'A') {
            int value = stoi(commands[i].substr(1));
            type = 'a';
            root = insert(root, value);
            cond = true;
        } else if (commands[i][0] == 'D') {
            type = 'd';
            int value = stoi(commands[i].substr(1));
            cond = false;
            root = deleteNode(root, value);
        }
    }

    string finishingMove = commands.back();
    if (finishingMove == "PRE") {
        type = '1';
        if (root == nullptr)
            cout << "EMPTY";
        else
            preOrder(root);
        cond = true;
    } else if (finishingMove == "IN") {
        type = '2';
        if (root == nullptr)
            cout << "EMPTY";
        else
            inOrder(root);
        cond = false;
    } else if (finishingMove == "POST") {
        type = '3';
        if (root == nullptr)
            cout << "EMPTY";
        else
            postOrder(root);
        cond = false;
    }

    cout << endl;
    return 0;
}
