#include "GameEngine.h"
#include <vector>
#include <iostream>
#include <sstream>
#include <string>
#include <algorithm>
#include <ctime>
#include <random>


//********************************** STATE IMPLEMENTATION ***********************************
//Default constrcutor
State::State(){
    state_status="pending";
}
//Parameterized constructor
State::State(string state_status){
    this->state_status=state_status;
}
//Copy constructor
State::State(const State &state_cpy){
    state_status = state_cpy.state_status;
}
//Destructor
State::~State(){}

//Getter
string State::get_state_status(){
    return state_status;
}
//Setter
void State::set_state_status(string new_state_status){
    state_status=new_state_status;
}

//Assignment operator
State& State::operator=(const State &state_cpy){
    //Self-assignment check
    if(this == &state_cpy){
        return *this;
    }
    //Copy
	state_status = state_cpy.state_status;
	return *this;
}

//Stream insertion (global function)
ostream &operator<<(ostream &out, const State &state_cpy){
    out << "Current State Status: " << state_cpy.state_status << endl;
    return out;
}



//***************************************** TRANSITION IMPLEMENTATION ****************************************
//Default constructor
Transition::Transition(){
    currentState = nullptr;
    nextState = nullptr;
    userCommand = "Pending";
}
//Parameterized constructor
Transition::Transition(State *currentState, State *nextState, const string command){
    this->currentState = currentState;
    this->nextState = nextState;
    this->userCommand = command;
}
//Copy constructor
Transition::Transition(const Transition& transition_cpy){
    userCommand = transition_cpy.userCommand;
    //Deep copy
    currentState = new State();
    nextState = new State();
    *currentState = *(transition_cpy.currentState);
    *nextState = *(transition_cpy.nextState);
}
//Destructor
Transition::~Transition(){
    delete currentState;
    delete nextState;
}

//Getters
State *Transition::getCurrentState(){
    return currentState;
}
State *Transition::getNextState(){
    return nextState;
}

//Assignment operator
Transition& Transition::operator=(const Transition& transition_cpy){
    //Self-assignment check
    if (this == &transition_cpy) {
        return *this;
    }
    //Copy
    userCommand = transition_cpy.userCommand;

    //Delete before deep copy
    if (currentState != nullptr) {
        delete currentState;
    }
    if (nextState != nullptr) {
        delete nextState;
    }
    currentState = new State();
    nextState = new State();
    *currentState = *(transition_cpy.currentState);
	*nextState = *(transition_cpy.nextState);
    //Dereference current object and return it so we can chain this operator
	return *this;
}

//Stream insertion (global function)
ostream &operator<<(ostream &out, const Transition &transition_cpy){
    out << "[State transitioning from current State: " <<transition_cpy.currentState->state_status<<" to next state: "<< transition_cpy.nextState->state_status<<"]\n";
    return out;
}


//******************************************* GRAPH IMPLEMENTATION *************************************
GameEngine::GameEngine(const GameEngine& GameEngine_cpy) : nodes([](const vector<State*>& src) { vector<State*> dest; for(auto s : src) dest.push_back(new State(*s)); return dest; }(GameEngine_cpy.nodes)), transitions([](const vector<Transition*>& src) { vector<Transition*> dest; for(auto t : src) dest.push_back(new Transition(*t)); return dest; }(GameEngine_cpy.transitions)), currentState(new State(*GameEngine_cpy.currentState))
{

}

GameEngine& GameEngine::operator=(const GameEngine& GameEngine_cpy)
{
    this->transitions=GameEngine_cpy.transitions;
    this->currentState=GameEngine_cpy.currentState;
    this->nodes=GameEngine_cpy.nodes;
    return *this;
}

