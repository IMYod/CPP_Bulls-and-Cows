#include "SmartGuesser.hpp"
#include <math.h>
#include <iostream>


using std::string, std::to_string, std::unordered_set;

string SmartGuesser::guess() {
	//strategy: guess any possible number
	string guess = *myset.begin();
	this->lastGuess = guess;
	return guess;
}

void SmartGuesser::startNewGame(uint theLength) {
	//insert all possible numbers to myset
	for (int i=0; i<pow(10.0,theLength); ++i){
		this->myset.insert(numToGuess(i,theLength));
	}
}
void SmartGuesser::learn(string response) {
	unordered_set<string> toRemove;
	//if number in myset is not match to the response -> insert it to the remove list
	for ( auto it = myset.begin(); it != myset.end(); ++it ){
		if (response.compare(bullpgia::calculateBullAndPgia(*it, lastGuess))!=0)
			toRemove.insert(*it);
	}

	//removes from myset be toRemve list
	for ( auto it = toRemove.begin(); it != toRemove.end(); ++it )
		myset.erase(*it);
}

//convert number to guess type by padding "0"
string numToGuess(int num, uint length){
	string guess = to_string(num);
	int numOfZeros = length - guess.length();
	for (int i=0; i<numOfZeros; ++i){
		guess = "0" + guess;
	}
	return guess;
}
