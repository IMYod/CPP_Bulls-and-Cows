#include "SmartGuesser.hpp"
#include <math.h>
#include <iostream>
#include <algorithm>


using std::string, std::to_string, std::unordered_set;

string SmartGuesser::guess() {
	if (myset.size() < pow(10.0, 6)){
		//strategy: guess any possible number
		string guess = *myset.begin();
		this->lastGuess = guess;
		return guess;
	}
	else
		return guessByMinOccur(length, myset);
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

//strategy: secret...
string guessByMinOccur(uint length, unordered_set<string>& myset) {
	std::array <uint,2> occurs[10];
	for (int i=0; i<10; ++i){
		occurs[i][0]=0;
		occurs[i][1]=i;
	}
	
	for (auto it = myset.begin(); it != myset.end(); ++it )
		for (int i=0; i<(*it).length(); ++i)
			occurs[(*it)[i] -'0'][0]++;
	
	std::sort(occurs, occurs+10); //doesn't work
	string guess = "";
	for (int i=0; i<length; ++i){
		guess += std::to_string(occurs[i][1]);
	}
	return guess;
}
