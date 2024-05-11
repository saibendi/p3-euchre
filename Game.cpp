//
//  Game.cpp
//  p3-euchre
//
//  Created by Bends on 5/11/24.
//

#include <iostream>
#include "Game.hpp"
#include "Player.hpp"
using namespace std;

Game::Game(const string shuffle_user_input, int points_user_input, const string name_array[], const string type_array[], const int array_size) {
    
    shuffle_option = shuffle_user_input;
    
    points_to_win = points_user_input;
    
    // setting name and type of each player to private member variable so you can use for other functions
    for (int i = 0; i < array_size; ++i) {
        players[i] = Player_factory(name_array[i], type_array[i]);
    }
}

void Game::shuffle() {
    pack.reset();
    if (shuffle_option) {
        pack.shuffle();
    }
}

void Game::deal(int hand_number, int &dealer_index, Card &upcard) {
    cout << "Hand " << hand_number << endl;
    cout << players[dealer_index] << " deals" << endl;
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

void Game::make_trump(Card &upcard, int &dealer_index, Suit &order_up_suit) {
    int trump_round = 1;
    bool is_dealer = false;

    while (trump_round < 3) {
        // iterate through all players
        for (int i = 0; i < players.size(); ++i) {
            // setting dealer_index value
            if (i == dealer_index) {
                is_dealer = true;
            }
            // if player doesn't make trump so we pass
            if (!players[i]->make_trump(upcard, is_dealer, trump_round, order_up_suit)) {
                cout << players[i] << " passes" << endl;;
            }
            // if players makes trump, then we order up and exit function
            else {
                cout << players[i] << " orders up " << order_up_suit;
                return;
            }
        }
        // increment trump round from 1 to 2
        ++trump_round;
    }
    
}
void Game::play() {
    int team_A_points = 0, team_B_points = 0;
    int dealer_index = 0;
    int hand_number = 0;
    Card upcard;
    Suit order_up_suit;
    while (team_A_points < points_to_win && team_B_points < points_to_win) {
        // shuffle();
        deal(hand_number, dealer_index, upcard);
        make_trump(upcard, dealer_index, order_up_suit);
        
        
        ++hand_number;
        dealer_index = (dealer_index + 1) % 4;
    }

    // define dealer_index OR who is dealer
}
