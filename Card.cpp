#include <cassert>
#include <iostream>
#include <array>
#include "Card.hpp"

using namespace std;

/////////////// Rank operator implementations - DO NOT CHANGE ///////////////

constexpr const char *const RANK_NAMES[] = {
  "Two",   // TWO
  "Three", // THREE
  "Four",  // FOUR
  "Five",  // FIVE
  "Six",   // SIX
  "Seven", // SEVEN
  "Eight", // EIGHT
  "Nine",  // NINE
  "Ten",   // TEN
  "Jack",  // JACK
  "Queen", // QUEEN
  "King",  // KING
  "Ace"    // ACE
};

//REQUIRES str represents a valid rank ("Two", "Three", ..., "Ace")
//EFFECTS returns the Rank correspoinding to str, for example "Two" -> TWO
Rank string_to_rank(const std::string &str) {
  for(int r = TWO; r <= ACE; ++r) {
    if (str == RANK_NAMES[r]) {
      return static_cast<Rank>(r);
    }
  }
  assert(false); // Input string didn't match any rank
  return {};
}

//EFFECTS Prints Rank to stream, for example "Two"
std::ostream & operator<<(std::ostream &os, Rank rank) {
  os << RANK_NAMES[rank];
  return os;
}

//REQUIRES If any input is read, it must be a valid rank
//EFFECTS Reads a Rank from a stream, for example "Two" -> TWO
std::istream & operator>>(std::istream &is, Rank &rank) {
  string str;
  if(is >> str) {
    rank = string_to_rank(str);
  }
  return is;
}



/////////////// Suit operator implementations - DO NOT CHANGE ///////////////

constexpr const char *const SUIT_NAMES[] = {
  "Spades",   // SPADES
  "Hearts",   // HEARTS
  "Clubs",    // CLUBS
  "Diamonds", // DIAMONDS
};

//REQUIRES str represents a valid suit ("Spades", "Hearts", "Clubs", or "Diamonds")
//EFFECTS returns the Suit correspoinding to str, for example "Clubs" -> CLUBS
Suit string_to_suit(const std::string &str) {
  for(int s = SPADES; s <= DIAMONDS; ++s) {
    if (str == SUIT_NAMES[s]) {
      return static_cast<Suit>(s);
    }
  }
  assert(false); // Input string didn't match any suit
  return {};
}

//EFFECTS Prints Suit to stream, for example "Spades"
std::ostream & operator<<(std::ostream &os, Suit suit) {
  os << SUIT_NAMES[suit];
  return os;
}

//REQUIRES If any input is read, it must be a valid suit
//EFFECTS Reads a Suit from a stream, for example "Spades" -> SPADES
std::istream & operator>>(std::istream &is, Suit &suit) {
  string str;
  if (is >> str) {
    suit = string_to_suit(str);
  }
  return is;
}


/////////////// Write your implementation for Card below ///////////////


// NOTE: We HIGHLY recommend you check out the operator overloading
// tutorial in the project spec before implementing
// the following operator overload functions:
//   operator<<
//   operator>>
//   operator<
//   operator<=
//   operator>
//   operator>=
//   operator==
//   operator!=

//EFFECTS Initializes Card to the Two of Spades
// TEST CASES:  - TEST 1:
//              - TEST 2:
//              - TEST 3:
Card::Card(){
    rank = TWO;
    suit = SPADES;
}

//EFFECTS Initializes Card to specified rank and suit
// TEST CASES:  - TEST 1:
//              - TEST 2:
//              - TEST 3:
Card::Card(Rank rank_in, Suit suit_in) {
    rank = rank_in;
    suit = suit_in;
}

//EFFECTS Returns the rank
// TEST CASES:  - TEST 1:
//              - TEST 2:
//              - TEST 3:
Rank Card::get_rank() const {
    return rank;
}

