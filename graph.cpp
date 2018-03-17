#include<iostream>
#include<list>

#include"Graph.h"

using namespace std;

int visitedNodes = 0;

Graph::Graph(int V)
{
    this->V = V;
    adj = new list<int>[V+1];
}

void Graph::addEdge(int v, int w)
{
     cout  << "addEdge: V-" << V << "  krawedz: " << v << " , "<< w << endl << endl;
    adj[v].push_back(w);
}

void Graph::DFSUtil(int v, bool visited[])
{
    visited[v] = true;

    visitedNodes++;

    cout << v << " ";

    list<int>::iterator i;
    for (i = adj[v].begin(); i != adj[v].end(); ++i)
        if (!visited[*i])
            DFSUtil(*i, visited);
}

bool Graph::checkConnectivity()
{
    cout << endl << endl << "checkConnectivity (poczatek): V-" << V << endl;
    bool *visited = new bool[V];
    for (int i = 0; i < V; i++)
        visited[i] = false;

    DFSUtil(2, visited);
    cout << endl << endl << "checkConnectivity (po DFSUtil): visited nodes-" << visitedNodes << ", V- " << V << endl;
    if(visitedNodes == V){
        return true;

    }

    return false;
}
/*
void Graph::printGraph()
{

	for(int i = 0; i < V; i++) {
		count = 0;
		cout<<"\n\t"<<i+1<<"-> { ";
		for(int j = 0; j < edges; j++) {
			if(edge[j][0] == i+1) {
				cout<<edge[j][1]<<"   ";
				count++;

			} else if(edge[j][1] == i+1) {
				cout<<edge[j][0]<<"   ";
				count++;

			} else if(j == edges-1 && count == 0)
				cout<<"Isolated Vertex!";
		}
		cout<<" }";
	}

	//*******
    int count;
    for(int i = 0; i < V; i++) {
		count = 0;
		cout<<"\n\t"<<i+1<<"-> { ";
		for (auto v : adj[i+1])
            cout << v << "   ";
		cout<<"}";
	}
}
*/
