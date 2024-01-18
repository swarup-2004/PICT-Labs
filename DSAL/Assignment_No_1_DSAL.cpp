#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

/*
1.Create Binary Tree
2.Insert new Nodes
3.Preorder display
4.Inorder display
5.Postorder display
6.Height of the tree
7.Count no of internal nodes
8.Count of external nodes
9.Mirror the treee
10.Level order traversal*/
template <class T>
class Queue;

template <class T>
class QueueNode
{
    friend class Queue<T>;
    T data;
    QueueNode *next;

public:
    QueueNode()
    {
        next = nullptr;
    }

    QueueNode(T data)
    {
        this->data = data;
        next = nullptr;
    }
};

template <class T>
class Queue
{
    QueueNode<T> *rear;
    QueueNode<T> *front;
    int size;

public:
    Queue()
    {
        front = rear = nullptr;
        size = 0;
    }

    bool isEmpty()
    {
        return front == nullptr && rear == nullptr;
    }

    void insert(T val)
    {
        QueueNode<T> *newNode = new QueueNode<T>(val);
        if (isEmpty())
        {
            front = rear = newNode;
        }
        else
        {
            rear->next = newNode;
            rear = newNode;
        }
        size++;
    }

    T remove()
    {
        size--;
        if (size == 0)
        {
            T data = front->data;
            front = rear = nullptr;
            return data;
        }
        else
        {
            T data = front->data;
            front = front->next;
            return data;
        }
    }
};

template <class T>
class Tree;

template <class T>
class TreeNode
{
public:
    T data;
    TreeNode<T> *left;
    TreeNode<T> *right;
    TreeNode()
    {
        left = right = nullptr;
    }
    TreeNode(char data)
    {
        this->data = data;
        left = right = nullptr;
    }
};

template <class T>
class Tree
{
    TreeNode<T> *root;
    int i;
    vector<T> preorder;

public:
    Tree()
    {
        int i = 0;
        getPreOrder(preorder);
        // showPre();
        root = createBinaryTree(preorder, i);
    }

    void getPreOrder(vector<T> &preorder)
    {
        cout << "Enter Preorder Sequence to generate tree" << endl;
        while (true)
        {
            cout << "\n1. Add more values\n2. Stop" << endl;
            cout << "Enter your choice: ";
            int choice;
            cin >> choice;

            if (choice == 1)
            {
                cout << "\n1. Internal Node\n2. Leaf Node:" << endl;
                int nodeType;
                cin >> nodeType;

                T val;
                cout << "Enter the value: ";
                cin >> val;

                preorder.push_back(val);
                if (nodeType == 2)
                {
                    preorder.push_back(-1);
                    preorder.push_back(-1); // Marker for leaf node
                }
            }
            else if (choice == 2)
            {
                break;
            }
            else
            {
                cout << "Invalid choice" << endl;
            }
        }
    }

    TreeNode<T> *createBinaryTree(vector<T> &preorder, int &i)
    {
        if (i >= preorder.size() || preorder[i] == -1)
        {
            i++;
            return nullptr;
        }

        TreeNode<T> *newNode = new TreeNode<T>(preorder[i]);
        i++;

        newNode->left = createBinaryTree(preorder, i);
        newNode->right = createBinaryTree(preorder, i);
        return newNode;
    }

    void showPre()
    {
        for (auto it = preorder.begin(); it != preorder.end(); it++)
        {
            cout << *it << " ";
        }
        cout << endl;
    }

    TreeNode<T> *copyTree(TreeNode<T> *node, TreeNode<T> *node2)
    {
        if (node2 == nullptr)
        {
            return nullptr;
        }
        node = new TreeNode<T>(node2->data);
        node->left = new TreeNode<T>(node->left, node2->left);
        node->right = new TreeNode<T>(node->right, node2->right);
        return node;
    }

    TreeNode<T> *getRoot()
    {
        return root;
    }

    void preOrder(TreeNode<T> *node)
    {
        if (node == nullptr)
        {
            return;
        }
        cout << node->data << " ";
        preOrder(node->left);
        preOrder(node->right);
    }

    void inorder(TreeNode<T> *node)
    {
        if (node == nullptr)
        {
            return;
        }

        inorder(node->left);
        cout << node->data << " ";
        inorder(node->right);
    }

    void postorder(TreeNode<T> *node)
    {
        if (node == nullptr)
        {
            return;
        }

        postorder(node->left);
        postorder(node->right);
        cout << node->data << " ";
    }

    int height(TreeNode<T> *node)
    {
        if (node == nullptr)
        {
            return 0;
        }
        return max(height(node->left), height(node->right)) + 1;
    }

    void countNodeType(TreeNode<T> *node, int type[])
    {
        if (node == nullptr)
        {
            return;
        }
        if (!node->left && !node->right)
        {
            // exteranl node count is at 0 idx
            type[0]++;
        }
        else
        {
            // internal node count is at 1 idx
            type[1]++;
        }
        countNodeType(node->left, type);
        countNodeType(node->right, type);
    }

    TreeNode<T> *mirrorTree(TreeNode<T> *node)
    {
        if (node == nullptr)
        {
            return nullptr;
        }
        TreeNode<T> *temp = node->left;
        node->left = mirrorTree(node->right);
        node->right = mirrorTree(temp);
        return node;
    }

    void levelOrder()
    {
        Queue<TreeNode<T> *> q;
        q.insert(root);
        q.insert(nullptr);
        while (!q.isEmpty())
        {
            TreeNode<T> *node = q.remove();
            if (node == nullptr)
            {
                cout << endl;
                if (q.isEmpty())
                {
                    return;
                }
                else
                {
                    q.insert(nullptr);
                }
            }
            else
            {
                cout << node->data << " ";
                if (node->left != nullptr)
                {
                    q.insert(node->left);
                }
                if (node->right != nullptr)
                {
                    q.insert(node->right);
                }
            }
        }
    }
};

int main()
{
    Tree<int> my;
    int ch;
    do
    {
        cout << "Menu\n1.Preorder\n2.Inorder\n3.Postorder\n4.Height\n5.No. of Nodes\n6.Mirror Tree\n7.Copy Nodes\n8.Remove leafs\n.9Exit" << endl;
        cout << "Enter your choice :";
        cin >> ch;
        TreeNode<int> *root = my.getRoot();
        if (ch == 1)
        {
            my.preOrder(root);
        }
        else if (ch == 2)
        {
            my.inorder(root);
        }
        else if (ch == 3)
        {
            my.postorder(root);
        }
        else if (ch == 4)
        {
            cout << "The height of the given tree is ";
            cout << my.height(root);
        }
        else if (ch == 5)
        {
            int arr[2];
            my.countNodeType(root, arr);
            cout << "External Node " << arr[0];
            cout << "Internal Node " << arr[1];
        }
        else if (ch == 6)
        {
            cout << "Tree Before mirroring" << endl;
            my.levelOrder();
            root = my.mirrorTree(root);
            cout << "Tree After mirroring" << endl;
            my.levelOrder();
        }
        else if (ch == 7)
        {
            TreeNode<int> *node;
            node = my.copyTree(node, root);
        }
        else if (ch == 8)
        {
            // remove nodes
        }
        else if (ch != 9)
        {
            cout << "Invalid choice" << endl;
        }
        cout << endl;

    } while (ch != 9);
    return 0;
}