//EFFECTS Returns the suit.  Does not consider trump.
// TEST CASES:  - TEST 1:
//              - TEST 2:
//              - TEST 3:
Suit Card::get_suit() const {
    return suit;
}

//EFFECTS Returns the suit
//HINT: the left bower is the trump suit!
// TEST CASES:  - TEST 1:
//              - TEST 2:
//              - TEST 3:
Suit Card::get_suit(Suit trump) const {
    if (trump == CLUBS) {
        return SPADES;
    }
    else if (trump == SPADES) {
        return CLUBS;
    }
    else if (trump == DIAMONDS) {
        return HEARTS;
    }
    else {
        return DIAMONDS;
    }
}

//EFFECTS Returns true if card is a face card (Jack, Queen, King or Ace)
// TEST CASES:  - TEST 1:
//              - TEST 2:
//              - TEST 3:
bool Card::is_face_or_ace() const {
    // suit doesn't matter at all
    // if rank = jack, queen, king or ace
    if (rank >= JACK && rank <= ACE)
        return true;
    return false;
}

//EFFECTS Returns true if card is the Jack of the trump suit
// TEST CASES:  - TEST 1:
//              - TEST 2:
//              - TEST 3:
bool Card::is_right_bower(Suit trump) const {
    if (suit == trump && rank == JACK)
        return true;
    return false;
}

//EFFECTS Returns true if card is the Jack of the next suit
// TEST CASES:  - TEST 1:
//              - TEST 2:
//              - TEST 3:
bool Card::is_left_bower(Suit trump) const {
    if ((trump == HEARTS && suit == DIAMONDS) || (trump == DIAMONDS && suit == HEARTS)) {
        if (rank == JACK) {
            return true;
        }
    }
    else if ((trump == SPADES && suit == CLUBS) || (trump == CLUBS && suit == SPADES)) {
        if (rank == JACK) {
            return true;
        }
    }
    return false;
}

//EFFECTS Returns true if the card is a trump card.  All cards of the trump
// suit are trump cards.  The left bower is also a trump card.
//TEST CASES: - should test left bower
//            - should jack from a cross suit
bool Card::is_trump(Suit trump) const {
    if (suit == trump || is_left_bower(trump)) {
        return true;
    }
    return false;
}

//EFFECTS Prints Card to stream, for example "Two of Spades"
std::ostream & operator<<(std::ostream &os, const Card &card) {
    os << RANK_NAMES[card.get_rank()] << " of " << SUIT_NAMES[card.get_suit()];
    return os;
}

//EFFECTS Reads a Card from a stream in the format "Two of Spades"
//NOTE The Card class declares this operator>> "friend" function,
//     which means it is allowed to access card.rank and card.suit.
std::istream & operator>>(std::istream &is, Card &card) {
    string rankStr;
    string ofStr;
    string suitStr;
    if (is >> rankStr >> ofStr >> suitStr) {
        card.rank = string_to_rank(rankStr);
        card.suit = string_to_suit(suitStr);
    }
    return is;
}

//EFFECTS Returns true if lhs is lower value than rhs.
//  Does not consider trump.
// TEST CASES:  - TEST 1: lhs = ace, clubs < rhs = ace, clubs   OUT: false
//              - TEST 2: lhs = ace, clubs < rhs = ace, hearts   OUT: false
//              - TEST 3: lhs = two, clubs < rhs = ace, clubs   OUT: true
bool operator<(const Card &lhs, const Card &rhs) {
    if (lhs.get_rank() < rhs.get_rank()) {
        return true;
    }
    else if (lhs.get_rank() == rhs.get_rank()) {
        if (lhs.get_suit() < rhs.get_suit()) {
            return true;
        }
        else {
            return false;
        }
    }
    // the else condition is if lhs.get_suit() >= rhs.get_suit(), in which case you return false
    return false;
}

