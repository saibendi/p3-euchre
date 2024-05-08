#include "Player.hpp"
#include "unit_test_framework.hpp"

#include <iostream>

using namespace std;

TEST(test_player_get_name) {
    Player * alice = Player_factory("Alice", "Simple");
    ASSERT_EQUAL("Alice", alice->get_name());

    delete alice;
}

TEST(test_make_trump_bob) {
    // Bob's hand
    Player * bob = Player_factory("Bob", "Simple");
    bob->add_card(Card(KING, HEARTS));
    bob->add_card(Card(ACE, HEARTS));
    bob->add_card(Card(NINE, SPADES));
    bob->add_card(Card(TEN, SPADES));
    bob->add_card(Card(JACK, SPADES));
    
    Player * kith = Player_factory("Kith", "Simple");
    kith->add_card(Card(KING, CLUBS));
    kith->add_card(Card(JACK, CLUBS));
    kith->add_card(Card(NINE, HEARTS));
    kith->add_card(Card(JACK, HEARTS));
    kith->add_card(Card(KING, DIAMONDS));
    
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
    cout << "Round 1: Upcard was JACK of DIAMONDS and Bob didn't order up!" << endl;
    
    orderup = bob->make_trump(
      upcard,    // Upcard
      false,           // Bob is also the dealer
      2,              // First round
      trump           // Suit ordered up (if any)
    );
    ASSERT_TRUE(orderup);
    ASSERT_EQUAL(trump, HEARTS);
    cout << "Round 2: Moving to 'next suit' which is HEARTS and Bob orders up and HEARTS is trump!" << endl;
    
    Card lead_card = bob->lead_card(trump); // should lead with jack of spades -> highest non trump
    ASSERT_EQUAL(lead_card, Card(JACK, SPADES));
    cout << "Trick Taking: Bob leads with highest NON-TRUMP Card which is the JACK of SPADES!" << endl;
    
    Card play_card = kith->play_card(lead_card, trump);
    cout << play_card << endl;
    ASSERT_EQUAL(play_card, Card(JACK, CLUBS));
 
    delete bob;
    delete kith;
}
// Add more tests here

