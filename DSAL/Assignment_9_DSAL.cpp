#include <iostream>
#include <string>
using namespace std;

class AVLTree;

class Node
{
    friend class AVLTree;
    string word, meaning;
    Node *left, *right;
    int height;

public:
    Node()
    {
        left = right = nullptr;
    }

    Node(string word, string meaning)
    {
        this->word = word;
        this->meaning = meaning;
        this->height = 1;
        left = right = nullptr;
    }
};

class AVLTree
{
    Node *root;

public:
    AVLTree()
    {
        root = nullptr;
    }

    Node *rotateRight(Node *node)
    {
        Node *x = node->left;
        Node *y = x->right;

        // Rotation
        x->right = node;
        node->left = y;

        // Update heights
        node->height = 1 + max((node->left ? node->left->height : 0), (node->right ? node->right->height : 0));
        x->height = 1 + max((x->left ? x->left->height : 0), (x->right ? x->right->height : 0));

        return x;
    }

    Node *rotateLeft(Node *node)
    {
        Node *x = node->right;
        Node *y = x->left;

        // Rotation
        x->left = node;
        node->right = y;

        // Update heights
        node->height = 1 + max((node->left ? node->left->height : 0), (node->right ? node->right->height : 0));
        x->height = 1 + max((x->left ? x->left->height : 0), (x->right ? x->right->height : 0));

        return x;
    }

    Node *insert(Node *node, string word, string meaning)
    {
        if (node == nullptr)
        {
            return new Node(word, meaning);
        }

        if (node->word > word)
        {
            node->left = insert(node->left, word, meaning);
        }
        else if (node->word < word)
        {
            node->right = insert(node->right, word, meaning);
        }
        else
        {
            return node; // Duplicate word, do nothing
        }

        // Update height of the current node
        node->height = 1 + max((node->left ? node->left->height : 0), (node->right ? node->right->height : 0));

        // Calculate balance factor
        int balance = (node->left ? node->left->height : 0) - (node->right ? node->right->height : 0);

        // Perform rotations if necessary

        // Left Left case
        if (balance > 1 && word < node->left->word)
        {
            return rotateRight(node);
        }

        // Right Right case
        if (balance < -1 && word > node->right->word)
        {
            return rotateLeft(node);
        }

        // Left Right case
        if (balance > 1 && word > node->left->word)
        {
            node->left = rotateLeft(node->left);
            return rotateRight(node);
        }

        // Right Left case
        if (balance < -1 && word < node->right->word)
        {
            node->right = rotateRight(node->right);
            return rotateLeft(node);
        }

        return node;
    }

    Node *deleteWord(string word, Node *node)
    {
        if (node == nullptr)
        {
            return nullptr;
        }

        if (node->word < word)
        {
            node->right = deleteWord(word, node->right);
        }
        else if (node->word > word)
        {
            node->left = deleteWord(word, node->left);
        }
        else
        {
            // No child or Single child
            if (node->left == nullptr)
            {
                Node *temp = node->right;
                delete node;
                return temp;
            }
            else if (node->right == nullptr)
            {
                Node *temp = node->left;
                delete node;
                return temp;
            }

            // Two children
            Node *inorderSuccessor = node->right;
            while (inorderSuccessor->left != nullptr)
            {
                inorderSuccessor = inorderSuccessor->left;
            }

            node->word = inorderSuccessor->word;
            node->meaning = inorderSuccessor->meaning;

            node->right = deleteWord(inorderSuccessor->word, node->right);
        }

        // Update height of the current node
        node->height = 1 + max((node->left ? node->left->height : 0), (node->right ? node->right->height : 0));

        // Calculate balance factor
        int balance = (node->left ? node->left->height : 0) - (node->right ? node->right->height : 0);

        // Perform rotations if necessary

        // Left Left case
        if (balance > 1 && word < node->left->word)
        {
            return rotateRight(node);
        }

        // Right Right case
        if (balance < -1 && word > node->right->word)
        {
            return rotateLeft(node);
        }

        // Left Right case
        if (balance > 1 && word > node->left->word)
        {
            node->left = rotateLeft(node->left);
            return rotateRight(node);
        }

        // Right Left case
        if (balance < -1 && word < node->right->word)
        {
            node->right = rotateRight(node->right);
            return rotateLeft(node);
        }

        return node;
    }

    void update(string word, string meaning)
    {
        Node *temp = root;
        bool flag = true;
        while (temp != nullptr)
        {
            if (temp->word == word)
            {
                temp->meaning = meaning;
                flag = false;
                cout << "Updated Successfully" << endl;
                break;
            }
            else if (temp->word > word)
            {
                temp = temp->left;
            }
            else
            {
                temp = temp->right;
            }
        }

        if (flag)
        {
            cout << "Word Doesn't exist" << endl;
        }
    }

    bool searchWord(string word, int &comparisons)
    {
        Node *temp = root;
        comparisons = 0;
        while (temp != nullptr)
        {
            comparisons++;
            if (temp->word == word)
            {
                cout << temp->meaning << endl;
                return true; // Word found
            }
            else if (temp->word > word)
            {
                temp = temp->left;
            }
            else
            {
                temp = temp->right;
            }
        }
        return false; // Word not found
    }

    void display(Node *root)
    {
        if (root == nullptr)
        {
            return;
        }
        display(root->left);
        cout << root->word << " ";
        display(root->right);
    }

    void menu()
    {
        int choice;
        string word, meaning;
        while (true)
        {
            cout << "\nAVL Tree Menu\n";
            cout << "1. Insert a word\n";
            cout << "2. Delete a word\n";
            cout << "3. Update meaning of a word\n";
            cout << "4. Search for a word\n";
            cout << "5. Display the AVL Tree\n";
            cout << "6. Exit\n";
            cout << "Enter your choice: ";
            cin >> choice;

            switch (choice)
            {
            case 1:
                cout << "Enter word to insert: ";
                cin >> word;
                cout << "Enter meaning: ";
                cin.ignore();
                getline(cin, meaning);
                root = insert(root, word, meaning);
                cout << "Word inserted successfully." << endl;
                break;
            case 2:
                cout << "Enter word to delete: ";
                cin >> word;
                root = deleteWord(word, root);
                cout << "Word deleted successfully." << endl;
                break;
            case 3:
                cout << "Enter word to update: ";
                cin >> word;
                cout << "Enter new meaning: ";
                cin.ignore();
                getline(cin, meaning);
                update(word, meaning);
                break;
            case 4:
                cout << "Enter word to search: ";
                cin >> word;
                int comparisons;
                if (searchWord(word, comparisons))
                {
                    cout << "Word found. Comparisons made: " << comparisons << endl;
                }
                else
                {
                    cout << "Word not found. Comparisons made: " << comparisons << endl;
                }
                break;
            case 5:
                display(root);
                cout << endl;
                break;
            case 6:
                cout << "Exiting program." << endl;
                return;
            default:
                cout << "Invalid choice. Please enter again." << endl;
            }
        }
    }
};

int main()
{
    AVLTree avl;
    avl.menu();
    return 0;
}
