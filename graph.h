#ifndef GRAPH_H
#define GRAPH_H

#include<list>

using namespace std;

class Graph
{
private:
    int V;
    list<int> *adj;

    void DFSUtil(int v, bool visited[]);

public:
    Graph(int V);

    void addEdge(int v, int w);

    bool checkConnectivity();

    //void printGraph()
};

#endif // GRAPH_H