TEST(test_make_trump_Following_PDF ) {
    // Bob's hand
    Player * bob = Player_factory("Bob", "Simple");
    bob->add_card(Card(KING, HEARTS));
    bob->add_card(Card(ACE, HEARTS));
    bob->add_card(Card(NINE, SPADES));
    bob->add_card(Card(TEN, SPADES));
    bob->add_card(Card(JACK, SPADES));
    
    Player * cathy = Player_factory("Cathy", "Simple");
    cathy->add_card(Card(NINE, CLUBS));
    cathy->add_card(Card(TEN, CLUBS));
    cathy->add_card(Card(JACK, CLUBS));
    cathy->add_card(Card(QUEEN, SPADES));
    cathy->add_card(Card(KING, SPADES));
    
    Player * drew = Player_factory("Drew", "Simple");
    drew->add_card(Card(QUEEN, CLUBS));
    drew->add_card(Card(KING, CLUBS));
    drew->add_card(Card(ACE, SPADES));
    drew->add_card(Card(NINE, HEARTS));
    drew->add_card(Card(TEN, HEARTS));
    
    Player * alice = Player_factory("Alice", "Simple");
    alice->add_card(Card(ACE, CLUBS));
    alice->add_card(Card(NINE, DIAMONDS));
    alice->add_card(Card(TEN, DIAMONDS));
    alice->add_card(Card(JACK, HEARTS));
    alice->add_card(Card(QUEEN, HEARTS));

    int round = 1;
    cout << "----- ROUND 1 of Making Trump Begins -------" << endl;
    // Bob makes tump
    Card upcard(JACK, DIAMONDS);
    Suit trump;
    bool orderup = bob->make_trump(
      upcard,    // Upcard
      false,           // Bob is also the dealer
      round,              // First round
      trump           // Suit ordered up (if any)
    );
    // Verify Bob's order up and trump suit
    ASSERT_FALSE(orderup);
    cout << "       - Bob passes ordering up." << endl;

    orderup = cathy->make_trump(upcard, false, round, trump);
    ASSERT_FALSE(orderup);
    cout << "       - cathy passes ordering up." << endl;

    orderup = drew->make_trump(upcard, false, round, trump);
    ASSERT_FALSE(orderup);
    cout << "       - drew passes ordering up." << endl;
    
    orderup = alice->make_trump(upcard, true, round, trump);
    ASSERT_FALSE(orderup);
    cout << "       - alice passes ordering up." << endl;
    cout << "   !Diamonds has been rejected as a trump by all players!" << endl;

    round = 2;
    cout << "----- ROUND 2 of Making Trump Begins -------" << endl;
    orderup = bob->make_trump(upcard, false, round, trump);
    ASSERT_TRUE(orderup);
    cout << "       - bob will order up hearts." << endl;
    cout << "   !Making Trump is Complete!" << endl;
    cout << endl << endl;
    
    cout << "----- ROUND 1 of Trick Taking Begins -------------" << endl;
    Card led_card_bob = bob->lead_card(trump);
    cout << "       - bob leads with Jack of Spades" << endl;
    ASSERT_EQUAL(led_card_bob, Card(JACK, SPADES));
    
    Card play_card_cathy = cathy->play_card(led_card_bob, trump);
    cout << "       - cathy plays King of Spades" << endl;
    ASSERT_EQUAL(play_card_cathy, Card(KING, SPADES));
    
    Card play_card_drew = drew->play_card(led_card_bob, trump);
    cout << "       - drew plays Ace of Spades" << endl;
    ASSERT_EQUAL(play_card_drew, Card(ACE, SPADES));
    
    Card play_card_alice = alice->play_card(led_card_bob, trump);
    cout << "       - alice plays Nine of Diamonds" << endl;
    ASSERT_EQUAL(play_card_alice, Card(NINE, DIAMONDS));

    cout << "   !Drew wins this Trick!" << endl;

    cout << "----- ROUND 2 of Trick Taking Begins -------------" << endl;
    Card led_card_drew = drew->lead_card(trump);
    cout << "       - drew leads with King of Clubs" << endl;
    ASSERT_EQUAL(led_card_drew, Card(KING, CLUBS));
    
    play_card_alice = alice->play_card(led_card_drew, trump);
    cout << "       - alice plays Ace of Clubs" << endl;
    ASSERT_EQUAL(play_card_alice, Card(ACE, CLUBS));
    
    Card play_card_bob = bob->play_card(led_card_drew, trump);
    cout << "       - bob plays Nine of Spades" << endl;
    ASSERT_EQUAL(play_card_bob, Card(NINE, SPADES));
    
    play_card_cathy = cathy->play_card(led_card_drew, trump);
    cout << "       - cathy plays Jack of Clubs" << endl;
    ASSERT_EQUAL(play_card_cathy, Card(JACK, CLUBS));

    cout << "   !Alice wins this Trick!" << endl;

    cout << "----- ROUND 3 of Trick Taking Begins -------------" << endl;
    Card led_card_alice = alice->lead_card(trump);
    cout << "       - alice leads with Ten of Diamonds" << endl;
    ASSERT_EQUAL(led_card_alice, Card(TEN, DIAMONDS));
    
    play_card_bob = bob->play_card(led_card_alice, trump);
    cout << "       - bob plays Ten of Spades" << endl;
    ASSERT_EQUAL(play_card_bob, Card(TEN, SPADES));

    play_card_cathy = cathy->play_card(led_card_alice, trump);
    cout << "       - cathy plays Nine of Clubs" << endl;
    ASSERT_EQUAL(play_card_cathy, Card(NINE, CLUBS));
    
    play_card_drew = drew->play_card(led_card_alice, trump);
    cout << "       - drew plays Queen of Clubs" << endl;
    ASSERT_EQUAL(play_card_drew, Card(QUEEN, CLUBS));
    
    cout << "   !Alice wins this Trick!" << endl;

    cout << "----- ROUND 4 of Trick Taking Begins -------------" << endl;
    led_card_alice = alice->lead_card(trump);
    cout << "       - alice leads with Jack of Hearts" << endl;
    ASSERT_EQUAL(led_card_alice, Card(JACK, HEARTS));
    
    play_card_bob = bob->play_card(led_card_alice, trump);
    cout << "       - bob plays Ace of Hearts" << endl;
    ASSERT_EQUAL(play_card_bob, Card(ACE, HEARTS));
    
    play_card_cathy = cathy->play_card(led_card_alice, trump);
    cout << "       - cathy plays Ten of Clubs" << endl;
    ASSERT_EQUAL(play_card_cathy, Card(TEN, CLUBS));
    
    play_card_drew = drew->play_card(led_card_alice, trump);
    cout << "       - drew plays Ten of Hearts" << endl;
    ASSERT_EQUAL(play_card_drew, Card(TEN, HEARTS));

    cout << "   !Alice wins this Trick!" << endl;

    cout << "----- ROUND 5 of Trick Taking Begins -------------" << endl;
    led_card_alice = alice->lead_card(trump);
    cout << "       - alice leads with Queen of Hearts" << endl;
    ASSERT_EQUAL(led_card_alice, Card(QUEEN, HEARTS));
    
    play_card_bob = bob->play_card(led_card_alice, trump);
    cout << "       - bob plays King of Hearts" << endl;
    ASSERT_EQUAL(play_card_bob, Card(KING, HEARTS));
    
    play_card_cathy = cathy->play_card(led_card_alice, trump);
    cout << "       - cathy plays Queen of Spades" << endl;
    ASSERT_EQUAL(play_card_cathy, Card(QUEEN, SPADES));
    
    play_card_drew = drew->play_card(led_card_alice, trump);
    cout << "       - drew plays Nine of Hearts" << endl;
    ASSERT_EQUAL(play_card_drew, Card(NINE, HEARTS));

    cout << "   !Bob wins this Trick!" << endl;

    
    delete bob;
    delete cathy;
    delete alice;
    delete drew;
}

TEST_MAIN()
