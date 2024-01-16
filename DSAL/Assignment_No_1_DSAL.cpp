#include <iostream>
#include <vector>
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
class QueueNode
{
    friend class Queue;
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
    QueueNode *front, *rear;
    int size;

public:
    Queue()
    {
        front = rear = nullptr;
        size = 0;
    }
    boolean isEmpty()
    {
        return front == nullptr && rear == nullptr;
    }
    void insert(T val)
    {
        QueueNode *node = new Node(val);
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
            return front->data;
            front = rear = nullptr;
        }
        else
        {
            return front->next->data;
            front = front->next;
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
    TreeNode *left, *right;
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
    vector<int> preorder;

public:
    Tree()
    {
        i = -1;
        getPreOrder(preorder);
        root = createBinaryTree(preorder);
    }

    void getPreOrder(vector<int> preorder)
    {
        cout << "Enter Preorder Sequence to generate tree" << endl;
        int ch;
        T val;
        do
        {
            cout << "\n1.Add more values\n2.Stop" << endl;
            cout << "Enter your choice :";
            cin >> ch;
            if (ch == 1)
            {
                int nodeType;
                cout << "\n1.Internal Node\n2.Leaf Node :" << endl;
                cin >> nodeType;
                cout << "Enter the value :";
                cin >> val;
                preorder.push_back(val);
                if (ch == 2)
                {
                    preorder.push_back(-1);
                }
            }
            else if (ch != 2)
            {
                cout << "Invalid choice" << endl;
            }
        } while (ch != 2);
    }

    TreeNode *createBinaryTree(vector<int> preorder)
    {
        i++;
        if (preorder[i] == -1)
        {
            return nullptr;
        }
        TreeNode<T> *newNode = new TreeNode(preorder[i]);
        newNode->left = createBinaryTree(preorder);
        newNode->right = createBinaryTree(preorder);
        return newNode;
    }

    TreeNode *getRoot()
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
        preorder(node->left);
        preorder(node->right);
    }

    void inorder(TreeNode<T> *node)
    {
        if (node == nullptr)
        {
            return;
        }

        preorder(node->left);
        cout << node->data << " ";
        preorder(node->right);
    }

    void postorder(TreeNode<T> *node)
    {
        if (node == nullptr)
        {
            return;
        }

        preorder(node->left);
        preorder(node->right);
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

    void mirrorTree(TreeNode<T> *node)
    {
        if (node == nullptr)
        {
            return;
        }
        TreeNode<T> *temp = node->left;
        node->left = node->right;
        node->right = temp;
        mirrorTree(node->left);
        mirrorTree(node->right);
    }

    void levelOrder()
    {
        Queue<*TreeNode<T>> q;
        q.insert(root);
        q.insert(nullptr) while (!q.isEmpty())
        {
            TreeNode *node = q.remove();
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
        cout << "Menu\n1.Preorder\n2.Inorder\n3.Postorder\n4.Height\n5.No. of Nodes\n6.Mirror Tree\n7.Exit" << endl;
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

    } while (ch != 7);
    return 0;
}
