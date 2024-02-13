#include <iostream>
#include <string>
using namespace std;

class HashTable;
int hashFunction(string name);
class HashElement
{
    friend class HashTable;
    friend class HashTable1;
    friend class HashTable2;

    string name;
    string telephone;

public:
    HashElement()
    {
        this->name = "--";
        this->telephone = "0";
    }

    HashElement(string name, string telephone)
    {
        this->name = name;
        this->telephone = telephone;
    }

    bool isEmpty()
    {
        return this->name == "--" && this->telephone == "0";
    }
};

class HashTable
{
protected:
    HashElement *hashTable;
    int size;

public:
    HashTable(int n)
    {
        size = n;
        hashTable = new HashElement[n];
    }

    virtual void put(string name, string telephone)
    {
        HashElement newHashElement(name, telephone);
        int hashKey = hashFunction(name) % size;
        int i = hashKey;
        while ((i + 1) % size != hashKey)
        {
            if (hashTable[i].isEmpty())
            {
                hashTable[i] = newHashElement;
                return;
            }
            i++;
        }
    }

    void get(string name)
    {
        int hashKey = hashFunction(name) % size;
        if (hashTable[hashKey].name == name)
        {
            cout << "Comparisons : " << 0 << endl;
            cout << name << " : " << hashTable[hashKey].telephone << endl;
            return;
        }
        int i = hashKey + 1;
        int comp = 1;
        while ((i + 1) % size != hashKey)
        {
            if (hashTable[i].name == name)
            {
                cout << "Comparisons :" << comp << endl;
                cout << name << " : " << hashTable[i].telephone << endl;
                return;
            }
            i++;
            comp++;
        }
        cout << "Record not found" << endl;
    }

    void display()
    {
        for (int i = 0; i < size; i++)
        {

            cout << i << " " << hashTable[i].name << " : " << hashTable[i].telephone << endl;
        }
    }
};

class HashTable1 : virtual public HashTable
{

public:
    HashTable1(int n) : HashTable(n){};
};

class HashTable2 : virtual public HashTable
{
public:
    HashTable2(int n) : HashTable(n){};

    void put(string name, string telephone)
    {
        HashElement newHashElement(name, telephone);
        int hashKey = hashFunction(name) % size;
        int i = hashKey;
        while ((i + 1) % size != hashKey)
        {
            if (hashTable[i].isEmpty())
            {
                hashTable[i] = newHashElement;
                return;
            }
            else
            {
                int newHashKey = hashFunction(hashTable[i].name) % size;
                if (newHashKey != hashKey)
                {
                    hashKey = newHashKey;
                    HashElement temp = newHashElement;
                    newHashElement = hashTable[i];
                    hashTable[i] = temp;
                }
            }
            i++;
        }
    }
};

int main()

{
    HashTable *hashTable;
    int size, ch;
    cout << "Enter the maximum size of the HashTable :";
    cin >> size;
    cout << "Menu\n1.Linear Probling without replacement\n2.Linear Probing with replacement" << endl;
    cout << "Enter your choice : ";
    cin >> ch;
    if (ch == 1)
    {
        hashTable = new HashTable1(size);
    }
    else
    {
        hashTable = new HashTable2(size);
    }
    do
    {
        cout << "Menu\n1.Insert\n2.Search\n3.Display\n4.Exit" << endl;
        cout << "Enter your choice : ";
        cin >> ch;
        if (ch == 1)
        {
            string name, telephone;
            cout << "Enter the name : ";
            cin >> name;
            cout << "Enter telephone : ";
            cin >> telephone;
            hashTable->put(name, telephone);
        }
        else if (ch == 2)
        {
            string name;
            cout << "Enter the name : ";
            cin >> name;
            hashTable->get(name);
        }
        else if (ch == 3)
        {
            hashTable->display();
        }
        else if (ch != 4)
        {
            cout << "Invalid Choice!!!" << endl;
        }

    } while (ch != 4);

    return 0;
}

int hashFunction(string name)
{
    int hashKey = 0;
    for (int i = 0; i < name.length(); i++)
    {
        hashKey += name[i];
    }
    return hashKey;
}