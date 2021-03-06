/**
 * A demo program for bull-pgia.
 * 
 * @author Erel Segal-Halevi
 * @since  2019-04
 */


#include <iostream>
using namespace std;

#include "play.hpp"
#include "DummyChoosers.hpp"
#include "DummyGuessers.hpp"
#include "SmartGuesser.hpp"
#include "badkan.hpp"
#define COMMA ,

using namespace bullpgia;

/****Help function for our Tests******/////////
string numberToGuess(int num, uint length){
	string guess = to_string(num);
        int numOfZeros = length - guess.length();
        for (int i=0; i<numOfZeros; ++i)
		guess = "0" + guess;
        return guess;
}
/************************************/////////

int main() {

	badkan::TestCase testcase;
	int grade=0;
	int signal = setjmp(badkan::longjmp_buffer);
	if (signal == 0) {

	// BASIC TESTS - DO NOT CHANGE
        ConstantChooser c1234{"1234"}, c12345{"12345"}, c9999{"9999"},c456789{"456789"};
        ConstantGuesser g1234{"1234"}, g12345{"12345"}, g9999{"9999"},g456789{"456789"} ,g111111{"111111"}, g111121{"1111121"};

	testcase.setname("Calculate bull and pgia")
	.CHECK_OUTPUT(calculateBullAndPgia("1234","1234"), "4,0")      // 4 bull, 0 pgia
	.CHECK_OUTPUT(calculateBullAndPgia("1234","4321"), "0,4")      // 0 bull, 4 pgia
	.CHECK_OUTPUT(calculateBullAndPgia("123","1234"), "3,0");      // 3 bull, 0 pgia         
        
        /*******
	our tests
	*******/
        testcase.setname("Calculate bull and pgia tests")
	.CHECK_OUTPUT(calculateBullAndPgia("0",""), "0,0")      // 0 bull, 0 pgia            	
	.CHECK_OUTPUT(calculateBullAndPgia("4567","1254"), "0,2")      // 0 bull, 2 pgia            
	.CHECK_OUTPUT(calculateBullAndPgia("4567","4576"), "2,2")      // 2 bull, 2 pgia    
      	.CHECK_OUTPUT(calculateBullAndPgia("4567","7465"), "1,3")      // 1 bull, 3 pgia    
      	.CHECK_OUTPUT(calculateBullAndPgia("4567","6645"), "0,3")      // 0 bull, 3 pgia  
      	.CHECK_OUTPUT(calculateBullAndPgia("123456789","987654321"), "1,8")      // 1 bull, 8 pgia    
        .CHECK_OUTPUT(calculateBullAndPgia("123456789","987694321"), "0,8")      // 0 bull, 8 pgia  
        .CHECK_OUTPUT(calculateBullAndPgia("1111","1234"), "1,0")      // 1 bull, 0 pgia  
        .CHECK_OUTPUT(calculateBullAndPgia("15253545","25628978"), "1,1")      // 1 bull, 1 pgia  
        .CHECK_OUTPUT(calculateBullAndPgia("223344","332244"), "2,4")      // 2 bull, 4 pgia  
        .CHECK_OUTPUT(calculateBullAndPgia("223344","332244"), "2,4")      // 2 bull, 4 pgia          
        .CHECK_OUTPUT(calculateBullAndPgia("1","2"), "0,0")      // 0 bull, 0 pgia
        .CHECK_OUTPUT(calculateBullAndPgia("01234","00112"), "1,2")      // 1 bull, 2 pgia
        .CHECK_OUTPUT(calculateBullAndPgia("12","12"), "2,0")      // 4 bull, 0 pgia
        .CHECK_OUTPUT(calculateBullAndPgia("1","1"), "1,0")      // 4 bull, 0 pgia
        .CHECK_OUTPUT(calculateBullAndPgia("12","21"), "0,2")      // 0 bull, 2 pgia
        .CHECK_OUTPUT(calculateBullAndPgia("123","321"), "1,2")      // 1 bull, 3 pgia
        .CHECK_OUTPUT(calculateBullAndPgia("55","65"), "1,0")      // 1 bull, 0 pgia
        .CHECK_OUTPUT(calculateBullAndPgia("55","55"), "2,0")      // 2 bull, 0 pgia
        .CHECK_OUTPUT(calculateBullAndPgia("111","111"), "3,0")      // 3 bull, 0 pgia
        .CHECK_OUTPUT(calculateBullAndPgia("123","423"), "2,0")      // 2 bull, 0 pgia
        .CHECK_OUTPUT(calculateBullAndPgia("123","453"), "1,0")      // 1 bull, 0 pgia
        .CHECK_OUTPUT(calculateBullAndPgia("123","137"), "1,1")      // 1 bull, 1 pgia
        .CHECK_OUTPUT(calculateBullAndPgia("567","576"), "1,2")      // 1 bull, 2 pgia
        .CHECK_OUTPUT(calculateBullAndPgia("156","615"), "0,3")      // 0 bull, 3 pgia
	.CHECK_OUTPUT(calculateBullAndPgia("5","5"), "1,0")      // 1 bull, 0 pgia
        .CHECK_OUTPUT(calculateBullAndPgia("5","0"), "0,0")     // 0 bull, 0 pgia
        .CHECK_OUTPUT(calculateBullAndPgia("1154245","1425422"), "1,4")      // 1 bull, 4 pgia
	.CHECK_OUTPUT(calculateBullAndPgia("78878887","77778888"), "5,2")  // 5 bull, 2 pgia
	.CHECK_OUTPUT(calculateBullAndPgia("1634522","2641352"), "2,5") // 2 bull, 5 pgia
         .CHECK_OUTPUT(calculateBullAndPgia("2800215363","4764144670"), "0,3") 	
	.CHECK_OUTPUT(calculateBullAndPgia("9669656009","8683488398"), "1,1") 
	.CHECK_OUTPUT(calculateBullAndPgia("5342347096","7691607883"), "1,4") 
	.CHECK_OUTPUT(calculateBullAndPgia("2800215363","4764144670"), "0,3") 
	.CHECK_OUTPUT(calculateBullAndPgia("3963538307","8550276028"), "0,5") 
	.CHECK_OUTPUT(calculateBullAndPgia("6176315347","2562980031"), "0,4") 
	.CHECK_OUTPUT(calculateBullAndPgia("0708539772","5796457075"), "2,4") 
	.CHECK_OUTPUT(calculateBullAndPgia("8119989091","0596072852"), "0,3") 
	.CHECK_OUTPUT(calculateBullAndPgia("2800215363","4764144670"), "0,3") 
	.CHECK_OUTPUT(calculateBullAndPgia("6535782560","7407600135"), "0,5") 
	.CHECK_OUTPUT(calculateBullAndPgia("8568760179","8885937926"), "1,5") 
	.CHECK_OUTPUT(calculateBullAndPgia("5139381503","1556375681"), "1,5") 
	.CHECK_OUTPUT(calculateBullAndPgia("456830914934","132730091019"), "2,4") 	
	.CHECK_OUTPUT(calculateBullAndPgia("348686083500","183574332196"), "0,6") 
	.CHECK_OUTPUT(calculateBullAndPgia("715125238819","228107580690"), "1,7") 
	.CHECK_OUTPUT(calculateBullAndPgia("670275899751","472529586696"), "1,7") 
	.CHECK_OUTPUT(calculateBullAndPgia("157473257537","636168868739"), "1,3") 
	.CHECK_OUTPUT(calculateBullAndPgia("160464846405","888379121428"), "1,2") 
	.CHECK_OUTPUT(calculateBullAndPgia("670183690121","229575583455"), "0,5") 
	.CHECK_OUTPUT(calculateBullAndPgia("8119989091","0596072852"), "0,3") 
	.CHECK_OUTPUT(calculateBullAndPgia("301811152259","652257358652"), "2,4")
	.CHECK_OUTPUT(calculateBullAndPgia("978803761355","652239020177"), "0,8") 
	.CHECK_OUTPUT(calculateBullAndPgia("960273899838","068885053606"), "1,5") 
	.CHECK_OUTPUT(calculateBullAndPgia("605276988440","689446661781"), "2,6") 
         .CHECK_OUTPUT(calculateBullAndPgia("01234567899876543210","9876543210123456789"), "1,18") // 1 bull, 18 pgia                              
	.CHECK_OUTPUT(calculateBullAndPgia("1111222233334444555566667777888899995","2233333554845553212120100011201213133"), "0,20");  // 0 bull, 20 pgia                    	         
				            
//----------------------------------------------------------------------------------------------------//

	testcase.setname("Play with dummy choosers and guessers")
	.CHECK_EQUAL(play(c1234, g1234, 4, 100), 1)      // guesser wins in one turn.
	.CHECK_EQUAL(play(c1234, g9999, 4, 100), 101)    // guesser loses by running out of turns 
	.CHECK_EQUAL(play(c1234, g12345, 4, 100), 101)   // guesser loses technically by making an illegal guess (too long).
	.CHECK_EQUAL(play(c12345, g1234, 4, 100), 0);     // chooser loses technically by choosing an illegal number (too long).
        
        /*******
	our tests
	*******/

        testcase.setname("Our tests")
        .CHECK_EQUAL(play(c456789, g456789, 6, 100), 1)      // guesser wins in one turn.
        .CHECK_EQUAL(play(c456789, g456789, 6, 100), 1)      // guesser wins in one turn.
        .CHECK_EQUAL(play(c456789, g111111, 6, 100), 101)      // guesser loses by running out of turns
        .CHECK_EQUAL(play(c456789, g111121, 6, 100), 101)      // guesser loses by running out of turns  
        .CHECK_EQUAL(play(c456789, g1234, 5, 100), 0)     // chooser loses technically by choosing an illegal number (too long).
        .CHECK_EQUAL(play(c456789, g1234, 4, 100), 0)     // chooser loses technically by choosing an illegal number (too long).
        .CHECK_EQUAL(play(c456789, g1234, 3, 100), 0)     // chooser loses technically by choosing an illegal number (too long).
        .CHECK_EQUAL(play(c456789, g1234, 2, 100), 0)     // chooser loses technically by choosing an illegal number (too long).
        .CHECK_EQUAL(play(c456789, g1234, 1, 100), 0);     // chooser loses technically by choosing an illegal number (too long).
        
   

//------------------------------------------------------------------------------------------------//		

	testcase.setname("Play with smart guesser");
	RandomChooser randy;
	SmartGuesser smarty;
	for (uint i=0; i<100; ++i) {
		testcase.CHECK_EQUAL(play(randy, smarty, 4, 100)<=100, true);  // smarty should always win in at most 100 turns!
	}
       
        /*******
	our tests
	*******/
        testcase.setname("Play short games with smart guesser");

	for (uint i=0; i<100; ++i) {
		testcase.CHECK_EQUAL(play(randy, smarty, 3, 100)<=100, true);  // smarty should always win in at most 100 turns!
	}
	for (uint i=0; i<100; ++i) {
		testcase.CHECK_EQUAL(play(randy, smarty, 2, 100)<=100, true);  // smarty should always win in at most 100 turns!
	}
	for (uint i=0; i<100; ++i) {
		testcase.CHECK_EQUAL(play(randy, smarty, 1, 100)<=100, true);  // smarty should always win in at most 100 turns!
	}
	
	//some cases with 4 digits!!
	for (int i=800; i<1300; i++){
		ConstantChooser chooseAll { numberToGuess(i, 4)};
		testcase.CHECK_EQUAL(play(chooseAll, smarty, 4, 100)<=100, true);  // smarty should always win in at most 100 turns!        
	}


        testcase.setname("Play long games with smart guesser");
	
	for (uint i=0; i<10; ++i) {
		testcase.CHECK_EQUAL(play(randy, smarty, 5, 100000)<=100000, true);  // smarty should always win!
	}
	for (uint i=0; i<10; ++i) {
		testcase.CHECK_EQUAL(play(randy, smarty, 6, 100000)<=100000, true);  // smarty should always win!
	}
	
 
    grade = testcase.grade();
	} else {
		testcase.print_signal(signal);
		grade = 0;
	}
	cout << "Your grade is: "  << grade << endl;
	return 0;
}
