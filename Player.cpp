#include "Player.hpp"
#include "Card.hpp"
#include <string>
#include <vector>

using namespace std;

class SimplePlayer : public Player {
public:
    // defualt ctor
    SimplePlayer() {}
    
    // custom ctor
    SimplePlayer(string name_in) {
        playerName = name_in;
    }
    
    //EFFECTS returns player's name
    virtual const std::string & get_name() const {
        return playerName;
    }
    
    //REQUIRES player has less than MAX_HAND_SIZE cards
    //EFFECTS  adds Card c to Player's hand
    virtual void add_card(const Card &c) {
        if (playerHand.size() < MAX_HAND_SIZE) {
            playerHand.push_back(c);
        }
    }
    
    /*    Round 1 of Making Trump
     - two face cards with the same suit as upcard
     - left bower counts as a face card
  
     Round 2 of Making Trump
     - one face card of "next suit" (other suit of same color as the upcard)
     - left bower counts as a face card
*/
    //REQUIRES round is 1 or 2
    //MODIFIES order_up_suit
    //EFFECTS If Player wishes to order up a trump suit then return true and
    //  change order_up_suit to desired suit.  If Player wishes to pass, then do
    //  not modify order_up_suit and return false.
    virtual bool make_trump(const Card &upcard, bool is_dealer,
                            int round, Suit &order_up_suit) const {
        Suit upcard_suit = upcard.get_suit();
        Suit next_suit = Suit_next(upcard_suit);

        if (round == 1) {
            int counter = 0;
            // if you have two face cards of same suit as upcard, you make trump
            for (int i = 0; i <playerHand.size(); ++i) {
                if (playerHand[i].is_face_or_ace()) {
                    if (playerHand[i].get_suit() == upcard_suit) {
                        ++counter;
                    }
                    else if (playerHand[i].is_left_bower(upcard_suit)) {
                        ++counter;
                    }
                }
            }
            if (counter > 1) {
                order_up_suit = upcard_suit;
                return true;
            }
        }
        else if (round == 2) {
            int counter = 0;
            for (int i = 0; i <playerHand.size(); ++i) {
                if (playerHand[i].get_suit() == next_suit) {
                    if (playerHand[i].is_face_or_ace()) {
                        ++counter;
                    }
                }
            }
            if (counter > 0) {
                order_up_suit = next_suit;
                return true;
            }
        }
        return false;
    }
 
    //REQUIRES Player has at least one card
    //EFFECTS  Player adds one card to hand and removes one card from hand.
    virtual void add_and_discard(const Card &upcard) {
       int index_min = 0;
        Card min = playerHand[0];
        playerHand.push_back(upcard);
        for(int i = 1; i < playerHand.size(); i++){
            if (playerHand[i] < min) {
                min = playerHand[i];
                index_min = i;
            }
        }
        playerHand.erase(playerHand.begin() + index_min);
    }
    
    //Spades is trump
    // 10 spades, J of hearts, 9 of spades, Ace of Spades, Ace of Clubs
    //REQUIRES Player has at least one card
    //EFFECTS  Leads one Card from Player's hand according to their strategy
    //  "Lead" means to play the first Card in a trick.  The card
    //  is removed the player's hand.
    virtual Card lead_card(Suit trump) {
        if (playerHand.size() >= 1) {
            // can iterate through player Hand and assign values to individual trump and non trump arrays
            // then we need to make sure those arrays' persist over each function call
            // so we would need to rearrange playerHand

            // OR can iterate through and compare each time
            // this implementation is to iterate using the loop for each function call
    
            Card maxTrump;
            Card maxNonTrump;
            int trumpCount = 0;
            int nonTrumpCount = 0;
            int trumpIndex = 0;
            int nonTrumpIndex = 0;
            // iterate through all cards in player's hand
            for (int i = 0; i < playerHand.size(); ++i) {
                // if card is trump
                if (playerHand[i].is_trump(trump)) {
                    // If trump count is 0 so far
                    if (trumpCount == 0) {
                        maxTrump = playerHand[i];    // sets new max
                        trumpIndex = i;
                    }
                    // If trump count is higher than 0 so far
                    else {
                        if (playerHand[i] > maxTrump) {
                            maxTrump = playerHand[i];
                            trumpIndex = i;
                        }
                    }
                    ++trumpCount;
                }
                // if non-trump card
                else {
                    if (nonTrumpCount == 0) {
                        maxNonTrump = playerHand[i];
                        nonTrumpIndex = i;
                    }
                    else {
                        if (playerHand[i] > maxNonTrump) {
                            maxNonTrump = playerHand[i];
                            nonTrumpIndex = i;
                        }
                    }
                    ++nonTrumpCount;        // counting to see if there actually is
                }
            }
            if (nonTrumpCount > 0) {
                playerHand.erase(playerHand.begin() + trumpIndex);
                return maxNonTrump;
            }
            else {
                playerHand.erase(playerHand.begin() + nonTrumpIndex);
                return maxTrump;
            }
        }
        else {
            cout << "Player doesn't have at least one card!" << endl;
            return {};
        }
    }
    
