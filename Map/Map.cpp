#include <iostream>
#include "Map.h"
#include <string>
#include <sstream>
#include <fstream>
#include <regex>
#include <vector>
#include <map>
#include <set>
#include <stack>
using namespace std;




//****************************************** TERRITORY IMPLEMENTATION ****************************************
//Default constructor (initializer list format)
Territory::Territory()
    :name(""), army_size(0), x_coord(0), y_coord(0), id(nullptr), player_id(0){
}
//Parameterized constructor
Territory::Territory(string name, int army_size, int x_coord, int y_coord, vector<Territory*> adjacent_territory, Continent* id, int player_id)
    :name(name), army_size(army_size), x_coord(x_coord), y_coord(y_coord), adjacent_territory(adjacent_territory),
    id(id), player_id(player_id){
}
//Copy constructor
Territory::Territory(const Territory& ter_cpy){
    name = ter_cpy.name;
    army_size = ter_cpy.army_size;
    x_coord = ter_cpy.x_coord;
    y_coord = ter_cpy.y_coord;
    player_id = ter_cpy.player_id;

    //Deep Copy for id
    id = new Continent();
    *id = *(ter_cpy.id);
    //Deep Copy for adjacent_territory
    for (Territory* adjacent : ter_cpy.adjacent_territory) {
        Territory* newAdjacent = new Territory(*adjacent);
        adjacent_territory.push_back(newAdjacent);
    }
}
//Destructor
Territory::~Territory(){
    //Deallocate memory for id
    delete id;
    //Deallocate memory for each element in adjacent_territory vector
    for (Territory* adjacent : adjacent_territory) {
        delete adjacent;
    }
    //Clear the vector after deleting its elements to avoid dangling pointers
    adjacent_territory.clear();
}

//Getter
string Territory::get_name() const{
    return name;
}
int Territory::get_army_size() const{
    return army_size;
}
int Territory::get_x_coord() const{
    return x_coord;
}
int Territory::get_y_coord() const{
    return y_coord;
}
int Territory::get_player_id() const {
    return player_id;
}
vector<Territory*> Territory::get_adjacent_territories() const{
    return adjacent_territory;
}
Continent* Territory::get_continent() const{
    return id;
}

//Setter
void Territory::set_name(string new_name){
    name = new_name;
}
void Territory::set_army_size(int new_army_size){
    army_size = new_army_size;
}
void Territory::set_x_coord(int new_x_coord){
    x_coord = new_x_coord;
}
void Territory::set_y_coord(int new_y_coord){
    y_coord = new_y_coord;
}
void Territory::set_player_id(int new_player_id) {
    player_id = new_player_id;
}
void Territory::set_continent(Continent *new_continent){
    id = new_continent;
}

//Methods
void Territory::add_adjacent_territory(Territory* adjacent){
    adjacent_territory.push_back(adjacent);
}
void Territory::print_all_adjacent() const{
    for(const auto& obj : adjacent_territory){
        cout << *obj;
    }
}

//Assignment operator
Territory& Territory::operator=(const Territory& ter_cpy){
    //Self-assignment check
    if(this == &ter_cpy){
        return *this;
    }
    //Copy
    name = ter_cpy.name;
    army_size = ter_cpy.army_size;
    x_coord = ter_cpy.x_coord;
    y_coord = ter_cpy.y_coord;
    player_id = ter_cpy.player_id;

    //Deep Copy for id
    if (id != nullptr) {
        delete id;
    }
    id = new Continent();
    *id = *(ter_cpy.id);

    //Deallocate memory for each element and perform a deep copy
    for (Territory* adjacent : adjacent_territory) {
        delete adjacent;
    }
    adjacent_territory.clear();
    for (Territory* adjacent : ter_cpy.adjacent_territory) {
        Territory* newAdjacent = new Territory(*adjacent);
        adjacent_territory.push_back(newAdjacent);
    }
    //Dereference current object and return it so we can chain this operator
    return *this;
}

