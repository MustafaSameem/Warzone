#include "Orders.h"
#include <iostream>

static void testOrdersList() {
Player* player1 = new Player();
Player* player2 = new Player();
Player* neutralPlayer = new Player();
neutralPlayer->setId(101);
// The neutral player will always have the ID "101" while each
// "real" player will have an ID from 1 to 6.
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
cout << "\nTesting player 1 attacking player 2" << endl;
Advance* advance = new Advance("advance", 20, territory5, territory4, player1);
Advance* advance2 = new Advance("advance", 5, territory5, territory4, player1);
advance->execute();
    cout << "\nTesting player 1 moving units to owned territory" << endl;
advance2->execute();
    territory4->set_player_id(2);
    Negotiate* negotiate = new Negotiate("negotiate", player2, player1);
    negotiate->execute();
    Advance* advance3 = new Advance("advance", 20, territory5, territory4, player1);
    cout << "\nTesting player 1 attacking player 2 with a negotiation" << endl;
    advance3->execute();
Blockade* blockade = new Blockade("blockade", 5, territory5, player1);
    cout << "\nTesting player 1 setting up a blockade" << endl;
    blockade->execute();
   cout << "Territory 5 is now owned by player with ID " << territory5->get_player_id() << endl;



}

int main() {
    testOrdersList();
    return 0;
}
