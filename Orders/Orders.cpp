#include "Orders.h"
#include <string>
#include <iostream>
#include <vector>
#include <algorithm>
#include <cctype>
// Test
using namespace std;

vector<string> orders = {"deploy","advance","bomb","blockade","airlift","negotiate"};

// Default constructor
Orders::Orders() {
    this->orderType = "Some order";
    this->executer = new Player();
    LogObserver *observer = new LogObserver(this);
}
// Copy constructor
Orders::Orders(const Orders& other) : orderType(other.orderType) {

}
// Parameterized constructor
Orders::Orders(string orderType, Player* executer) {
    this->orderType = orderType;
    this->executer = executer;
    LogObserver *observer = new LogObserver(this);
    
}
// Destructor
Orders::~Orders() {

}

int Orders::NegotiatedPlayers[maxPlayers][maxPlayers] = {0};
int Orders::receivedCard[maxPlayers] = {0};
// Getters
string Orders::getOrderType() const{
    return this->orderType;
}

Player* Orders::getPlayer() const {
    return this->executer;
}

int Orders::getNegotiatedPlayer(int row, int column) {
    return NegotiatedPlayers[row][column];
}

int Orders::getReceivedCard(int player_ID) {
    return receivedCard[player_ID-1];
}

// Setters
void Orders::setOrderType(string order) {
    this->orderType = order;
}

void Orders::setPlayer(Player *execute) {
    this->executer = execute;
}

void Orders::setNegotiatedPlayer(int playerID_1, int playerID_2) {
    if (playerID_1 != 101 && playerID_2 != 101) {
        NegotiatedPlayers[playerID_1 - 1][playerID_2 - 1] = playerID_2;
    }
}

void Orders::setReceivedCard(int player_ID) {
    receivedCard[player_ID-1] = 1;
}

// Assignment operator
Orders& Orders::operator=(const Orders& o) {
    if (this == &o) {
        return *this;
    }
    this->orderType = o.orderType;
    return *this;
}

// Stream operator overload for deploy order
ostream& operator << (ostream& output, const Orders& obj) {

    output << "Order Type: " << obj.orderType;
    return output;
}

bool Orders::validate()  {
    return true;
}

void Orders::execute() {
    cout << "Used to execute order" << endl;
    Notify(this);
}

//Implementing stringToLog from ILoggable
string Orders::stringToLog()
{
    return "Order effect: " + getOrderType();
}



// Default constructor for deploy order
Deploy::Deploy() : Orders() {
    this->numSoldiers = 0;
    this->target = new Territory();
}

// Parameterized constructor for deploy order
Deploy::Deploy(string orderType, int numSoldiers, Territory* target, Player* executer) : Orders(orderType, executer) {
    this->numSoldiers = numSoldiers;
    this->target = target;
}
// Copy constructor for deploy order
Deploy::Deploy(const Deploy& other) : Orders(other) {
    this->numSoldiers = other.numSoldiers;
    this->target = new Territory(*(other.target));
}

// Destructor, delete the dynamic object
Deploy::~Deploy() {
    delete target;
}

// Validate method for deploy order
bool Deploy::validate()  {
    // If player has no more soldiers to deploy

    if (Orders::getPlayer()->getPlayerId() == target->Territory::get_player_id()) {
        return true;
    }
    else {
        cout << "Do not own this territory" << endl;
        return false;
    }

    
}
// Execute method for deploy order
void Deploy::execute() {
    if (!(validate())) {
        cout << "Could not perform action" << endl;
    }
    else {
        int update = numSoldiers + target->get_army_size();
        target->set_army_size(update);
    }
    Notify(this);
}
// Getter and setter for 'numSoldiers'
int Deploy::getNumSoldiers() const {
    return numSoldiers;
}

void Deploy::setNumSoldiers(int Soldiers) {
    this->numSoldiers = Soldiers;
}
// Getter and setter for 'target'
Territory* Deploy::getTarget() const {
    return target;
}


