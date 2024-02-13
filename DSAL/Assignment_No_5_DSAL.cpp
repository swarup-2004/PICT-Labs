#include <iostream>
#include <string>
#include <functional> // Include for std::hash
using namespace std;

// Universal hash function struct
template <class T>
struct UniversalHash
{
    size_t operator()(const T &key) const
    {
        std::hash<T> hasher;
        return hasher(key);
    }
};

template <class T1, class T2>
class Dictionary;

// Pair class
template <class T1, class T2>
class Pair
{
    friend class Dictionary<T1, T2>;
    T1 key;
    T2 value;
    Pair *next;

public:
    Pair() : next(nullptr) {}                                         // Default constructor
    Pair(T1 key, T2 value) : key(key), value(value), next(nullptr) {} // Parameterized constructor

    bool isEmpty()
    {
        return next == nullptr; // Check if next pointer is nullptr
    }
};

// Dictionary class
template <class T1, class T2>
class Dictionary
{
    Pair<T1, T2> **dictionary;
    int size;
    UniversalHash<T1> hashFunction; // Universal hash function

public:
    Dictionary(int size) : size(size)
    {                                            // Constructor
        dictionary = new Pair<T1, T2> *[size](); // Initialize dictionary array with nullptr
    }

    void insert(T1 key, T2 value)
    {
        size_t hashKey = hashFunction(key) % size;   // Hash the key
        Pair<T1, T2> *&bucket = dictionary[hashKey]; // Reference to the bucket
        Pair<T1, T2> *temp = bucket;
        Pair<T1, T2> *prev = nullptr;
        while (temp != nullptr && temp->key != key)
        { // Traverse the chain
            prev = temp;
            temp = temp->next;
        }
        if (temp == nullptr)
        { // If key not found
            if (prev == nullptr)
            { // If first node
                bucket = new Pair<T1, T2>(key, value);
            }
            else
            { // If middle or last node
                prev->next = new Pair<T1, T2>(key, value);
            }
        }
        else
        { // If key found
            cout << "Duplicate Key!!!" << endl;
        }
    }

    void find(T1 key)
    {
        size_t hashKey = hashFunction(key) % size; // Hash the key
        Pair<T1, T2> *temp = dictionary[hashKey];
        while (temp != nullptr && temp->key != key)
        { // Traverse the chain
            temp = temp->next;
        }
        if (temp != nullptr && temp->key == key)
        { // If key found
            cout << temp->key << " : " << temp->value << endl;
        }
        else
        {
            cout << "Element not found" << endl;
        }
    }

    void remove(T1 key)
    {
        size_t hashKey = hashFunction(key) % size; // Hash the key
        Pair<T1, T2> *temp = dictionary[hashKey];
        Pair<T1, T2> *prev = nullptr;
        while (temp != nullptr && temp->key != key)
        { // Traverse the chain
            prev = temp;
            temp = temp->next;
        }
        if (temp != nullptr && temp->key == key)
        { // If key found
            if (prev == nullptr)
            { // If first node
                dictionary[hashKey] = temp->next;
            }
            else
            {
                prev->next = temp->next;
            }
            delete temp; // Delete node
            cout << "Element removed" << endl;
        }
        else
        {
            cout << "Element not found" << endl;
        }
    }

    ~Dictionary()
    { // Destructor
        for (int i = 0; i < size; ++i)
        { // Delete all nodes
            Pair<T1, T2> *current = dictionary[i];
            while (current != nullptr)
            {
                Pair<T1, T2> *next = current->next;
                delete current;
                current = next;
            }
        }
        delete[] dictionary; // Delete dictionary array
    }
};

int main()
{
    int size;
    cout << "Enter the maximum number of buckets :" << endl;
    cin >> size;
    Dictionary<int, string> dict(size); // Create dictionary object
    int ch;
    do
    {
        cout << "Menu\n1.Insert\n2.Find\n3.Delete\n4.Exit" << endl; // Menu
        cout << "Enter your choice :";
        cin >> ch;
        if (ch == 1)
        { // Insert
            int key;
            string val;
            cout << "Enter the key :";
            cin >> key;
            cout << "Enter the value :";
            cin >> val;
            dict.insert(key, val);
        }
        else if (ch == 2)
        { // Find
            int key;
            cout << "Enter the key :";
            cin >> key;
            dict.find(key);
        }
        else if (ch == 3)
        { // Remove
            int key;
            cout << "Enter the key :";
            cin >> key;
            dict.remove(key);
        }
        else if (ch != 4)
        { // Invalid choice
            cout << "Invalid choice!!!" << endl;
        }
    } while (ch != 4);
    return 0;
}
