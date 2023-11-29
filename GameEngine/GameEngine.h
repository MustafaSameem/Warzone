#include <string>
#include<iostream>
#include <vector>
#include "../LoggingObserver/LoggingObserver.h"
#include "../Player/Player.h"
#include "../CommandProcessing/CommandProcessing.h"
using namespace std;
#pragma once



//Forward declaration
class CommandProcessor;


class State{
public:
    string state_status;

    //Default constructor
    State();
    //Parameterized constructor
    explicit State(string state_status);
    //Copy constructor 
    State(const State& state_cpy);
    //Destructor
    ~State();

    //Getter
    string get_state_status();
    //Setter
    void set_state_status(string state_name);

    //Assignment operator
    State& operator=(const State& state_cpy);
    //Stream insertion operator
    friend ostream& operator<<(ostream& out, const State& state_cpy);
};


//Holds a pointer that points to different states
class Transition{
public:
    State *currentState;
    State *nextState;
    string userCommand;

    //Default constructor
    Transition();
    //Parameterized constructor
    Transition(State* currentState,State* nextState, const string command);
    //Copy constructor
    Transition(const Transition& transition_cpy);
    //destructor
    ~Transition();

    //Getters
    State* getCurrentState();
    State* getNextState();

    //Assignment operator
    Transition& operator=(const Transition& transition_cpy);
    //Stream insertion operator
    friend ostream& operator<<(ostream& out, const Transition& transition_cpy);

};


class GameEngine : public Subject, public ILoggable{
public:
    vector<State*> nodes;
    vector<Transition*> transitions;
    State* currentState;
    //Used in StartupPhase()
    vector<Player*> players_in_game;
    Map* map_instance1;
    vector<Territory*> territories_in_game;
    OrdersList* orders_in_game;
    Hand* hand_in_game;

    //Default constructor
    GameEngine() : currentState(nullptr){}
    //Copy constructor
    GameEngine(const GameEngine& GameEngine_cpy);
    //Assignment operator
    GameEngine& operator=(const GameEngine& GameEngine_cpy);
    //Destructor
    ~GameEngine();

    //Getter
    State* getCurrenState();
    //Setter
    void setCurrentState(State* state);
    void addNode(State* node);
    void addTransition(State* source, State* destination, const string& command);
    void add_player(Player* current_player);

    //Methods
    bool checkCurrentState(string command);
    void end();
    State* nextState(const string& command);
    void printGraph();
    string stringToLog();

    //Start the game
    void startupPhase(CommandProcessor *cp_obj);

    //stream insertion operator
    friend ostream& operator<<(ostream& out, const GameEngine& GameEngine_cpy);
};


class Reinforcement{
    public:
    void reinforcementPhase(vector<Player> playerList);
    int armyIncome(Player player);
};


class IssueOrder{
    public:
    void issueOrder();
    void executeOrder();
};

