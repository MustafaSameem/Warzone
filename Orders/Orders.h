#pragma once
#ifndef ORDERS_H
#define ORDERS_H
#include <string>
#include <vector>
#include <list>
#include <cstdlib>
#include <random>
using namespace std;
#include "../Map/Map.h"
#include "../Player/Player.h"
#include "../Cards/Cards.h"
#include "../LoggingObserver/LoggingObserver.h"


class Player;
class Territory;
class ILoggable;
class Subject;

class Orders : public Subject, public ILoggable{
private:
    Player* executer;
    string orderType;
    static const int maxPlayers = 7;
    static int NegotiatedPlayers[maxPlayers][maxPlayers];
    static int receivedCard[maxPlayers];

public:

    Orders();
    // Default constructor

    Orders(string orderType, Player* executer);
    // Parametrized constructor

    Orders(const Orders& other);
    // Copy constructor

    virtual ~Orders();
    // Destructor

    virtual bool validate();
    // Validates for a valid order
    virtual void execute() = 0;
    // Executes the order

    string stringToLog();//overriding pure virtual function from ILoggable

    string getOrderType() const;
    // Getter

    int getNegotiatedPlayer(int row, int column);

    int getReceivedCard(int player_ID);

    void setOrderType(string orderType);
    // Setter

    void setNegotiatedPlayer(int playerID_1, int playerID_2);

    void setReceivedCard(int player_ID);

    Player* getPlayer() const;
    void setPlayer(Player* executer);

    friend ostream& operator << (ostream& output, const Orders& obj);
    // Stream insertion operator

    Orders& operator=(const Orders& o);



};



class Deploy : public Orders {
    private:
        int numSoldiers;
        Territory* target;
    public:

        Deploy();
        // Default constructor

        Deploy(string orderType, int numSoldiers, Territory* target, Player* executer);
        // Parameterized constructor

        Deploy(const Deploy& other);
        // Copy constructor

        ~Deploy();
        // Destructor

        bool validate() override;
        // Overriden validate method
        void execute() override;
        // Overriden execute method
        int getNumSoldiers() const;
        // Getter and setter for 'numSoldiers'
        void setNumSoldiers(int numSoldiers);
        Territory* getTarget() const;
        // Getter and setter for 'target'
        void setTarget(Territory* target);
        // Ostream overloading
        friend ostream& operator << (ostream& output, const Deploy& obj);
        // Assignment overloading
        Deploy& operator=(const Deploy& d);


            
};

class Advance : public Orders {
    private:
        // "targetOwner" will be 0 if no owner, 1 if owned by player
        // And 2 if owned by an enemy.
        int targetOwner;
        int numSoldiers;
        Territory* source;
        Territory* target;
    public:
        Advance();
        // Default constructor

        Advance(string orderType, int numSoldiers, Territory* source, Territory* target, Player* executer, int targetOwner = 0);
        // Parameterized constructor

        Advance(const Advance& other);
        // Copy constructor

        ~Advance();
        // Destructor

        bool validate() override;
        // Overriden validate method

        void execute() override;
        // Overriden execute method

        void attacking(int& attackingArmy, int& defendingArmy);

        int getNumSoldiers() const;
        // Getter and setter for 'numSoldiers'
        void setNumSoldiers(int numSoldiers);

        Territory* getSource() const;
        // Getter and setter for 'source'
        void setSource(Territory* source);

        Territory* getTarget() const;
        // Getter and setter for 'target'
        void setTarget(Territory* target);


        friend ostream& operator << (ostream& output, const Advance& obj);
        // Ostream overloading

        Advance& operator=(const Advance& a);
        // Assignment overloading
            
};

class Bomb : public Orders {
     private:
        Territory* target;
    public:

        Bomb();
        // Default constructor

        Bomb(string orderType, Territory* target, Player* executer);
        // Parameterized constructor

        Bomb(const Bomb& other);
        // Copy constructor

        ~Bomb();
        // Destructor

        bool validate() override;
        // Overriden validate method

        void execute() override;
        // Overriden execute method

        Territory* getTarget() const;
        // Getter and setter for 'target'
        void setTarget(Territory* target);


        friend ostream& operator << (ostream& output, const Bomb& obj);
        // Ostream overload

        Bomb& operator=(const Bomb& b);
        // Assignment overload
};

class Blockade : public Orders {
     private:
        Territory* target;
        int numSoldiers;
    public:

        Blockade();
        // Default constructor

        Blockade(string orderType, int numSoldiers, Territory* target, Player* executer);
        // Parameterized constructor

        Blockade(const Blockade& other);
        // Copy constructor

        ~Blockade();
        // Destructor

        bool validate() override;
        // Overriden validate method

        void execute() override;
        // Overriden execute method

        int getNumSoldiers() const;
        // Getter and setter for 'numSoldiers'
        void setNumSoldiers(int numSoldiers);

        Territory* getTarget() const;
        // Getter and setter for 'target'
        void setTarget(Territory* target);


        friend ostream& operator << (ostream& output, const Blockade& obj);
        // Ostream overload

        Blockade& operator=(const Blockade& bl);
        // Assignment overload
};

class Airlift : public Orders {
    private:
        int numSoldiers;
        Territory* source;
        Territory* target;
    public:
        Airlift();
        // Default constructor

        Airlift(string orderType, int numSoldiers, Territory* source, Territory* target, Player* executer);
        // Parameterized constructor

        Airlift(const Airlift& other);
        // Copy constructor

        ~Airlift();
        // Destructor

        bool validate() override;
        // Overriden validate method

        void execute() override;
        // Overriden execute method

        int getNumSoldiers() const;
        // Getter and setter for 'numSoldiers'
        void setNumSoldiers(int numSoldiers);

        Territory* getSource() const;
        // Getter and setter for 'source'
        void setSource(Territory* source);

        Territory* getTarget() const;
        // Getter and setter for 'target'
        void setTarget(Territory* target);

        friend ostream& operator << (ostream& output, const Airlift& obj);
        // Ostream overloading

        Airlift& operator=(const Airlift& air);
        // Assignment overloading
            
};

class Negotiate : public Orders {
     private:
        Player* player2; 
    public:

        Negotiate();
        // Default constructor

        Negotiate(string orderType, Player* player2, Player* executer);
        // Parameterized constructor

        Negotiate(const Negotiate& other);
        // Copy constructor

        ~Negotiate();
        // Destructor

        bool validate() override;
        // Overriden validate method

        void execute() override;
        // Overriden execute method

        Player* getPlayer2() const;
        // Getter and setter for 'player2'
        void setPlayer2(Player* player2);

        friend ostream& operator << (ostream& output, const Negotiate& obj);
        // Ostream overloading

        Negotiate& operator=(const Negotiate& n);
        // Assignment overloading
};

class OrdersList : public Subject, public ILoggable{
    private:
        list<Orders*> orders;
    public:
        OrdersList();
        // Default constructor

        ~OrdersList();
        // Destructor

        void add(Orders* order);
        // Add method

        void remove(Orders* order);
        // Remove method

        void move(int Index1, int Index2);
        // Move method

        void printOrdersAndValidate();
        // Print method

        string stringToLog();//overriding pure virtual function from ILoggable

        friend ostream& operator <<(ostream& output, const OrdersList& obj);


};



#endif




