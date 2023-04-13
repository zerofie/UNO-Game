/* class Player 
public data members are- 
	play cards to center
	draw card
	pass turn
	show amount of cards left 
	show cards in hand (for playing to center) 
private data members are-
	cards on the hand ( limit to the half the deck of cards) 
	an array 
*/
#ifndef PLAYER_H
#define PLAYER_H
#include "card.h"
class player
{
public:
	player();									  //Default Constructor
	player(const player &other);				  //Parameterized Constructor
	const player &operator=(const player &other); //Operator Overloading
	~player();									  //Destructor
	void hand_add(card temp);					  //Function to add a card to hand
	card hand_remove(int pos);					  //Function to remove a card to hand
	void uno();
	void print() const;	  //Function to print the hand
	int get_size() const; //Function to get the number of cards
	card peek(int pos) const;
	//FUnction to return specific card at a specific position in the player's hand
private:
	class card_elem //Linked list used to represent a hand of a player
	{
	public:
		card_elem()
		{
			next = NULL;
		}
		card data;
		card_elem *next;
	};
	card_elem *head;
	int size;
	void copy(const player &other); //Copy function
	void clear();
};
#endif
