// Program to check if a given directed graph is strongly connected or not
#include <iostream>
#include <list>
#include <stack>
#include <cstdlib>
#include <string>
#include <ctime>
#include <cstdio>

using namespace std;

// consts for scalefree network
const int NO_OF_NODES_SF = 50;

// consts for small-word network
const int NO_OF_NODES_SW = 40;
const int DEGREE_SM = 4;
const double BETA = 0.0;

// general consts
const int MAX_NODES = 1000;

// Storage for visited nodes
bool visited[MAX_NODES];

void printData() {
    cout << "Sieci bezskalowa: " << endl;
    cout << "\tliczba wezlow: " << NO_OF_NODES_SF << endl;

    cout << endl;

    cout << "Siec malego swiata: " << endl;
    cout << "\tliczba wezlow: " << NO_OF_NODES_SW << endl;
    cout << "\tliczba stopni: " << DEGREE_SM << endl;
    cout << "\tparametr beta: " << BETA << endl;

    cout << endl;
}

//**************** BEGIN OF GRAPH CLASS *****************
class Graph
{
    int V;    // No. of vertices
    bool directed;
    list<int> *adj;    // An array of adjacency lists

    // A recursive function to print DFS starting from v
    void DFSUtil(int v, bool visited[]);
public:
    // Constructor and Destructor
    Graph(int V, bool directed)
    {
        this->V = V;
        this->directed = directed;
        adj = new list<int>[V];
    }
    ~Graph() { delete [] adj; }

    // Method to add an edge
    void addEdge(int v, int w);

    // Method to remove a random edge
    void removeRandomEdge();

    // The main method that returns true if the graph is strongly
    // connected, otherwise false
    bool isSC();

    // Method that returns reverse (or transpose) of this graph
    Graph* getTranspose();

    // Method that print the graph
    void printGraph();
};

// A recursive function to print DFS starting from v
void Graph::DFSUtil(int v, bool visited[])
{
    // Mark the current node as visited and print it
    visited[v] = true;

    // Recur for all the vertices adjacent to this vertex

    list<int>::iterator i;
    for (i = adj[v].begin(); i != adj[v].end(); ++i)
        if (!visited[*i])
            DFSUtil(*i, visited);
}

// Function that returns reverse (or transpose) of this graph
Graph* Graph::getTranspose()
{
    Graph* g = new Graph(V, directed);
    for (int v = 0; v < V; v++)
    {
        // Recur for all the vertices adjacent to this vertex
        list<int>::iterator i;
        for(i = adj[v].begin(); i != adj[v].end(); ++i)
            g->adj[*i].push_back(v);
    }
    return g;
}

void Graph::addEdge(int v, int w)
{
    adj[v].push_back(w);

    if (!directed)
        adj[w].push_back(v);
}

void Graph::removeRandomEdge()
{
    int firstNode = ((int)rand()) % V;

    int positionOfSecondNode = ((int)rand()) % adj[firstNode].size();
    list<int>::iterator it = adj[firstNode].begin();
    advance (it, positionOfSecondNode);

    adj[firstNode].remove(*it);

    if (!directed)
        adj[*it].remove(firstNode);

}

// The main function that returns true if graph is strongly connected
bool Graph::isSC()
{
    // Step 1: Mark all the vertices as not visited (For first DFS)

    for (int i = 0; i < V; i++)
        visited[i] = false;

    // Step 2: Do DFS traversal starting from first vertex.
    DFSUtil(0, visited);

     // If DFS traversal doesn’t visit all vertices, then return false.
    for (int i = 0; i < V; i++)
        if (visited[i] == false)
             return false;

    // Step 3: Create a reversed graph
    Graph* gr = getTranspose();

    // Step 4: Mark all the vertices as not visited (For second DFS)
    for(int i = 0; i < V; i++)
        visited[i] = false;

    // Step 5: Do DFS for reversed graph starting from first vertex.
    // Starting Vertex must be same starting point of first DFS
    gr->DFSUtil(0, visited);

    // If all vertices are not visited in second DFS, then
    // return false
    for (int i = 0; i < V; i++)
        if (visited[i] == false)
             return false;

    return true;
}

void Graph::printGraph()
{
    for(int i = 0; i < V; i++)
    {
        cout << i << " -> { ";
        for(list<int>::iterator it = adj[i].begin(); it != adj[i].end(); ++it)
            cout << *it << "  ";

        cout << "}\n";
    }
}
//**************** END OF GRAPH CLASS *****************


// Generating network
Graph* generateSmallWorldGraph(int nodes, int degree, double beta, bool directed)
{
    if(degree%2 != 0 || degree <= 0 || degree >= nodes || nodes > MAX_NODES)
    {
        cout << "Niepoprawne parametry.\n";
        return nullptr;
    }

    Graph* g = new Graph(nodes, directed);

    int edge[2];
    double randNumber;

    for(int i=0; i<nodes; i++)
    {
        for(int j=0; j<degree/2; j++)
        {
            if(i+j+2 > nodes)
            {
                edge[0] = i;
                edge[1] = i+j+1-nodes ;
            } else
            {
                edge[0] = i;
                edge[1] = i+j+1 ;
            }

            if(beta != 0.0)
            {
                randNumber = ((double)rand() / RAND_MAX);

                if(randNumber <= beta)
                {
                    do {
                        edge[1] = ((int)rand()) % nodes;
                    } while(edge[0] == edge[1]);
                }
            }

            //cout << "dodana krawedz: " << edge[0] << " , " << edge[1] << endl;
            g->addEdge(edge[0], edge[1]);
        }
    }

	return g;
}

int main()
{
    srand(time(NULL));

    printData();

    Graph* smallWorldGraph = generateSmallWorldGraph(NO_OF_NODES_SW, DEGREE_SM, BETA, false);

    if (smallWorldGraph == nullptr)
        return 1;

    cout << "PRZED USUNIECIEM:\n";
    smallWorldGraph->printGraph();
    cout << "Graf malego swiata przed usunieciem krawedzi jest:\t";
    smallWorldGraph->isSC() ? cout << "spojny.\n" :
                cout << "niespojny.\n";

    smallWorldGraph->removeRandomEdge();

    cout << "\nPO USUNIECIU:\n";
    smallWorldGraph->printGraph();
    cout << "Graf malego swiata po usunieciu krawedzi jest:\t\t";
    smallWorldGraph->isSC() ? cout << "spojny.\n" :
                cout << "niespojny.\n";

    return 0;
}
