#include <time.h>
#include <iostream>
#include <fstream> 
#include <string> 
#include <cstdlib> 
#include <limits> 

#include "card.h"
#include "deck.h"
#include "player.h"
using namespace std;

#define TEXTFILE "intro.txt"
#define PRINT_ALL_PLAYERS 0
#define TEMP_DECK 1
#define TURN 2
#define TEST -1

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
	cout << "Confirm Player" << x << " by typing " << "'" << x << "'" << " and pressing enter" << ": ";
	int temp=0;
	while (temp != x)
	{
		cin >> temp;
	}
}

COLOR FromString(const string & str)
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
	system("cls"); 
	display_intro(TEXTFILE);
	int amount_players;
	int flag = 0;

	cout << "\n***** Welcome *****" << endl;
	cout << "***** Uno Game *****\n" << endl;

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
	deck main_deck;
	main_deck.create();
	main_deck.quick_shuffle();
	player * play_array;
	play_array = new player[amount_players];
	for (int i = 0; i < amount_players; i++)
	{
		for (int k = 0; k < 7; k++)
		{
			card temp_card;
			temp_card = main_deck.draw();
			play_array[i].hand_add(temp_card);
		}
	}
	deck temp_deck;
	card played_card;
	card temp_card;
	int card_flag = 0;
	while (card_flag == 0)
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


#if TEST == PRINT_ALL_PLAYERS
	for (int i = 0; i < amount_players; i++)
	{
		cout << "player: " << i << endl;
		play_array[i].print();
	}
#endif
	srand(unsigned int(time(NULL)));
	int turn = rand() % amount_players;
	cout << "PLAYER " << turn << " is randomly selected to play first" << endl;
	confirm_turn(turn);

	bool force_draw_bool = false;
	int turn_flag = 1;
	int win = 0;
	while (win == 0)
	{
		system("cls");


#if TEST == TEMP_DECK
		temp_deck.print_deck();
#endif 

		player * curr_player = &play_array[turn%amount_players];

		cout << "PLAYER " << turn % amount_players << endl;

		if (force_draw_bool)
		{
			if (played_card.number == 10)
			{
				cout << "Forced Draw-2" << endl;
				card draw_2;
				for (int i = 0; i < 2; i++)
				{
					draw_2 = main_deck.draw();
					curr_player->hand_add(draw_2);
				}
			}
			if (played_card.number == 14)
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
		cout << "Cards remaining for each player: " << endl;
		for (int i = 0; i < amount_players; i++)
		{
			cout << "PLAYER " << i << ": " << play_array[i].get_size() << "   ";
		}
		cout << endl;
		cout << "Played Card: " << played_card << endl;
		cout << "PLAYER " << turn % amount_players << endl;

		curr_player->print();
		int check_flag = 0;
		int index;
		int size = curr_player->get_size();
		while (check_flag == 0)
		{
			cout << "which card do you want to play? " << endl;
			cout << "If you want to draw a card please enter '-1' " << endl;
			cout << "Type the index of the card and press enter: ";
			cin >> index;
			if (index == -1)
			{
				card draw_temp;
				draw_temp = main_deck.draw();
				cout << "DRAWN CARD: " << draw_temp << endl;
				if (draw_temp == played_card && draw_temp.color != wild)
				{

					int play_draw_flag = 0;
					while (play_draw_flag == 0)
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
			if (index >= 0 && index < size)
			{
				card temp = curr_player->peek(index);
				if (temp == played_card)
				{
					curr_player->hand_remove(index);
					temp_deck.add_card(temp);
					played_card = temp;
					if (played_card.color == wild)
					{
						int check_color = 0;
						COLOR temp_color;
						string str_color;
						while (check_color == 0)
						{
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

		if (curr_player->get_size() == 0)
		{
			win = 1;
			cout << "PLAYER " << turn % amount_players << " has won the game." << endl;
			break;
		}


		if (played_card.number == 11 && force_draw_bool == true)
		{
			if (turn_flag == 1)
				turn = turn + 2;
			else
				turn = turn - 2;
		}
		else if (played_card.number == 12 && force_draw_bool == true)
		{
			if (amount_players == 2)
			{
				turn = turn + 2;
			}
			else
			{
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
		else
		{
			if (turn_flag == 1)
				turn++;
			else
				turn--;
		}


		system("cls");
		cout << "Cards remaining for each player: " << endl;
		for (int i = 0; i < amount_players; i++)
		{
			cout << "PLAYER " << i << ": " << play_array[i].get_size() << "   ";
		}
		cout << endl;
		cout << "Played Card: " << played_card << endl;
		confirm_turn(turn%amount_players);

	}

	return 0;
}
