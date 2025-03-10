#include "Pack.hpp"
#include "unit_test_framework.hpp"

#include <iostream>
#include <fstream>

using namespace std;

TEST(test_pack_default_ctor_AND_deal_one_AND_reset) {
    // Testing default ctor and deal_one
    Pack pack;
    Card first = pack.deal_one();
    Card second = pack.deal_one();
    ASSERT_EQUAL(NINE, first.get_rank());
    ASSERT_EQUAL(SPADES, first.get_suit());
    cout << "Test 1 passed!" << endl;
    ASSERT_EQUAL(second, Card(TEN,SPADES));
    cout << "Test 2 passed!" << endl;
    
    // Testing .reset()
    pack.reset();
    Card first_again = pack.deal_one();
    ASSERT_EQUAL(first_again, Card(NINE,SPADES));
    cout << "Test 3 passed!" << endl;
}

TEST(test_empty) {
    Pack pack;
    // Testing .empty()
    // emptying the pack by dealing 24 cards, card number 0 through 23
    for (int i = 0; i < 24; ++i) {
        pack.deal_one();
        //cout << new_card << endl;
    }
    ASSERT_EQUAL(pack.empty(), true);
    cout << "Test 1 passed!" << endl;
    
    // Testing .reset() again
    pack.reset();
    Card another_card = pack.deal_one();
    ASSERT_EQUAL(another_card, Card(NINE,SPADES));
    cout << "Test 2 passed!" << endl;
}

// TODO: NEED TO CHECK EXPECTED BEHAVIOR AFTER 1st LOOP
TEST(test_shuffle) {
    Pack pack;
    for (int i = 0; i < 24; ++i) {
        Card new_card = pack.deal_one();
        cout << "Card " << i << " is: " << new_card << endl;
    }
    pack.reset();    // leads to problems - comment out to find out
    pack.shuffle();
    for (int i = 0; i < 24; ++i) {
        Card new_card = pack.deal_one();
        cout << "Card " << i << " is: " << new_card << endl;
    }
}

// TODO: create new file (test_pack.in) with different order of cards and test that
TEST(test_istream_ctor) {
    // Your implementation may assume any pack input is formatted correctly, with exactly 24 unique and correctly formatted cards.
    string filename = "pack.in";
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "opening file failed!" << endl;
        exit(1);
    }
    Pack pack(file);
    Card new_card = pack.deal_one();
    ASSERT_EQUAL(new_card, Card(NINE, SPADES));
    Card next_card = pack.deal_one();
    ASSERT_EQUAL(next_card, Card(TEN, SPADES));

}


// Add more tests here

TEST_MAIN()
