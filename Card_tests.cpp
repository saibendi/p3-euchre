#include "Card.hpp"
#include "unit_test_framework.hpp"
#include <iostream>

using namespace std;


TEST(test_card_ctor) {
    cout << "------------------------------------------------------" << endl;;
    Card c(ACE, HEARTS);
    ASSERT_EQUAL(ACE, c.get_rank());
    ASSERT_EQUAL(HEARTS, c.get_suit());
}

TEST(test_less_than_AND_less_than_or_equal_to) {
    cout << "------------------------------------------------------" << endl;
    // Test 1:
    Card AceOfClubs(ACE,CLUBS);
    ASSERT_EQUAL(AceOfClubs < AceOfClubs, false);
    ASSERT_EQUAL(AceOfClubs <= AceOfClubs, true);
    cout << "Passed Test 1!" << endl;
    // Test 2:
    Card AceOfHearts(ACE,HEARTS);
    ASSERT_EQUAL(AceOfClubs < AceOfHearts, false);
    ASSERT_EQUAL(AceOfClubs <= AceOfHearts, false);
    cout << "Passed Test 2!" << endl;
    // Test 3:
    Card TwoOfClubs(TWO,CLUBS);
    ASSERT_EQUAL(TwoOfClubs < AceOfClubs, true);
    ASSERT_EQUAL(TwoOfClubs <= AceOfClubs, true);
    cout << "Passed Test 3!" << endl;
}

TEST(test_greater_than_AND_greater_than_or_equal_to) {
    cout << "------------------------------------------------------" << endl;
    // Test 1:
    Card TwoOfDiamonds(TWO,DIAMONDS);
    Card AceOfClubs(ACE,CLUBS);
    ASSERT_EQUAL(TwoOfDiamonds > AceOfClubs, true);
    ASSERT_EQUAL(TwoOfDiamonds >= AceOfClubs, true);
    cout << "Passed Test 1!" << endl;
    // Test 2:
    Card AceOfDiamonds(ACE,DIAMONDS);
    ASSERT_EQUAL(AceOfDiamonds > TwoOfDiamonds, true);
    ASSERT_EQUAL(AceOfDiamonds >= TwoOfDiamonds, true);
    cout << "Passed Test 2!" << endl;
    // Test 3:
    ASSERT_EQUAL(AceOfDiamonds > AceOfDiamonds, false);
    ASSERT_EQUAL(AceOfDiamonds >= AceOfDiamonds, true);
    cout << "Passed Test 3!" << endl;
}

TEST(test_equal_to_AND_not_equal_to) {
    cout << "------------------------------------------------------" << endl;
    // Test 1:
    Card TwoOfDiamonds(TWO,DIAMONDS);
    Card AceOfClubs(ACE,CLUBS);
    ASSERT_EQUAL(TwoOfDiamonds != AceOfClubs, true);
    ASSERT_EQUAL(TwoOfDiamonds == TwoOfDiamonds, true);
    ASSERT_EQUAL(TwoOfDiamonds == AceOfClubs, false);
    ASSERT_EQUAL(TwoOfDiamonds != TwoOfDiamonds, false);
    cout << "Passed Test 1!" << endl;
    // Test 2:
    Card AceOfDiamonds(ACE,DIAMONDS);
    ASSERT_EQUAL(AceOfDiamonds == AceOfClubs, false);
    ASSERT_EQUAL(AceOfDiamonds != AceOfClubs, true);
    ASSERT_EQUAL(AceOfDiamonds != TwoOfDiamonds, true);
    cout << "Passed Test 2!" << endl;
}

TEST(test_next_suit) {
    cout << "------------------------------------------------------" << endl;
    // Test 1:
    Card TwoOfDiamonds(TWO,DIAMONDS);
    ASSERT_EQUAL(Suit_next(TwoOfDiamonds.get_suit()), HEARTS);
    cout << "Passed Test 1!" << endl;
    // Test 2:
    Card KingOfHearts(KING,HEARTS);
    ASSERT_EQUAL(Suit_next(KingOfHearts.get_suit()), DIAMONDS);
    cout << "Passed Test 2!" << endl;
    // Test 3:
    Card AceOfSpades(ACE,SPADES);
    ASSERT_EQUAL(Suit_next(AceOfSpades.get_suit()), CLUBS);
    cout << "Passed Test 3!" << endl;
}

TEST(test_card_less) {
    cout << "------------------------------------------------------" << endl;
    // Test 1:
    Card JackOfSpades(JACK,SPADES);
    Card AceOfClubs(ACE,CLUBS);
    ASSERT_EQUAL(Card_less(JackOfSpades, AceOfClubs, CLUBS), false);
    cout << "Passed Test 1!" << endl;
    // Test 2:
    ASSERT_EQUAL(Card_less(AceOfClubs, JackOfSpades, CLUBS), true);
    cout << "Passed Test 2!" << endl;
    // Test 3:
    Card FiveOfHearts(FIVE,HEARTS);
    Card TwoOfDiamonds(TWO,DIAMONDS);
    ASSERT_EQUAL(Card_less(FiveOfHearts, TwoOfDiamonds, CLUBS), true);
    cout << "Passed Test 3!" << endl;
}

TEST(test_card_less_led_card) {
    cout << "------------------------------------------------------" << endl;
    Card led_card(JACK,HEARTS);
    // Test 1:
    Card JackOfSpades(JACK,SPADES);
    Card AceOfClubs(ACE,CLUBS);
    ASSERT_EQUAL(Card_less(JackOfSpades, AceOfClubs, led_card, CLUBS), false);
    cout << "Passed Test 1!" << endl;
    // Test 2:
    ASSERT_EQUAL(Card_less(AceOfClubs, JackOfSpades, led_card, CLUBS), true);
    cout << "Passed Test 2!" << endl;
    // Test 3:
    Card TenOfHearts(TEN,HEARTS);
    Card JackOfDiamonds(JACK,DIAMONDS);
    ASSERT_EQUAL(Card_less(JackOfDiamonds, TenOfHearts, led_card, CLUBS), true);
    cout << "Passed Test 3!" << endl;
}


// Add more test cases here

TEST_MAIN()