    //REQUIRES Player has at least one card
    //EFFECTS  Plays one Card from Player's hand according to their strategy.
    //  The card is removed from the player's hand.
    virtual Card play_card(const Card &led_card, Suit trump) {
        /* TODO: remove later; using to debug
        for (int i = 0; i < playerHand.size(); ++i) {
            cout << playerName << "'s Card " << i+1 << " is: " << playerHand[i] << endl;
        }
         */

        // Follow Simple Player leads with HIGHEST LED suit card, if no led suit cards, LOWEST CARD"
        if (playerHand.size() >= 1) {
            Card maxLed;
            Card minNonLed;
            int LedCount = 0;
            int nonLedCount = 0;
            int maxLed_index = 0;
            int minNonLed_index = 0;

            // iterate through all cards in player's hand
            for (int i = 0; i < playerHand.size(); ++i) {
                // if led suit card
                    // then highest card
                    if (playerHand[i].get_suit() == led_card.get_suit()) {
                        if (LedCount == 0) {
                            maxLed = playerHand[i];    // sets new max
                            maxLed_index = i;
                        }
                        else {
                            if (playerHand[i] > maxLed) {
                                maxLed = playerHand[i];
                                maxLed_index = i;
                            }
                        }
                        ++LedCount;
                    }
                // if no led suit card
                        // then lowest card
                    else {
                        if (nonLedCount == 0) {
                            minNonLed = playerHand[i];
                            minNonLed_index = i;
                        }
                        else {
                            if (playerHand[i] < minNonLed) {
                                minNonLed = playerHand[i];
                                minNonLed_index = i;
                            }
                        }
                        ++nonLedCount;
                    }
                }
            if (LedCount > 0) {
                playerHand.erase(playerHand.begin() + maxLed_index);
                return maxLed;
            }
            else {
                playerHand.erase(playerHand.begin() + minNonLed_index);
                return minNonLed;
            }
            }
        else {
            cout << "Player doesn't have at least one card!" << endl;
            return {};
        }
    }

    static const int MAX_HAND_SIZE = 5;
    
private:
    string playerName;
    vector<Card> playerHand;
};


class HumanPlayer : public Player {
public:
    // defualt ctor
    HumanPlayer() {}
    
    // custom ctor
    HumanPlayer(string name_in) {
        playerName = name_in;
    }
    
    //EFFECTS returns player's name
    virtual const std::string & get_name() const {
        return playerName;
    }
    
    //REQUIRES player has less than MAX_HAND_SIZE cards
    //EFFECTS  adds Card c to Player's hand
    virtual void add_card(const Card &c) {
        if (playerHand.size() < MAX_HAND_SIZE) {
            playerHand.push_back(c);
        }
    }
    
    //REQUIRES round is 1 or 2
    //MODIFIES order_up_suit
    //EFFECTS If Player wishes to order up a trump suit then return true and
    //  change order_up_suit to desired suit.  If Player wishes to pass, then do
    //  not modify order_up_suit and return false.
    virtual bool make_trump(const Card &upcard, bool is_dealer,
                            int round, Suit &order_up_suit) const {
        
        //TODO: use is_dealer variable
        
        Suit upcard_suit = upcard.get_suit();
        Suit next_suit = Suit_next(upcard_suit);

        if (round == 1) {
            int counter = 0;
            // if you have two face cards of same suit as upcard, you make trump
            for (int i = 0; i <playerHand.size(); ++i) {
                if (playerHand[i].is_face_or_ace()) {
                    if (playerHand[i].get_suit() == upcard_suit) {
                        ++counter;
                    }
                    else if (playerHand[i].is_left_bower(upcard_suit)) {
                        ++counter;
                    }
                }
            }
            if (counter > 1) {
                order_up_suit = upcard_suit;
                return true;
            }
        }
        else if (round == 2) {
            int counter = 0;
            for (int i = 0; i <playerHand.size(); ++i) {
                if (playerHand[i].get_suit() == next_suit) {
                    if (playerHand[i].is_face_or_ace()) {
                        ++counter;
                    }
                }
            }
            if (counter > 0) {
                order_up_suit = next_suit;
                return true;
            }
        }
        return false;
    }
    
    //REQUIRES Player has at least one card
    //EFFECTS  Player adds one card to hand and removes one card from hand.
    virtual void add_and_discard(const Card &upcard) {
       int index_min = 0;
        Card min = playerHand[0];
        playerHand.push_back(upcard);
        for(int i = 1; i < playerHand.size(); i++){
            if (playerHand[i] < min) {
                min = playerHand[i];
                index_min = i;
            }
        }
        playerHand.erase(playerHand.begin() + index_min);
    }

