#include <iostream>
#include <stack>
using namespace std;

class TBinaryTree;

class TBTNode
{
    int data;
    TBTNode *left, *right;
    bool lthread, rthread;

    friend class TBinaryTree;

public:
    TBTNode() {}

    TBTNode(int data)
    {
        this->data = data;
        left = right = nullptr;
        lthread = rthread = true;
    }
};

class TBinaryTree
{
    TBTNode *root;

public:
    TBinaryTree()
    {
        root = nullptr;
    }

    // Insert a Node in Binary Threaded Tree
    TBTNode *insert(int ikey)
    {
        // Searching for a Node with given value
        TBTNode *ptr = root;
        TBTNode *par = nullptr; // Parent of key to be inserted
        while (ptr != nullptr)
        {
            // If key already exists, return
            if (ikey == (ptr->data))
            {
                printf("Duplicate Key !\n");
                return root;
            }

            par = ptr; // Update parent pointer

            // Moving on left subtree.
            if (ikey < ptr->data)
            {
                if (ptr->lthread == false)
                    ptr = ptr->left;
                else
                    break;
            }

            // Moving on right subtree.
            else
            {
                if (ptr->rthread == false)
                    ptr = ptr->right;
                else
                    break;
            }
        }

        // Create a new node
        TBTNode *tmp = new TBTNode(ikey);

        if (par == nullptr)
        {
            root = tmp;
        }
        else if (ikey < (par->data))
        {
            tmp->left = par->left;
            tmp->right = par;
            par->lthread = false;
            par->left = tmp;
        }
        else
        {
            tmp->left = par;
            tmp->right = par->right;
            par->rthread = false;
            par->right = tmp;
        }

        return root;
    }

    // Returns inorder successor using rthread
    TBTNode *inorderSuccessor(TBTNode *ptr)
    {
        // If rthread is set, we can quickly find
        if (ptr->rthread == true)
            return ptr->right;

        // Else return leftmost child of right subtree
        ptr = ptr->right;
        while (ptr->lthread == false)
            ptr = ptr->left;
        return ptr;
    }

    // Returns inorder predecessor of the node
    TBTNode *inorderPredecessor(TBTNode *ptr)
    {
        if (ptr->lthread == true)
            return ptr->left;

        ptr = ptr->left;
        while (ptr->rthread == false)
            ptr = ptr->right;
        return ptr;
    }

    // Printing the threaded tree
    void inorder()
    {
        if (root == nullptr)
            cout << "Tree is empty" << endl;

        // Reach leftmost node
        TBTNode *ptr = root;
        while (ptr->lthread == false)
            ptr = ptr->left;

        // One by one print successors
        while (ptr != nullptr)
        {
            cout << ptr->data << " ";
            ptr = inorderSuccessor(ptr);
        }
        cout << endl;
    }

    void preorder()
    {
        stack<TBTNode *> nodeStack;
        nodeStack.push(root);
        while (!nodeStack.empty())
        {

            // pop the node at top of the stack and show data
            TBTNode *current = nodeStack.top();
            nodeStack.pop();

            cout << current->data << " ";

            // if right node is not null push it inside the stack
            if (current->rthread != true)
            {
                nodeStack.push(current->right);
            }

            // if left node is not null push it inside the stack
            if (current->lthread != true)
            {
                nodeStack.push(current->left);
            }
        }
        cout << endl;
    }

    // Here 'par' is pointer to parent Node and 'ptr' is
    // pointer to current Node.
    TBTNode *caseA(TBTNode *par,
                   TBTNode *ptr)
    {
        // If Node to be deleted is root
        if (par == nullptr)
            root = nullptr;

        // If Node to be deleted is left
        // of its parent
        else if (ptr == par->left)
        {
            par->lthread = true;
            par->left = ptr->left;
        }
        else
        {
            par->rthread = true;
            par->right = ptr->right;
        }

        // Free memory and return new root
        delete ptr;
        return root;
    }