//Stream insertion (global function)
ostream& operator<<(ostream& out, const Territory& ter_cpy){
    out << "NAME: " << ter_cpy.get_name() << endl;
    out << "ARMY SIZE: " << ter_cpy.get_army_size() << endl;
    out << "x:" << ter_cpy.x_coord << ", y:" << ter_cpy.y_coord << endl;
    out << "PLAYER ID: " << ter_cpy.get_player_id() << endl;
    out << "CONTINENT: " << ter_cpy.id->get_name() << "\n\n";
    return out;
}



//****************************************** CONTINENT IMPLEMENTATION ****************************************
//Default Constructor (initializer list format)
Continent::Continent()
    :name(""), bonus_army(0){
}
//Parameterized Constructor
Continent::Continent(string name, int bonus_army, vector<Territory*> territories_within)
    :name(name), bonus_army(bonus_army), territories_within(territories_within){
}
//Copy Constructor
Continent::Continent(const Continent& cont_cpy){
    name = cont_cpy.name;
    bonus_army = cont_cpy.bonus_army;
    //Deep Copy for territories_within
    for (Territory* territory : cont_cpy.territories_within) {
        Territory* newTerritory = new Territory(*territory);
        territories_within.push_back(newTerritory);
    }
}
//Destructor
Continent::~Continent(){
    //Deallocate memory for each element in territories_within vector
    for (Territory* territory : territories_within) {
        delete territory;
    }
    //Clear the vector after deleting its elements to avoid dangling pointers
    territories_within.clear();
}

//Getter
string Continent::get_name() const{
    return name;
}
int Continent::get_bonus_army() const{
    return bonus_army;
}
vector<Territory*> Continent::get_territories_within() const{
    return territories_within;
}

//Setter
void Continent::set_name(std::string new_name){
    name = new_name;
}
void Continent::set_bonus_army(int new_bonus_army){
    bonus_army = new_bonus_army;
}
void Continent::set_territories_within(vector<Territory*> new_territories){
    territories_within = new_territories;
}

//Methods
void Continent::add_within(Territory* territory){
    territories_within.push_back(territory);
}
void Continent::print_all_in_continent(){
    for(const auto& obj : territories_within){
        cout << *obj;
    }
}

//Assignment operator
Continent& Continent::operator=(const Continent &cont_cpy){
    if(this == &cont_cpy){
        return *this;
    }
    // Copy
    name = cont_cpy.name;
    bonus_army = cont_cpy.bonus_army;

    //Deallocate memory for each element and perform a deep copy
    for (Territory* territory : territories_within) {
        delete territory;
    }
    territories_within.clear();
    for (Territory* territory : cont_cpy.territories_within) {
        Territory* newTerritory = new Territory(*territory);
        territories_within.push_back(newTerritory);
    }
    //Dereference current object and return it so we can chain this operator
    return *this;
}

//Stream insertion operator
ostream& operator<<(ostream& out, const Continent& cont_cpy){
    out << "Name: " << cont_cpy.get_name() << " | Bonus_Army: " << cont_cpy.get_bonus_army() << endl;
    return out;
}



//****************************************** MAP IMPLEMENTATION ****************************************
Map::Map(){
}
Map::Map(vector<Territory*> all_territories, vector<Continent*> all_continents)
    :all_territories(all_territories), all_continents(all_continents){
}
Map::Map(const Map &map_cpy){
    //Deep Copy for all_territories and all_continents
    for (Territory* territory : map_cpy.all_territories) {
        Territory* newTerritory = new Territory(*territory);
        all_territories.push_back(newTerritory);
    }
    for (Continent* continent : map_cpy.all_continents) {
        Continent* newContinent = new Continent(*continent);
        all_continents.push_back(newContinent);
    }
}
Map::~Map(){
    //Deallocate memory for each element in all_territories vector
    for (Territory* territory : all_territories) {
        delete territory;
    }
    all_territories.clear();
    //Deallocate memory for each element in all_continents vector
    for (Continent* continent : all_continents) {
        delete continent;
    }
    all_continents.clear();
}

