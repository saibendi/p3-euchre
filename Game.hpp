//
//  Game.hpp
//  p3-euchre
//
//  Created by Bends on 5/11/24.
//

#ifndef Game_hpp
#define Game_hpp

#include <stdio.h>
#include <string>
#include "Card.hpp"
#include "Pack.hpp"
#include "Player.hpp"

using namespace std;

class Game {
public:
    Game();
    Game(string shuffle_user_input, int points_user_input, const string name_array[], const string type_array[], const int array_size);
    void play();
    
private:
    std::vector<Player*> players;
    string shuffle_option;
    int points_to_win;
    Pack pack;
    void shuffle();
    void deal(int hand_number, int &dealer_index, Card &upcard);
    void make_trump(Card &upcard, int &dealer_index, Suit &order_up_suit);
    void play_hand(/* ... */);
};


#endif /* Game_hpp */
