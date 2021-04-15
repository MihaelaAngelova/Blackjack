#include <iostream>
enum suits
{
    clubs,
    diamonds,
    hearts,
    spades
};
/*
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
    Q,
    K,
    A
};*/

class Card
{

private:
    suits suits_;
    short value;
    /*
    A - 1
    J - 11
    Q - 12
    K - 13
    */
    char serialNumberCard[15];

public:
    Card();
    Card(char *serNumDeck)
    {
        for(int i=0;serNumDeck[i];i++)
            serialNumberCard[i]=serNumDeck[i];
    }
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
    
    void mergedecknum(int number)
    {
        int numberdigits=1;
        for(int i=0, n=number;n;n/=10)
            numberdigits*=10;
        for(int i=0;;i++)
        {
            if(serialNumberCard[i]=='\0')
            {
                for(int n=number;n;n%=numberdigits)
                {
                    numberdigits/=10;
                    serialNumberCard[i++]=n/numberdigits+'0';
                }
                break;
            }
        }
    }
    void createcard(int &a, int &b)
    {
        if(a==1)
            suits_=clubs;
        if(a==2)
            suits_=diamonds;
        if(a==3)
            suits_=hearts;
        if(a==4)
            suits_=spades;
        value=b;
    }
};

class Deck
{
private:
    Card *seqOfCards;
    char serialNumberDeck[10];
    size_t countCards;

public:
    Deck()
    {
        this->seqOfCards("Default") = new Card[52];
        this->serialNumberDeck = "Default"
        this->countCards = 52;
        for(int i=1;i<=52;i++)
        {
            seqOfCards[i].mergedecknum(i);
        }//дотук си правехме серийна номер на картите
        for(int a=1, i=0;a<=4;a++)//тука почвами генерация на картите
        {
            for(int b=1;b<=13;b++)
            {
                seqOfCards[i++].createcard(a,b);
            }
        }
        shuffle(seqOfCards, 52);
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
    void shuffle(Card &cards[], int size)
    {
        srand(time(0));
        for (int i=0; i<size ;i++)
        {
            int r = i + (rand() % (52 -i));
            swap(card[i], card[r]);
        }
    }
};
