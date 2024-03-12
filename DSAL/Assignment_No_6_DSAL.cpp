#include <iostream>
#include <string>
#include <queue>
#include <set>
#include <stack>
using namespace std;

// Forword Declaration
class Graph;

class GraphNode
{
    string city;     // Name of the city
    GraphNode *next; // Nodes connected to the current node
    GraphNode *down; // Next Node in the list

public:
    // Declaring Friend Class
    friend class Graph;

    // Default constructor
    GraphNode()
    {
        next = down = nullptr;
    }
    // Parameterized constructor
    GraphNode(string city)
    {
        this->city = city;
        next = down = nullptr;
    }
};

class Graph
{

    GraphNode *head; // Pointer to the array storing adjacency list
    int size;        // Size of the graph

public:
    // Constructor
    Graph(int size)
    {
        this->size = size;
        head = new GraphNode("City");
        head = createGraph();
    }

    // Creating a Graph
    GraphNode *createGraph()
    {
        GraphNode *temp = head;
        // Traversing through each vertex
        for (int i = 0; i < size; i++)
        {
            string city;
            int degree;
            cout << "Enter the city :";
            cin >> city;
            cout << "Enter the number of connected cities :";
            cin >> degree;
            GraphNode *newNode = new GraphNode(city);
            GraphNode *temp2 = newNode;
            for (int i = 0; i < degree; i++)
            {
                string city;
                cout << "Enter the city connected to the " << newNode->city << " : ";
                cin >> city;
                GraphNode *cityNode = new GraphNode(city);
                temp2->next = cityNode;
                temp2 = temp2->next;
            }

            temp->down = newNode;
            temp = temp->down;
        }
        return head;
    }

    // Displayig Adjacency List
    void display()
    {
        if (head == nullptr)
        {
            cout << "Empty List" << endl;
            return;
        }
        GraphNode *temp = head->down;
        while (temp != nullptr)
        {
            cout << temp->city << " : ";
            GraphNode *temp2 = temp->next;
            while (temp2 != nullptr)
            {
                cout << temp2->city << " ";
                temp2 = temp2->next;
            }
            cout << endl;
            temp = temp->down;
        }
    }

    // Finding out degree of the Nodes
    void degree()
    {
        if (head == nullptr)
        {
            cout << "Empty List" << endl;
            return;
        }
        GraphNode *temp = head->down;
        while (temp != nullptr)
        {

            int count = 0;
            GraphNode *temp2 = temp->next;
            while (temp2 != nullptr)
            {
                count++;
                temp2 = temp2->next;
            }
            cout << temp->city << " : " << count << endl;
            temp = temp->down;
        }
    }

    // Function for the BFS
    void BFS()
    {
        set<string> visited;
        GraphNode *temp = head->down;
        queue<GraphNode *> q;
        q.push(temp);
        while (!q.empty())
        {
            GraphNode *popped = q.front();
            q.pop();
            auto vis = visited.find(popped->city);
            if (vis == visited.end())
            {
                cout << popped->city << " ";
                visited.insert(popped->city);
                GraphNode *temp2 = popped->next;
                while (temp2 != nullptr)
                {
                    auto temp2_vis = visited.find(temp2->city);
                    if (temp2_vis == visited.end())
                    {
                        GraphNode *temp3 = temp->down;
                        while (temp3 != nullptr)
                        {
                            if (temp3->city == temp2->city)
                            {
                                q.push(temp3);
                                break;
                            }
                            temp3 = temp3->down;
                        }
                    }
                    temp2 = temp2->next;
                }
            }
        }
        cout << endl;
    }

    // Helper function for the BFS
    void bfsHelp(GraphNode *temp, set<string> &visited)
    {
        queue<GraphNode *> q;
        q.push(temp);
        while (!q.empty())
        {
            GraphNode *popped = q.front();
            q.pop();
            auto vis = visited.find(popped->city);
            if (vis == visited.end())
            {
                cout << popped->city << " ";
                visited.insert(popped->city);
                GraphNode *temp2 = popped->next;
                while (temp2 != nullptr)
                {
                    auto temp2_vis = visited.find(temp2->city);
                    if (temp2_vis == visited.end())
                    {
                        GraphNode *temp3 = temp->down;
                        while (temp3 != nullptr)
                        {
                            if (temp3->city == temp2->city)
                            {
                                q.push(temp3);
                                break;
                            }
                            temp3 = temp3->down;
                        }
                    }
                    temp2 = temp2->next;
                }
            }
        }
    }

    // Function for the BFS
    void bfs()
    {
        set<string> visited;
        GraphNode *temp = head->down;
        while (temp != nullptr)
        {
            auto vis = visited.find(temp->city);
            if (vis == visited.end())
            {
                bfsHelp(temp, visited);
                cout << endl;
            }
            temp = temp->down;
        }
    }

    // Helper function for DFS
    void dfsHelp(GraphNode *temp, set<string> &visited)
    {
        stack<GraphNode *> stk;
        stk.push(temp);
        while (!stk.empty())
        {
            GraphNode *current = stk.top();
            stk.pop();
            string currcity;
            if (visited.find(current->city) == visited.end())
            {
                currcity = current->city;
                cout << current->city << " ";
                visited.insert(current->city);
            }
            GraphNode *temp2 = current->next;

            while (temp2 != nullptr)
            {
                string nextcity;
                auto vis = visited.find(temp2->city);
                if (vis == visited.end())
                {
                    nextcity = temp2->city;
                    GraphNode *temp3 = head->down;
                    while (temp3 != nullptr)
                    {
                        string imp = temp3->city;
                        if (temp3->city == temp2->city)
                        {
                            stk.push(temp3);
                            break;
                        }
                        temp3 = temp3->down;
                    }
                }
                temp2 = temp2->next;
            }
        }
    }

    // Function for the DFS
    void dfs()
    {
        set<string> visited;
        GraphNode *temp = head->down;
        while (temp != nullptr)
        {
            auto vis = visited.find(temp->city);
            if (vis == visited.end())
            {
                dfsHelp(temp, visited);
                cout << endl;
            }
            temp = temp->down;
        }
    }
};

int main()
{
    Graph g(4);
    g.display();
    g.degree();
    g.bfs();
    g.dfs();
    return 0;
}