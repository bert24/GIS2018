#include <iostream>
#include <cstdlib>
#include <string>

#include "utils.h"
#include "scale-free.h"
#include "small-world.h"

// sta³e dla sieci bezskalowej
const int NO_OF_NODES_SF = 50;

// sta³e dla sieci ma³ego œwiata
const int NO_OF_NODES_SM = 50;
const int DEGREE_SM = 6;

using namespace std;

int main()
{
    cout << "Sieci bezskalowa: " << endl;
    cout << "\tliczba wezlow: " << NO_OF_NODES_SF << endl;

    cout << endl;

    cout << "Siec malego swiata: " << endl;
    cout << "\tliczba wezlow: " << NO_OF_NODES_SM << endl;
    cout << "\tliczba stopni: " << DEGREE_SM << endl;

    cout << endl;

    return 0;
}
