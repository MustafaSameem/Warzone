#pragma once
#include "../Orders/Orders.h"
#include "../Map/Map.h"
#include "../Cards/Cards.h"


#include <ostream>
#include <vector>

class OrdersList;
class Orders;
class Territory;
class Card;

class Player{

private:

vector<Territory*> _territories;
OrdersList* _orders ;
int _playerId;
Hand * _hand;
int _army;
string name;


public:
        //Default constructor
        Player();
        //Parameterized constructor
        Player(vector<Territory*>& territories,OrdersList& orders, int playerID, Hand& hand, string name);
        //copy constructor
        Player(const Player& PlayerCopy);
        //destructor
        ~Player();

        //Assignment operator overload
        Player& operator =(const Player& obj);

        //Output stream operator overload
        friend std::ostream& operator<<(std::ostream& os, const Player& player);
        
        //Getters
        const int getPlayerId() const;
        const std::string getTerritories() const;
        const OrdersList* getOrders() const;
        const Hand* getHand() const;
        const int getArmy() const;

        const vector<Territory*> getVecTer()const;

        //Setters
        void setId(int id);
        void setTerritories(vector<Territory*>& territories);
        void setOrders(OrdersList& orders);
        void setHand(Hand& hand);
        void addArmyUnits(int unit);

        //methods
        vector<Territory*> toAttack();
        vector<Territory*> toDefend();
        void issueOrders();
        void add_territory(Territory* player_territory);

        const string printOrder() const;

};
