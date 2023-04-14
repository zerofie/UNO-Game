/* This cpp file will be the main function for the game
   -asking players to play cards into a middle temp deck
   -distributing cards
   -comparing playable cards and non playable cards
   -use of wild cards and special action cards
   -show the amount of cards left for each player
   -a player wins if the number of cards remaining is zero will start the game by
   -asking amount of players
   -creating main deck and temporary deck
*/
#include "card.h"
#include "deck.h"
#include "player.h"
#include <iostream>
#include <ctime>
#include <fstream> // for opening and closing files
#include <string>
#include <cstdlib>	// std::system() ; std::rand()
#include <limits>	// std::numeric_limits
#include <stdlib.h> //std::system("CLS");

using namespace std;

#define TEXTFILE "intro.txt"
#define PRINT_ALL_PLAYERS 0
#define TEMP_DECK 1
#define TURN 2
#define DECK_SIZE 108

//card code
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

//deck code
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
	Shuffle function to shuffle the cards of the deck
	temporary deck is made which is copy of the original
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

//player code
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


void display_intro(string filename)
{
	string line;
	fstream myfile;
	myfile.open(filename.c_str());
	if (myfile.is_open())
	{
		while (getline(myfile, line))
		{
			cout << line << endl;
		}
		myfile.close();
	}
	else
	{
		cout << "error unable to open file " << endl;
	}
}

void confirm_turn(int x)
{
	cout << "Confirm Player" << x << " by typing "
		 << "'" << x << "'"
		 << " and pressing enter"
		 << ": ";
	int temp;
	while (temp != x)
	{
		cin >> temp;
	}
}
COLOR FromString(const string &str)
{
	if (str == "red")
		return red;
	else if (str == "green")
		return green;
	else if (str == "blue")
		return blue;
	else if (str == "yellow")
		return yellow;
	else
		return wild;
}

