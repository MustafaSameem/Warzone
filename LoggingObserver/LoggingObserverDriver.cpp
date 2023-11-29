#include "LoggingObserver.h"
#include "../GameEngine/GameEngine.h"
#include "../Map/Map.h"
#include "../CommandProcessing/CommandProcessing.h"
#include "../Orders/Orders.h"
#include <iostream>
using namespace std;


//g++ LoggingObserverDriver.cpp LoggingObserver.cpp ../Cards/Cards.cpp ../GameEngine/GameEngine.cpp ../Orders/Orders.cpp  ../Player/Player.cpp ../GameEngine/GameEngine.cpp ../Map/Map.cpp ../CommandProcessing/CommandProcessing.cpp
/*
    tasks.json:

    "LoggingObserverDriver.cpp",
    "LoggingObserver.cpp",
    "../Cards/Cards.cpp",
    "../Player/Player.cpp",
    "../Map/Map.cpp",
    "../Orders/Orders.cpp",
    "../CommandProcessing/CommandProcessing.cpp",
    "../GameEngine/GameEngine.cpp",
*/


static void testLoggingObserver()
{
    // Instantiate Observer object
    Observer* observer = new LogObserver();

    /*
    CommandProcessor::saveCommand()
    Order::execute() --> good
    Command::saveEffect()
    OrderList::addOrder() --> good
    GameEngine::transition()
    */    
    //----------------------------------------------------------------------------------------------
    //                                     Orders testing
    // ----------------------------------------------------------------------------------------------
    Player* player1 = new Player();
    Player* player2 = new Player();
    Player* neutralPlayer = new Player();
    neutralPlayer->setId(101);    
    Territory* territory1 = new Territory();
    Territory* territory2 = new Territory();
    Territory* territory3 = new Territory();
 
    
    vector<Territory*> adjacent;
    adjacent.push_back(territory1);
    adjacent.push_back(territory2);
    adjacent.push_back(territory3);
    Continent* con = new Continent();
    Territory* territory4 = new Territory("Soup", 5, 5, 5, adjacent, con);
    territory4->set_player_id(2);
    player1->setId(1);
    player2->setId(2);
    
    vector<Territory*> adjacent2;
    adjacent2.push_back(territory1);
    adjacent2.push_back(territory2);
    adjacent2.push_back(territory3);
    adjacent2.push_back(territory4);
    vector<Territory*> player1Owned;
    Territory* territory5 = new Territory("Sky", 20, 5, 5, adjacent2, con);
    territory5->set_player_id(1);
    player1Owned.push_back(territory5);
    player1->setTerritories(player1Owned);
    
    // Testing Orders::execute for Notify()
    Advance* advance = new Advance("advance", 20, territory5, territory4, player1);
    Advance* advance2 = new Advance("advance", 5, territory5, territory4, player1);
    advance->execute();//writing to gamelog.txt    
    advance2->execute();//writing to gamelog.txt
    
    territory4->set_player_id(2);
    
    Negotiate* negotiate = new Negotiate("negotiate", player2, player1);
    negotiate->execute();//writing to gamelog.txt
    
    Advance* advance3 = new Advance("advance", 20, territory5, territory4, player1);
    advance3->execute();//writing to gamelog.txt
    
    Blockade* blockade = new Blockade("blockade", 5, territory5, player1);
    blockade->execute();//writing to gamelog.txt
    
    // Testing OrdersList::add for Notify()
    OrdersList *myList = new OrdersList();  

    myList->add(advance);//writing to gamelog.txt
    myList->add(negotiate);//writing to gamelog.txt
    myList->add(blockade);//writing to gamelog.txt

    //----------------------------------------------------------------------------------------------
    //                                  CommandProcessor testing
    //----------------------------------------------------------------------------------------------
    // CommandProcessor *cprocessor = new CommandProcessor();

    // GameEngine *game = new GameEngine();

    // State *start = new State("start");
    // State *map_loaded = new State("map_loaded");
    // State *map_validated = new State("map_validated");
    // State *players_added = new State("players_added");
    // State *assign_reinforcement = new State("assign_reinforcement");
    // State *win = new State("win");
    // State *end_game = new State("end_game");


    // game->addNode(start);
    // game->addNode(map_loaded);
    // game->addNode(map_validated);
    // game->addNode(players_added);
    // game->addNode(assign_reinforcement);
    // game->addNode(win);
    // game->addNode(end_game);

    // //Add valid Transitions to our existing gameEngine.
    // game->addTransition(start, map_loaded, "loadmap");
    // game->addTransition(map_loaded, map_loaded, "loadmap");
    // game->addTransition(map_loaded, map_validated, "validatemap");
    // game->addTransition(map_validated, players_added, "addplayer");
    // game->addTransition(players_added, players_added, "addplayer");
    // game->addTransition(players_added, assign_reinforcement, "gamestart");
    // game->addTransition(assign_reinforcement, win, "gameend");

    // game->addTransition(win, start, "replay");
    // game->addTransition(win, end_game, "quit");

    // game->setCurrentState(start);

    // string userResponse;
    // string followUpResponse;
    // string fileName;

    // cout
    //         << "which method would you like to accept commands from, via the console or via reading from a file? please type \"console\" or \"file\"\n";
    // cin >> userResponse;


    // if (userResponse == "console") {
    //     cout<<"***Now accepting command from console***";
    //     while (!(cprocessor->getExitProgramstatus())) {
    //         cprocessor->getCommand(game, cprocessor);
    //     }

    //     cout << "\n All commands:";
    //     vector<Command *> commands = cprocessor->getCommandsList();
    //     for (const auto &command: commands) {
    //         cout << *command << "," << endl;
    //     }
    //     cout << "\n All valid commands:";
    //     vector<Command *> validCommands = cprocessor->getValidcommands();
    //     for (const auto &command: validCommands) {
    //         cout << *command << "," << endl;
    //     }

    //     delete cprocessor;

    // }
    // else if(userResponse== "file"){
    //     cout<<"***Now accepting command from file***\n Please enter the file name you wish to open\n";

    //     cin>>fileName;
    //     cout<<endl;

    //     FileLineReader* fileReader = new FileLineReader();
    //     fileReader->readFromFile(fileName);

    //     FileCommandProcessorAdapter* commandFile = new FileCommandProcessorAdapter(fileReader);

    //     while (!(cprocessor->getExitProgramstatus())){
    //         cprocessor->getCommand(game,commandFile);
    //     }

    //     cout << "\n All commands:";
    //     vector<Command *> commands = cprocessor->getCommandsList();
    //     for (const auto &command: commands) {
    //         cout << *command << "," << endl;
    //     }
    //     cout << "\n All valid commands:";
    //     vector<Command *> validCommands = cprocessor->getValidcommands();
    //     for (const auto &command: validCommands) {
    //         cout << *command << "," << endl;
    //     }

    //     delete commandFile;
    //     delete fileReader;
    //     delete cprocessor;
    // }

    // game->end();
    // game=NULL;


    //GameEngine testing
    //Instantiate pointer Objects from Class State, and assign various States which represent State Nodes
    State *start = new State("start");
    State *map_loaded = new State("map_loaded");
    State *map_validated = new State("map_validated");
    State *players_added = new State("players_added");
    State *assign_reinforcement = new State("assign_reinforcement");
    State *issue_orders = new State("issue_orders");
    State *execute_orders = new State("execute_orders");
    State *win = new State("win");

    //Instantiate one pointer of GameEngine object that we would use to hold our States, and Valid Transitions.
    GameEngine *Play = new GameEngine;

    //Populate the Graphs with Nodes that represent the States of our Game.
    Play->addNode(start);
    Play->addNode(map_loaded);
    Play->addNode(map_validated);
    Play->addNode(players_added);
    Play->addNode(assign_reinforcement);
    Play->addNode(issue_orders);
    Play->addNode(execute_orders);
    Play->addNode(win);

    //Add valid Transitions to our existing Play GameEngine.
    Play->addTransition(start, map_loaded, "loadmap");
    Play->addTransition(map_loaded, map_loaded, "loadmap");
    Play->addTransition(map_loaded, map_validated, "validatemap");
    Play->addTransition(map_validated, players_added, "addplayer");
    Play->addTransition(players_added, players_added, "addplayer");
    Play->addTransition(players_added, assign_reinforcement, "assigncountries");
    Play->addTransition(assign_reinforcement, issue_orders, "issueorder");
    Play->addTransition(issue_orders, issue_orders, "issueorder");
    Play->addTransition(issue_orders, execute_orders, "endissueorders");
    Play->addTransition(execute_orders, execute_orders, "execorder");
    Play->addTransition(execute_orders, assign_reinforcement, "endexecorders");
    Play->addTransition(execute_orders, win, "win");
    Play->addTransition(win, start, "play");
    Play->addTransition(win, nullptr, "end");

//    //Print out to the console, the valid transitions that represent our graph.
//    cout<<"\t\t*******************************"<<endl<<"\t\t****VALID GRAPH TRANSITIONS****"<<endl<<"\t\t*******************************"<<endl;
//    Play->printGraph();

    //When Code runs the game automatically starts, and our initial state would always be 'START'
    Play->setCurrentState(start);



    //Initialize and define an empty command string that takes input from the user
    string command = "";


//        Infinte loop that breaks either when a transition is wrong, or a command is invalid, or The user decides to end game.
        while (true) {
            //prompt user for command
            cout << "Please enter command: ";
            cin >> command;

            //Keep Track of our next State, so we can inform the user. whilst he makes his transitions.
            State *nextState = Play->nextState(command);

            //While there exists a nextState, keep prompting user for an input.
            if (nextState) {

                //Print out CurrentState, NextState.
                cout << *Play->getCurrenState();
                cout << "Next State: " << nextState->stateStatus << "\n\n";
                //Set the nextState to be the currenState in order to update the graph, as the user Traverses the GameEngine.
                Play->setCurrentState(nextState);
            } else {
                if (command == "end" && Play->getCurrenState()== win ) {
                    //Concluding Message once the user attempts to finish the game after winning.
                    cout << "Thanks for participating" << endl;
                    break;
                }
                //Throw Error once we receive an invalid action, and an invalid transaction.
                cerr<<"Invalid action or no valid transition.\nPlease enter Valid transition.\n";
            }
        }


    //Deallocate all pointers, and free up all used memory to ensure no memory leak occurs.

    delete Play;

}

int main()
{
    testLoggingObserver();

}