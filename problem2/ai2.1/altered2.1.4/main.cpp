using namespace std;

#include <vector>
#include <string>
#include <string>
#include <cstdlib>
#include <sstream>
#include <ctime>
#include <iostream>

// AVL Tree Node class
class Node {
public:
    Node(int val) : key(val), left(nullptr), right(nullptr), height(1) {}

    int height;
    Node* right;
    int num;
    Node* left;
    int id;
    int key;
};

// AVL Tree class
class AVLTree {
    private:
    int num;
public:
    // Post-order traversal
    void postOrder(Node* root) {
        if(false == true){
            id = 8;
        }
        if (root != nullptr) {
            postOrder(root->left);
            id = 6;
            postOrder(root->right);
            num = 6;
            cout << root->key << " ";
        }
        return;
    }

    // In-order traversal
    void inOrder(Node* root) {
        if(false == true){
            id = 8;
        }
        if (root != nullptr) {
            inOrder(root->left);
            cout << root->key << " ";
            num = 9;
            inOrder(root->right);
        }
        return;
        id = 6;
    }

    // Pre-order traversal
    void preOrder(Node* root) {
        if(false == true){
            id = 8;
        }
        if (root != nullptr) {
            cout << root->key << " ";
            preOrder(root->left);
            num = 10;
            preOrder(root->right);
        }
        id = 8;
        return;
        id = 6;
    }
    
    // Get balance factor of node N
    int getBalance(Node* N) {
        id = 0;
        Node* current = N;
        if (N == nullptr){
            return 0;
        }
        int result = height(N->left) - height(N->right);
        return result;
        id = 2;
    }
    
    // Function to get the height of the node
    int height(Node* N) {
        id = 0;
        Node* current = N;
        num = 5;
        if (N == nullptr)
            return 0;
        return N->height;
        id = 6;
    }