    // Here 'par' is pointer to parent Node and 'ptr' is
    // pointer to current Node.
    TBTNode *caseB(TBTNode *par,
                   TBTNode *ptr)
    {
        TBTNode *child;

        // Initialize child Node to be deleted has
        // left child.
        if (ptr->lthread == false)
            child = ptr->left;

        // Node to be deleted has right child.
        else
            child = ptr->right;

        // Node to be deleted is root Node.
        if (par == nullptr)
            root = child;

        // Node is left child of its parent.
        else if (ptr == par->left)
            par->left = child;
        else
            par->right = child;

        // Find successor and predecessor
        TBTNode *s = inorderSuccessor(ptr);
        TBTNode *p = inorderPredecessor(ptr);

        // If ptr has left subtree.
        if (ptr->lthread == false)
            p->right = s;

        // If ptr has right subtree.
        else
        {
            if (ptr->rthread == false)
                s->left = p;
        }

        delete ptr;
        return root;
    }

    // Here 'par' is pointer to parent Node and 'ptr' is
    // pointer to current Node.
    TBTNode *caseC(TBTNode *par,
                   TBTNode *ptr)
    {
        // Find inorder successor and its parent.
        TBTNode *parsucc = ptr;
        TBTNode *succ = ptr->right;

        // Find leftmost child of successor
        while (succ->left != nullptr)
        {
            parsucc = succ;
            succ = succ->left;
        }

        ptr->data = succ->data;

        if (succ->lthread == true && succ->rthread == true)
            root = caseA(parsucc, succ);
        else
            root = caseB(parsucc, succ);

        return root;
    }

    // Deletes a key from threaded BST with given root and
    // returns new root of BST.
    TBTNode *delThreadedBST(int dkey)
    {
        // Initialize parent as NULL and ptrent
        // Node as root.
        TBTNode *par = nullptr, *ptr = root;

        // Set true if key is found
        int found = 0;

        // Search key in BST : find Node and its
        // parent.
        while (ptr != nullptr)
        {
            if (dkey == ptr->data)
            {
                found = 1;
                break;
            }
            par = ptr;
            if (dkey < ptr->data)
            {
                if (ptr->lthread == false)
                    ptr = ptr->left;
                else
                    break;
            }
            else
            {
                if (ptr->rthread == false)
                    ptr = ptr->right;
                else
                    break;
            }
        }

        if (found == 0)
            cout << "Key not present in the tree" << endl;

        // Two Children
        else if (ptr->lthread == false && ptr->rthread == false)
            root = caseC(par, ptr);

        // Only Left Child
        else if (ptr->lthread == false)
            root = caseB(par, ptr);

        // Only Right Child
        else if (ptr->rthread == false)
            root = caseB(par, ptr);

        // No child
        else
            root = caseA(par, ptr);

        return root;
    }
};

int main()
{
    TBinaryTree *myTree = new TBinaryTree();
    int ch, val;
    do
    {
        cout << "Menu\n1.Insert Node\n2.Inorder\n3.Preorder\n4.Delete Node\n5.Exit" << endl;
        cout << "Enter your choice :";
        cin >> ch;

        if (ch == 1)
        {
            cout << "Enter value to be inserted :";
            cin >> val;
            myTree->insert(val);
        }

        else if (ch == 2)
        {
            cout << "Inorder for the Threaded Binary Tree :" << endl;
            myTree->inorder();
        }

        else if (ch == 3)
        {
            cout << "Preorder for the Threaded Binary Tree :" << endl;
            myTree->preorder();
        }
        else if (ch == 4)
        {
            cout << "Enter the value to be deleted :";
            cin >> val;
            myTree->delThreadedBST(val);
        }

        else if (ch != 5)
        {
            cout << "Invalid Choice !!!" << endl;
        }

    } while (ch != 5);
    return 0;
}