#include "SmartGuesser.hpp"
#include <math.h>
#include <iostream>
#include <algorithm>


using std::string, std::to_string, std::unordered_set, bullpgia::answer;

string SmartGuesser::guess() {
	string guess;
	if (myset.size()*pow(10.0, length) > 500000 || myset.size()<=2){
		//strategy: guess any possible number
		guess = *myset.begin();
	}
	else
		guess = guessByEfficiency();
	
	this->lastGuess = guess;
	return guess;
}

void SmartGuesser::startNewGame(uint theLength) {
	//insert all possible numbers to myset
	for (int i=0; i<pow(10.0,theLength); ++i){
		this->myset.insert(numToGuess(i,theLength));
	}
	length = theLength;
}
void SmartGuesser::learn(answer response) {
	//if number in myset is match to the response -> insert it to the new set
	myset.erase(lastGuess);
	for ( auto it = myset.begin(); it != myset.end(); ++it ){
		if (response==bullpgia::calculateBullAndPgia(*it, lastGuess)){
			newSet.insert(*it);
		}
	}
	myset=newSet;
	newSet.clear();

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
string SmartGuesser::guessByMinOccur() {
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

//strategy: secret...
string SmartGuesser::guessByEfficiency() {
	int maxNumber = pow(10.0, length);
	int possibleReply[length+1][length+1];
	
	int minOfMaximums = maxNumber; //very high number
	string bestGuess = "-1";


	for (int i=0; i<maxNumber; ++i){
		for (int j=0; j<=length; ++j)
			for (int k=0; k<=length; ++k)
				possibleReply[j][k]=0;

		string iAsString = numToGuess(i,length);
		for (auto it = myset.begin(); it != myset.end(); ++it ){
			answer posReply = bullpgia::calculateBullAndPgia(*it, iAsString);
			possibleReply[posReply.bull][posReply.pgia]++;		
		}

		int maxForI = 0;		
		for (int j=0; j<=length; ++j)
			for (int k=0; k<=length; ++k)
				if (possibleReply[j][k] > maxForI)
					maxForI = possibleReply[j][k];
		
		if (maxForI < minOfMaximums){
			minOfMaximums = maxForI;
			bestGuess = iAsString;
		}
	}
	return bestGuess;
}










