#include "calculate.hpp"
#include <string>
#include <iostream>
using std::string, std::to_string;

namespace bullpgia {
	const string calculateBullAndPgia(const string choice, const string guess){
		uint length = choice.length();
		int bools=0, pgia=0;
		uint choiceCount[10]; //count i digits in choice
		uint guessCount[10]; //count i digits in guess
		for (int i=0; i<10; ++i) { //intilize the arrays
			choiceCount[i] = 0;
			guessCount[i] = 0;
		}

		for (int i=0; i<length; ++i) {
			if (choice[i] == guess[i]) //check bool
				bools++;
			choiceCount[choice[i]-'0']++; //The index choice[i] as int
			guessCount[guess[i]-'0']++; //The index guess[i] as int
		}
		
		int sumBullAndPgia = 0;
		for (int i=0; i<10; ++i) {
			sumBullAndPgia += std::min(choiceCount[i], guessCount[i]);
		}
		
		return (to_string(bools) +"," + to_string(sumBullAndPgia - bools));
	}
}