//Getter
vector<Territory*> Map::get_all_territories() {
    return all_territories;
}


//Assignment operator
Map& Map::operator=(const Map &map_cpy){
    if(this == &map_cpy){
        return *this;
    }
    //Deallocate memory for each element and perform a deep copy
    for (Territory* territory : all_territories) {
        delete territory;
    }
    all_territories.clear();
    for (Territory* territory : map_cpy.all_territories) {
        Territory* newTerritory = new Territory(*territory);
        all_territories.push_back(newTerritory);
    }
    //Deallocate memory for each element and perform a deep copy
    for (Continent* continent : all_continents) {
        delete continent;
    }
    all_continents.clear();
    for (Continent* continent : map_cpy.all_continents) {
        Continent* newContinent = new Continent(*continent);
        all_continents.push_back(newContinent);
    }
    //Dereference current object and return it so we can chain this operator
    return *this;
}

//Insertion stream operator
ostream& operator<<(ostream& out, const Map& map_cpy){
    out << "--TERRITORIES--" << endl;
    for(const auto &obj : map_cpy.all_territories){
        out << obj->get_name() << endl;
    }
    out << endl << "--CONTINENTS--" << endl;
    for(const auto &obj : map_cpy.all_continents){
        out << obj->get_name() << endl;
    }
    return out;
}

void Map::validate() {
    //Check for empty graph
    if(all_territories.size() == 0 || all_continents.size() == 0){
        cout << "The map is empty" << endl;
        return;
    }

    //Store all visited (only 1 copy of each)
    set<Territory*> visited_territories;
    // Perform DFS
    if(!all_territories.empty()){
        Territory* start = all_territories[0];
        stack<Territory*> territory_stack;
        territory_stack.push(start);

        while (!territory_stack.empty()) {
            Territory *current_territory = territory_stack.top();
            territory_stack.pop();
            // Check if the current territory has already been visited. If not, insert it
            if (visited_territories.find(current_territory) == visited_territories.end()) {
                visited_territories.insert(current_territory);
                // Add adjacent territories to stack to process
                for (Territory *adjacent: current_territory->get_adjacent_territories()) {
                    territory_stack.push(adjacent);
                }
            }
        }
    }
    if(visited_territories.size() != all_territories.size()){
        cout << "The map is invalid" << endl;
        return;
    }
    //Print if function not exited
    cout << "1) The map is a connected graph" << endl;
    cout << "2) Continents are connected subgraphs" << endl;
    cout << "3) Each country belongs to one and only one continent" << endl;
}



