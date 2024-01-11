#include <iostream>
#include <string>
#include <vector>
using namespace std;

class TreeNode {
public:
    string data;
    vector<TreeNode *> childNodes;

    // Constructor to initialize data
    TreeNode(const string& d) : data(d) {}
};

class GeneralTree {
    TreeNode *root;

public:
    // Constructor to initialize root using makeTree
    GeneralTree() : root(nullptr) {
        root = makeTree(root);
    }

    // Function to create a tree recursively
    TreeNode *makeTree(TreeNode *root, int level = 0) {
        string data;
        if (root == nullptr) {
            cout << "Making root Level 0" << endl;
            cout << "Enter data :";
            cin >> data;
            root = new TreeNode(data);
        }

        int ch;
        do {
            cout << "Level :" << level + 1 << endl;
            cout << "1. Add more nodes\n2. Stop" << endl;
            cout << "Enter your choice :";
            cin >> ch;
            if (ch == 1) {
                int nodeType;
                cout << "Making node at Level " << level + 1 << endl;
                cout << "1. Internal Node\n2. Leaf Node" << endl;
                cout << "Enter your choice :";
                cin >> nodeType;
                cout << "Enter data :" << endl;
                cin >> data;
                TreeNode *newNode = new TreeNode(data);
                root->childNodes.push_back(newNode);
                if (nodeType != 2) {
                    // Recursively call makeTree for internal nodes
                    makeTree(newNode, level + 1);
                }
            }
        } while (ch != 2);

        return root;
    }

    // Function to display the tree
    void displayTree(TreeNode *node, int level = 0) {
        if (!node) {
        	cout << " -1 ";
            return;
        }

        cout << node->data << " ";

        for (const auto &child : node->childNodes) {
            displayTree(child, level + 1);
        }
    }

    // Wrapper function to start displaying from the root
    void display() {
        if (root == nullptr) {
            cout << "Tree is empty." << endl;
            return;
        }

        cout << "Tree Structure:" << endl;
        displayTree(root);
    }
};

int main() {
    GeneralTree t1;
    t1.display();
    return 0;
}
