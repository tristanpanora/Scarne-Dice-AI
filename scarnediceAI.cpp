#include <random>
#include <iostream>
#include <stdlib.h>
#include <string>
using namespace std;

class Player
{
private:
	int points;
	int last_turn_score;
	string end_turn;
	int score;
	int target;
public:

	void get_total_score(int score)
	{
		this->score = score;
	}

	void get_target_score(int target)
	{
		this->target = target;
	}

	int total_score(int turnCheck)
	{
		last_turn_score = 0;
		points = 0;

		int roll = 0;
		random_device dev;
		mt19937 rng(dev());
		uniform_int_distribution<mt19937::result_type> dist6(1,6);

		while (end_turn != "p" && roll != 1 && turnCheck % 2 == 0) //P1's turn
		{

			roll = dist6(rng); //set roll equal to this
			cout << "You rolled: " << roll << endl;
			points += roll;

			if (roll == 1)
			{
				points = 0;
			}

			if (roll != 1)
			{
				cout << "Do you wish to end turn?" << endl;
				cin >> end_turn;
			}

		}

		int rollCount = 0;
		int AI_target_points = 12;

		while (roll != 1 && turnCheck % 2 != 0 && rollCount < 4 && points < AI_target_points && (score + points < target)) //Computer's turn
		{

			
			roll = dist6(rng); //set roll equal to this
			
			cout << "You rolled: " << roll << endl;
			points += roll;

			if (roll == 1)
			{
				points = 0;
				break;
			}

			if ((roll != 1 && rollCount < 4) || points < AI_target_points) //AI will do 4 rolls or until more than 12 points are scored
			{
				rollCount++;
				cout << "Do you wish to end turn?" << endl;

				if (rollCount == 4 || points >= AI_target_points || score + points >= target)
				{
					cout << "Yes.\n";
				}

				else if (rollCount < 4 && points < AI_target_points)
				{
					cout << "No." << endl;
				}
				
				
			}
		}

		rollCount = 0;
		
		//turnCheck++;
		//points = 0;
		end_turn = "";

		last_turn_score += points;

		cout << "Your score for this turn is: " << last_turn_score << endl;

		return last_turn_score;
	}

	


};

int main()
{
	Player player1;
	Player player2;
	string name = "";

	int player1_total_score = 0;
	int player2_total_score = 0;
	int turnCheck = 0; //even for p1
	//int seed = 0;

	cout << "Enter your name: ";
	cin >> name;

	const int target_score = 100;

	player2.get_target_score(target_score); //sends target score for computer to stop playing if it reaches target score

	do
	{

		if (turnCheck % 2 == 0)
		{
			cout << "-------" << name << "'s turn-------" << endl;
			player1_total_score += player1.total_score(turnCheck);
			cout << "P1 TOTAL: " << player1_total_score << endl;
			cout << "-----END " << name << "'s TURN-----\n\n" << endl;
			
		}
		
		else
		{
			cout << "-------Computer's turn-------" << endl;
			player2_total_score += player2.total_score(turnCheck);
			cout << "COMPUTER TOTAL: " << player2_total_score << endl;
			cout << "-----END COMPUTER's TURN-----\n\n" << endl;
			
		}

		player2.get_total_score(player2_total_score);

		turnCheck++;
		//seed += player1_total_score;
	
	} while (player1_total_score < target_score && player2_total_score < target_score);


	
	if (player1_total_score >= target_score)
	{
		cout << name << " wins!\n" << endl;
	}

	else if (player2_total_score >= target_score)
	{
		cout << "Computer wins!" << endl;
	}

	//total turn score for each player can be saved in main

	return 0;
}
