#pragma once
#include "Guesser.hpp"

#include "calculate.hpp"
using std::string;


/**
 * ConstantGuesser is a guesser that always guesses the same string. 
 */
class SmartGuesser: public bullpgia::Guesser {
		string myConstantString = "1234";
	public:
		string guess() override {
			return myConstantString;
		}

		void startNewGame(uint theLength) override;
		void learn(string response) override;
};
