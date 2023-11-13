#include <iostream>
#include <list>
#include <fstream>
#include <string>
#include <vector>
#include <random>
#include <memory>
#include <cstdlib>
#include <ctime>
#include <stdlib.h>

using namespace std;

class Card
{
public:
    string describtion;
    int effect;
    Card()
    {
        describtion = "No effect";
        effect = 0;
    }
    Card(string input)
    {
        effect = 0;
        for (int i = 0; i < input.size(); i++)
        {
            if (isdigit(input[i]))
            {
                effect = effect * 10 + (input[i] - '0');
            }
        }
        if ((input.find('+') != string::npos))
        {
            effect = effect;
        }
        else
        {
            effect = -effect;
        }
        describtion = input;
    }
    ~Card()
    {

    }
    friend istream& operator>>(istream& is, Card& card)
    {
        string str;
        is >> str;
        card = Card(str);
        return is;
    }
    friend ostream& operator<<(ostream& os, const Card& card)
    {
        os << card.describtion << endl;
        return os;
    }
};

class Deck
{
private:
    std::vector<Card> cards;

public:
    Deck()
    {
        std::vector<Card> n(0);
        this->cards = n;
    }
    void printlistit(char ch)
    {
        int index = ch;
        if (index >= 0 && index < cards.size())
        {
            cout << cards[index] << endl;
        }
        else
        {
            cout << "Invalid index" << endl;
        }
    }
    bool checkcard(int ch)
    {
        int index = ch;
        if (index >= 0 && index < cards.size())
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    void addCard(const Card& card)
    {
        cards.push_back(card);
    }
    Card getCard(int index) const
    {
        if (index >= 0 && index < cards.size())
        {
            return cards[index];
        }
        else
        {
            throw std::out_of_range("Invalid index");
        }
    }
    void cardeffects(int& health1, int& health2, int ch)
    {
        if (cards[ch].effect > 0)
        {
            health1 += cards[ch].effect;
        }
        else
        {
            health2 += cards[ch].effect;
        }
    }
    void printlist1()
    {
        int n = 0;
        for (auto i = cards.begin(); i != cards.end(); ++i)
        {
            cout << "( " << n << " ) " << *i << endl;
            n++;
        }
    }
    void removelist2(vector <string>& vector2, int ch)
    {
        cards.erase(cards.begin() + ch);
    }
    void filetovec(string path)
    {
        ifstream fin;
        fin.open(path);

        string str;

        while (!fin.eof())
        {
            str = "";
            getline(fin, str);
            cards.push_back(str);
        }
        fin.close();

        std::random_device rd;
        auto rng = std::default_random_engine{ rd() };

        // generate a random index and swap the elements in the vector
        for (int i = cards.size() - 1; i > 0; i--)
        {
            std::uniform_int_distribution<int> dist(0, i);
            int j = dist(rng);
            std::swap(cards[i], cards[j]);
        }
    }
    int size()
    {
        return cards.size();
    }
    ~Deck()
    {

    }
};

class Game
{
private:
    Deck myVector;
    Deck myList;
    vector <string> myListrem;
    int round;
    char menu_;
    int hppl = 20;
    int hpcomp = 20;
    int ran;
    string strq;
    int ch1 = 1;
    bool QUIT = 0;
public:
    Game()
    {

    }
    void game_process()
    {
        while (true)
        {

            //1. Add 3 elements in vector(hand)
            for (auto i = 0; i <= 2; ++i)
            {
                myList.addCard(myVector.getCard(i));
            }



            //2. Print hand
            //setLocale();
            //locale::global(locale("en_US.UTF-8"));
            cout << "####################################################################################" << endl;
            cout << "HP (Tom) = " << hpcomp << "\t\t\t\t\t\t\t\t\t\t\t\t\t" << "YOUR HP (Jerry) = " << hppl << endl;
            cout << "\n"
                "╱▔▔╲┈┈╱╱╱┈╱▔▔▏┈┈ \t\t\t\t\t\t\t\t\t\t\t\t┈┈┈▕▔╲┈┈┈┈╱▔▔╲┈┈ \n\n"
                "▔▏▔╲╲╱┈┈▔▔▔╲╱┈┈┈ \t\t\t\t\t\t\t\t\t\t\t\t┈┈╱▔▔▔▔▔╲╱╱▔▔╲▏┈ \n\n"
                "┈▏┈╰╲┈┈╱▔┈┈▔╲┈TOM\t\t\t\t\t\t\t\t\t\t\t\t ▕╭╮┈╭╮┈┈▕▂┈┈▕┈┈ \n\n"
                "┈▏┈╭▔┈┈╱╲┈┈╱╮▏┈& \t\t\t\t\t\t\t\t\t\t\t\t┈▕┃▋┈┃▋┈┈┈╱┈┈╱┈┈ \n\n"
                "┈╲┈╱┈┈┈▏▕┈┈▏┃▏┈┈ \t\t\t\t\t\t\t\t\t\t\t\t┈▕┃┊┈┃┊╭┈▕┈┈╱┈┈┈ \n\n"
                "┈╱▔┈┈┈╮▋▕┈┈▋┃▔╲┈ \t\t\t\t\t\t\t\t\t\t\t\t▕▔▔▆▔▔▔▏┈▕▔▔┈JERRY\n\n"
                "▕╱╱╱┈╯╲▔▔▕▆▔▔▏╲▏ \t\t\t\t\t\t\t\t\t\t\t\t┈╲╰━━━╯╲┈╱┈┈┈┈┈┈ \n\n"
                "┈▔▔▔╲┈┈╲▂▂▂╱╱▔▔┈ \t\t\t\t\t\t\t\t\t\t\t\t┈┈▔▔▔▏▕▔▔┈┈┈┈┈┈┈\n\n";
            /*/std::cout << "\u2571\u2534\u2523\u2518\u2514\u250C\u2570\u2500\u2502\u251C\u253C\u252C\u2524" << std::endl;
            std::cout << "\u2572\u2577\u2537\u252B\u2510\u2502\u2514\u2573\u2500\u2520\u2534\u251C\u2502" << std::endl;
            std::cout << "\u251C\u2534\u2500\u2571\u2574\u2502\u2518\u2500\u2514\u2534\u2518\u2524\u253C" << std::endl;
            std::cout << "\u251C\u2500\u2502\u2572\u2571\u2500\u250C\u2510\u2571\u2500\u252C\u253C\u2514" << std::endl;
            std::cout << "\u2502\u250C\u2518\u2510\u252C\u2572\u2500\u2534\u2502\u2573\u2572\u2500\u250C" << std::endl;
            std::cout << "\u2514\u2502\u2500\u252C\u2524\u2574\u251C\u2500\u2534\u2500\u2571\u2500\u2500" << std::endl;
            std::cout << "\u2524\u2534\u251C\u2570\u2500\u2534\u2534\u2500\u2518\u252C\u2573\u2534\u2500" << std::endl;*/



            cout << "####################################################################################" << endl;
            cout << "Your hand : \n";
            myList.printlist1();
            cout << "####################################" << endl;
            cout << endl;


            //3. Use card



            while (true)
            {
                cout << "Now is your turn! Use card! :" << endl;
                cin >> ch1;
                if (myList.checkcard(ch1) == true)
                {
                    break;
                }
                cout << "\n!!Try another card!!\n\n";
            }



            //4.Print used card

            cout << "\nThis card were used: \n";
            cout << "====================================" << endl;
            myList.printlistit(ch1);
            cout << "====================================" << endl;



            //5.Card effect
            myList.cardeffects(hppl, hpcomp, ch1);

            //6.Deleting the selected card
            myList.removelist2(myListrem, ch1);

            cout << "\nSelected card was discarded...\n";
            cout << "------------------------------------\n";



            //7.Detect a size of vector, choose a random card to discard
            ran = rand() % myList.size();

            if (myList.size() > 1)
            {
                cout << "Random card was removed -----> " << ran << endl << endl;
                myList.removelist2(myListrem, ran);
            }
            else
            {
                cout << "No cards to remove\n";
            }


            //Enemy used card
            ran = rand() % myVector.size();
            if (myVector.size() > 1)
            {
                cout << "Enemy's turn! This card were used: \n====================================\n"
                    << myVector.getCard(ran);
                cout << "\n====================================" << endl;
                myVector.cardeffects(hpcomp, hppl, ran);
                cout << endl;

                //3.Delete card from vector
                myVector.removelist2(myListrem, ran);
            }
            else
            {
                cout << "Enemy's turn! No cards to beat\n";
            }
            if (hppl <= 0 || hpcomp <= 0)
            {
                if (hpcomp <= 0) cout << "CONGRATULATIONS!! YOU ARE THE WINNER!!" << endl;
                else cout << "YOU LOST ;(  TRY AGAIN" << endl;
                launch();
            }

            if (myVector.size() <= 3)
            {
                cout << "Deck is out of cards...Сards are shuffled...\n";
                myVector.filetovec("game.txt");
            }

            round++;

            //menu to stop or quit game
            cout << "---------------------------------------------------\n"
                "|        Type 'P' to pause the game (then enter)  |\n"
                "|        Type 'Q' to quit the game                |\n"
                "|        Type any other key to continue           |\n"
                "---------------------------------------------------\n";
            cin >> menu_;
            system("cls");
            if (menu_ == 'q')
            {
                QUIT = 1;
                return;
            }
            else if (menu_ == 'p')
            {
                fflush(stdin);
                std::cin.get();
            }

            //max 5 cards implementing
            if (myList.size() > 5)
            {
                ran = rand() % myList.size();
                myList.removelist2(myListrem, ran);
                cout << "Random card was removed(max 5 card in hand)-----> " << ran << endl << endl;
            }
        }
    }
    void menu()
    {
        if (QUIT) return;
        cout << " --------------------------\n|        Card Game        |\n--------------------------";
        cout << "\n1. Start Game\n2. Quit\n";
        cin >> menu_;
        system("cls");
        if (menu_ == '2')
        {
            QUIT = 1;
            return;
        }

        else if (menu_ == '1') game_process();
        else cout << "Command does not exist\n";
        if (QUIT) return;
        menu();
    }
    void launch()
    {
        myVector = Deck();
        myList = Deck();
        myListrem.clear();
        round = 1;
        hppl = 20;
        hpcomp = 20;
        ch1 = 1;
        myVector.filetovec("game.txt");
        srand(time(NULL));
        if (QUIT) return;
        menu();




    }
    ~Game()
    {

    }
};

int main()
{
    Game a;
    a.launch();
}
