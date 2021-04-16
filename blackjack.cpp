#include <iostream>

enum suits
{
    clubs,
    diamonds,
    hearts,
    spades
};

enum value
{
    two = 2,
    three = 3,
    four = 4,
    five = 5,
    six = 6,
    seven = 7,
    eight = 8,
    nine = 9,
    ten = 10,
    J = 10,
    Q = 10,
    K = 10,
    A = 11

};

class Card
{

private:
    suits suits_;
    value value_;
    char *serialNumberCard;

public:
    Card();
    Card(Card &other)
    {
        this->serialNumberCard = new char[15];
        for (size_t i = 0; serialNumberCard[i] != '\0'; i++)
        {
            this->serialNumberCard[i] = other.serialNumberCard[i];
        }
    };
    ~Card()
    {
        delete[] this->serialNumberCard;
    };
};

class Deck
{
private:
    Card *seqOfCards;
    char *serialNumberDeck;
    size_t countCards;

public:
    Deck()
    {
        this->seqOfCards = new Card[52];
        this->serialNumberDeck = new char[10];
        this->countCards = 0;
    };
    Deck(Deck &other)
    {
        this->countCards = other.countCards;
        this->seqOfCards = new Card[other.countCards];
        for (size_t i = 0; i < countCards; i++)
        {
            seqOfCards[i] = other.seqOfCards[i];
        }
        this->serialNumberDeck = new char[10];
        for (size_t i = 0; serialNumberDeck[i] != '\0'; i++)
        {
            serialNumberDeck[i] = other.serialNumberDeck[i];
        }
    };
    ~Deck()
    {
        delete [] seqOfCards;
        delete [] serialNumberDeck;
    }
};