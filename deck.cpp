#define DECK_SIZE 108
#include "deck.h"
#include "card.h"
#include <ctime>
#include <iostream> // std:: cout
#include <cstdlib>	// std::rand, std::srand
using namespace std;
deck::deck() //Default Constructor
{
	ptr_deck = new card[DECK_SIZE];
	size = 0;
}
void deck::create() //Create function to create a deck
{
	int num = 0;
	// card number 0
	for (int col = 1; col <= 4; col++)
	{
		ptr_deck[size].number = num;
		ptr_deck[size].color = static_cast<COLOR>(col);
		size++;
	}
	// card number 1 till 9 , "draw-two", "skip", "reverse"
	for (num = 1; num <= 12; num++)
	{
		for (int x = 0; x < 2; x++)
		{
			for (int col = 1; col <= 4; col++)
			{
				ptr_deck[size].number = num;
				ptr_deck[size].color = static_cast<COLOR>(col);
				size++;
			}
		}
	}
	// card "wild", "wild-draw-four"
	for (num = 13; num <= 14; num++)
	{
		for (int x = 0; x < 4; x++)
		{
			ptr_deck[size].number = num;
			ptr_deck[size].color = wild;
			size++;
		}
	}
}
deck::deck(const deck &other) //Parameterized Constructor
{
	copy(other);
}
const deck &deck::operator=(const deck &other) //Operator Overloading
{
	if (this != &other)
	{
		clear();
		copy(other);
	}
	return *this;
}
deck::~deck() //Destructor
{
	clear();
}
void deck::shuffle()
{
	/*
	Shuffule function to shuffle the cards of the deck
	temprorary deck is made which is copy of the original 
	The rand function is used to choose random card from the original 
	is swapped from a random card of the temporary deck
	repeat the process 
	time complexity of this algorithm will be O(n^2)  
	*/
	card *temp_deck = new card[size];
	for (int i = 0; i < size; i++)
	{
		temp_deck[i] = ptr_deck[i];
	}
	int temp_size = size;
	int temp_pos;
	int pos;
	for (int i = 0; i < size; i++)
	{
		// randomly find a position in temp_deck
		srand(time(NULL)); // change the seed , so randomized number is different each time
		pos = rand() % temp_size;
		//assign random element to deck[i]
		ptr_deck[i] = temp_deck[pos];
		// removing element from temp_deck (O(n) to shift)
		temp_size--;
		for (temp_pos = pos; temp_pos < temp_size; temp_pos++)
		{
			temp_deck[temp_pos] = temp_deck[temp_pos + 1];
		}
	}
	delete[] temp_deck;
}
card deck::draw() //Draw a card from the deck and reduce its size by one
{
	if (size <= 0)
	{
		return card();
	}
	card temp_card = ptr_deck[size - 1];
	size--;
	return temp_card;
}
int deck::add_card(card temp_card)
{
	// O(1) insert
	if (size < DECK_SIZE)
	{
		ptr_deck[size] = temp_card;
		size++;
		return 0;
	}
	else
		return -1;
}
void deck::quick_shuffle()
{
	/* O(n) shuffle : fisher -yates shuffle algorithm 
	given rand() generates a random number in O(1)
	start from last element 
	swap it with randomly selected from whole array including last
	now consider array from 0 to n-2(size reduced by 1 ) 
	repeat the process until we hit first element 
*/
	int pos;
	int temp_size = size - 1;
	card temp_card;
	while (temp_size > 0)
	{					   //generate random
		srand(time(NULL)); // change the seed , so randomized number is different each time
		pos = rand() % temp_size;
		// swap elements
		temp_card = ptr_deck[temp_size];
		ptr_deck[temp_size] = ptr_deck[pos];
		ptr_deck[pos] = temp_card;
		temp_size--; // reduce size by 1
	}
}
void deck::print_deck()
{
	for (int i = 0; i < size; i++)
	{
		cout << i << ": " << ptr_deck[i] << endl;
	}
}
void deck::copy(const deck &other) //Copy function to make a copy of an original deck
{
	size = other.size;
	ptr_deck = new card[size];
	for (int i = 0; i < size; i++)
	{
		ptr_deck[i] = other.ptr_deck[i];
	}
}
void deck::clear()
{
	delete[] ptr_deck;
	ptr_deck = NULL;
	size = 0;
}
int deck::get_size()
{
	return size;
}