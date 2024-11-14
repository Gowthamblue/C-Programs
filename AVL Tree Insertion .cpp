#include <bits/stdc++.h>
using namespace std;
// AVL Tree

class BinaryNode {
public:
    int key;
    int height;
    BinaryNode *left, *right;
};

BinaryNode* newNode1(int data) {
    BinaryNode* temp = new BinaryNode();
    temp->key = data;
    temp->left = NULL;
    temp->right = NULL;
    temp->height = 1;
    return temp;
}

BinaryNode* display(BinaryNode* root) {
    if (root == NULL) {
        cout << "Tree Empty" << endl;
        return root;
    }

    queue<BinaryNode*> queue;
    queue.push(root);

    while (!queue.empty()) {
        BinaryNode* front = queue.front();
        queue.pop();
        cout << front->key << " -> ";

        if (front->left != NULL) {
            queue.push(front->left);
        }
        if (front->right != NULL) {
            queue.push(front->right);
        }
    }
    cout << "NULL" << endl;
    return root;
}

int getHeight(BinaryNode* node) {
    if (node == NULL) {
        return 0;
    }
    return node->height;
}

int getBalance(BinaryNode* node) {
    if (node == NULL) {
        return 0;
    }
    return getHeight(node->left) - getHeight(node->right);
}


BinaryNode* rotateRight(BinaryNode* disbalancedNode) {
    BinaryNode* newRoot = disbalancedNode->left;
    disbalancedNode->left = newRoot->right;
    newRoot->right = disbalancedNode;

    disbalancedNode->height = 1 + max(getHeight(disbalancedNode->left), getHeight(disbalancedNode->right));
    newRoot->height = 1 + max(getHeight(newRoot->left), getHeight(newRoot->right));

    return newRoot;
}

BinaryNode* rotateLeft(BinaryNode* disbalancedNode) {
    BinaryNode* newRoot = disbalancedNode->right;
    disbalancedNode->right = newRoot->left;
    newRoot->left = disbalancedNode;

    disbalancedNode->height = 1 + max(getHeight(disbalancedNode->left), getHeight(disbalancedNode->right));
    newRoot->height = 1 + max(getHeight(newRoot->left), getHeight(newRoot->right));

    return newRoot;
}


BinaryNode* insert(BinaryNode* node, int key) {
    if (node == NULL) {
        return newNode1(key);
    }
    if (key < node->key) 
    {
        node->left = insert(node->left, key);
    }
    else if (key > node->key)
    {
        node->right = insert(node->right, key);
    }
    else
    {
        return node; 
    }

    node->height = 1 + max(getHeight(node->left), getHeight(node->right));

    int balance = getBalance(node);

    if (balance > 1 && key < node->left->key) {
        return rotateRight(node);
    }

    if (balance < -1 && key > node->right->key) {
        return rotateLeft(node);
    }
    
    if (balance > 1 && key > node->left->key) {
        node->left = rotateLeft(node->left);
        return rotateRight(node);
    }

    if (balance < -1 && key < node->right->key) {
        node->right = rotateRight(node->right);
        return rotateLeft(node);
    }

    return node;
}
int main() {
    BinaryNode* root = NULL;
    root = insert(root, 5);
    root = insert(root, 10);
    root = insert(root, 15);
    root = insert(root, 20);
    root = insert(root, 25);
    root = insert(root, 30);
    root = insert(root, 35);
    display(root);

    return 0;
}
