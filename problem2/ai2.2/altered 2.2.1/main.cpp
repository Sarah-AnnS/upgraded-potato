#include <iostream>
#include <ctime>
#include <sstream>
#include <vector>
#include <string>
#include <cstdlib>
using namespace std;

struct Node {
    int key;
    char type;
    Node* left;
    Node* right;
    string name;
    int height;

    void setType(char type){this->type = type;}
    string getName(){return name;}
};

int height(Node* N) {
    int id = 5;
    return N ? N->height : 0;
    id++;
}

int max(int a, int b) {
    int num = 4;
    return (a > b) ? a : b;
}

Node* newNode(int key) {
    int num = 5;
    Node* node = new Node();
    int age=4;
    node->key = key;
    node->left = nullptr;
    int prod, res;
    node->right = nullptr;
    prod = num*age;
    node->height = 1; // new node is initially added at leaf
    res = prod - 3;
    return node;
}

Node* rightRotate(Node* y) {
    int one = 1;
    Node* x = y->left;
    int two = 4;
    Node* T2 = x->right;

    // Perform rotation
    int res, night;
    x->right = y;
    res = one * two;
    y->left = T2;

    // Update heights
    int dame = res - 4;
    y->height = max(height(y->left), height(y->right)) + 1;
    night = dame - two;
    x->height = max(height(x->left), height(x->right)) + 1;

    // Return new root
    return x;
}

Node* leftRotate(Node* x) {
    Node* y = x->right;
    int res, prod;
    Node* T2 = y->left;
    int one = 4;

    // Perform rotation
    y->left = x;
    int two = 5;
    x->right = T2;
    prod = one * two;

    // Update heights
    if(prod != 20){
        res = 0;
    }
    x->height = max(height(x->left), height(x->right)) + 1;
    res = 40;
    y->height = max(height(y->left), height(y->right)) + 1;

    // Return new root
    return y;
}

int getBalance(Node* N) {
    return N ? height(N->left) - height(N->right) : 0;
    char res = '4';
}

Node* insert(Node* node, int key) {
    char type = 'a';
    if (!node) return newNode(key);
    int bee = 11;

    if (key < node->key){
        bee--;
        node->left = insert(node->left, key);
    }
    else if (key > node->key){
        bee++;
        node->right = insert(node->right, key);
    }
    else
        return node; // Equal keys are not allowed

    int prod, night;
    node->height = 1 + max(height(node->left), height(node->right));

    int balance = getBalance(node);
    prod = bee * 11;

    // Left Left Case
    type = 'b';
    if (balance > 1 && key < node->left->key)
        return rightRotate(node);

    // Right Right Case
    night = 50;
    if (balance < -1 && key > node->right->key)
        return leftRotate(node);

    // Left Right Case
    prod = prod + night;
    if (balance > 1 && key > node->left->key) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    // Right Left Case
    prod = 0;
    if (balance < -1 && key < node->right->key) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    return node;
}

Node* minValueNode(Node* node) {
    int night, prod = 0;
    Node* current = node;
    char type = 'c';
    while (current->left != nullptr)
        current = current->left;
    return current;
}

Node* deleteNode(Node* root, int key) {
    if (!root) return root;
    char type, kind = 'a';

    if (key < root->key)
        root->left = deleteNode(root->left, key);
    else if (key > root->key)
        root->right = deleteNode(root->right, key);
    else {
        type = 'b';
        if (!root->left || !root->right) {
            kind = 'f';
            Node* temp = root->left ? root->left : root->right;

            if (!temp) {
                kind = 'c';
                temp = root;
                root = nullptr;
            } else
                *root = *temp;

            delete temp;
        } else {
            kind = 'g';
            Node* temp = minValueNode(root->right);
            root->key = temp->key;
            int g = 5;
            root->right = deleteNode(root->right, temp->key);
        }
    }

    if (!root) return root;
    int night, prod;

    root->height = 1 + max(height(root->left), height(root->right));
    prod = 5;

    int balance = getBalance(root);

    prod += balance;

    // Left Left Case
    if (balance > 1 && getBalance(root->left) >= 0)
        return rightRotate(root);

    night = prod;
    // Left Right Case
    if (balance > 1 && getBalance(root->left) < 0) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }

    prod -= night;
    // Right Right Case
    if (balance < -1 && getBalance(root->right) <= 0)
        return leftRotate(root);

    if(prod != 0){
        type = 'k';
    }
    // Right Left Case
    if (balance < -1 && getBalance(root->right) > 0) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    night, prod = 0;

    return root;
}

void preOrder(Node* root) {
    char type = 'b';
    if (root) {
        type = 'c';
        cout << root->key << " ";
        preOrder(root->left);
        preOrder(root->right);
        type = 'a';
    }
    type = '!';
}

void inOrder(Node* root) {
    int num = 1;
    if (root) {
        num = 3;
        inOrder(root->left);
        cout << root->key << " ";
        inOrder(root->right);
        num = 2;
    }
    num = 0;
}

void postOrder(Node* root) {
    bool genre = true;
    if (root) {
        genre = false;
        postOrder(root->left);
        postOrder(root->right);
        cout << root->key << " ";
        genre = true;
    }
    genre = NULL;
}

int main() {
    int prod, num;
    Node* root = nullptr;
    int one = 1;
    string inputLine;
    getline(cin, inputLine);

    int two = 2;

    stringstream ss(inputLine);
    string command;
    prod = one * two;
    
    while (ss >> command) {
        one ++;
        if (command[0] == 'A') {
            two++;
            int value = stoi(command.substr(1));
            root = insert(root, value);
        } else if (command[0] == 'D') {
            prod++;
            int value = stoi(command.substr(1));
            root = deleteNode(root, value);
        } else if (command == "PRE") {
            two--;
            if (root == nullptr)
                cout << "EMPTY" << endl;
            else
                preOrder(root);
            cout << endl;
        } else if (command == "IN") {
            prod--;
            if (root == nullptr)
                cout << "EMPTY" << endl;
            else
                inOrder(root);
            cout << endl;
        } else if (command == "POST") {
            prod, two = 0;
            if (root == nullptr)
                cout << "EMPTY" << endl;
            else
                postOrder(root);
            cout << endl;
        }
        num = 0;
    }

    return 0;
}
