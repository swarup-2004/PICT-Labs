#include <iostream>
#include <string>
#include <vector>
using namespace std;

class TreeNode
{
public:
    string data;
    vector<TreeNode *> childNodes;

    // Constructor to initialize data
    TreeNode(const string &d) : data(d) {}
};

class GeneralTree
{
    TreeNode *root;

public:
    // Constructor to initialize root using makeTree
    GeneralTree()
    {
        string data;
        cout << "Making root Level 0" << endl;
        cout << "Enter data :";
        cin >> data;
        root = new TreeNode(data);

        root = makeTree(root);
    }

    // Function to create a tree recursively
    TreeNode *makeTree(TreeNode *root, int level = 0)
    {
        string data;

        int ch;
        do
        {
            cout << "Level :" << level + 1 << endl;
            cout << "1. Add more nodes\n2. Stop" << endl;
            cout << "Enter your choice :";
            cin >> ch;
            if (ch == 1)
            {
                int nodeType;
                cout << "Making node at Level " << level + 1 << endl;
                cout << "1. Internal Node\n2. Leaf Node" << endl;
                cout << "Enter your choice :";
                cin >> nodeType;
                cout << "Enter data :";
                cin >> data;
                TreeNode *newNode = new TreeNode(data);
                root->childNodes.push_back(newNode);
                if (nodeType == 1)
                {
                    // Recursively call makeTree for internal nodes
                    makeTree(newNode, level + 1);
                }
            }
        } while (ch != 2);

        return root;
    }

    // Function to display the tree
    void displayTree(TreeNode *node)
    {

        cout << node->data << " ";

        if (node->childNodes.empty())
        {
            cout << "-1"
                 << " ";
        }

        for (const auto &child : node->childNodes)
        {

            displayTree(child);
        }
    }

    // Wrapper function to start displaying from the root
    void display()
    {
        if (root == nullptr)
        {
            cout << "Tree is empty." << endl;
            return;
        }

        cout << "Tree Structure:" << endl;
        displayTree(root);
    }
};

int main()
{
    GeneralTree t1;
    t1.display();
    return 0;
}
