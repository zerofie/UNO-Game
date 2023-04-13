#ifndef _CARD_H_
#define _CARD_H_
#include <iostream>
enum COLOR
{
	wild,
	red,
	green,
	blue,
	yellow
};
//It represents a card in a deck
class card
{
public:
	int number;	 // 0-9 numbers, +2, skip, reverse, +4 (all color)
	COLOR color; // 5 colors: red, green, blue, yellow, and wild(no color)
	bool operator==(card const &next_card) const;
	//operator overloading to define "==" to check equality between two cards
	bool operator!=(card const &next_card) const;
	//operator overloading to define "!=" to check inequality between two cards
	card();					  //Default constructor
	card(int num, COLOR col); //Parameterized constructor
};

/*
Stream operator to write to output stream like cout
out is the stram to be written to and temp_card is used to write to the stream 
*/
std::ostream &operator<<(std::ostream &out, card const &temp_card);
#endif // _CARD_H_