int main()
{
	//clear screen
	system("CLS");
	//display an introduction to the game in the beginning
	display_intro(TEXTFILE);
	//ask user for amount of players
	int amount_players;
	int flag = 0;
	while (flag == 0)
	{
		cout << "Please enter amount of players: ";
		cin >> amount_players;
		if (amount_players >= 2 && amount_players <= 5)
		{
			cout << amount_players << " players entering game .... " << endl;
			flag = 1;
			break;
		}
		else
		{
			cout << "invalid amount of players" << endl;
		}
	}
	//creating deck
	deck main_deck;
	main_deck.create();
	main_deck.quick_shuffle();
	//creating player array
	player *play_array;
	play_array = new player[amount_players];
	//distributing 7 starting cards to each player
	for (int i = 0; i < amount_players; i++)
	{
		for (int k = 0; k < 7; k++)
		{
			card temp_card;
			temp_card = main_deck.draw();
			play_array[i].hand_add(temp_card);
		}
	}
	//all cards that are played will go to temp_deck
	deck temp_deck;
	//create the first starting card, by drawing from deck
	card played_card;
	card temp_card;
	int card_flag = 0;
	while (card_flag == 0) //Only non wild cards are drawn first
	{
		temp_card = main_deck.draw();
		if (temp_card.color != wild)
		{
			card_flag = 1;
			played_card = temp_card;
		}
		else
		{
			temp_deck.add_card(temp_card);
		}
	}
	//randomize who starts first
	srand(time(NULL));
	int turn = rand() % amount_players;
	cout << "PLAYER " << turn << " is randomly selected to play first" << endl;
	confirm_turn(turn);

	bool force_draw_bool = false;
	int turn_flag = 1;
	int win = 0;
	//keep playing until a player wins
	while (win == 0)
	{
		system("CLS"); // clear screen
		player *curr_player = &play_array[turn % amount_players];
		// checked for forced draw cards
		cout << "PLAYER " << turn % amount_players << endl;
		if (force_draw_bool)
		{
			if (played_card.number == 10) // checked for Draw-2
			{
				cout << "Forced Draw-2" << endl;
				card draw_2;
				for (int i = 0; i < 2; i++)
				{
					draw_2 = main_deck.draw();
					curr_player->hand_add(draw_2);
				}
			}
			if (played_card.number == 14) // checked for Draw-4
			{
				cout << "Forced Draw-4" << endl;
				card draw_4;
				for (int i = 0; i < 4; i++)
				{
					draw_4 = main_deck.draw();
					curr_player->hand_add(draw_4);
				}
			}
			force_draw_bool = false;
		}
		// print out the cards remaining for each player
		cout << "Cards remaining for each player: " << endl;
		for (int i = 0; i < amount_players; i++)
		{
			cout << "PLAYER " << i << ": " << play_array[i].get_size() << "   ";
		}
		cout << endl;
		cout << "Played Card: " << played_card << endl;
		// print out cards in player's hand
		cout << "PLAYER " << turn % amount_players << endl;
		curr_player->print();
		int check_flag = 0;
		int index;
		int size = curr_player->get_size();
		// ask for which card to play into middle
		while (check_flag == 0)
		{
			cout << "which card do you want to play? " << endl;
			cout << "If you want to draw a card please enter '-1' " << endl;
			cout << "Type the index of the card and press enter: ";
			cin >> index;
			if (index == -1) //check if index is to draw a card
			{
				card draw_temp;
				draw_temp = main_deck.draw();
				cout << "DRAWN CARD: " << draw_temp << endl;
				if (draw_temp == played_card && draw_temp.color != wild)
				{
					int play_draw_flag = 0;
					while (play_draw_flag == 0) //check for playing the drawn card
					{
						string temp_play;
						cout << "Do you want to play the drawn card [y/n] : ";
						cin >> temp_play;
						if (temp_play == "y")
						{
							played_card = draw_temp;
							temp_deck.add_card(draw_temp);
							if (played_card.number >= 10 && played_card.number <= 14)
							{
								force_draw_bool = true;
							}
							play_draw_flag = 1;
						}
						if (temp_play == "n")
						{
							curr_player->hand_add(draw_temp);
							play_draw_flag = 1;
						}
					}
				}
				else
				{
					curr_player->hand_add(draw_temp);
				}
				check_flag = 1;
			}
			//if the player wants to play a card from his hand
			if (index >= 0 && index < size)
			{
				// check if card is compatilbe with played card
				card temp = curr_player->peek(index);
				if (temp == played_card)
				{
					curr_player->hand_remove(index);
					temp_deck.add_card(temp);
					played_card = temp;
					if (played_card.color == wild) //if played card is wild
					{
						int check_color = 0;
						COLOR temp_color;
						string str_color;
						while (check_color == 0)
						{ // ask for new color
							cout << "Please choose a color (red , green, blue, yellow) :";
							cin >> str_color;
							temp_color = FromString(str_color);
							if (temp_color != wild)
							{
								played_card.color = temp_color;
								check_color = 1;
							}
							else
							{
								cout << "invalid color" << endl;
							}
						}
					}
					if (played_card.number >= 10 && played_card.number <= 14)
					{
						force_draw_bool = true;
					}
					check_flag = 1;
				}
				else
				{
					cout << "card cannot be played " << endl;
				}
			}
			else
			{
				cout << "invalid index " << endl;
			}
		}
		// check if there is a winner, and break while loop
		if (curr_player->get_size() == 0)
		{
			win = 1;
			cout << "PLAYER " << turn % amount_players << " has won the game." << endl;
			break;
		}
		// check for action cards that influence the turn here
		if (played_card.number == 11 && force_draw_bool == true) // skip case
		{
			if (turn_flag == 1)
				turn = turn + 2;
			else
				turn = turn - 2;
		}
		else if (played_card.number == 12 && force_draw_bool == true) // reverse case
		{															  // if only two players, behaves like a skip card
			if (amount_players == 2)
			{
				turn = turn + 2;
			}
			else
			{ // changes the rotation of game (from CW to CCW or vice versa)
				if (turn_flag == 1)
				{
					turn_flag = -1;
					turn--;
				}
				else
				{
					turn_flag = 1;
					turn++;
				}
			}
		}
		// for other cards
		else
		{
			if (turn_flag == 1)
				turn++;
			else
				turn--;
		}
		system("CLS");
		// print out the cards remaining for each player
		cout << "Cards remaining for each player: " << endl;
		for (int i = 0; i < amount_players; i++)
		{
			cout << "PLAYER " << i << ": " << play_array[i].get_size() << "   ";
		}
		cout << endl;
		// print out the temporary card
		cout << "Played Card: " << played_card << endl;
		confirm_turn(turn % amount_players);
	}
	return 0;
}
