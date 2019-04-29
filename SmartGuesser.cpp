#include "SmartGuesser.hpp"
#include <math.h>
#include <iostream>
#include <algorithm>
#include <bits/stdc++.h>


using std::string, std::to_string, std::unordered_set, bullpgia::answer;

string SmartGuesser::guess() {
	string guess;
	if (myset.size()<=2){
		guess = guessPossible();
	}
	else if (lastGuess == "-1"){ //first guess
		guess = "";
		for (int i=0; i<length; i++)
			guess += to_string(i);
	}
	else if (myset.size()*pow(10.0, length) < 100000) 
		guess = guessByEfficiency();
	/*else if (myset.size()*length < 500000) 
		guess = guessByMinOccur();*/
	else
		guess = guessPossible();
	
	this->lastGuess = guess;
	return guess;
}

void SmartGuesser::startNewGame(uint theLength) {
	//insert all possible numbers to myset
	for (int i=0; i<pow(10.0,theLength); ++i){
		this->myset.insert(numToGuess(i,theLength));
	}
	length = theLength;
	lastGuess="-1";
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

//strategy: guess any possible number
string SmartGuesser::guessPossible() {
	return *myset.begin();
}

//strategy: secret...
struct countDigits{char digit; int counter;};
bool cdCompare(countDigits left, countDigits right) {return left.counter < right.counter;}

string SmartGuesser::guessByMinOccur() {
	countDigits occurs[10];
	for (int i=0; i<10; ++i){
		occurs[i].counter=0;
		occurs[i].digit = '0'+i;
	}
	
	for (auto it = myset.begin(); it != myset.end(); ++it )
		for (int i=0; i<(*it).length(); ++i)
			occurs[(*it)[i] -'0'].counter++;

	/*for (int i=0; i<10; ++i){
		std::cout << "The digit " << occurs[i].digit << " occurs " << occurs[i].counter << " times" << std::endl;
	}*/
	
	std::sort(occurs, occurs+10, cdCompare); //doesn't work
	string guess = "";
	for (int i=0; i<length; ++i){
		guess += occurs[i].digit;
	}

	if (guess==lastGuess)
		return guessPossible();

	std::vector<int> arr;
	for (int i=0; i<length; ++i)
		arr.push_back(i);
	
	string randGuess="";
	std::random_shuffle(arr.begin(), arr.end());
	for (std::vector<int>::iterator i=arr.begin(); i!=arr.end(); ++i)
		randGuess += occurs[(*i)].digit;

	return randGuess;
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










