#include <iostream>
using namespace std;

class BinarySearchTree;

class TreeNode
{
    friend class BinarySearchTree;
    int data;
    TreeNode *left;
    TreeNode *right;

public:
    TreeNode()
    {
        left = right = nullptr;
    }

    TreeNode(int data)
    {
        this->data = data;
        left = right = nullptr;
    }
};

class Stack
{
    int size = 50;
    TreeNode *arr[50];
    int top = -1;

public:
    bool isEmpty()
    {
        return top == -1;
    }

    void push(TreeNode *node)
    {
        top++;
        arr[top] = node;
    }

    TreeNode *pop()
    {
        return arr[top--];
    }
};

class BinarySearchTree
{
    TreeNode *root;

public:
    BinarySearchTree()
    {
        root = nullptr;
        create();
    }

    TreeNode *getRoot()
    {
        return root;
    }

    void create()
    {

        int ch, val;
        do
        {
            cout << "1.Insert Nodes\n2.Stop" << endl;
            cout << "Enter your choice :";
            cin >> ch;
            if (ch == 1)
            {
                cout << "Enter the value :";
                cin >> val;
                root = insert(root, val);
            }
            else if (ch != 2)
            {
                cout << "Invalid choice" << endl;
            }
        } while (ch != 2);
    }

    TreeNode *insert(TreeNode *node, int val)
    {
        TreeNode *newNode = new TreeNode(val);
        // if the root is null then make the root and return
        if (node == nullptr)
        {
            node = newNode;
            return node;
        }
        // the value is less than the data at root then go to the left side of the bst
        if (node->data < val)
        {
            node->right = insert(node->right, val);
        }
        // the value is greater than the root then go to the right side of the bst
        else
        {
            node->left = insert(node->left, val);
        }
        return node;
    }

    void preorder()
    {
        Stack nodeStack;
        nodeStack.push(root);
        while (!nodeStack.isEmpty())
        {

            // pop the node at top of the stack and show data
            TreeNode *current = nodeStack.pop();

            cout << current->data << " ";

            // if right node is not null push it inside the stack
            if (current->right != nullptr)
            {
                nodeStack.push(current->right);
            }

            // if left node is not null push it inside the stack
            if (current->left != nullptr)
            {
                nodeStack.push(current->left);
            }
        }
    }

    void postorder(TreeNode *node)
    {
        if (node == nullptr)
        {
            return;
        }

        // calling for the left subtree
        postorder(node->left);

        // calling for the right subtree
        postorder(node->right);
        cout << node->data << " ";
    }

    void inorder(TreeNode *node)
    {
        if (node == nullptr)
        {
            return;
        }

        inorder(node->left);

        cout << node->data << " ";

        inorder(node->right);
    }

    int min()
    {
        // the min value in the bst is the value of the left most node in the bst
        TreeNode *current = root;
        while (current->left != nullptr)
        {
            current = current->left;
        }
        return current->data;
    }

    int max()
    {
        // the max value in the bst is the value of right most node in the bst
        TreeNode *current = root;
        while (current->right != nullptr)
        {
            current = current->right;
        }
        return current->data;
    }

    TreeNode *mirrorTree(TreeNode *node)
    {
        if (node == nullptr)
        {
            return nullptr;
        }
        TreeNode *temp = node->left;
        node->left = mirrorTree(node->right);
        node->right = mirrorTree(temp);
        return node;
    }

    int height(TreeNode *node)
    {
        if (node == nullptr)
        {
            return 0;
        }

        // finding the height of the left subtree
        int left = height(node->left);

        // finding the height of the right subtree
        int right = height(node->right);

        // returing the max height of the tree from the left and right height and adding the value of the current level
        if (left > right)
        {
            return left + 1;
        }
        else
        {
            return right + 1;
        }
    }

    int diameter(TreeNode *node)
    {
        if (node == nullptr)
        {
            return 0;
        }

        // if the diameter passes through the current node
        int currDiameter = height(node->left) + height(node->right) + 1;

        // if diameter passes through the left subtree of current node
        int leftDiameter = diameter(node->left);

        // if diameter passes through the right subtree of the current node
        int rightDiameter = diameter(node->right);

        if (currDiameter > leftDiameter && currDiameter > rightDiameter)
        {
            return currDiameter;
        }
        else if (leftDiameter > currDiameter && leftDiameter > rightDiameter)
        {
            return leftDiameter;
        }
        else
        {
            return rightDiameter;
        }
    }

    bool search(TreeNode *node, int val, int comp)
    {

        // if the current node is null then return false;
        if (node == nullptr)
        {
            cout << "Comparisons :" << comp << endl;
            return false;
        }

        // if the data of the current node is equal to the value return true
        if (node->data == val)
        {
            cout << "Comparisons :" << comp + 1 << endl;
            return true;
        }

        // if the data of the current node is less than than the value go to the right part
        if (node->data < val)
        {
            return search(node->right, val, comp + 1);
        }

        // if the data of the current node is greater than the value then go to the left part
        else
        {
            return search(node->left, val, comp + 1);
        }
    }
};

int main()
{
    BinarySearchTree my;
    TreeNode *root = my.getRoot();

    

    int ch, val;

    do
    {
        cout << "Menu\n1.Insert\n2.Preorder\n3.Postorder\n4.Inorder\n5.Maximum value\n6.Minimum value\n";
    cout << "7.Mirror Tree\n8.Height\n9.Diameter\n10.Search\n11.Exit\n";
        cout << "Enter your choice :";
        cin >> ch;
        if (ch == 1)
        {
            cout << "Enter the value :";
            cin >> val;
            my.insert(root, val);
        }
        else if (ch == 2)
        {
            my.preorder();
        }
        else if (ch == 3)
        {
            my.postorder(root);
        }
        else if (ch == 4)
        {
            my.inorder(root);
        }
        else if (ch == 5)
        {
            val = my.max();
            cout << "Maximum value is " << val;
        }
        else if (ch == 6)
        {
            val = my.min();
            cout << "Minimum value is " << val;
        }
        else if (ch == 7)
        {
            my.mirrorTree(root);
        }
        else if (ch == 8)
        {
            val = my.height(root);
            cout << "Height of the BST is " << val;
        }
        else if (ch == 9)
        {
            val = my.diameter(root);
            cout << "Diameter of the BST is " << val;
        }
        else if (ch == 10)
        {
            cout << "Enter value to search :";
            cin >> val;
            bool ans = my.search(root, val, 0);
            if (ans)
            {
                cout << "Value found";
            }
            else
            {
                cout << "Not found";
            }
        }
        else if (ch != 11)
        {
            cout << "Invalid choice!!!";
        }
        cout << endl;
    } while (ch != 11);

    return 0;
}