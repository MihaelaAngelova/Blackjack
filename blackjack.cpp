#include <iostream>
#include <time.h>
#include <stdlib.h>
#include <cstring>

void game();
enum suits
{
    clubs = 1,
    diamonds,
    hearts,
    spades
};

class Card
{

private:
    suits suits_;
    /*
        A - 1
        J - 11
        Q - 12
        K - 13
        */
    short value;
    char serialNumberCard[15];

public:
    Card()
    {
        //this->serialNumberCard[15] = "";
        this->suits_ = diamonds;
        this->value = 2;
    }
    Card(char *serNumDeck)
    {
        for (int i = 0; serNumDeck[i]; i++)
            serialNumberCard[i] = serNumDeck[i];
    }
    Card(Card &other)
    {
        for (size_t i = 0; serialNumberCard[i] != '\0'; i++)
        {
            this->serialNumberCard[i] = other.serialNumberCard[i];
        }
        value = other.value;
    };

    void mergedecknum(int number)
    {
        int numberdigits = 1;
        for (int i = 0, n = number; n; n /= 10)
            numberdigits *= 10;
        for (int i = 0;; i++)
        {
            if (serialNumberCard[i] == '\0')
            {
                for (int n = number; n; n %= numberdigits)
                {
                    numberdigits /= 10;
                    serialNumberCard[i++] = n / numberdigits + '0';
                }
                break;
            }
        }
    }
    void createcard(int &a, int &b)
    {
        if (a == 1)
            suits_ = clubs;
        if (a == 2)
            suits_ = diamonds;
        if (a == 3)
            suits_ = hearts;
        if (a == 4)
            suits_ = spades;
        value = b;
    }

    const suits getSuits() const
    {
        return this->suits_;
    }

    const short getValue() const
    {
        return this->value;
    }

    const char *getSerialNumberCards() const
    {
        return this->serialNumberCard;
    }

    short cardValue(Card &card1)
    {
        short value = card1.getValue();
        switch (value)
        {
        case 2:
        case 3:
        case 4:
        case 5:
        case 6:
        case 7:
        case 8:
        case 9:
        case 10:
            return value;
            break;
        case 11:
            return 10;
            break;
        case 12:
            return 10;
            break;
        case 13:
            return 10;
            break;
        case 1:
            return 1;
            break;
        }
    }
    void swapi(Card &other)
    {
        Card temp;
        temp.suits_ = other.suits_;
        temp.value = other.value;
        std::strcpy(temp.serialNumberCard,other.serialNumberCard);


        other.suits_ = suits_;
        other.value = value;
        std::strcpy(other.serialNumberCard,serialNumberCard);


        suits_ = temp.suits_;
        value = temp.value;
        std::strcpy(serialNumberCard,temp.serialNumberCard);
    }
    int addpoints()
    {
        if (value > 1 && value < 10)
            return value;
        if (value > 10 && value < 14)
            return 10;
        return 11;
    }
};

class Deck
{
private:
    Card *seqOfCards;
    char serialNumberDeck[10];
    int countCards;

public:
    Deck()
    { //serial number of cards
        this->seqOfCards = new Card[52];
        serialNumberDeck[0] = 'D';
        serialNumberDeck[1] = 'e';
        serialNumberDeck[2] = 'f';
        serialNumberDeck[3] = 'a';
        serialNumberDeck[4] = 'u';
        serialNumberDeck[5] = 'l';
        serialNumberDeck[6] = 't';
        this->countCards = 52;
        for (int i = 1; i <= 52; i++)
        {
            seqOfCards[i].mergedecknum(i);
        }
       
        int i = 0;
        for (int suits = 1; suits <= 4; ++suits)
        {
            for (int value = 1; value < 14; ++value)
            {
                this->seqOfCards[i++].createcard(suits, value);
            }
        }

        shuffle(52);
    };
    Deck(Deck &other)
    {
        this->countCards = other.countCards;
        this->seqOfCards = new Card[other.countCards];
        for (size_t i = 0; i < countCards; i++)
        {
            seqOfCards[i] = other.seqOfCards[i];
        }
        for (size_t i = 0; serialNumberDeck[i] != '\0'; i++)
        {
            serialNumberDeck[i] = other.serialNumberDeck[i];
        }
    };

    Deck(int k, char s[10])
    {
        this->seqOfCards = new Card[k];
        serialNumberDeck[0] = 'C';
        serialNumberDeck[1] = 'u';
        serialNumberDeck[2] = 's';
        serialNumberDeck[3] = 't';
        serialNumberDeck[4] = 'o';
        serialNumberDeck[5] = 'm';
        this->countCards = k;
        for (int i = 1; i <= k; i++)
        {
            seqOfCards[i].mergedecknum(i);
        }
        for (int a = 1, i = 0; i != k; (a == 4 ? a = 1 : a++)) //cards generating
        {
            for (int b = 1; b <= k / 4 && i != k; b++)
            {
                seqOfCards[i++].createcard(a, b);
            }
        }
        shuffle(k);
    }

    ~Deck()
    {
        delete[] seqOfCards;
    }

