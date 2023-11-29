#include "Cards.h"
#include <iostream>
using namespace std;
using std::vector;

static void testCards()
{
    //adding cards to the deck
    Deck* deck = new Deck();
    deck->addCardTypeToDeck(CardType::BOMB);
    deck->addCardTypeToDeck(CardType::REINFORCEMENT);
    deck->addCardTypeToDeck(CardType::BLOCKADE);
    deck->addCardTypeToDeck(CardType::AIRLIFT);
    deck->addCardTypeToDeck(CardType::DIPLOMACY);
    
    //drawing cards from the hand and putting them in the deck
    Hand* p1hand = new Hand();
    deck->draw(p1hand);
    deck->draw(p1hand);
    deck->draw(p1hand);
    deck->draw(p1hand);
    deck->draw(p1hand);

    std::cout<< *deck;
    std::cout<< *p1hand;
    
    //playing available cards in the hand
    p1hand->getCardsInHand().at(0)->play();//playing the top card in a player's hand
    p1hand->getCardsInHand().at(0)->play();
    p1hand->getCardsInHand().at(0)->play();
    p1hand->getCardsInHand().at(0)->play();
    p1hand->getCardsInHand().at(0)->play();

    std::cout<< *deck;
    std::cout<< *p1hand;

    delete deck;
    deck = NULL;
    
    delete p1hand;
    p1hand = NULL;
}

int main()
{
    testCards();
}