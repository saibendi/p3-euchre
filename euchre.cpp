//
//  euchre.cpp
//  p3-euchre
//
//  Created by Bends on 5/9/24.
//

#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <stdio.h>
#include "Card.hpp"
#include "Pack.hpp"
#include "Player.hpp"

using namespace std;

//static void Euchre_print_failure();

class Game {
public:
    Game(string name1, string name2, string name3, string name4, string type1, string type2, string type3, string type4, istream& pack_input, int points_user_input);
    void play();
    void delete_players();

private:
    std::vector<Player*> players;
    string shuffle_option;
    int points_to_win;
    Pack pack;
    Card upcard;
    
    void shuffle();
    void deal(int hand_number, int dealer_index);
    void make_trump(int dealer_index, Suit &order_up_suit, int &order_up_player_index);
    void play_hand(int dealer_index, Suit &order_up_suit, int order_up_player_index, int &team_A_points, int &team_B_points);
    int trick_winner(const vector<Card> trick_cards, Card led_card, Suit order_up_suit);

};

Game::Game(string name1, string name2, string name3, string name4, string type1, string type2, string type3, string type4, istream& pack_input, int points_user_input) : players({Player_factory(name1, type1), Player_factory(name2, type2),
    Player_factory(name3, type3), Player_factory(name4, type4)}),
    points_to_win(points_user_input), pack(pack_input) {
        /*
     TODO: For some reason initializing custom ctor withint the brackets doesn't work
    points_to_win = points_user_input;
    cout << "test 1" << endl;
    players[0] = Player_factory(name1, type1);
    cout << "test 2" << endl;
    players[1] = Player_factory(name2, type2);
    players[2] = Player_factory(name3, type3);
    players[3] = Player_factory(name4, type4);
    cout << "test 3" << endl;


    // setting name and type of each player to private member variable so you can use for other functions
    //for (int i = 0; i < 4; ++i) {
    //    players[i] = Player_factory(player_names[i], type_names[i]);
    //}
    //Pack pack(pack_input);
     */
}

/*
void Game::shuffle() {
    pack.reset();
    if (shuffle_option) {
        pack.shuffle();
    }
}
 */

void Game::deal(int hand_number, int dealer_index) {
    cout << "Hand " << hand_number << endl;
    cout << players[dealer_index]->get_name() << " deals" << endl;
    int deal_round = 1;
    
    // dealing cards to all players
    while (deal_round < 3) {
        if (deal_round == 1) {
            for (int j = 0; j < 3; ++j) {
                players[(dealer_index+1)%4]->add_card(pack.deal_one());
            }
            for (int j = 0; j < 2; ++j) {
                players[(dealer_index+2)%4]->add_card(pack.deal_one());
            }
            for (int j = 0; j < 3; ++j) {
                players[(dealer_index+3)%4]->add_card(pack.deal_one());
            }
            for (int j = 0; j < 2; ++j) {
                players[(dealer_index+4)%4]->add_card(pack.deal_one());
            }
        }
        else if (deal_round == 2) {
            for (int j = 0; j < 2; ++j) {
                players[(dealer_index+1)%4]->add_card(pack.deal_one());
            }
            for (int j = 0; j < 3; ++j) {
                players[(dealer_index+2)%4]->add_card(pack.deal_one());
            }
            for (int j = 0; j < 2; ++j) {
                players[(dealer_index+3)%4]->add_card(pack.deal_one());
            }
            for (int j = 0; j < 3; ++j) {
                players[(dealer_index+4)%4]->add_card(pack.deal_one());
            }
        }
        ++deal_round;
    }
    
    // output upcard
    upcard = pack.deal_one();
    cout << upcard << " turned up" << endl;
}

void Game::make_trump(int dealer_index, Suit &order_up_suit, int &order_up_player_index) {
    int trump_round = 1;
    bool is_dealer = false;
    int player_index;
    
    while (trump_round < 3) {
        // iterate through all players
        for (int i = 1 ; i < 5; ++i) {
            // setting dealer_index value
            player_index = (dealer_index + i) % 4;
            if (player_index == dealer_index) {
                is_dealer = true;
            }
            // if player doesn't make trump so we pass
            if (!players[player_index]->make_trump(upcard, is_dealer, trump_round, order_up_suit)) {
                cout << players[player_index]->get_name() << " passes" << endl;;
            }
            // if players makes trump, then we order up and exit function
            else {
                cout << players[player_index]->get_name() << " orders up " << order_up_suit << endl << endl;
                order_up_player_index = player_index;
                if (trump_round == 1) {
                    players[player_index]->add_and_discard(upcard);
                }
                return;
            }
        }
        // increment trump round from 1 to 2
        ++trump_round;
    }
}

int Game::trick_winner(const vector<Card> trick_cards, Card led_card, Suit order_up_suit) {
    // set max to first card in vector
    // first card in vector is also the led_card
    int winner_index = 0;
    Card max = trick_cards[winner_index];
    for (int i = 1; i < trick_cards.size(); ++i) {
        if (Card_less(max, trick_cards[i], led_card, order_up_suit)) {
            winner_index = i;
        }
    }
    return winner_index;
}