    //REQUIRES Player has at least one card
    //EFFECTS  Leads one Card from Player's hand according to their strategy
    //  "Lead" means to play the first Card in a trick.  The card
    //  is removed the player's hand.
    virtual Card lead_card(Suit trump) {
        if (playerHand.size() >= 1) {
            // can iterate through player Hand and assign values to individual trump and non trump arrays
            // then we need to make sure those arrays' persist over each function call
            // so we would need to rearrange playerHand

            // OR can iterate through and compare each time
    
            Card maxTrump;
            Card maxNonTrump;
            int trumpCount = 0;
            int nonTrumpCount = 0;
            // iterate through all cards in player's hand
            for (int i = 0; i < playerHand.size(); ++i) {
                // if card is trump
                if (playerHand[i].is_trump(trump)) {
                    if (trumpCount == 0) {
                        maxTrump = playerHand[i];    // sets new max
                    }
                    else {
                        if (playerHand[i] > maxTrump) {
                            maxTrump = playerHand[i];
                        }
                    }
                    ++trumpCount;
                }
                // if non-trump card
                else {
                    if (nonTrumpCount == 0) {
                        maxNonTrump = playerHand[i];
                    }
                    if (nonTrumpCount > 0) {
                        if (playerHand[i] > maxNonTrump) {
                            maxNonTrump = playerHand[i];
                        }
                    }
                    ++nonTrumpCount;        // counting to see if there actually is
                }
            }
            if (nonTrumpCount > 0) {
                return maxNonTrump;
            }
            else {
                return maxTrump;
            }
        }
        else {
            cout << "Player doesn't have at least one card!" << endl;
            return {};
        }
        return {};
    }

    //REQUIRES Player has at least one card
    //EFFECTS  Plays one Card from Player's hand according to their strategy.
    //  The card is removed from the player's hand.
    virtual Card play_card(const Card &led_card, Suit trump) {
        
        // Follow Simple Player leads with HIGHEST LED suit card, if no led suit cards, LOWEST CARD"
        if (playerHand.size() >= 1) {
            Card maxLed;
            Card minNonLed;
            int LedCount = 0;
            int nonLedCount = 0;
            // iterate through all cards in player's hand
            for (int i = 0; i < playerHand.size(); ++i) {
                // if led suit card
                    // then highest card
                    if (playerHand[i].get_suit() == led_card.get_suit()) {
                        if (LedCount == 0) {
                            maxLed = playerHand[i];    // sets new max
                        }
                        else {
                            if (playerHand[i] > maxLed) {
                                maxLed = playerHand[i];
                            }
                        }
                        ++LedCount;
                    }
                // if no led suit card
                        // then lowest card
                    else {
                        if (nonLedCount == 0) {
                            minNonLed = playerHand[i];
                        }
                        else {
                            if (playerHand[i] < minNonLed) {
                                minNonLed = playerHand[i];
                            }
                        }
                        ++nonLedCount;
                    }
                }
            if (LedCount > 0) {
                return maxLed;
            }
            else {
                return minNonLed;
            }
            }
        else {
            cout << "Player doesn't have at least one card!" << endl;
            return {};
        }
    }
    
    static const int MAX_HAND_SIZE = 5;

private:
    string playerName;
    vector<Card> playerHand;
};


//EFFECTS: Returns a pointer to a player with the given name and strategy
//To create an object that won't go out of scope when the function returns,
//use "return new Simple(name)" or "return new Human(name)"
//Don't forget to call "delete" on each Player* after the game is over
Player * Player_factory(const std::string &name, const std::string &strategy) {
    // player is the object defined in Player.hpp with the pure virtual functions
    string Human = "Human";
    string Simple = "Simple";
    
    // We need to check the value of strategy and return
    // the corresponding player type.
    if (strategy == Simple) {
        // The "new" keyword dynamically allocates an object.
        return new SimplePlayer(name);
    }
    else if (strategy == Human) {
        return new HumanPlayer(name);
    }
    // Invalid strategy if we get here
    assert(false);
    return nullptr;
}

// TODO: Look into this function further
//EFFECTS: Prints player's name to os
std::ostream & operator<<(std::ostream &os, const Player &p) {
    os << p.get_name();
    return os;
}




/*
 MAKING TRUMP------------------
 
    Round 1 of Making Trump
    - two face cards with the same suit as upcard
    - left bower counts as a face card
 
    Round 2 of Making Trump
    - one face card of "next suit" (other suit of same color as the upcard)
    - left bower counts as a face card
 
 TRICK TAKING-------------------
 
 - Leader of first trick is to the left of dealer or "eldest hand"
 - LEAD REGULAR player can lead with any card
 - LEAD SIMPLE Player leads with HIGHEST NON-TRUMP card, if all trump card, then HIGHEST TRUMP card"
 

 - Follow SImple Player leads with HIGHEST LED suit card, if no led suit cards, LOWEST CARD"
 - player with highest card wins trick
 
 
 - player who won trick, is leader of next trick and leads next trick
 -
 */
