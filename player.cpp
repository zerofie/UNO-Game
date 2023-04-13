#include "card.h"
#include "player.h"
#include <iostream>
#include <ctime>
using namespace std;
player::player() //Default Constructor
{
	head = NULL;
	size = 0;
}
player::player(const player &other) //Parameterized Constructor
{
	copy(other);
}
const player &player::operator=(const player &other) //Equality Operator
{
	if (this != &other)
	{
		clear();
		copy(other);
	}
	return *this;
}
player::~player() //Destructor
{
	clear();
}
void player::hand_add(card temp_card)
{ //Insertion of an element in linked list
	card_elem *temp_ptr;
	temp_ptr = new card_elem();
	temp_ptr->data = temp_card;
	temp_ptr->next = head;
	head = temp_ptr;
	size++;
}
card player::hand_remove(int pos)
{ //Deletion of an element in linked list
	if (pos < 0 || pos >= size)
	{
		return card();
	}
	card_elem *prev_ptr = head;
	card_elem *target = prev_ptr->next;
	card temp_card;
	int temp_pos = pos;
	//If the element is at front
	if (pos == 0)
	{
		temp_card = head->data;
		head = head->next;
		delete prev_ptr;
		size--;
		return temp_card;
	}
	//If the element is not at front
	while (temp_pos > 1)
	{
		prev_ptr = prev_ptr->next;
		target = prev_ptr->next;
		temp_pos--;
	}
	prev_ptr->next = target->next;
	temp_card = target->data;
	delete target;
	size--;
	return temp_card;
}
void player::uno() {}
void player::print() const //Print the hand of the player
{
	int temp_size = size;
	int i = 0;
	card_elem *temp_ptr = head;
	while (temp_size > 0)
	{
		cout << i << ":  " << temp_ptr->data << endl;
		temp_ptr = temp_ptr->next;
		i++;
		temp_size--;
	}
}
void player::copy(const player &other) //Copy function
{
	size = other.size;
	//create the head of target player
	if (size > 0)
	{
		head = new card_elem();
		//fill head with data
		head->data = other.head->data;
	}
	else
	{
		head = NULL;
		return;
	}
	card_elem *other_ptr = other.head->next;
	card_elem *temp_ptr;
	card_elem *prev_ptr = head;
	for (int i = 1; i < size; i++)
	{
		temp_ptr = new card_elem();
		prev_ptr->next = temp_ptr;
		temp_ptr->data = other_ptr->data;
		prev_ptr = temp_ptr;
		temp_ptr = NULL;
		other_ptr = other_ptr->next;
	}
}
void player::clear()
{
	card_elem *temp_ptr = head;
	card_elem *next_ptr;
	while (size > 0)
	{
		next_ptr = temp_ptr->next;
		delete temp_ptr;
		temp_ptr = next_ptr;
		size--;
	}
	head = NULL;
}
int player::get_size() const //Return number of cards in a player's hand
{
	return size;
}
card player::peek(int pos) const //Return the card at a specific position
{
	int temp_pos = pos;
	card_elem *temp_elem = head;
	while (temp_pos > 0)
	{
		temp_elem = temp_elem->next;
		temp_pos--;
	}
	return temp_elem->data;
}