void Game::play_hand(int dealer_index, Suit &order_up_suit, int order_up_player_index, int &team_A_points, int &team_B_points) {
    int trick_round = 1;
    Card led_card;
    vector<Card> trick_cards(4);
    vector<int> player_points = {0,0,0,0};
    Card play_card;
    int winner_index;
    int led_index;
    int player_index;
    
    // start of trick rounds
    while (trick_round < 6) {
        if (trick_round == 1) {
            // left of the dealer leads card in first trick round
            led_index = (dealer_index+1)%4;
            led_card = players[led_index]->lead_card(order_up_suit);
            trick_cards[led_index] = led_card;
            cout << led_card << " led by " << players[led_index]->get_name() << endl;
            for (int i = 2; i < 5; ++i) {
                int player_index = (dealer_index+i)%4;
                play_card = players[player_index]->play_card(led_card, order_up_suit);
                trick_cards[player_index] = play_card;
                cout << play_card << " played by " << players[player_index]->get_name() << endl;
            }
        }
        else {
            // winner of trick leads card in every other trick round
            led_index = (winner_index)%4;
            led_card = players[led_index]->lead_card(order_up_suit);
            trick_cards[led_index] = led_card;
            cout << led_card << " led by " << players[led_index]->get_name() << endl;
            for (int i = 1; i < 4; ++i) {
                player_index = (winner_index+i)%4;
                play_card = players[player_index]->play_card(led_card, order_up_suit);
                trick_cards[player_index] = play_card;
                cout << play_card << " played by " << players[player_index]->get_name() << endl;
            }
        }
        winner_index = trick_winner(trick_cards, led_card, order_up_suit);
        ++player_points[winner_index];
        cout << players[winner_index]->get_name() << " takes the trick" << endl << endl;
        ++trick_round;
    }
    // end of trick rounds - trick rounds are finished
    
    // Points calculation and report out
    if ((player_points[0] + player_points[2]) > (player_points[1] + player_points[3])) {
        ++team_A_points;
        cout << players[0]->get_name() << " and " << players[2]->get_name() << " win the hand" << endl;
        if (order_up_player_index == 1 || order_up_player_index == 3) {
            ++team_A_points;
            cout << "euchred!" << endl;
        }
    }
    else if ((player_points[0] + player_points[2]) < (player_points[1] + player_points[3])) {
        ++team_B_points;
        cout << players[1]->get_name() << " and " << players[3]->get_name() << " win the hand" << endl;
        if (order_up_player_index == 0 || order_up_player_index == 2) {
            ++team_B_points;
            cout << "euchred!" << endl;
        }
    }

    // Team report out
    cout << players[0]->get_name() << " and " << players[2]->get_name() << " have " << team_A_points << " points" << endl;
    cout << players[1]->get_name() << " and " << players[3]->get_name() << " have " << team_B_points << " points" << endl << endl;
}

void Game::play() {
    int team_A_points = 0, team_B_points = 0;
    int dealer_index = 0;
    int hand_number = 0;
    int order_up_player_index;
    Suit order_up_suit;
    
    while (team_A_points < points_to_win && team_B_points < points_to_win) {
    // EACH HAND:
        // one dealer per hand
        // 1. shuffle();
        
        // 2. deal()
        deal(hand_number, dealer_index);
        
        // 3. make_trump()
        make_trump(dealer_index, order_up_suit, order_up_player_index);
        
        // 4. play()
        play_hand(dealer_index, order_up_suit, order_up_player_index, team_A_points, team_B_points);
        
        ++hand_number;
        dealer_index = (dealer_index + 1) % 4;
    }
    
    // if outside of the while loop, we assume that one of the team's points is greater than or equal to points to win
    if (team_A_points >= points_to_win) {
        cout << players[0]->get_name() << " and " << players[2]->get_name() << " win!" << endl;
    }
    else {
        cout << players[1]->get_name() << " and " << players[3]->get_name() << " win!" << endl;
    }
}

void Game::delete_players(){
    for (int i = 0; i < players.size(); ++i){
        delete players[i];
    }
}


int main(int argc, char *argv[]) {
    /*
    if (argc == 12) {
        if (strcmp("./euchre.exe", argv[0])) {
            Euchre_print_failure();
        }
        string filename = argv[1];
        fin.open(filename.c_str());
        if (!fin.is_open()) {
            // Assume pack_filename is a variable containing
            // the specified pack filename from argv
            cout << "Error opening " << filename << endl;
        }
        if (strcmp("shuffle", argv[2]) && strcmp("noshuffle", argv[2])) {
            Euchre_print_failure();
        }
        if ((atoi(argv[3]) > 100 || atoi(argv[3]) < 1)) {
            Euchre_print_failure();
        }
        for (int i = 5; i < 12; i = i+2) {
            if (strcmp(argv[i], "Human") && strcmp(argv[i], "Simple")) {
                Euchre_print_failure();
            }
        }
    }
    else {
        Euchre_print_failure();
    }
*/
    
    string pack_filename = argv[1];
    ifstream fin(pack_filename);
    if (! fin.is_open() ) {
        cout << "Error opening " << pack_filename << endl;
        return 1;
    }

    for (int i = 0; i != argc; ++i){
        cout << argv[i] << " ";
    }
    cout << endl;

    Game game(argv[4], argv[6], argv[8], argv[10], argv[5], argv[7], argv[9], argv[11], fin, atoi(argv[3]));
    game.play();
    
    fin.close();
    game.delete_players();
}
/*
static void Euchre_print_failure()
{
    cout << "Usage: euchre PACK_FILENAME [shuffle|noshuffle] POINTS_TO_WIN NAME1 TYPE1 NAME2 TYPE2 NAME3 TYPE3 NAME4 TYPE4" << endl;

    exit(EXIT_FAILURE);
}
*/