void Deploy::setTarget(Territory* targetTer) {
    this->target = targetTer;
}
// Stream operator overload for deploy order
ostream& operator << (ostream& output, const Deploy& obj) {
    output << "The order 'Deploy' Deploys soldiers from the player's reinforcement pool to a territory owned by the player." << endl;
    return output;
}
// Assignment operator overload for deploy order
Deploy& Deploy::operator=(const Deploy& d) {
    if (this == &d) {
        return *this;
    }
    Orders::operator= (d);
    this->numSoldiers = d.numSoldiers;
    this->target = d.target;
    return *this;

}
// Default constructor for advance order
Advance::Advance() : Orders() {
    this->numSoldiers = 0;
    this->source = new Territory();
    this->target = new Territory();
}
// Parameterized constructor for advance order
Advance::Advance(string orderType, int numSoldiers, Territory* source, Territory* target, Player* executer, int targetOwner) : Orders(orderType, executer) {
    this->numSoldiers = numSoldiers;
    this->source = source;
    this->target = target;
    this->targetOwner = targetOwner;
}
// Copy constructor for advance order
Advance::Advance(const Advance& other) : Orders(other) {
    this->source = new Territory(*(other.source));
    this->target = new Territory(*(other.target));
    this->numSoldiers = other.numSoldiers;

}
// Destructor
Advance::~Advance() {
    delete source;
    delete target;
}

// Getter and setter for 'numSoldiers'
int Advance::getNumSoldiers() const{
    return numSoldiers;
}

void Advance::setNumSoldiers(int Soldiers) {
    this->numSoldiers = Soldiers;
}
// Getter and setter for 'source'
Territory* Advance::getSource() const {
    return source;
}

void Advance::setSource(Territory* sourceTer) {
    this->source = sourceTer;
}
// Getter and setter for 'target'
Territory* Advance::getTarget() const {
    return target;
}

void Advance::setTarget(Territory* targetTer) {
    this->target = targetTer;
}
// Validate method for advance order
bool Advance::validate() {
    bool hasTerritory = false;
    bool isAdjacent = false;
    bool canAttack = false;
    // Create a reference to the vector of territories that the player owns
    const std::vector<Territory*>& territories = Orders::getPlayer()->getVecTer();
    cout << territories.size() << endl;
    // Iterate through the territories with a pointer
    for (const Territory* territory : territories) {
        // Check if the two pointers point to the same object.
        // Meaning, check if the player has the territory that is the same as the
        // target territory.
        cout << "Going again" << endl;
        if (territory == getSource()) {
            hasTerritory = true;
            cout << "You have the source" << endl;
        }
        if (territory == getTarget()) {
            this->targetOwner = 1;
            cout << "You have the target" << endl;
        }

    }
    // If the player attribute is NULL in a territory, it means that it is owned by the neutral player
    // If the territory is not owned by the player calling the order, but it is not null, it means
    // That another player owns it.
    if (this->targetOwner != 1) {
        if (target->Territory::get_player_id() == 101)
            this->targetOwner = 0;
        else
            this->targetOwner = 2;
    }
    const std::vector<Territory*>& adjacentTer = source->get_adjacent_territories();
    cout << adjacentTer.size() << endl;
    for (const Territory* adjacent : adjacentTer) {
        // Check if the two pointers point to the same object.
        // Meaning, check if the player has the territory that is the same as the
        // target territory.
        if (adjacent == getTarget()) {
            isAdjacent = true;
            cout << "this territory is adjacent" << endl;
            break;
        }
    }
    if (this->targetOwner == 2) {
        if (Orders::getNegotiatedPlayer(Orders::getPlayer()->getPlayerId(), target->get_player_id()) == 0) {
            canAttack = true;
        }
    }
    if (!hasTerritory || !isAdjacent || !canAttack) {
        return false;
    }
    else {
        return true;
    }

}
// Execute method for advance order
void Advance::execute() {
    if (!validate()) {
        cout << "Could not execute order" << endl;
    }
    else {
        if (targetOwner == 1) {
            int update = numSoldiers + target->get_army_size();
            target->set_army_size(update);
            update = abs(source->get_army_size()-numSoldiers);
            source->set_army_size(update);
        }
        else if (targetOwner == 2) {
            int defendingArmy = target->get_army_size();
            cout << "Defending player is defending with " << defendingArmy << endl;
            int sourceArmy = abs(numSoldiers-source->get_army_size());
            cout << "Attacking player is attacking with " << numSoldiers << endl;
            Advance::attacking(numSoldiers, defendingArmy);
        }
    }
    Notify(this);
}

