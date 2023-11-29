#include <string>
#include <vector>
using namespace std;
#pragma once

class Hand;

//enum type to limit CardType values
enum CardType
{
    BOMB, REINFORCEMENT, BLOCKADE, AIRLIFT, DIPLOMACY
};

class Card
{
    private:
        CardType type;
        bool drawn;

    public:
        //Default constructor
        Card();

        //Parameterized constructor
        Card(CardType type);

        //Copy constructor
        Card(const Card &othercards);

        //Destructor
        ~Card();

        void play();

        //Card type should not be settable after the card has been declared (if you need a card of a particular type, use the parameterized constructor)
        CardType getCardType() const;
        string getCardTypeName() const;
        
        bool getDrawn() const;
        void setDrawn(bool drawn);

        friend ostream& operator<<(ostream&, const Card&);    
};

//-----------------------------------------------

class Deck
{
    private:
        vector<Card*> cards;

    public:
        //Default constructor
        Deck();
        
        //Parameterized constructor
        Deck(vector<Card> othercards);
        
        //Copy constructor
        Deck(const Deck &otherdeck);

        //Destructor
        ~Deck();

        void draw(Hand* hand);

        //setDeck() not needed as there is a parameterized constructor already.

        vector<Card*> getDeck() const;//all cards in the deck, including those which may have been drawn
        vector<Card*> getAvailableCards() const;//only remaining non-drawn cards in the deck
        void addCardTypeToDeck(CardType type);

        friend ostream& operator<<(ostream&, const Deck&);
};

//-----------------------------------------------

class Hand
{
    private:
        vector<Card*> cards;
    
    public:
        //Default contructor
        Hand();

        //Parameterized constructor
        Hand(Deck* d, int n);

        //Copy constructor
        Hand(const Hand &otherhand);

        //Destructor
        ~Hand();

        //setHand() is not needed as it may violate the deck. Use parameterized constructor instead.

        void addCardsToHand(Card* c);
        vector<Card*> getCardsInHand() const;//cards which are still usable (drawn) in the hand
        vector<Card*> getHand() const;//all cards in the hand, including those which may have been returned to the deck

        friend ostream& operator<<(ostream&, const Hand&);
};

