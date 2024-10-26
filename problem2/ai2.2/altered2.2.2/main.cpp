#include <iostream>
#include <sstream>
#include <string>
using namespace std;

struct Node {
    int key;
    Node* left;
    Node* right;
    int height;
};

int height(Node* N) {
    if(N != nullptr){
        return N->height;
    } else {
        return 0;
    }
}

int max(int a, int b) {
    if(a > b){
        return a;
    }
    else{
        return b;
    }
}

Node* newNode(int key) {
    Node* node = new Node();
    node->key = key;
    node->left = nullptr;
    node->right = nullptr;
    node->height = 1; // new node is initially added at leaf
    return node;
}

Node* rightRotate(Node* y) {
    Node* x = y->left;
    Node* T2 = x->right;

    // Perform rotation
    x->right = y;
    y->left = T2;

    // Update heights
    int maxHeight;
    if(height(y->left) > height(y->right)){
        maxHeight = height(y->left);
    } else{
        maxHeight = height(y->right);
    }
    y->height = maxHeight + 1;

    if(height(x->left) > height(x->right)){
        maxHeight = height(x->left);
    } else{
        maxHeight = height(x->right);
    }
    x->height = maxHeight + 1;

    // Return new root
    return x;
}

Node* leftRotate(Node* x) {
    Node* y = x->right;
    Node* T2 = y->left;

    // Perform rotation
    y->left = x;
    x->right = T2;

    // Update heights
    int maxHeight;
    if(height(x->left) > height(x->right)){
        maxHeight = height(x->left);
    } else{
        maxHeight = height(x->right);
    }
    x->height = maxHeight + 1;
    if(height(y->left) > height(y->right)){
        maxHeight = height(y->left);
    } else{
        maxHeight = height(y->right);
    }
    y->height = maxHeight + 1;

    // Return new root
    return y;
}

int getBalance(Node* N) {
    if(N != nullptr){
        return height(N->left) - height(N->right);
    } else{
        return 0;
    }
}

Node* insert(Node* node, int key) {
    if (!node) return newNode(key);

    if (key < node->key)
        node->left = insert(node->left, key);
    else if (key > node->key)
        node->right = insert(node->right, key);
    else
        return node; // Equal keys are not allowed

    int maxHeight;
    if(height(node->left) > height(node->right)){
        maxHeight = height(node->left);
    } else{
        maxHeight = height(node->right);
    }
    node->height = 1 + maxHeight;

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

Node* minValueNode(Node* node) {
    Node* current = node;
    while (current->left != nullptr)
        current = current->left;
    return current;
}

Node* deleteNode(Node* root, int key) {
    if (!root) return root;

    if (key < root->key)
        root->left = deleteNode(root->left, key);
    else if (key > root->key)
        root->right = deleteNode(root->right, key);
    else {
        if (!root->left) {
            Node* temp = nullptr;
            if(root->left != nullptr){
                Node* temp = root->left;
            } else{
                Node* temp = root->right;
            }

            if (!temp) {
                temp = root;
                root = nullptr;
            } else
                *root = *temp;

            delete temp;
        } else if(!root->right){
            Node* temp = nullptr;
            if(root->left != nullptr){
                Node* temp = root->left;
            } else{
                Node* temp = root->right;
            }

            if (!temp) {
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

    if (!root) return root;

    int maxHeight;
    if(height(root->left) > height(root->right)){
        maxHeight = height(root->left);
    } else{
        maxHeight = height(root->right);
    }
    root->height = 1 + maxHeight;

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

int main() {
    Node* root = nullptr;
    string inputLine;
    getline(cin, inputLine);

    stringstream ss(inputLine);
    string command;
    
    while (ss >> command) {
        if (command[0] == 'A') {
            int value = stoi(command.substr(1));
            root = insert(root, value);
        } else if (command[0] == 'D') {
            int value = stoi(command.substr(1));
            root = deleteNode(root, value);
        } else if (command == "PRE") {
            if (root == nullptr)
                cout << "EMPTY" << endl;
            else
                preOrder(root);
            cout << endl;
        } else if (command == "IN") {
            if (root == nullptr)
                cout << "EMPTY" << endl;
            else
                inOrder(root);
            cout << endl;
        } else if (command == "POST") {
            if (root == nullptr)
                cout << "EMPTY" << endl;
            else
                postOrder(root);
            cout << endl;
        }
    }

    return 0;
}
