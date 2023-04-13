#include "card.h"
#include <ctime>
card::card() : number(0), color(wild) // Default Constructor
{
}
card::card(int num, COLOR col) : number(num), color(col) // Parameterized Constructor
{
}
bool card::operator==(card const &next_card) const // Equality Operator
{
	return number == next_card.number || color == next_card.color || color == wild || next_card.color == wild;
}
bool card::operator!=(card const &next_card) const // Inequality Operator
{
	return !(*this == next_card);
}
std::ostream &operator<<(std::ostream &out, card const &temp_card)
{ // Switch case to print the number and color of a card
	out << "Number:";
	switch (temp_card.number)
	{
	case 10:
		out << "DRAW-2";
		break;
	case 11:
		out << "SKIP";
		break;
	case 12:
		out << "REVERSE";
		break;
	case 13:
		out << "WILD";
		break;
	case 14:
		out << "DRAW-4-WILD";
		break;
	default:
		out << (int)temp_card.number;
		break;
	}

	out << "   Color:";
	switch (temp_card.color)
	{
	case wild:
		out << "wild";
		break;
	case red:
		out << "red";
		break;
	case green:
		out << "green";
		break;
	case blue:
		out << "blue";
		break;
	case yellow:
		out << "yellow";
		break;
	default:
		out << "N/A";
		break;
	}
	return out;
}
