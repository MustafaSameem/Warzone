#include "Cards.h"
#include <vector>
#include <iostream>
using namespace std;

//----------------------------------------------------------------------------------------------
//* Card *
//----------------------------------------------------------------------------------------------
//Default constructor
Card::Card()
{
    //default Card constructor creates a card of a random type
    vector<CardType> types = {BOMB, REINFORCEMENT, BLOCKADE, AIRLIFT, DIPLOMACY};
    int randint = (1 + rand()) % 5;
    this->type = types.at(randint);
    drawn = false;
}

//Parameterized constructor
Card::Card(CardType type)
{
    this->type = type;
    drawn = false;
}

//Copy constructor
Card::Card(const Card &othercards)
{
    this->type = CardType(othercards.getCardType());
    this->drawn = othercards.getDrawn();
}

//Destructor
Card::~Card(){}

//play method
void Card::play()
{
    if(drawn)//card can only be played if it has been drawn by a player
    {
        //special orders
        if(type == BOMB)
        {
            std::cout << "special order BOMB created\n";
        }
        else if(type == REINFORCEMENT)
        {
            std::cout << "special order REINFORCEMENT created\n";
        }
        else if(type == BLOCKADE)
        {
            std::cout << "special order BLOCKADE created\n";
        }
        else if(type == AIRLIFT)
        {
            std::cout << "special order AIRLIFT created\n";
        }
        else if(type == DIPLOMACY)
        {
            std::cout << "special order DIPLOMACY created\n";
        }
    }
    setDrawn(false);//card has been used, so it is returned to the deck
    //note: it's not *actually* removed from the hand. it's simply set to not drawn, which means the hand cannot use it any more.
}

//getters + setters for CARDS
void Card::setDrawn(bool drawn) {this->drawn = drawn;}
bool Card::getDrawn() const {return drawn;}
CardType Card::getCardType() const {return type;}
string Card::getCardTypeName() const//getting the type as a string so we can print it
{
    string s;
    if(type == BOMB)
    {
        s = "BOMB";
    }
    else if(type == REINFORCEMENT)
    {
        s = "REINFORCEMENT";
    }
    else if(type == BLOCKADE)
    {
        s = "BLOCKADE";
    }
    else if(type == AIRLIFT)
    {
        s = "AIRLIFT";
    }
    else if(type == DIPLOMACY)
    {
        s = "DIPLOMACY";
    }
    return s;
}

ostream& operator<<(ostream& ostream, const Card& card)
{
    ostream << "Type: " << card.type << ", drawn: " << card.drawn << endl;
    return ostream;
}

//----------------------------------------------------------------------------------------------
//* Deck *
//----------------------------------------------------------------------------------------------

//Default constructor
Deck::Deck()
{
    //creates an empty Deck object
}

//Parameterized constructor
Deck::Deck(vector<Card> othercards)
{
    for(int i=0; i<othercards.size(); i++)
    {
        CardType newtype = othercards.at(i).getCardType();
        Card* newcard = new Card(newtype);
        cards.push_back(newcard);
    }
}

//Copy constructor
Deck::Deck(const Deck &otherdeck)
{
    for (Card* c : otherdeck.getDeck())
    {
        Card* c2 = new Card(c->getCardType());
        c2->setDrawn(c->getDrawn());
        this->cards.push_back(c2);
    }
}

//Destructor
Deck::~Deck()
{
    for (Card* c : getAvailableCards())//need to delete all manually, since it's a vector of pointers; deleting available cards since some cards are in both hand and deck
    {
        delete c;
    }
}

void Deck::addCardTypeToDeck(CardType type)
{
    Card* newcard = new Card(type);
    cards.push_back(newcard);
}

//draw function for taking a card from the hand; parameter is a Hand object, so the deck knows to which hand to add the drawn card
void Deck::draw(Hand* hand)
{
    vector<Card*> deckcards = this->getAvailableCards();//only draw from non-drawn cards
    if(deckcards.empty())//if the deck is empty or every card has been drawn
    {
        cout << "Deck is empty. No more cards to draw.\n";
        return;
    }
    int randint = (1 + rand()) % deckcards.size();
    Card* c = deckcards.at(randint);
    c->setDrawn(true);
    hand->addCardsToHand(c);
}

//getters + setters for DECKS
vector<Card*> Deck::getDeck() const {return cards;}

vector<Card*> Deck::getAvailableCards() const //some cards may have already been drawn. thus, this function just returns the non-drawn cards
{
    vector<Card*> deckcards = this->getDeck();
    vector<Card*> availcards;
    for(int i=0; i<deckcards.size(); i++)
    {
        if(deckcards.at(i)->getDrawn() == false)
        {
            availcards.push_back(deckcards.at(i));
        }
    }
    return availcards;
}

ostream& operator<<(ostream& ostream, const Deck& deck)
{
    ostream << "Cards in deck: { ";
    for(int i=0; i<deck.getAvailableCards().size(); i++)
    {
        ostream << deck.getAvailableCards().at(i)->getCardTypeName() << ((i==deck.getAvailableCards().size()-1)? " " : ", ");
    }
    ostream << "}" << endl;
    return ostream;
}

//----------------------------------------------------------------------------------------------
//* Hand *
//----------------------------------------------------------------------------------------------

//Default constructor
Hand::Hand()
{
    //creates an empty Hand object
}

//Parameterized constructor
//Creates a hand object given a deck to draw from and the number of cards to add to the hand
Hand::Hand(Deck* d, int n)
{
    for(int i=0; i<n; i++)
    {
        d->draw(this);
    }
}

//Copy constructor
Hand::Hand(const Hand &otherhand)
{
    for (Card* c : otherhand.getHand())
    {
        Card* c2 = new Card(c->getCardType());
        c2->setDrawn(c->getDrawn());
        this->cards.push_back(c2);
    }
}

//Destructor
Hand::~Hand()
{
    for (Card* c : getCardsInHand())//going thru cards in hand since some cards are both in hand and in deck (because of implementation)
    {
        delete c;
    }
}

void Hand::addCardsToHand(Card* c)
{
    std::cout << "Card added to hand\n";
    cards.push_back(c);
}

vector<Card*> Hand::getCardsInHand() const
{
    //we need to do it like this because cards can still be in the hand but have been played (and thus, returned to the deck)
    vector<Card*> unusedcards;
    for(int i=0; i<cards.size(); i++)
    {
        if(cards.at(i)->getDrawn() == true)
        {
            unusedcards.push_back(cards.at(i));
        }
    }
    return unusedcards;
}

vector<Card*> Hand::getHand() const
{
    return cards;
}

ostream& operator<<(ostream& ostream, const Hand& hand)
{
    ostream << "Cards in hand: { ";
    for(int i=0; i<hand.getCardsInHand().size(); i++)
    {
        ostream << hand.getCardsInHand().at(i)->getCardTypeName() << ((i==hand.getCardsInHand().size()-1)? " " : ", ");
    }
    ostream << "}" << endl;
    return ostream;
}