//****************************************** MAP LOADER IMPLEMENTATION ****************************************
Map* MapLoader::instantiation(std::string map_file_path){

    // Store all territories and continents
    vector<Territory*> all_territories;
    vector<Continent*> all_continents;

    // Create ifstream object for input file in order to parse it
    ifstream input_file;
    input_file.open(map_file_path);

    // Check if file is opened
    if (input_file.is_open()) {
        //Skip lines until the [Continents] section is found
        string line;
        while (getline(input_file, line)) {
            if (line == "[Continents]")
                break;
        }
        // If it traverses entire file and [continent] is not found, terminate
        if (line != "[Continents]") {
            cout << "No [Continents] section found in the file." << endl;
            input_file.close();
            // Return empty graph
            Map* map_ptr = new Map({}, {});
            return map_ptr;
        }
        // Read content in [Continents]
        while (getline(input_file, line)) {
            regex pattern("^([^=]+)=([0-9]+)$");
            smatch matches;

            if(regex_match(line, matches, pattern)){
                string key = matches[1];
                string value = matches[2];
                all_continents.emplace_back(new Continent(key, stoi(value), {}));

            } else if (line == "[Territories]") {
                break;
            }
            else if (!line.empty()){
                cout << "Invalid [Continent] format" << endl;
                input_file.close();
                // Return empty graph
                Map* map_ptr = new Map({}, {});
                return map_ptr;
            }
        }

        // Terminate
        if(line != "[Territories]"){
            cout << "No [Territories] section found in the file." << endl;
            input_file.close();
            // Return empty graph
            Map* map_ptr = new Map({}, {});
            return map_ptr;
        }

        // Read content in [Territories]
        map<string, vector<string>> adjacent_map;
        bool continent_exists = false;
        while(getline(input_file, line)){
            string country_name;
            string x;
            string y;
            string continent;

            string adj_country_name;
            istringstream stream(line);

            if (getline(stream, country_name, ',') &&
                getline(stream, x, ',') &&
                getline(stream, y, ',') &&
                getline(stream, continent, ',')) {

                // Remove leading and trailing spaces from each variable
                country_name.erase(0, country_name.find_first_not_of(" \t\n\r\f\v"));
                country_name.erase(country_name.find_last_not_of(" \t\n\r\f\v") + 1);
                x.erase(0, x.find_first_not_of(" \t\n\r\f\v"));
                x.erase(x.find_last_not_of(" \t\n\r\f\v") + 1);
                y.erase(0, y.find_first_not_of(" \t\n\r\f\v"));
                y.erase(y.find_last_not_of(" \t\n\r\f\v") + 1);
                continent.erase(0, continent.find_first_not_of(" \t\n\r\f\v"));
                continent.erase(continent.find_last_not_of(" \t\n\r\f\v") + 1);

                //Add adjacent countries in a map associated to country
                while(getline(stream, adj_country_name, ',')){
                    adj_country_name.erase(0, adj_country_name.find_first_not_of(" \t\n\r\f\v"));
                    adj_country_name.erase(adj_country_name.find_last_not_of(" \t\n\r\f\v") + 1);
                    adjacent_map[country_name].push_back(adj_country_name);
                }

                //Check if continent exists, if it does, hold its pointer and pass to Territory initialization
                Continent *id = new Continent();
                for (Continent *obj_iter: all_continents) {
                    if (continent == obj_iter->get_name()) {
                        id = obj_iter;
                        continent_exists = true;
                    }
                }
                if(continent_exists){
                    continent_exists = false;
                }
                else{
                    cout << "A continent does not exist" << endl;
                    input_file.close();
                    // Return empty graph
                    Map* map_ptr = new Map({}, {});
                    return map_ptr;
                }

                while(getline(stream, adj_country_name, ',')){
                    adjacent_map[country_name].push_back(adj_country_name);
                }
                all_territories.emplace_back(new Territory(country_name, 0, stoi(x), stoi(y), {}, id, 0));
            }
        }


        // Populate adjacent list from all territories with the territory names associated to them from the map
        bool territory_exists = false;
        for(Territory* ter_iter : all_territories){
            // Compare territory name with map key
            if(adjacent_map.find(ter_iter->get_name()) != adjacent_map.end()){
                // Return string vector
                vector<string>& adj_vector = adjacent_map[ter_iter->get_name()];
                // Loop over vector<string> in map and all_territories to add their corresponding pointers
                for(string str : adj_vector){
                    for(Territory* ter_iter_2 : all_territories){
                        if(str == ter_iter_2->get_name()){
                            ter_iter->add_adjacent_territory(ter_iter_2);
                            territory_exists = true;
                            break;
                        }
                    }
                    if(territory_exists){
                        territory_exists = false;
                    }
                    else {
                        cout << "An adjacent territory does not exist" << endl;
                        input_file.close();
                        // Return empty graph
                        Map* map_ptr = new Map({}, {});
                        return map_ptr;
                    }
                }
            }
        }

        //Add all territories in their corresponding Continent
        for(Continent* cont_iter : all_continents) {
            for(Territory* ter_iter : all_territories) {
                if(ter_iter->get_continent()->get_name() == cont_iter->get_name()) {
                    cont_iter->add_within(ter_iter);
                }
            }
        }

        input_file.close();
    }
    //Instantiate Map object and return
    Map* map_ptr = new Map(all_territories, all_continents);
    return map_ptr;
}



