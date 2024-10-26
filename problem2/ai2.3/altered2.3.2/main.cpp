#include <iostream>
#include <sstream>
#include <vector>
using namespace std;

// AVL Tree Node structure
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

// Helper function to get the height of a node
int height(Node* node) {
    if (node == nullptr){
        return 0;
    }
    int result = node->height;
    return result;
}

// Helper function to get the balance factor of a node
int getBalance(Node* node) {
    if (node == nullptr){
        return 0;
    }
    int result = height(node->left) - height(node->right);
    return result;
}

// Helper function to perform a right rotation
Node* rightRotate(Node* y) {
    Node* x = y->left;
    Node* T2 = x->right;

    // Rotation
    x->right = y;
    y->left = T2;

    // Update heights
    int maxHeight;
    if(height(y->left) > height(y->right)){
        maxHeight = height(y->left);
    } else{
        maxHeight = height(y->right);
    }
    y->height = maxHeight +1;

    if(height(x->left) > height(x->right)){
        maxHeight = height(x->left);
    } else{
        maxHeight = height(x->right);
    }
    x->height = maxHeight +1;

    return x;
}

// Helper function to perform a left rotation
Node* leftRotate(Node* x) {
    Node* y = x->right;
    Node* T2 = y->left;

    // Rotation
    y->left = x;
    x->right = T2;

    // Update heights
    int maxHeight;
    if(height(y->left) > height(y->right)){
        maxHeight = height(y->left);
    } else{
        maxHeight = height(y->right);
    }
    y->height = maxHeight +1;

    if(height(x->left) > height(x->right)){
        maxHeight = height(x->left);
    } else{
        maxHeight = height(x->right);
    }
    x->height = maxHeight +1;

    return y;
}

// Insert a node in the AVL tree
Node* insert(Node* node, int key) {
    if (node == nullptr){
        return new Node(key);
    }

    if (key < node->key){
        node->left = insert(node->left, key);
    }else if (key > node->key){
        node->right = insert(node->right, key);
    }else{
        return node; // No duplicate keys allowed
    }

    int maxHeight;
    if(height(node->left) > height(node->right)){
        maxHeight = height(node->left);
    } else {
        maxHeight = height(node->right);
    }
    node->height = maxHeight +1;

    int balance = getBalance(node);

    // Left Left Case
    if (balance > 1){
        if(key < node->left->key){
            return rightRotate(node);
        }
    }
    // Right Right Case
    if (balance < -1){
        if(key > node->right->key){
            return leftRotate(node);
        }
    }
    // Left Right Case
    if (balance > 1) {
        if(key > node->left->key){
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }
    }

    // Right Left Case
    if (balance < -1) {
        if(key < node->right->key){
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }
    }

    return node;
}

// Find the node with the minimum key value
Node* minValueNode(Node* node) {
    Node* current = node;
    while (current->left != nullptr){
        current = current->left;
    }
    return current;
}

// Delete a node from the AVL tree
Node* deleteNode(Node* root, int key) {
    if (root == nullptr){
        return root;
    }

    if (key < root->key){
        root->left = deleteNode(root->left, key);
    }else if (key > root->key){
        root->right = deleteNode(root->right, key);
    }else {
        if (root->left == nullptr) {
            Node* temp = root->left ? root->left : root->right;

            if (temp == nullptr) {
                temp = root;
                root = nullptr;
            } else
                *root = *temp;

            delete temp;
        }else if( root->right == nullptr) {
            Node* temp = root->left ? root->left : root->right;

            if (temp == nullptr) {
                temp = root;
                root = nullptr;
            } else
                *root = *temp;

            delete temp;
        }else {
            Node* temp = minValueNode(root->right);
            root->key = temp->key;
            root->right = deleteNode(root->right, temp->key);
        }
    }

    if (root == nullptr){
        return root;
    }

    int maxHeight;
    if(height(root->left) > height(root->right)){
        maxHeight = height(root->left);
    } else {
        maxHeight = height(root->right);
    }
    root->height = maxHeight +1;

    int balance = getBalance(root);

    if (balance > 1){
        if(getBalance(root->left) >= 0){
            return rightRotate(root);
        }
    }
    if (balance > 1) {
        if(getBalance(root->left) < 0){
            root->left = leftRotate(root->left);
            return rightRotate(root);
        }
    }

    if (balance < -1){
        if(getBalance(root->right) <= 0){
            return leftRotate(root);
        }
    }
    if (balance < -1) {
        if(getBalance(root->right) > 0){
            root->right = rightRotate(root->right);
            return leftRotate(root);
        }
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

// Main function to handle the input and output
int main() {
    Node* root = nullptr;
    string input;
    getline(cin, input);

    istringstream iss(input);
    vector<string> commands;
    string command;

    while (iss >> command) {
        commands.push_back(command);
    }

    int index = 0;
    while(index < commands.size() - 1){
        if (commands[index][0] == 'A') {
            int value = stoi(commands[index].substr(1));
            root = insert(root, value);
        } else if (commands[index][0] == 'D') {
            int value = stoi(commands[index].substr(1));
            root = deleteNode(root, value);
        }
        index++;
    }

    string finishingMove = commands.back();
    if (finishingMove == "PRE") {
        if (root == nullptr){
            cout << "EMPTY";
        }else{
            preOrder(root);
        }
    } else if (finishingMove == "IN") {
        if (root == nullptr){
            cout << "EMPTY";
        }else{
            inOrder(root);}
    } else if (finishingMove == "POST") {
        if (root == nullptr){
            cout << "EMPTY";
        }else{
            postOrder(root);}
    }

    cout << endl;
    return 0;
}
