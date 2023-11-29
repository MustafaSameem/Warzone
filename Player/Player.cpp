#include <vector>
#include "../Orders/Orders.h"
#include "Player.h"
#include <iostream>


    //Constructers
    Player::Player(){
   
    _playerId = 0;
    this-> _territories = vector<Territory*>();
    this-> _orders = new OrdersList();
    this-> _hand = new Hand();

    }

    Player::Player(vector<Territory*>& territories, OrdersList& orders, int playerID,Hand& hand, string name){

    _playerId = playerID;
    this-> _territories = territories;
    this-> _orders = &orders;
    this-> _hand = &hand;
    this->name = name;
    }

    Player::Player(const Player& PlayerCopy) {
    _playerId = PlayerCopy._playerId;
    for (Territory* terr : PlayerCopy._territories) {
        _territories.push_back(new Territory(*terr));  
    }
    _orders = new OrdersList(*(PlayerCopy._orders));
    _hand = new Hand(*(PlayerCopy._hand));
}
    //Destructor
    Player::~Player() {
    for (Territory* terr : _territories) {
        delete terr;
    }
    _territories.clear();  

    delete _orders;

    delete _hand;
}

Player& Player::operator=(const Player& object) {
    if (this == &object) {
        return *this;
    }
    for (Territory* terr : _territories) {
        delete terr;
    }
    delete _orders;  
    delete _hand;     

    _playerId = object._playerId;

    _territories.clear();
    for (Territory* terr : object._territories) {
        _territories.push_back(new Territory(*terr));
    }
    _orders = new OrdersList(*(object._orders));  
    _hand = new Hand(*(object._hand));          

    return *this;
}
    //Output Stream Operator
    ostream& operator << (ostream &os, const Player &player){
	os << "\nPlayer id :" << player._playerId;
	os << "\nPlayer territories: " << player.getTerritories();
	os << "\nPlayer hand: " << *player._hand;
	os << "\nPlayer orders: \n" << *player._orders;
	return os;
    }

    //Getters
    const int Player::getPlayerId() const{
    return _playerId;
    }

    const std::string Player::getTerritories() const{
    std::string string;

    for (const auto& territoryPtr : _territories) {
        if (territoryPtr) { 
             string.append(territoryPtr->get_name());
                           string.append(" ");
        }
        
    }
    return string;
    }
    
    const vector<Territory*> Player::getVecTer()const{
    return _territories;
}

    const OrdersList* Player::getOrders() const{
    return _orders;
    }

    const Hand* Player::getHand() const{
	return _hand;}

    const int Player::getArmy() const{
    return _army;}

    void Player::addArmyUnits(int units){
    _army += units;
    }

    //Setters
    void Player::setId(int id){
    _playerId = id;
    }

    void Player::setTerritories(vector<Territory*>& territories){
    _territories = territories;
    }

    void Player::setHand(Hand& hand){
    _hand = &hand;}

    void Player::setOrders(OrdersList &orders) {
    _orders =  &orders;
}

    //methods
    vector<Territory*> Player::toAttack(){
    return vector<Territory*>();
    }
    
    vector<Territory*> Player::toDefend(){
    return vector<Territory*>();
    }

    void Player::issueOrders(){
    // Orders *order = new Orders();
    // this->_orders->add(order);
    }

    void Player::add_territory(Territory* player_territory){
        _territories.push_back(player_territory);
    }
