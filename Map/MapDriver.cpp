#include <iostream>
#include "Map.h"
using namespace std;

// Function to test loading and validating maps
void testLoadMaps() {
    Map* map_instance1 = MapLoader::instantiation("../Warzone/Map/MapFiles/Europe.txt");
    Map* map_instance2 = MapLoader::instantiation("../Warzone/Map/MapFiles/USA.txt");
    Map* map_instance3 = MapLoader::instantiation("../Warzone/Map/MapFiles/Africa.txt");

    cout << "--- Europe ---" << endl;
    map_instance1->validate();
    cout << "--- USA ---" << endl;
    map_instance2->validate();
    cout << "--- Africa ---" << endl;
    map_instance3->validate();

    delete map_instance1;
    delete map_instance2;
    delete map_instance3;
}

int main() {
    // Call the testLoadMaps function
    testLoadMaps();

    return 0;
}