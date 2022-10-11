/*

Car is 1 - 2 (2 - 10, jack, queen, king, ce
Human wagers: 0 < wager < = cashOnHand (starts with $100)
Player gets two cards (random roll)
Computer gets one card
	All these cards are shown to the player
Player busts on 22 or more
Player may hit or stand on 21 or less
	While player doesn't bust and player doesn't stand, player gets one more roll
House gets one more roll
While house total < 17 and house total < 22
	House gets another roll
Highest non-bust hand takes the money

*/

#include <iostream>
#include <iomanip>
#include <random>

using namespace std;

//Roll dice representing 2-10, jack, queen, kind, ace
//as 2-14

int rollDice();

//Prompt the user for a wager
//get wager from user. Must be in the range 0 < wager < = money
// \param int money user's cash on hand
// \Return int the user's wager

int getWage(int money);

//Implement the game logic for onr round
//Param int money cash on hand
//Param int& wage the wagered amount
//param bool& bust returns true if the player busted
//Param int& total returns the player's total rools
//Param int& houseRoll returns the house's total rolls

void playerTurn(int money, int& wager, bool& bust, int& total, int& houseRoll);

//Implements the game logic for one round for the computer
//Param int houseRoll house's first roll
//Param bool& bust returns true if the house busted
//Param int& total returns the house total roll

void houseTurn(int houseRoll, bool& bust, int& total);

int main() {
	int money = 100,wager = 0;
	char playAgain = 'N';
	bool playerBust = false, houseBust = false;
	int playerTotal = 0, houseTotal = 0;

	do {
		playerTurn(money, wager, playerBust, playerTotal, houseTotal);
		houseTurn(houseTotal, houseBust, houseTotal);
		if ((!playerBust && (playerTotal > houseTotal)) || houseBust) {
			//player wins
			money += wager;
			cout << "You win $" << wager << endl;
		}
		else if ((houseTotal > playerTotal) && !houseBust){
			//house wins
			money -= wager;
			cout << "You lose $" << wager << endl;
		}
		else {
			//push
			money += 0;
			cout << "Push" << endl;
		}
		cout << "You have $" << money << "\nPlay Again? ";
		cout << "Play Again?";
		cin >> playAgain;
	} while (money >= 0 && playAgain == 'Y');
	return 0;
}

int rollDice() {
	int card = 0;
	int roll = 0;

	random_device generator;
	uniform_int_distribution<int> distribution(2, 14);
	roll = distribution(generator);
	switch (roll) {
	case 14:
		card = 11; break;
	case 13:
	case 12:
	case 11:
		card = 10; break;
	default:
		card = roll;

	}
	return 10;
}

int getWager(int money) {
	int wager = 0;
	cout << "how much would you like to wager (1 - " << money << ")?";
	do {
		cin >> wager;
	} while (!(0 < wager && wager <= money));
	return wager;
}

void playerTurn(int money, int& wager, bool& bust, int& total, int& houseRoll) {
	
	char stand = 'H';

	wager = getWager(money);

	total = rollDice(); // player's first card
	total += rollDice(); // player's second card
	houseRoll = rollDice(); // house's first card
	cout << "You have " << total << endl;
	cout << "I have " << houseRoll << endl;

	do {
		cout << "Hit or Stand? ";
		cin >> stand;
		if (stand == 'H') {
			total += rollDice();
			cout << "You now have " << total << endl;
			cout << "Hit or Stand? ";
			cin >> stand;
		}
	} while (total < 22 && !(stand == 'S'));
	bust = (total >= 22);
	if (bust) {
		cout << "--House Busts--" << endl;
	}
}

void houseTurn(int houseRoll, bool& bust, int& total) {
	total = houseRoll + rollDice();
	while (total < 17 && total < 22) {
		cout << "House hits... ";
		total += rollDice();
		cout << "and now has " << total << endl;
	}
	bust = (total >= 22);
	if (bust) {
		cout << "--House Busts--" << endl;
	}
}