    void shuffle(int size)
    {
        srand(time(NULL));
        for (int i = 0; i < size; i++)
        {
            int r = i + (rand() % (52 - i));
            seqOfCards[i].swapi(seqOfCards[r]);
        }
    }

    int draw()
    {
        Card temp = this->seqOfCards[0];
        for (size_t i = 0; i < this->countCards - 1; i++)
        {
            this->seqOfCards[i] = this->seqOfCards[i + 1];
        }
        this->seqOfCards[countCards] = temp;
        return temp.addpoints();
    }

    void swap(size_t &a, size_t &b)
    {
        if (a <= this->countCards && b <= this->countCards)
        {
            Card temp = this->seqOfCards[a - 1]; // the first card from seqOfCards is on position 0, so every other card is one index back
            this->seqOfCards[a - 1] = this->seqOfCards[b - 1];
            this->seqOfCards[b - 1] = temp;
        }
    }

    int suit_count(size_t number)
    {
        int counter = 0;

        for (size_t i = 0; i < this->countCards; i++)
        {
            if (this->seqOfCards[i].getSuits() == number)
            {
                counter++;
            }
        }
        return counter;
    }

    int rank_count(int number)
    {
        int counter = 0;
        for (size_t i = 0; i < this->countCards; i++)
        {
            if (this->seqOfCards[i].getValue() == number)
            {
                counter++;
            }
        }
        return counter;
    }
};

class Player
{
private:
    char *name;
    size_t age;
    size_t wins;
    double coefWins;
    size_t currPoints;

public:
    Player()
    {
        this->name = new char[7];
        name[0] = 'P';
        name[1] = 'l';
        name[2] = 'a';
        name[3] = 'y';
        name[4] = 'e';
        name[5] = 'r';
        this->age = 18;
        this->wins = 0;
        this->coefWins = 0;
        this->currPoints = 0;
    }

    Player(bool gender) //1 - player 0 - dealer
    {
        name = new char[7];
        if (gender)
        {
            name[0] = 'P';
            name[1] = 'l';
            name[2] = 'a';
            name[3] = 'y';
            name[4] = 'e';
            name[5] = 'r';
        }
        else
        {
            name[0] = 'D';
            name[1] = 'e';
            name[2] = 'a';
            name[3] = 'l';
            name[4] = 'e';
            name[5] = 'r';
        }
        this->age = 18;
        this->wins = 0;
        this->coefWins = 0;
        this->currPoints = 0;
    }

    Player(Player &other)
    {
        this->name = new char[32];
        for (size_t i = 0; name[i]; i++)
        {
            this->name[i] = other.name[i];
        }
        this->age = other.age;
        this->wins = other.wins;
        this->coefWins = other.coefWins;
        this->currPoints = other.currPoints;
    }

    Player &operator=(Player &other)
    {
        if (this != &other)
        {
            delete[] this->name;
            this->name = new char[32];
            for (size_t i = 0; name[i]; i++)
            {
                this->name[i] = other.name[i];
            }
            this->age = other.age;
            this->wins = other.wins;
            this->coefWins = other.coefWins;
            this->currPoints = other.currPoints;
        }
        return *this;
    }

    ~Player()
    {
        delete[] this->name;
    }

    void draw(int pts)
    {
        currPoints += pts;
    }
    int getpoints()
    {
        return currPoints;
    }
    void setName(char *name_)
    {
        this->name = name_;
    }
};

int main()
{
    game();
    return 0;
}

void game()
{
    Deck cards;
    Player player(1);
    Player dealer(0);
    std::cout << "First and last name:" << std::endl;
    char *name_;
    std::cin>>name_;
    player.setName(name_);
    printf("\033[2J\033[H"); //clear screen and cursor topleft
    bool loser = 0;
    int firstCard = cards.draw();
    player.draw(firstCard);
    while (true)
    {
        char draw;
        if (player.getpoints() > 21)
        {
            loser = 1;
            std::cout << "You lost! :(" << std::endl;
            break;
        }
        std::cout << "Current result::" << player.getpoints() << std::endl;
        printf("Will you draw again(Y/N)? ");
        std::cin >> draw;
        if (draw == 'n' || draw == 'N')
            break;

        int blep = cards.draw();
        if (blep == 1) // asak
        {
            if (player.getpoints() + 11 > 21)
            {
                blep = 1;
            }
            else
                blep = 11;
        }
        player.draw(blep);
    }
    if (loser == 1)
    {
        std::cout << "Game over!" << std::endl;
    }
    else
    {
        while (true)
        {
            char draw;
            if (dealer.getpoints() > 17)
            {
                break;
            }

            int blep = cards.draw();
            if (blep == 1) // asak
            {
                if (dealer.getpoints() + 11 > 17)
                {
                    blep = 1;
                }
                else
                    blep = 11;
            }
            dealer.draw(blep);
        }
        std::cout<<"Player's points: "<<player.getpoints()<<std::endl<<"Dealer's points: "<<dealer.getpoints()<<std::endl;
        if (dealer.getpoints() > 21 || player.getpoints() >= dealer.getpoints())
        {
            std::cout << "You won!" << std::endl;
        }
        else
        {
            std::cout << "Dealer won!" << std::endl;
        }
    }
    return;
}