//EFFECTS Returns true if lhs is lower value than rhs or the same card as rhs.
//  Does not consider trump.
// TEST CASES:  - TEST 1: lhs = ace, clubs <= rhs = ace, clubs   OUT: true
//              - TEST 2: lhs = ace, clubs <= rhs = ace, hearts   OUT: false
//              - TEST 3: lhs = two, clubs <= rhs = ace, clubs   OUT: true
bool operator<=(const Card &lhs, const Card &rhs) {
    if (lhs.get_rank() < rhs.get_rank()) {
        return true;
    }
    else if (lhs.get_rank() == rhs.get_rank()) {
        if (lhs.get_suit() <= rhs.get_suit()) {
            return true;
        }
        else {
            return false;
        }
    }
    // the else condition is if lhs.get_suit() >= rhs.get_suit(), in which case you return false
    return false;
}

//EFFECTS Returns true if lhs is higher value than rhs.
//  Does not consider trump.
// TEST CASES:  - TEST 1: lhs = two, diamonds > rhs = ace, clubs    OUT: true
//              - TEST 2: lhs = ace, diamonds > rhs = two, diamonds    OUT: true
//              - TEST 3: lhs = ace, diamonds > rhs = ace, diamonds     OUT: false
bool operator>(const Card &lhs, const Card &rhs) {
    // Solution 1: Using implementation for '<' and '<='
    if (!(lhs <= rhs))
        return true;
    return false;
    
    /* Solution 2: implementation from scratch
    if (lhs.get_suit() > rhs.get_suit()) {
        return true;
    }
    else if (lhs.get_suit() == rhs.get_suit()) {
        if (lhs.get_rank() > rhs.get_rank()) {
            return true;
        }
        else {
            return false;
        }
    }
    // the else condition is if lhs.get_suit() <= rhs.get_suit(), in which case you return false
    return false;
     */
}

//EFFECTS Returns true if lhs is higher value than rhs or the same card as rhs.
//  Does not consider trump.
// TEST CASES:  - TEST 1: lhs = two, diamonds >= rhs = ace, clubs    OUT: true
//              - TEST 2: lhs = ace, diamonds >= rhs = two, diamonds    OUT: true
//              - TEST 3: lhs = ace, diamonds >= rhs = ace, diamonds     OUT: true
bool operator>=(const Card &lhs, const Card &rhs) {
    // Solution 1: Using implementation for '<' and '<='
    if (!(lhs < rhs))
        return true;
    return false;
    
    /* Solution 2: implementation from scratch
    if (lhs.get_suit() > rhs.get_suit()) {
        return true;
    }
    else if (lhs.get_suit() == rhs.get_suit()) {
        if (lhs.get_rank() >= rhs.get_rank()) {
            return true;
        }
        else {
            return false;
        }
    }
    // the else condition is if lhs.get_suit() < rhs.get_suit(), in which case you return false
    return false;
     */
}

//EFFECTS Returns true if lhs is same card as rhs.
//  Does not consider trump.
// TEST CASES: done
bool operator==(const Card &lhs, const Card &rhs) {
    if (lhs.get_suit() == rhs.get_suit() && lhs.get_rank() == rhs.get_rank()) {
        return true;
    }
    return false;
}

//EFFECTS Returns true if lhs is not the same card as rhs.
//  Does not consider trump.
// TEST CASES: done
bool operator!=(const Card &lhs, const Card &rhs) {
    if (!(lhs == rhs))
        return true;
    return false;
}

//EFFECTS returns the next suit, which is the suit of the same color
// TEST CASES:  - TEST 1: if suit = Diamonds    OUT: hearts
//              - TEST 2: if suit = Hearts      OUT: diamonds
//              - TEST 3: if suit = spades      OUT: clubs
Suit Suit_next(Suit suit) {
    if (suit == DIAMONDS) {
        return HEARTS;
    }
    else if (suit == HEARTS) {
        return DIAMONDS;
    }
    else if (suit == CLUBS) {
        return SPADES;
    }
    else {
        return CLUBS;
    }
}