void Advance::attacking(int& attackingArmy, int& defendingArmy) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> distribution(1, 10);
    int attackKill = 0;
    int defenseKill = 0;
    while (attackingArmy > 0 && defendingArmy > 0) {
        attackKill = distribution(gen);
        defenseKill = distribution(gen);
        cout << attackKill << endl;
        cout << defenseKill << endl;
        if (attackKill >= 1 && attackKill <= 6) {
            defendingArmy--;
        }
        if (defenseKill >= 1 && defenseKill <= 7) {
            attackingArmy--;
        }

    }
    if (attackingArmy == 0) {
        target->set_army_size(defendingArmy);
        cout << "Attacker lost" << endl;
    }
    else if (defendingArmy == 0) {
        cout << "Attacker won" << endl;
        int newOwner = Orders::getPlayer()->getPlayerId();
        target->set_player_id(newOwner);
        // Need territories to hold the player that owns it.
        // So I can change ownership if an attacking army wins.

        // Need a method here that removes a territory from a player's list

        // Need a method here that adds a territory to player's list
        if (Orders::getReceivedCard(Orders::getPlayer()->getPlayerId()) == 0) {
            target->set_army_size(attackingArmy);
            Card *newCard = new Card();
            Orders::setReceivedCard(Orders::getPlayer()->getPlayerId());
            //Orders::getPlayer()->getHand()->addCardsToHand(newCard);
            newCard = nullptr;
        }

    }
}
// Stream overload operator for advance order
ostream& operator << (ostream& output, const Advance& obj) {
    output << "The order 'Advance' advances a certain number of army units from a player's territory "
    << "to an adjacent territory. If the adjacent territory belongs to another player, then an attack sequence will begin."
    << "The armies deployed by the player calling the advance order will battle with the player in the defending territory."
    << "If the attacking player is successful, the army units that survive will occupy the territory, and will be under the attacking player's possession"
    << endl;
    return output;
}

// Assignment overload for advance order
Advance& Advance::operator=(const Advance& a) {
    if (this == &a) {
        return *this;
    }
    Orders::operator= (a);
    this->numSoldiers = a.numSoldiers;
    this->source = a.source;
    this->target = a.target;
    return *this;
}

// Default constructor for Bomb order
Bomb::Bomb() : Orders() {
    this->target = new Territory();
}

// Parameterized constructor for Bomb order
Bomb::Bomb(string orderType, Territory* target, Player* executer) : Orders(orderType, executer) {
    this->target = target;
}

// Copy constructor for Bomb order
Bomb::Bomb(const Bomb& other) : Orders(other) {
    this->target = new Territory(*(other.target));

}
// Destructor
Bomb::~Bomb() {
    delete target;
}

Territory* Bomb::getTarget() const {
    return target;
}
// Getter and setter for 'target'
void Bomb::setTarget(Territory* targetTer) {
    this->target = targetTer;
}
// Overriden method for validate method
bool Bomb::validate()  {
    bool hasTerritory = false;
    bool isAdjacent = false;
    // Create a reference to the vector of territories that the player owns
    if (Orders::getPlayer()->getPlayerId() == target->Territory::get_player_id()) {
        hasTerritory = true;
    }
    // Check if the territory is adjacent to a player's territory
    const std::vector<Territory*>& adjacentTer = target->get_adjacent_territories();
    for (const Territory* adjacent : adjacentTer) {
        if (Orders::getPlayer()->getPlayerId() == adjacent->Territory::get_player_id()) {
            isAdjacent = true;
        }
    }
    if (hasTerritory || !isAdjacent) {
        return false;
    }
    else {
        return true;
    }

}
// Overriden method for execute method
void Bomb::execute() {
    if (!(validate())) {
        cout << "Could not execute order" << endl;
    }
    else {
        int remainingArmy = target->get_army_size();
        remainingArmy = remainingArmy / 2;
        target->set_army_size(remainingArmy);
    }
    Notify(this);
}
// Ostream overloading for Bomb order
ostream& operator << (ostream& output, const Bomb& obj) {
    output << "The order 'Bomb' Destroys half the the army units of another player positioned at an adjacent territory"
    << "The player must have a bomb card to perform this order" << endl;
    return output;
}
// Assignment overloading for Bomb order
Bomb& Bomb::operator=(const Bomb& b) {
    if (this == &b) {
        return *this;
    }
    Orders::operator= (b);
    this->target = b.target;
    return *this;
}
// Default constructor for Blockade order
Blockade::Blockade() : Orders() {
    this->target = new Territory();
    this->numSoldiers = 0;
}
// Parameterized constructor for Blockade order
Blockade::Blockade(string orderType, int numSoldiers, Territory* target, Player* executer) : Orders(orderType, executer) {
    this->target = target;
    this->numSoldiers = numSoldiers;
}
// Copy constructor for Blockade method
Blockade::Blockade(const Blockade& other) : Orders(other) {
    this->target = new Territory(*(other.target));
    this->numSoldiers = other.numSoldiers;
}

