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

    /*
    if (round == 1) {
        
        order_up_suit = ;
        return true;
    }
    else if (round == 2) {
        
    }
    return false;
     */
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



