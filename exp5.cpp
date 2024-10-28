#include <iostream>
#include <queue>
#include <vector>

using namespace std;

// Structure for tree node
struct Node {
    int data;
    Node* left;
    Node* right;
};

// Function to create a new node
Node* createNode(int data) {
    Node* newNode = new Node();
    if (!newNode) {
        cout << "Memory error\n";
        return NULL;
    }
    newNode->data = data;
    newNode->left = newNode->right = NULL;
    return newNode;
}

// Function to construct the broadcast tree
Node* constructTree() {
    Node* root = createNode(0); // Root node

    // Level 1
    root->left = createNode(1); // Node A
    root->right = createNode(2); // Node B

    // Level 2
    root->left->left = createNode(3); // Host 1
    root->left->right = createNode(4); // Host 2
    root->right->left = createNode(5); // Host 3
    root->right->right = createNode(6); // Host 4

    // Level 3
    root->right->right->left = createNode(7); // Host 5
    root->right->right->right = createNode(8); // Host 6
    root->right->right->left->left = createNode(9); // Host 7
    root->right->right->left->right = createNode(10); // Host 8

    return root;
}

// Function to print the broadcast tree using level-order traversal
void printTree(Node* root) {
    if (root == NULL) return;

    queue<Node*> q;
    q.push(root);

    while (!q.empty()) {
        Node* temp = q.front();
        q.pop();

        if (temp->data != 0) // Skip root node
            cout << "Host " << temp->data << " ";

        if (temp->left != NULL) q.push(temp->left);
        if (temp->right != NULL) q.push(temp->right);
    }
}

int main() {
    Node* root = constructTree();
    cout << "Broadcast Tree: ";
    printTree(root);
    return 0;
}