//Added A delete statement to handle transition deletion in destructor to avoid memory leaks.
GameEngine::~GameEngine() {
    // Free memory for nodes
    for (auto node : nodes) {
        delete node;
    }
    nodes.clear();

    // Free memory for transitions
    for (auto transition : transitions) {
        delete transition;
    }
    transitions.clear();


    //deallocate memory for all data structures used in startupPhase()
    for (Player* player : players_in_game) {
        delete player;
    }
    players_in_game.clear();

    for (Territory* ter : territories_in_game) {
        delete ter;
    }
    territories_in_game.clear();

    delete map_instance1;
    delete orders_in_game;
    delete hand_in_game;
}

ostream &operator<<(ostream &out, const GameEngine &GameEngine_cpy){
    for (const auto& transition : GameEngine_cpy.transitions) {
        out << "Transition: ";
        out << "From State " << transition->currentState->get_state_status();
        out << " to State " << transition->nextState->get_state_status();
        out << " (Command: " << transition->userCommand << ")";
        out << "\n";
    }
    return out;
}

void GameEngine::addNode(State *node) {
    nodes.push_back(node);

}

void GameEngine::addTransition(State *source, State *destination, const string &command) {
    transitions.emplace_back(new Transition(source,destination,command));
}

void GameEngine::printGraph() {

    for (const auto& transition : transitions) {
        cout << "Transition: State " << transition->currentState->get_state_status()  << " to State " << transition->nextState->get_state_status() << " (Command: " << transition->userCommand << ")" << endl;
    }
}
void GameEngine::setCurrentState(State *state){
    currentState = state;
}
State* GameEngine::getCurrenState() {
    return currentState;
}
State* GameEngine::nextState(const string &command)  {
    LogObserver *observer = new LogObserver(this);
    for (const auto& transition : transitions) {
        if (transition->currentState == currentState && transition->userCommand == command) {
            Notify(this);//NOTE: not sure if this belongs here
            delete observer;
            observer = NULL;
            return transition->nextState;
        }
    }
    return nullptr; // Invalid action or no valid transition found
}
bool GameEngine::checkCurrentState(string command) {
    for (int i = 0; i < transitions.size(); i++)
    {
        if (currentState->state_status == transitions[i]->currentState->state_status && command == transitions[i]->userCommand)
        {
            currentState = transitions[i]->nextState;
            cout << *currentState;
            return true;
        }
        else if (currentState->state_status == "win" && command == "end") return true;
    }
    return false;
}

void GameEngine::end() {
    delete this;
    cout<<"Game has now ended, Thanks for playing! :)\n";
}

//stringToLog implementation from ILoggable
string GameEngine::stringToLog()
{
    return "GameEngine State: " + currentState->state_status;
}

