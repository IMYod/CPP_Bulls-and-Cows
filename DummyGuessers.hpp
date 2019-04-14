#pragma once
#include "Guesser.hpp"
using std::string;


/**
 * ConstantGuesser is a guesser that always guesses the same string. 
 */
class ConstantGuesser: public bullpgia::Guesser {
		string myConstantString;
	public:
		ConstantGuesser(const string& constantString) { myConstantString = constantString; }
		string guess() override {
			return myConstantString;
		}

		void startNewGame(uint theLength) override{ ;}
		void learn(string response) override{ ;}
};

/**
 * RandomGuesser is a guesser that guesses a random string.
 */
class RandomGuesser: public bullpgia::Guesser {
	string guess() override;

	void startNewGame(uint theLength) override{ ;}
	void learn(string response) override{ ;}
};
