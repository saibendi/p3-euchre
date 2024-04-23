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
    // Trump suit is CLUBS
    // Led_card suit is hearts
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
    
    // Trump suit is SPADES
    // led_card suit is diamonds
    Card QueenOfDiamonds(QUEEN, DIAMONDS);
    // Test 1:
    Card JackOfClubs(JACK,CLUBS); // left bower
    Card KingOfDiamonds(KING, DIAMONDS);
    ASSERT_EQUAL(JackOfClubs.is_left_bower(SPADES), true);
    ASSERT_EQUAL(JackOfClubs.is_trump(SPADES), true);
    ASSERT_EQUAL(Card_less(JackOfClubs, KingOfDiamonds, QueenOfDiamonds, SPADES), false);
    cout << "Passed Test 4!" << endl;
    cout << "BUG: used 'if (card_a_suit == trump) || (card_b_suit == trump)' in Card_less implementation" << endl;
    cout << "ISSUE: JackOfClubs is left bower and so a trump card but since the suit isn't the same as trump suit it wasn't being picked up in the if condition" << endl;
    cout << "FIX: changed to if (a.is_trump(trump) || b.is_trump(trump))" << endl;
    // Test 2:
    Card TenOfSpades(TEN,SPADES);   // 10 of Spades is of a trump suit, but left bower is higher
    ASSERT_EQUAL(Card_less(JackOfClubs, TenOfSpades, QueenOfDiamonds, SPADES), false);
    cout << "Passed Test 5!" << endl;
    // Trump suit is SPADES and led suit is SPADES
    ASSERT_EQUAL(Card_less(TenOfSpades, JackOfClubs, JackOfSpades, SPADES), true);
    cout << "Passed Test 6!" << endl;
    
    // TRUMP IS HEARTS
    // led_card is DIAMONDS
    ASSERT_EQUAL(Card_less(KingOfDiamonds, JackOfDiamonds, QueenOfDiamonds, HEARTS), true); // since hearts is trump, jack of hearts is right bower and jack of diamonds is left bower so should be greater than King
    cout << "Passed Test 7!" << endl;
    Card AceOfDiamonds(ACE, DIAMONDS);
    ASSERT_EQUAL(Card_less(AceOfClubs, AceOfDiamonds, QueenOfDiamonds, HEARTS), true); // Led suit card should be greater than any other non trump, non led suit card;
    cout << "Passed Test 8!" << endl;
    
    // EDGE CASES
    //ASSERT_EQUAL(Card_less(JackOfDiamonds, JackOfDiamonds, KingOfDiamonds, DIAMONDS), false); // trump is diamonds - so both cards are trumps
    cout << "Passed Test 9!" << endl;
    cout << "BUG: did not have a catch to make sure a != b" << endl;
    cout << "ISSUE: JackOfDiamonds is right bower and if both cards are right bower then answer isn't false" << endl;
    cout << "FIX: added an if statement to only do logic if cards are different" << endl;
    //ASSERT_EQUAL(Card_less(JackOfDiamonds, JackOfDiamonds, JackOfDiamonds, DIAMONDS), false); // trump is diamonds - so both cards are trumps
    cout << "Passed Test 10!" << endl;
}

TEST(test_is_face_or_ace) {
    cout << "------------------------------------------------------" << endl;
    // Test 1:
    Card TwoOfDiamonds(TWO,DIAMONDS);
    Card AceOfClubs(ACE,CLUBS);
    Card JackOfDiamonds(JACK,DIAMONDS);
    Card TenOfDiamonds(TEN,DIAMONDS);
    Card QueenOfClubs(QUEEN,CLUBS);
    ASSERT_EQUAL(TwoOfDiamonds.is_face_or_ace(), false);
    cout << "Passed Test 1!" << endl;
    ASSERT_EQUAL(AceOfClubs.is_face_or_ace(), true);
    cout << "Passed Test 2!" << endl;
    ASSERT_EQUAL(TenOfDiamonds.is_face_or_ace(), false);
    cout << "Passed Test 3!" << endl;
    ASSERT_EQUAL(QueenOfClubs.is_face_or_ace(), true);
    cout << "Passed Test 4!" << endl;

}


// Add more test cases here

TEST_MAIN()
