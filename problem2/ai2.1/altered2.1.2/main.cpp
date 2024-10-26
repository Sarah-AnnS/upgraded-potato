#include <iostream>
#include <string>
#include <sstream>
#include <vector>



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
        
        return x;
    }
    
    // Function to left rotate subtree rooted with x
    Node* leftRotate(Node* x) {
        Node* y = x->right;
        Node* T2 = y->left;
        
        y->left = x;
        x->right = T2;
        
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
        
        return y;
    }

    // Get balance factor of node N
    int getBalance(Node* N) {
        if (N == nullptr){
            return 0;
        }
        int result = height(N->left) - height(N->right);
        return result;
    }

    // Insert a node
    Node* insert(Node* node, int key) {
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
        
        int balance = getBalance(node);
        
        // Left Left Case
        if (balance > 1 && key < node->left->key){
            return rightRotate(node);
        }
        // Right Right Case
        if (balance < -1 && key > node->right->key){
            return leftRotate(node);
        }
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
        while (current->left != nullptr){
            current = current->left;
        }
        return current;
    }

    // Delete a node
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
            } else if(root->right == nullptr){
                Node* temp = root->left ? root->left : root->right;
                
                if (temp == nullptr) {
                    temp = root;
                    root = nullptr;
                } else
                    *root = *temp;
                
                delete temp;               
            }
            else {
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
        
        // Left Left Case
        if (balance > 1 && getBalance(root->left) >= 0){
            return rightRotate(root);
        }
        // Left Right Case
        if (balance > 1 && getBalance(root->left) < 0) {
            root->left = leftRotate(root->left);
            return rightRotate(root);
        }
        
        // Right Right Case
        if (balance < -1 && getBalance(root->right) <= 0){
            return leftRotate(root);
        }
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
            std::cout << root->key << " ";
            preOrder(root->left);
            preOrder(root->right);
        }
    }
    
    // In-order traversal
    void inOrder(Node* root) {
        if (root != nullptr) {
            inOrder(root->left);
            std::cout << root->key << " ";
            inOrder(root->right);
        }
    }
    
    // Post-order traversal
    void postOrder(Node* root) {
        if (root != nullptr) {
            postOrder(root->left);
            postOrder(root->right);
            std::cout << root->key << " ";
        }
    }
};

int main() {
    AVLTree tree;
    std::string input;
    
    std::getline(std::cin, input);
    
    std::istringstream ss(input);
    std::vector<std::string> commands;
    std::string command;
    
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
    std::string finishingMove = commands.back();
    
    if (tree.root == nullptr) {
        std::cout << "EMPTY" << std::endl;
    } else {
        if (finishingMove == "PRE") {
            tree.preOrder(tree.root);
        } else if (finishingMove == "IN") {
            tree.inOrder(tree.root);
        } else if (finishingMove == "POST") {
            tree.postOrder(tree.root);
        }
        std::cout << std::endl;
    }

    return 0;
}
