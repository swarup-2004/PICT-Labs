#include <iostream>
#include <vector>
#include <queue>
using namespace std;

// Forward declaration
class Graph;

// Class representing an edge in the graph
class Edge
{
    int src;
    int dest;
    int wei;

public:
    friend class Graph;

    // Constructor for Edge
    Edge(int src, int dest, int wei)
    {
        this->src = src;
        this->dest = dest;
        this->wei = wei;
    }

    // Overloading output stream operator for Edge
    friend ostream &operator<<(ostream &os, const Edge &edge)
    {
        os << edge.src << "->" << edge.dest << " (Weight: " << edge.wei << ")";
        return os;
    }
};

// Class representing a pair of office and its distance
class Pair
{
    int office;
    int distance;

public:
    friend class Graph;
    // Constructor for Pair
    Pair(int office, int distance)
    {
        this->office = office;
        this->distance = distance;
    }

    // Overloading less than operator for Pair
    bool operator<(const Pair &p2) const
    {
        return distance > p2.distance; // For min priority queue
    }
};

// Class representing the graph
class Graph
{
    vector<Edge> *graph;
    int size;

public:
    // Constructor for Graph
    Graph(int size)
    {
        this->size = size;
        graph = new vector<Edge>[size];
        for (int i = 0; i < size; i++)
        {
            vector<Edge> v;
            graph[i] = v;
        }
        create();
    }

    // Function to create the graph
    void create()
    {
        for (int i = 0; i < size; i++)
        {
            int degree;
            cout << "Enter the number of connected offices for office " << i << " :";
            cin >> degree;
            for (int j = 0; j < degree; j++)
            {
                int office, distance;
                cout << "Enter the connected office to office " << i << " :";
                cin >> office;
                cout << "Enter the distance between office " << i << " and office " << office << " :";
                cin >> distance;
                graph[i].push_back(Edge(i, office, distance));
            }
        }
    }

    // Function to display the graph
    void display()
    {
        for (int i = 0; i < size; i++)
        {
            cout << "Edges from office " << i << ": ";
            for (int j = 0; j < graph[i].size(); j++)
            {
                cout << graph[i][j] << " ";
            }
            cout << endl;
        }
    }

    // Function to find the minimum spanning tree cost
    int minimumSpanningTree()
    {
        int cost = 0;
        priority_queue<Pair> pq;
        bool visited[size] = {false}; // Array to keep track of visited offices

        // Start with office 0
        pq.push(Pair(0, 0));

        // Loop until priority queue is empty
        while (!pq.empty())
        {
            Pair current = pq.top();
            pq.pop();

            // If the office is not visited yet
            if (!visited[current.office])
            {
                visited[current.office] = true; // Mark the office as visited
                cost += current.distance;       // Add distance to the total cost

                // Explore all neighbors of the current office
                for (int i = 0; i < graph[current.office].size(); i++)
                {
                    Edge neighbor = graph[current.office][i];
                    if (!visited[neighbor.dest])
                    {
                        // Push neighbor into the priority queue
                        pq.push(Pair(neighbor.dest, neighbor.wei));
                    }
                }
            }
        }
        return cost;
    }
};

int main()
{
    int numOffices;
    cout << "Enter the number of offices: ";
    cin >> numOffices;
    Graph g(numOffices);
    g.display();
    cout << "Minimum spanning tree cost: " << g.minimumSpanningTree() << endl;
    return 0;
}
