#include <iostream>
#include <cstdlib>
#include <string>
#include <ctime>
#include <cstdio>

#include"Graph.h"

// stale dla sieci bezskalowej
const int NO_OF_NODES_SF = 50;

// stale dla sieci malego œwiata
const int NO_OF_NODES_SW = 20;
const int DEGREE_SM = 4;
const double BETA = 0.5;

using namespace std;

Graph smallWorldGraph(NO_OF_NODES_SW);

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

void generateSmallWorldGraphTest(int nodes, int degree, double beta) {
    if(degree%2 != 0 || degree <= 0 || degree >= nodes) {
        cout << "Niepoprawne parametry.\n";
        return;
    }

    int edges = (nodes*degree)/2;
    int count, i=0, j=0, edge[edges][2];
    double number;

    for (i=0; i<nodes; i++) {
        for (j=0; j<degree/2; j++) {
            edge[((degree/2)*i)+j][0] = i+1;
            edge[((degree/2)*i)+j][1] = i+j+2;

            if(i+j+2 > nodes)
                edge[((degree/2)*i)+j][1] = edge[((degree/2)*i)+j][1] - nodes;

            if(beta != 0.0) {
                number = ((double)rand() / RAND_MAX);
                cout << number << " : ";
                if(number <= beta) {
                    do {
                        edge[((degree/2)*i)+j][1] = ((((int)rand()) % nodes) + 1);
                        cout << i << "|"<< j << " - "<<edge[((degree/2)*i)+j][0] << " , "<< edge[((degree/2)*i)+j][1];
                    } while(edge[((degree/2)*i)+j][1] == edge[((degree/2)*i)+j][0]);
                }
                cout << endl;
            }
            cout << "Dodawana krawedz nr " << ((degree/2)*i)+j+1 << ": ";
            cout << edge[((degree/2)*i)+j][0] << " , " <<  edge[((degree/2)*i)+j][1]  << endl;
            smallWorldGraph.addEdge(edge[((degree/2)*i)+j][0], edge[((degree/2)*i)+j][1]);
        }
    }

	cout<<"\nThe generated small world graph is: ";
	i=0;
	for(i = 0; i < nodes; i++) {
		count = 0;
		cout<<"\n\t"<<i+1<<"-> { ";
		for(j = 0; j < edges; j++) {
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

	return;
}

int main()
{
    srand(time(NULL));
    printData();


    generateSmallWorldGraphTest(NO_OF_NODES_SW, DEGREE_SM, BETA);

    cout << endl;
    //smallWorldGraph.printGraph();

    bool smallWorldGraphConnectivity = smallWorldGraph.checkConnectivity();

    if(smallWorldGraphConnectivity == true)
        cout << endl << "Graf spojny" << endl;

    if(smallWorldGraphConnectivity == false)
        cout << endl << "Graf niespojny" << endl;

    return 0;
}
