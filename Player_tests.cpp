#include "Player.hpp"
#include "unit_test_framework.hpp"

#include <iostream>

using namespace std;

TEST(test_player_get_name) {
    Player * alice = Player_factory("Alice", "Simple");
    ASSERT_EQUAL("Alice", alice->get_name());

    delete alice;
}

TEST(test_make_trump) {
    // Bob's hand
    Player * bob = Player_factory("Bob", "Simple");
    bob->add_card(Card(KING, HEARTS));
    bob->add_card(Card(ACE, HEARTS));
    bob->add_card(Card(NINE, SPADES));
    bob->add_card(Card(TEN, SPADES));
    bob->add_card(Card(JACK, SPADES));

    // Bob makes tump
    Card upcard(JACK, DIAMONDS);
    Suit trump;
    bool orderup = bob->make_trump(
      upcard,    // Upcard
      false,           // Bob is also the dealer
      1,              // First round
      trump           // Suit ordered up (if any)
    );
    // Verify Bob's order up and trump suit
    ASSERT_FALSE(orderup);
    
    orderup = bob->make_trump(
      upcard,    // Upcard
      false,           // Bob is also the dealer
      2,              // First round
      trump           // Suit ordered up (if any)
    );
    ASSERT_TRUE(orderup);
    ASSERT_EQUAL(trump, HEARTS);
    
    delete bob;
}
// Add more tests here

TEST_MAIN()
