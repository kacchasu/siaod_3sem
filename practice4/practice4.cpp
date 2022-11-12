#include <iostream>
#include <string>
using namespace std;

// nodes for tree
struct Node { 
    string key; // node value
    // pointers for neighbors
    Node *left; 
    Node *right;
    Node *parent;
    // constructor with key as arg
    Node(string key) : key(key), left(NULL), right(NULL), parent(NULL)  {};
};

void insert(Node *root, Node *node) { 
    while (root) { // go through tree
        if (node->key > root->key) {  // in case insertable node key > current node key
            if (root->right) 
                root = root->right; // right (bigger) node exists = moving into it
            else {
                node->parent = root; // right (bigger) node doesnt exist = turning it into insertable node
                root->right = node;
                break;
            }
        }
        else if (node->key < root->key) { // in case insertable node key < current node key
            if (root->left)
                root = root->left; // left (lower) node exists = moving into it
            else {
                node->parent = root; // left (lower) node doesnt exist = turning it into insertable node
                root->left = node;
                break;
            }
        }
    }
}
void preorderTraversal(Node *x) {
    if (x) { // while we dont reach end of a branch moving deeper
        cout << x->key << " "; // printing current node
        preorderTraversal(x->left); // printing left node-tree
        preorderTraversal(x->right); // printing right node-tree
    }
    else {
        return; // end of a branch have been reached
    }
}
void inorderTraversal(Node *x) {
    if (x) { // while we dont reach end of a branch moving deeper
        inorderTraversal(x->left); // printing left node-tree
        cout << x->key << " "; // printing current node
        inorderTraversal(x->right); // printing right node-tree
    }
    else return;
}
int averageValue(Node *x, int sum) {
    if (x) {
        averageValue(x->left, sum); // sum up left node-tree
        for (char c : x->key) // sum up current node
            sum += c - '0';
        averageValue(x->right, sum);  // sum up right node-tree
    }
    else return sum; // returning sum
}
int search(Node *x, string key, int cnt) {
    if (!x) // end of a branch or required node have been reached
        return 0;
    else if (key == x->key)
        return cnt;
    if (key < x->key)
        return search(x->left, key, cnt + 1); // key bigger than required = recursively moving to left branch
    else
        return search(x->right, key, cnt + 1); // else recursively moving to right branch
}

int main()
{
    cout << "enter amount of nodes in binary search tree: ";
    int n;
    Node* root = new Node(""); // root node
    cin >> n;

    // building tree from keyboard
    for (int i = 0; i < n; i++) {
        cout << "enter " << i + 1 << " town: ";
        string town;
        cin >> town;
        insert(root, new Node(town));
    }
    cout << "tree has been built. list of all commands\n";
    cout << "/inorder - to inorder traversal\n";
    cout << "/preorder - to preorder traversal\n";
    cout << "/search - to find depth of a node\n";
    cout << "/insert - to insert a node\n";
    cout << "/average - to find average value of all nodes\n";
    cout << "/stop - to stop processing\n";
    cout << "enter command to execute: ";

    // starting command processing
    string command;
    getline(cin, command);
    while (getline(cin, command)) {
        if (command == "/inorder") {
            cout << "inorder traversal: ";
            inorderTraversal(root);
            cout << endl;
            cout << "enter next command: ";
        }
        else if (command == "/preorder") {
            cout << "preorder traversal: ";
            preorderTraversal(root);
            cout << endl;
            cout << "enter next command: ";
        }
        else if (command == "/search") {
            string key;
            cout << "enter key to search for: ";
            cin >> key;
            getline(cin, command);
            cout << "depth of a node: ";
            cout << search(root, key, 0) << endl;
            cout << "enter next command: ";
        }
        else if (command == "/insert") {
            string node;
            cout << "enter town to insert: ";
            cin >> node;
            getline(cin, command);
            insert(root, new Node(node));
            cout << "town has been inserted\n";
            cout << "enter next command: ";
        }
        else if (command == "/average") {
            cout << "average value of all nodes: ";
            cout <<  double(averageValue(root, 0)) / n << endl;
            cout << "enter next command: ";
        }
        else if (command == "/stop") {
            cout << "programm stopped";
            exit(0);
        }
        else cout << "wrong command" << endl << "enter next command: ";
    }


}