//StartupPhase()
void GameEngine::startupPhase(CommandProcessor *cp_obj) {

    cout << endl << "STARTUP PHASE" << endl;
    State *start = new State("start");
    this->setCurrentState(start);
    cout << *(this->getCurrenState());


    vector<Command*> validCommands = cp_obj->getValidcommands();
    for (const auto &command: validCommands) {
        //cout << *command << "," << endl;
        string command_string = command->getCommandPassed();

        if (command_string.find("loadmap") != string::npos) {
            string effect_string = command->getCommandPassed();

            size_t startPos = effect_string.find('<');
            size_t endPos = effect_string.find('>');
            // Check if both '<' and '>' are found
            if (startPos != std::string::npos && endPos != std::string::npos) {
                // Extract the map name
                std::string map_name = effect_string.substr(startPos + 1, endPos - startPos - 1);
                cout << "MAP NAME: " << map_name << endl;
                string file_path = "../Warzone/Map/MapFiles/" + map_name;
                cout << "FILEPATH: " << file_path << endl;
                map_instance1 = MapLoader::instantiation(file_path);
                // State Transition
                State *map_loaded = new State("map_loaded");
                this->setCurrentState(map_loaded);
                cout << *(this->getCurrenState());
            }
        }

        if (command_string.find("validatemap") != string::npos) {
            string effect_string = command->getCommandPassed();
            map_instance1->validate();
            // State Transition
            if (map_instance1->get_all_territories().size() != 0){
                State *map_validated = new State("map_validated");
                this->setCurrentState(map_validated);
                cout << *(this->getCurrenState());
            }
        }

        if (command_string.find("addplayer") != string::npos) {
            string effect_string = command->getCommandPassed();

            size_t startPos = effect_string.find('<');
            size_t endPos = effect_string.find('>');
            // Check if both '<' and '>' are found
            if (startPos != std::string::npos && endPos != std::string::npos) {
                // Extract the player name
                std::string player_name = effect_string.substr(startPos + 1, endPos - startPos - 1);
                cout << "PLAYER NAME: " << player_name << endl;
                Player *p = new Player(territories_in_game, *orders_in_game, 0, *hand_in_game, player_name);
                add_player(p);
                // State Transition
                State *players_added = new State("players_added");
                this->setCurrentState(players_added);
                cout << *(this->getCurrenState());
            }
        }

        if (command_string.find("gamestart") != string::npos){

            for(int i=0; i < players_in_game.size(); i++){
                players_in_game[i]->setId(i);
            }

            // Distribute territories fairly to all players
            vector<Territory*> territories = map_instance1->get_all_territories();
            for (int i=0; i<territories.size(); ++i) {
                Territory* territory = territories[i];
                Player* player = players_in_game[i % players_in_game.size()];

                territory->set_player_id(player->getPlayerId());
                player->add_territory(territory);
            }
            cout << "ROUND-ROBIN TERRITORY DISTRIBUTION COMPLETE" << endl;


            // Determine the turn order randomly
            std::srand(std::time(0));
            std::shuffle(players_in_game.begin(), players_in_game.end(), std::default_random_engine(std::time(0)));

            // Output the turn order
            cout << "Turn Order: ";
            for (const auto& player : players_in_game) {
                cout << "Player " << player->getPlayerId() << " || ";
            }
            cout << endl;

            //Assign 50 army for each player
            for (const auto& player : players_in_game) {
                player->addArmyUnits(50);
            }

            // Make each player draw 2 cards
            Deck* deck = new Deck();
            for(int i=0; i < 10; i++){
                deck->addCardTypeToDeck(CardType::BOMB);
                deck->addCardTypeToDeck(CardType::REINFORCEMENT);
                deck->addCardTypeToDeck(CardType::BLOCKADE);
                deck->addCardTypeToDeck(CardType::AIRLIFT);
                deck->addCardTypeToDeck(CardType::DIPLOMACY);
            }

            for (const auto& player : players_in_game) {
                Hand* player_hand = new Hand();
                deck->draw(player_hand);
                deck->draw(player_hand);
                cout << "PLAYER HAND: " << *player_hand << endl;
                player->setHand(*player_hand);
            }
            cout << "PLAYERS ASSIGNED 2 CARDS EACH" << endl;

            // State Transition
            State *assign_reinforcement = new State("assign_reinforcement");
            this->setCurrentState(assign_reinforcement);
            cout << *(this->getCurrenState());
        }
    }
}

void Reinforcement::reinforcementPhase(vector<Player> playerList){
        
    std::cout << "Reinforcement Phase starting" << std::endl;

     for (Player player : playerList) {
        int amount = armyIncome(player);
        player.addArmyUnits(amount);
        std::cout << "Player " << player.getPlayerId() << " is gaining " << amount << " units" << std::endl;
     }
    std::cout << "Reinforcement Phase ending" << std::endl;
}

int Reinforcement::armyIncome(Player player){

    int income = 0;
    int numOfTerr = 0;

    vector<Territory*> territory = player.getVecTer();


    int numOfArmies = territory.size();
        numOfArmies = floor(numOfArmies / 3);

    for (Territory* terr : territory) {
        numOfTerr ++;
        income += terr->get_army_size(); 
    }
    
    
    if(income < 0){
    income = 3;
    }

    return income;
}

void IssueOrder::issueOrder(){

}

void IssueOrder::executeOrder(){

}

void GameEngine::add_player(Player *current_player) {
    players_in_game.push_back(current_player);
}

