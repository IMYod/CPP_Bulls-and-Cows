#include "calculate.hpp"
#include <string>
using std::string, std::to_string;

namespace bullpgia {
	const string calculateBullAndPgia(const string choice, const string guess){
		uint length = choice.length();
		int bools=0, pgia=0;
		bool choiceChecked[length]; //true if the digit didn't used for bool\pgia
		bool guessChecked[length];
		for (int i=0; i<length; ++i) { //intilize the arrays
			choiceChecked[i] = true;
			guessChecked[i] = true;
		}

		for (int i=0; i<length; ++i) { //check bool
			if (choice[i] == guess[i]){
				bools++;
				choiceChecked[i] = false;
				guessChecked[i] = false;
			}				
		}

		for (int i=0; i<length; ++i) //check pgia
			if (choiceChecked[i]) //not used
				for (int j=0; j<length; ++j)
					if (guessChecked[j] && choice[i] == guess[j]){ //not used
						choiceChecked[i] = false;
						guessChecked[j] = false;
						pgia++;
					}

		return (to_string(bools) +"," + to_string(pgia));
	}
}
