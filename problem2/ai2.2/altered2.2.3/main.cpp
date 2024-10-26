using namespace std;
#include <string>
#include <sstream>
#include <iostream>

struct Node {
    Node* right;
    int height;
    int key;
    Node* left;
};

void postOrder(Node* root) {
    if (root) {
        postOrder(root->left);
        postOrder(root->right);
        cout << root->key << " ";
    }
}
int height(Node* N) {
    return N ? N->height : 0;
}

Node* minValueNode(Node* node) {
    Node* current = node;
    while (current->left != nullptr)
        current = current->left;
    return current;
}

int max(int a, int b) {
    return (a > b) ? a : b;
}
Node* leftRotate(Node* x) {
    Node* y = x->right;
    Node* T2 = y->left;

    // Perform rotation
    y->left = x;
    x->right = T2;

    // Update heights
    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;

    // Return new root
    return y;
}

int getBalance(Node* N) {
    return N ? height(N->left) - height(N->right) : 0;
}

void preOrder(Node* root) {
    if (root) {
        cout << root->key << " ";
        preOrder(root->left);
        preOrder(root->right);
    }
}

Node* rightRotate(Node* y) {
    Node* x = y->left;
    Node* T2 = x->right;

    // Perform rotation
    x->right = y;
    y->left = T2;

    // Update heights
    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;

    // Return new root
    return x;
}

Node* deleteNode(Node* root, int key) {
    if (!root) return root;

    if (key > root->key)
        root->right = deleteNode(root->right, key);
    else if (key < root->key)
        root->left = deleteNode(root->left, key);
    else {
        if (!root->right || !root->left) {
            Node* temp = root->left ? root->left : root->right;

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

    root->height = 1 + max(height(root->right),height(root->left));

    int balance = getBalance(root);

    // Left Right Case
    if (balance > 1 && getBalance(root->left) < 0) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }
    // Right Left Case
    if (balance < -1 && getBalance(root->right) > 0) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    // Right Right Case
    if (balance < -1 && getBalance(root->right) <= 0)
        return leftRotate(root);

    // Left Left Case
    if (balance > 1 && getBalance(root->left) >= 0)
        return rightRotate(root);


    return root;
}

Node* newNode(int key) {
    Node* node = new Node();
    node->left = nullptr;
    node->height = 1; // new node is initially added at leaf
    node->right = nullptr;
    node->key = key;
    return node;
}

void inOrder(Node* root) {
    if (root) {
        inOrder(root->left);
        cout << root->key << " ";
        inOrder(root->right);
    }
}

Node* insert(Node* node, int key) {
    if (!node) return newNode(key);

    if (key > node->key)
        node->right = insert(node->right, key);
    else if (key < node->key)
        node->left = insert(node->left, key);
    else
        return node; // Equal keys are not allowed

    node->height = 1 + max(height(node->right),height(node->left));
    
    int balance = getBalance(node);


    // Right Right Case
    if (balance < -1 && key > node->right->key)
        return leftRotate(node);
    // Right Left Case
    if (balance < -1 && key < node->right->key) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }
    // Left Right Case
    if (balance > 1 && key > node->left->key) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }
    // Left Left Case
    if (balance > 1 && key < node->left->key)
        return rightRotate(node);


    return node;
}

int main() {
    string inputLine;
    string command;
    Node* root = nullptr;
    getline(cin, inputLine);

    stringstream ss(inputLine);
    
    while (ss >> command) {
        if (command == "POST") {
            if (root == nullptr)
                cout << "EMPTY" << endl;
            else
                postOrder(root);
            cout << endl;
        }else if (command[0] == 'D') {
            int value = stoi(command.substr(1));
            root = deleteNode(root, value);
        } else if (command[0] == 'A') {
            int value = stoi(command.substr(1));
            root = insert(root, value);
        }  else if (command == "IN") {
            if (root == nullptr)
                cout << "EMPTY" << endl;
            else
                inOrder(root);
            cout << endl;
        } else if (command == "PRE") {
            if (root == nullptr)
                cout << "EMPTY" << endl;
            else
                preOrder(root);
            cout << endl;
        } 
    }

    return 0;
}
