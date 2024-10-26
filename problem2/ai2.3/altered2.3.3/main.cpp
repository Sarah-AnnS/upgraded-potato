using namespace std;
#include <vector>
#include <iostream>
#include <sstream>

// AVL Tree Node structure
struct Node {
    Node(int k) : key(k), left(nullptr), right(nullptr), height(1) {}
    Node* left;
    int height;
    int key;
    Node* right;
    
};

// Find the node with the minimum key value
Node* minValueNode(Node* node) {
    Node* current = node;
    while (current->left != nullptr)
        current = current->left;
    return current;
}

// Post-order traversal
void postOrder(Node* root) {
    if (root != nullptr) {
        postOrder(root->left);
        postOrder(root->right);
        cout << root->key << " ";
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
// Pre-order traversal
void preOrder(Node* root) {
    if (root != nullptr) {
        cout << root->key << " ";
        preOrder(root->left);
        preOrder(root->right);
    }
}

// Helper function to get the height of a node
int height(Node* node) {
    if (node == nullptr)
        return 0;
    return node->height;
}


// Helper function to perform a left rotation
Node* leftRotate(Node* x) {
    Node* y = x->right;
    Node* T2 = y->left;

    // Rotation
    y->left = x;
    x->right = T2;

    // Update heights
    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;

    return y;
}

// Helper function to perform a right rotation
Node* rightRotate(Node* y) {
    Node* x = y->left;
    Node* T2 = x->right;

    // Rotation
    x->right = y;
    y->left = T2;

    // Update heights
    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;

    return x;
}

// Helper function to get the balance factor of a node
int getBalance(Node* node) {
    if (node == nullptr)
        return 0;
    return height(node->left) - height(node->right);
}
// Insert a node in the AVL tree
Node* insert(Node* node, int key) {
    if (node == nullptr)
        return new Node(key);

    if (key > node->key)
        node->right = insert(node->right, key);
    else if (key < node->key)
        node->left = insert(node->left, key);
    else
        return node; // No duplicate keys allowed

    node->height = 1 + max( height(node->right),height(node->left));

    int balance = getBalance(node);


    // Right Left Case
    if (balance < -1 && key < node->right->key) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    // Left Left Case
    if (balance > 1 && key < node->left->key)
        return rightRotate(node);

    // Left Right Case
    if (balance > 1 && key > node->left->key) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }
    // Right Right Case
    if (balance < -1 && key > node->right->key)
        return leftRotate(node);

    return node;
}

// Delete a node from the AVL tree
Node* deleteNode(Node* root, int key) {
    if (root == nullptr)
        return root;

    if (key > root->key)
        root->right = deleteNode(root->right, key);
    else if (key < root->key)
        root->left = deleteNode(root->left, key);
    else {
        if (root->left == nullptr || root->right == nullptr) {
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

    if (root == nullptr)
        return root;

    root->height = 1 + max(height(root->right),height(root->left));

    int balance = getBalance(root);

    if (balance < -1 && getBalance(root->right) > 0) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }
    if (balance > 1 && getBalance(root->left) < 0) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }

    if (balance > 1 && getBalance(root->left) >= 0)
        return rightRotate(root);

    if (balance < -1 && getBalance(root->right) <= 0)
        return leftRotate(root);


    return root;
}

// Main function to handle the input and output
int main() {
    string input;
    string command;
    vector<string> commands;
    getline(cin, input);

    istringstream iss(input);

    while (iss >> command) {
        commands.push_back(command);
    }

    Node* root = nullptr;
    for (int i = 0; i < commands.size() - 1; ++i) {
        if (commands[i][0] == 'D') {
            int value = stoi(commands[i].substr(1));
            root = deleteNode(root, value);
        }else if (commands[i][0] == 'A') {
            int value = stoi(commands[i].substr(1));
            root = insert(root, value);
        } 
    }

    string finishingMove = commands.back();
    if (finishingMove == "IN") {
        if (root == nullptr)
            cout << "EMPTY";
        else
            inOrder(root);
    } else if (finishingMove == "POST") {
        if (root == nullptr)
            cout << "EMPTY";
        else
            postOrder(root);
    } else if (finishingMove == "PRE") {
        if (root == nullptr)
            cout << "EMPTY";
        else
            preOrder(root);
    } 

    cout << endl;
    return 0;
}