Blockade::~Blockade() {
    delete target;
}

int Blockade::getNumSoldiers() const{
    return numSoldiers;
}
// Getter and setter for 'numSoldiers'
void Blockade::setNumSoldiers(int Soldiers) {
    this->numSoldiers = Soldiers;
}

Territory* Blockade::getTarget() const{
    return target;
}
// Getter and setter for 'target'
void Blockade::setTarget(Territory* targetTer) {
    this->target = targetTer;
}
// Overriden validate method for Blockade order
bool Blockade::validate() {
    if (Orders::getPlayer()->getPlayerId() == target->get_player_id()) {
        return true;
    }
    else {
        return false;
    }

}
// Overriden execute method for Blockade order
void Blockade::execute() {
    if (!(validate())) {
        cout << "Could not execute order" << endl;
    }
    else {
        int triple = 2*(target->get_army_size());
        target->set_army_size(triple);
        // set the target owner to the neutral player "101" is the player ID for a neutral player

        target->Territory::set_player_id(101);

    }
    Notify(this);
}
// Ostream overloading for Blockade order
ostream& operator << (ostream& output, const Blockade& obj) {
    output << "The order 'Blockade' triples the number of army units on a player's territory."
    << "This also makes a territory a neutral territory, meaning it cannot be attack or send any offensive orders" 
    << "The player needs a blockade card to perform this order" << endl;
    return output;
}
// Assignment overloading for Blockade order
Blockade& Blockade::operator=(const Blockade& bl) {
    if (this == &bl) {
        return *this;
    }
    Orders::operator=(bl);
    this->numSoldiers = bl.numSoldiers;
    this->target = bl.target;
    return *this;

}
// Default constructor for Airlift order
Airlift::Airlift() : Orders() {
    this->numSoldiers = 0;
    this->source = new Territory();
    this->target = new Territory();
}
// Parameterized constructor for Airlift order
Airlift::Airlift(string orderType, int numSoldiers, Territory* source, Territory* target, Player* executer) : Orders(orderType, executer) {
    this->numSoldiers = numSoldiers;
    this->source = source;
    this->target = target;
}
// Copy constructor for Airlift order
Airlift::Airlift(const Airlift& other) : Orders(other) {
    this->target = new Territory(*(other.target));
    this->source = new Territory(*(other.source));
    this->numSoldiers = other.numSoldiers;
}

Airlift::~Airlift() {
    delete source;
    delete target;
}

// Getters
int Airlift::getNumSoldiers() const {
    return numSoldiers;
}
 
Territory* Airlift::getSource() const {
    return source;
}

Territory* Airlift::getTarget() const {
    return target;
}
// Setters
void Airlift::setNumSoldiers(int Soldiers) {
    this->numSoldiers = Soldiers;
} 

void Airlift::setSource(Territory* sourceTer) {
    this->source = sourceTer;
} 

void Airlift::setTarget(Territory* targetTer) {
    this->target = targetTer;
} 
// Overriden validate method for Airlift order
bool Airlift::validate()  {
    bool hasTerritory = false;
    bool hasSource = false;
    if (Orders::getPlayer()->getPlayerId() != source->get_player_id()) {
        return false;
    }
    else if (Orders::getPlayer()->getPlayerId() != target->get_player_id()) {
        return false;
    }
    else {
        return true;
    }

}
// Overriden execute method for Airlift order
void Airlift::execute() {
    if (!(validate())) {
        cout << "Could not execute order" << endl;
    }
    else {
        int update = numSoldiers + target->get_army_size();
        target->set_army_size(update);
        update = abs(numSoldiers-source->get_army_size());
        source->set_army_size(update);
    }
    Notify(this);

}
// Ostream overloading for Airlift method
ostream& operator << (ostream& output, const Airlift& obj) {
    output << "The order 'Airlift' advances a certain number of army units from the player's territory to another."
    << "The target territory does not need not need to be adjacent to the source territory." 
    << "The player needs an airlift card to perform this order" << endl;
    return output;
}
// Assignment overloading for Airlift method
Airlift& Airlift::operator=(const Airlift& air) {
    if (this == &air) {
        return *this;
    }
    Orders::operator=(air);
    this->numSoldiers = air.numSoldiers;
    this->source = air.source;
    this->target = air.target;
    return *this;
}
// Default constructor for Negotiate order
Negotiate::Negotiate() : Orders(){
    this->player2 = new Player();
}
// Paramterized constructor for Negotiate order
Negotiate::Negotiate(string orderType, Player* player2, Player* executer) : Orders(orderType, executer) {
    this->player2 = player2;
}

