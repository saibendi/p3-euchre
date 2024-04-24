#include "Pack.hpp"
#include <array>
#include <string>

using namespace std;

/*
 private:
   static const int PACK_SIZE = 24;
   std::array<Card, PACK_SIZE> cards;
   int next; //index of next card to be dealt
 */

// EFFECTS: Initializes the Pack to be in the following standard order:
//          the cards of the lowest suit arranged from lowest rank to
//          highest rank, followed by the cards of the next lowest suit
//          in order from lowest to highest rank, and so on.
// NOTE: The standard order is the same as that in pack.in.
// NOTE: Do NOT use pack.in in your implementation of this function
// NOTE: The pack is initially full, with no cards dealt.
// QUESTIONS: - can we create a new variable card_number or are we just supposed to use the private member variables?
Pack::Pack() {
    // cards is the array that we need to pack the cards in from lowest to highest
    // 9 of spades, 10 of spades, J of spades etc.
    // enum Suit and enum Rank are global variables
    // iterate through and start with spades
        // set suit = spades
    int card_number = 0;
    for (int s = SPADES; s <= DIAMONDS; ++s) {
        Suit suit = static_cast<Suit>(s);   // assigning suit
        for (int r = NINE; r <= ACE; ++r) {
            Rank rank = static_cast<Rank>(r);
            cards[card_number] = Card(rank,suit);
            //std::cout << "Card " << card_number + 1 << " is: " << cards[card_number] << std::endl;
            card_number++;
        }
    }
}

// REQUIRES: pack_input contains a representation of a Pack in the
//           format required by the project specification
// MODIFIES: pack_input
// EFFECTS: Initializes Pack by reading from pack_input.
// NOTE: The pack is initially full, with no cards dealt.
Pack::Pack(std::istream& pack_input) {
    assert(false);
}

// REQUIRES: cards remain in the Pack
// EFFECTS: Returns the next card in the pack and increments the next index
// QUESTIONS: - can we initialize next variable in the private part of class?
Card Pack::deal_one() {
    Card cardToDeal;    // default constructor initializes this to Two of Spades
    if (next <= 23) {
        cardToDeal = cards[next];
        next++;
        return cardToDeal;
    }
    
    cout << "No more cards left to deal" << endl;
    return {};      // making sure that we don't return Two of Spades
}

  // EFFECTS: Resets next index to first card in the Pack
void Pack::reset() {
    next = 0;
}

// EFFECTS: Shuffles the Pack and resets the next index. This
//          performs an in shuffle seven times. See
//          https://en.wikipedia.org/wiki/In_shuffle.
void Pack::shuffle() {
    /*
     12 -> 0
                0 -> 1
     13 -> 2
                1 -> 3
     14 -> 4
                2 -> 5
     15 -> 6
                3 -> 7
     16 -> 8
                4 -> 9
     17 -> 10
                5 -> 11
     18 -> 12
                6 -> 13
     19 -> 14
                7 -> 15
     20 -> 16
                8 -> 17
     21 -> 18
                9 -> 19
     22 -> 20
                10 -> 21
     23 -> 22
                11 -> 23
     */
    // index 0 - 11: relocated to an odd index starting from 1 - 23, respectively
    // index 12 - 23: relocated to an even index starting from 0 - 22, respectively
    // first half - ODD
    // second half - EVEN
    // use PACK_SIZE - 1 = to get 23
        //
    
    const int NUM_TIMES_SHUFFLE = 7;
    array<Card, PACK_SIZE> temp_cards;         // creating a temp array to avoid the overwrite problem
    // shuffle 7 times
    for (int shuffle_count = 0; shuffle_count < NUM_TIMES_SHUFFLE; ++shuffle_count) {
        temp_cards = cards;
        int card_number = 0;
        int odd_card_number = 1;
        //for (card_number = 0; card_number < (PACK_SIZE / 2); ++card_number) {
        while (card_number < PACK_SIZE / 2) {
            cards[odd_card_number] = temp_cards[card_number];
            odd_card_number = odd_card_number + 2;
            ++card_number;
        }
        int even_card_number = 0;
        //for (int second_half = 12; second_half < (PACK_SIZE); ++second_half) {
        while (card_number < PACK_SIZE) {
            cards[even_card_number] = temp_cards[card_number];
            even_card_number = even_card_number + 2;
            ++card_number;
        }
    }
}

// EFFECTS: returns true if there are no more cards left in the pack
bool Pack::empty() const {
    // cards.size() won't work because the card size is always going to be 24
    if (next == 24) {
        return true;
    }
    return false;
}