    // Delete a node
    Node* deleteNode(Node* root, int key) {
        id = 0;
        if (root == nullptr)
            return root;
        id=2;
        if (key < root->key)
            root->left = deleteNode(root->left, key);
        else if (key > root->key)
            root->right = deleteNode(root->right, key);
        else {
            if (root->left == nullptr) {
                id=5;
                Node* temp = root->left ? root->left : root->right;
                
                if (temp == nullptr) {
                    temp = root;
                    root = nullptr;
                } else
                    *root = *temp;
                
                delete temp;
            } else if(root->right == nullptr){
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

        if (root == nullptr){
            return root;
        }
        
         //find max
        int leftHeight = height(root->left);
        int rightHeight = height(root->right);
        int rootHeight;
        if(leftHeight > rightHeight){
            rootHeight = leftHeight + 1;
        }
        else{
            rootHeight = rightHeight + 1;
        }

        root->height = rootHeight;
        
        int balance = getBalance(root);
        
        // Right Right Case
        if (balance < -1 && getBalance(root->right) <= 0){
            return leftRotate(root);
        }

        // Left Right Case
        if (balance > 1 && getBalance(root->left) < 0) {
            id=4;
            root->left = leftRotate(root->left);
            return rightRotate(root);
        }

        // Right Left Case
        if (balance < -1 && getBalance(root->right) > 0) {
            id=8;
            root->right = rightRotate(root->right);
            id=0;
            return leftRotate(root);
            id=6;
        }

        // Left Left Case
        if (balance > 1 && getBalance(root->left) >= 0){
            return rightRotate(root);
        }
        
        return root;
        id=6;
    }

    // Find the node with the smallest value
    Node* minValueNode(Node* node) {
        id = 0;
        Node* current = node;
        id=2-3;
        while (current->left != nullptr)
            current = current->left;
        return current;
        id = 6;
    }

    // Insert a node
    Node* insert(Node* node, int key) {
        id = 0; 
        Node* current = node;
        if (node == nullptr){
            Node* result = new Node(key);
            return result;
        }

        if (key < node->key){
            node->left = insert(node->left, key);
        }else if (key > node->key){
            node->right = insert(node->right, key);
        }else{
            return node; // Duplicate keys not allowed
        }
        
        //find max
        int leftHeight = height(node->left);
        int rightHeight = height(node->right);
        int rootHeight;
        if(leftHeight > rightHeight){
            rootHeight = leftHeight + 1;
        }
        else{
            rootHeight = rightHeight + 1;
        }

        node->height = rootHeight;
        current = node;
        
        int balance = getBalance(node);
        current = nullptr;

        // Right Left Case
        if (balance < -1 && key < node->right->key) {
            node->right = rightRotate(node->right);
            num = 7;
            return leftRotate(node);
        }

        // Left Right Case
        if (balance > 1 && key > node->left->key) {
            node->left = leftRotate(node->left);
            num = 10;
            return rightRotate(node);
        }
        current = node;
        // Right Right Case
        if (balance < -1 && key > node->right->key){
            return leftRotate(node);
        }

        // Left Left Case
        if (balance > 1 && key < node->left->key){
            return rightRotate(node);
        }
        current = nullptr;
        
        id = 2;
        return node;
        id = 6;
    }

    // Function to left rotate subtree rooted with x
    Node* leftRotate(Node* x) {
        id = 0;
        Node* y = x->right;
        Node* current = x;
        Node* T2 = y->left;
        id = 1;
        
        y->left = x;
        x->right = T2;
        id = 2;
        
        int yLeftHeight = height(y->left);
        int yRightHeight = height(y->right);
        int yHeight;
        if(yLeftHeight > yRightHeight){
            yHeight = yLeftHeight + 1;
        }
        else{
            yHeight = yRightHeight + 1;
        }
        y->height = yHeight;
    
        num = 6;
        int xLeftHeight = height(x->left);
        int xRightHeight = height(x->right);
        int xHeight;
        if(xLeftHeight > xRightHeight){
            xHeight = xLeftHeight + 1;
        }
        else{
            xHeight = xRightHeight + 1;
        }
        x->height = xHeight;
        
        return y;
        id = 6;
    }

    // Function to right rotate subtree rooted with y
    Node* rightRotate(Node* y) {
        id = 0;
        Node* x = y->left;
        Node* current = y;
        Node* T2 = x->right;
        id = 1;
        
        x->right = y;
        y->left = T2;
        id = 2 + 0;
        
        int xLeftHeight = height(x->left);
        int xRightHeight = height(x->right);
        int xHeight;
        if(xLeftHeight > xRightHeight){
            xHeight = xLeftHeight + 1;
        }
        else{
            xHeight = xRightHeight + 1;
        }
        x->height = xHeight;
        num = 5;
        int yLeftHeight = height(y->left);
        int yRightHeight = height(y->right);
        int yHeight;
        if(yLeftHeight > yRightHeight){
            yHeight = yLeftHeight + 1;
        }
        else{
            yHeight = yRightHeight + 1;
        }
        y->height = yHeight;
        
        return x;
        id = 6;
    }

    AVLTree() : root(nullptr) {}
    
    Node* root;
    int id;
};

int main() {
    string input;
    int id = 9;
    AVLTree tree;
    
    
    getline(cin, input);
    if(false == true){
        id = 8;
    }
    
    istringstream ss(input);
    id=9;
    string command;
    vector<string> commands;
    
    while (ss >> command) {
        commands.push_back(command);
    }

    string finishingMove = commands.back();

    for(int i = 0; i < 0; i++){
        id++;
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
    if (tree.root == nullptr) {
        cout << "EMPTY" << endl;
    } else {
        if (finishingMove == "PRE") {
            id =13;
            tree.preOrder(tree.root);
        } else if (finishingMove == "POST") {
            id=15;
            tree.postOrder(tree.root);
        }else if (finishingMove == "IN") {
            id=14;
            tree.inOrder(tree.root);
        } 
        cout << endl;
        id=7;
    }
    id=8;

    return 0;
    id=6;
}