// Copy constructor for Negotiate order. Line giving error.
Negotiate::Negotiate(const Negotiate& other) : Orders(other), player2(other.player2) {
    this->player2 = new Player(*(other.player2));
}

Negotiate::~Negotiate() {
    delete player2;
}

Player* Negotiate::getPlayer2() const {
    return player2;
}
// Getter and setter for 'player2'
void Negotiate::setPlayer2(Player* player) {
    this->player2 = player;
}
// Overriden validate method for Negotiate order
bool Negotiate::validate() {
    if (player2 == Orders::getPlayer()) {
        return false;
    }
    else{
        return true;
    }

}
// Overriden execute method for Negotiate order
void Negotiate::execute() {
    if (!(validate())) {
        cout << "Could not execute order" << endl;
    }
    else {
        Orders::setNegotiatedPlayer(Orders::getPlayer()->getPlayerId(), player2->getPlayerId());
        Orders::setNegotiatedPlayer(player2->getPlayerId(), Orders::getPlayer()->getPlayerId());
    }
    Notify(this);
}
// Ostream overloading for Negotiate order
ostream& operator << (ostream& output, const Negotiate& obj) {
    output << "The order 'Negotiate' prevents the player from receiving any attacks from another player"
    << "until the end of their turn. The player needs a negotiate card to perform this order." << endl;
    return output;
}
// Assignment overloading for Negotiate order
Negotiate& Negotiate::operator=(const Negotiate& n) {
    if (this == &n) {
        return *this;
    }
    Orders::operator=(n);
    // Line gives error?
    this->player2 = n.player2;
    return *this;
}
// Default constructor for Orderlist
OrdersList::OrdersList() {

}
// Destructor that deletes all the objects in the list
// By calling their destructors
OrdersList::~OrdersList() {
    for (auto order : orders) {
        delete order;
    }
}


// Add method for OrderList
void OrdersList::add(Orders* order) {
    LogObserver *observer = new LogObserver(this);
    orders.push_back(order);
    Notify(this);
    delete observer;
    observer = NULL;
}

// Remove method for OrderList
// Pass a reference of the pointer to the object
void OrdersList::remove(Orders* order) {
    // Making an iterator
    auto itr = orders.begin();
    // If the iterator does not reach the end
    while (itr != orders.end()) {
        // If a match is found
        if (*itr == order) {
            // Delete the order pointed by the iterator
            // to avoid a memory leak
            delete *itr;

            // Set the objects original pointer to null to avoid
            // a dangling pointer
            order = nullptr;

            // Erase the iterator from the list
            itr = orders.erase(itr);
        } else {
            ++itr;
        }
    }
}
// Move method for OrderList
void OrdersList::move(int Index1, int Index2) {
    // Check if indexes are valid
      if (Index1 >= 0 && Index1 < orders.size() &&
        Index2 >= 0 && Index2 < orders.size() &&
        Index1 != Index2) {

        // Make an iterator that points to the first index
        auto it1 = orders.begin();
        std::advance(it1, Index1);

        // Store the element in a placeholder
        Orders* elementAtIndex1 = *it1;

        // Remove the element at Index
        orders.erase(it1);


        // Create an iterator that points to Index2
        auto it2 = orders.begin();
        // Move the iterator to Index2
        std::advance(it2, Index2);

        // Insert the element at Index2
        orders.insert(it2, elementAtIndex1);
    } 
    
    else {
        // If the indexes are invalid
        cout << "Could not perform move operation" << endl;
    }
}

// Print method for OrderList
void OrdersList::printOrdersAndValidate() {
    for (const auto& orderPtr : orders) {
        // Dereference the pointer and call the getName() method

        cout << orderPtr->getOrderType() << ": " << std::boolalpha << orderPtr->validate() << endl;

    }
}

//Implementing stringToLog from ILoggable
string OrdersList::stringToLog()
{
    return "Inserted order " + orders.back()->getOrderType() + " into list.";
}

ostream& operator <<(ostream& output, const OrdersList& obj) {
    for (const Orders *order: obj.orders) {
        output << *order << endl;
    }
    return output;
}