//EFFECTS Returns true if a is lower value than b.  Uses trump to determine
// order, as described in the spec.
// TEST CASES:  - TEST 1: trump = clubs AND a = Jack, Spades < b = Ace, clubs   OUT = false;
//              - TEST 2: trump = clubs AND a = Ace, clubs < a = Jack, Spades      OUT = true;
//              - TEST 3: trump = clubs AND a = 5, hearts < b = 2, diamonds         OUT = true;
bool Card_less(const Card &a, const Card &b, Suit trump) {
    //assert(a != b);
    // Make sure that a and b aren't the same cards
    if (a != b) {
        // Card a is trump, Card b is trump
        // ex: let's say trump = clubs
        // right bower suit = clubs
        // left_bower suit = spades
        if (a.is_trump(trump) && b.is_trump(trump)) {
            if (a.is_right_bower(trump)) {  // if a is right bower, b cannot be greater than a
                return false;
            }
            else if (b.is_right_bower(trump)) { // if b is right bower, a has to be less than b
                return true;
            }
            // at this point neither cards are right bower
            else if (a.is_left_bower(trump)){
                return false;
            }
            else if (b.is_left_bower(trump)) {
                return true;
            }
            // at this point neither cards are left bower, so we compare normally
            else {
                if (a < b) {
                    return true;
                }
                else {
                    return false;
                }
            }
        }
        // Card a is trump, Card b is NOT trump
        // if a is trump and b isn't, then a > b, so return false
        else if (a.is_trump(trump) && !(b.is_trump(trump))) {
            return false;
        }
        // Card a is NOT trump, Card b is trump
        // if a isn't trump and b is, then a < b, so return true
        else if (!(a.is_trump(trump)) && b.is_trump(trump)) {
            return true;
        }
        // Card a is NOT trump, Card b is NOT trump
        // if neither cards are trump, we just follow normal behavior
        else {
            if (a < b) {
                return true;
            }
            else {
                return false;
            }
        }
    }
    return false;
}

//EFFECTS Returns true if a is lower value than b.  Uses both the trump suit
//  and the suit led to determine order, as described in the spec.
// TEST CASES:  - TEST 1: trump = clubs AND a = Jack, Spades < b = Ace, clubs   OUT = false;
//              - TEST 2: trump = clubs AND a = Ace, clubs < a = Jack, Spades      OUT = true;
//              - TEST 3: trump = clubs, led card = Hearts, AND a = Jack, diamonds < b = 10, hearts         OUT = true;
bool Card_less(const Card &a, const Card &b, const Card &led_card, Suit trump) {
    Suit card_a_suit = a.get_suit();
    Suit card_b_suit = b.get_suit();
    Suit led_card_suit = led_card.get_suit();
    //assert(a != b && b != led_card && led_card != a);
    // Make sure that a, b and led_card are all different cards
// REMOVED BELOW IF STATEMENT BC LED CARD IS SAME AS COMPARED CARD IN TRICK_WINNER()
    //if (a != b && b != led_card && led_card != a) {
        // if at least one card is a trump card, then I don't care what the led_card suit is
        // this condition also takes care of when led_card suit == trump suit; if led_card suit is trump suit - I don't care about led card
        if (a.is_trump(trump) || b.is_trump(trump)) {
            return Card_less(a, b, trump);
        }
        // if neither cards are trump - this is when I care about led_card
        else {
            // a and b aren't trump cards
            // a is led card, b isn't
            if ((card_a_suit == led_card_suit) && (card_b_suit != led_card_suit)) {
                return false;
            }
            // a and b aren't trump cards
            // a isn't led card, b is
            else if ((card_a_suit != led_card_suit) && (card_b_suit == led_card_suit)) {
                return true;
            }
            // a and b aren't trump cards
            // both are ledcard suits or both are not led card suits
            else {
                if (a < b)
                    return true;
                else
                    return false;
            }
        }
    //}
    return false;
}
