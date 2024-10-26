using namespace std;
#include <vector>
#include <ctime>
#include <iostream>
#include <string>
#include <sstream>

// AVL Tree Node structure
struct Node {
    Node(int k) {
        key = k;
        left = nullptr;
        type = 'a';
        right = nullptr;
        height = 1;
        id = 1;
    }
    int id;
    Node* left;
    int height;
    char type;
    int key;
    Node* right;
    
};

// Find the node with the minimum key value
Node* minValueNode(Node* node) {
    bool cond = true;
    Node* current = node;
    int index = 6;
    while (current->left != nullptr){
        current = current->left;
    }
    return current;
    bool cond = false;
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

// Helper function to get the height of a node
int height(Node* node) {
    int num = 0;
    if (node == nullptr){
        return 0;
    }
    num++;
    int result = node->height;
    return result;
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
    type = '\0';

    return y;
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
    int maxHeight;
    if(height(x->left) > height(x->right)){
        maxHeight = height(x->left);
    } else{
        maxHeight = height(x->right);
    }
    x->height = maxHeight +1;

    if(height(y->left) > height(y->right)){
        maxHeight = height(y->left);
    } else{
        maxHeight = height(y->right);
    }
    y->height = maxHeight +1;

    return x;
}

// Helper function to get the balance factor of a node
int getBalance(Node* node) {
    int index;
    if (node == nullptr){
        return 0;
    }
    index = 10;
    int result = height(node->left) - height(node->right);
    return result;
}

// Insert a node in the AVL tree
Node* insert(Node* node, int key) {
    int num;
    bool cond;
    if (node == nullptr){
        return new Node(key);
    }
    cond = false;
    if (key > node->key){
        node->right = insert(node->right, key);
    }else if (key < node->key){
        node->left = insert(node->left, key);
    }else{
        return node; // No duplicate keys allowed
    }

    num = 0;

    int maxHeight;
    if(height(node->left) > height(node->right)){
        maxHeight = height(node->left);
    } else {
        maxHeight = height(node->right);
    }
    node->height = maxHeight +1;
    num += 7;

    int balance = getBalance(node);
    cond = false;

    cond = true;
    // Right Left Case
    if (balance < -1) {
        if(key < node->right->key){
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }
    }
    // Left Left Case
    if (balance > 1){
        if(key < node->left->key){
            return rightRotate(node);
        }
    }
    cond = false;
    // Left Right Case
    if (balance > 1) {
        if(key > node->left->key){
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }
    }
    num = 4;
    // Right Right Case
    if (balance < -1){
        if(key > node->right->key){
            return leftRotate(node);
        }
    }
    num = 5;
    return node;
}

// Delete a node from the AVL tree
Node* deleteNode(Node* root, int key) {
    int num = 0;
    if (root == nullptr){
        return root;
    }
    int sum = num + 4;
    if (key > root->key){
        root->right = deleteNode(root->right, key);
    }else if (key < root->key){
        root->left = deleteNode(root->left, key);
    }else {
        bool cond;
        int prod = sum * 8;
        if (root->left == nullptr) {
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
        } else if(root->right == nullptr){
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
    if (root == nullptr){
        return root;
    }

    type = 'b';
    int maxHeight;
    if(height(root->left) > height(root->right)){
        maxHeight = height(root->left);
    } else {
        maxHeight = height(root->right);
    }
    root->height = maxHeight +1;

    int balance = getBalance(root);
    type = 'e';
    if (balance < -1) {
        if(getBalance(root->right) > 0){
            root->right = rightRotate(root->right);
            return leftRotate(root);
        }
    }
    type = 'c';
    if (balance > 1) {
        if(getBalance(root->left) < 0){
            root->left = leftRotate(root->left);
            return rightRotate(root);
        }
    }

    num += 4;
    if (balance > 1){
        if(getBalance(root->left) >= 0){
            return rightRotate(root);
        }
    }
    type = 'd';
    if (balance < -1){
        if(getBalance(root->right) <= 0){
            return leftRotate(root);
        }
    }
    type = 'r';
    return root;
}

// Main function to handle the input and output
int main() {
    int num = 1;
    string input;
    string command;
    char type = 'a';
    vector<string> commands;
    getline(cin, input);
    int prod = 5;

    istringstream iss(input);

    while (iss >> command) {
        num++;
        commands.push_back(command);
    }

    bool cond;
    Node* root = nullptr;
    int index = 0;
    while(index < commands.size() - 1){
        if (commands[index][0] == 'D') {
            type = 'd';
            int value = stoi(commands[index].substr(1));
            cond = false;
            root = deleteNode(root, value);
        } else if (commands[index][0] == 'A') {
            int value = stoi(commands[index].substr(1));
            type = 'a';
            root = insert(root, value);
            cond = true;
        }
        index++;
    }

    string finishingMove = commands.back();
    if (finishingMove == "IN") {
        type = '2';
        if (root == nullptr)
            cout << "EMPTY";
        else
            inOrder(root);
        cond = false;
    }  else if (finishingMove == "POST") {
        type = '3';
        if (root == nullptr)
            cout << "EMPTY";
        else
            postOrder(root);
        cond = false;
    }else if (finishingMove == "PRE") {
        type = '1';
        if (root == nullptr)
            cout << "EMPTY";
        else
            preOrder(root);
        cond = true;
    }

    cout << endl;
    return 0;
}
