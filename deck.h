/* 
Deck is the subclass of card class
public members will include 
shuffle of cards 
drawing of cards (+1, +2, +4)
- will use queue to pop out 
- check if deck has run out 
- if ran out ( reshuffle entire deck) 

private members : 
 the deck of cards 
 a queue 

The deck will contain :-
zero - 4 cards (RGBY) 
one till nine - 4 cards (RGBY) & 4 cards (RGBY)
"Skip" -  4 cards (RGBY) & 4 cards (RGBY)
"Draw Two" -  4 cards (RGBY) & 4 cards (RGBY)
"Reverse " -  4 cards (RGBY) & 4 cards (RGBY)
"Wild " -  4 cards (RGBY)
"Wild Draw Four" -  4 cards (RGBY)
*/
#ifndef DECK_H
#define DECK_H
#include "card.h"
#include <iostream>
class deck : public card
{
public:
	deck();									  //Default Constructor
	deck(const deck &other);				  //Parameterized Constructor
	const deck &operator=(const deck &other); //Equality Operator
	~deck();								  //Destructor
	void shuffle();
	card draw();
	void create();
	int add_card(card temp_card);
	void quick_shuffle();
	void print_deck();
	int get_size();

private:
	card *ptr_deck; //Queue of cards using array
	int size;
	void clear();
	void copy(const deck &other); //Copy Constructor
};
std::ostream &operator<<(std::ostream &out, deck const &temp_deck);
//Stream operator to write a deck to output stream
#endif
