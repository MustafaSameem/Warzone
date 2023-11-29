#include <string>
#include <vector>
using namespace std;
#pragma once


//Forward declaration
class Continent;

//****************************************** TERRITORY DECLARATION ****************************************
//Nodes for the graph
class Territory{
private:
    string name;
    int army_size;
    int x_coord;
    int y_coord;
    int player_id;
    vector<Territory*> adjacent_territory;
    Continent* id;

public:
    //Default constructor
    Territory();
    //Parameterized constructor
    Territory(string name, int army_size, int x_coord, int y_coord, vector<Territory*> adjacent_territory, Continent* id, int player_id);
    //Copy constructor
    Territory(const Territory &ter_cpy);
    //Destructor
    ~Territory();

    //Getter
    string get_name() const;
    int get_army_size() const;
    int get_x_coord() const;
    int get_y_coord() const;
    vector<Territory*> get_adjacent_territories() const;
    Continent* get_continent() const;
    int get_player_id() const;

    //Setter
    void set_name(string name);
    void set_army_size(int army_size);
    void set_x_coord(int new_x_coord);
    void set_y_coord(int new_y_coord);
    void set_continent(Continent* new_continent);
    void set_player_id(int player_id);

    //Methods
    void add_adjacent_territory(Territory* adjacent);
    void print_all_adjacent() const;

    //Assignment operator
    Territory& operator=(const Territory& ter_cpy);
    //Stream insertion operator
    friend ostream& operator<<(ostream& out, const Territory& ter_cpy);
};


//****************************************** CONTINENT DECLARATION ****************************************
class Continent{
private:
    string name;
    int bonus_army;
    vector<Territory*> territories_within;

public:
    //Default Constructor
    Continent();
    //Parameterized Constructor
    Continent(string name, int bonus_army, vector<Territory*> territories_within);
    //Copy Constructor
    Continent(const Continent& cont_cpy);
    //Destructor
    ~Continent();

    //Getter
    string get_name() const;
    int get_bonus_army() const;
    vector<Territory*> get_territories_within() const;

    //Setter
    void set_name(string new_name);
    void set_bonus_army(int new_bonus_army);
    void set_territories_within(vector<Territory*> new_territories);

    //methods
    void add_within(Territory* territory);
    void print_all_in_continent();

    //Assignment operator
    Continent& operator=(const Continent& cont_cpy);
    //Stream insertion operator
    friend ostream& operator<<(ostream& out, const Continent& cont_cpy);
};


//****************************************** MAP DECLARATION ****************************************
class Map{
private:
    //string name;
    vector<Territory*> all_territories;
    vector<Continent*> all_continents;

public:
    //Default constructor
    Map();
    //Parameterized constructor
    Map(vector<Territory*> all_territories, vector<Continent*> all_continents);
    //Copy constructor
    Map(const Map &map_cpy);
    //Destructor
    ~Map();

    //Getter
    vector<Territory*> get_all_territories();

    //Assignment operator
    Map& operator=(const Map& map_cpy);
    //Stream insertion operator
    friend ostream& operator<<(ostream& out, const Map& map_cpy);

    //Method
    void validate();
};


//****************************************** MAP LOADER DECLARATION ****************************************
class MapLoader{
public:
    static Map* instantiation(string map_file_path);
};
