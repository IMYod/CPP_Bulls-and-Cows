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


int main() {

	badkan::TestCase testcase;
	int grade=0;
	int signal = setjmp(badkan::longjmp_buffer);
	if (signal == 0) {

		// BASIC TESTS - DO NOT CHANGE
        ConstantChooser c1234{"1234"}, c12345{"12345"}, c9999{"9999"},c456789{"456789"};
        ConstantGuesser g1234{"1234"}, g12345{"12345"}, g9999{"9999"},g456789{"456789"},g11111{"111111"}g111121{"1111121"};

		testcase.setname("Calculate bull and pgia")
		.CHECK_OUTPUT(calculateBullAndPgia("1234","1234"), "4,0")      // 4 bull, 0 pgia
		.CHECK_OUTPUT(calculateBullAndPgia("1234","4321"), "0,4")      // 0 bull, 4 pgia
		.CHECK_OUTPUT(calculateBullAndPgia("123","1234"), "3,0")      // 3 bull, 0 pgia         
		.CHECK_OUTPUT(calculateBullAndPgia("12","1234"), "2,0")      // 2 bull, 0 pgia
		.CHECK_OUTPUT(calculateBullAndPgia("1","1234"), "1,0")      // 1 bull, 0 pgia
		.CHECK_OUTPUT(calculateBullAndPgia("4567","1254"), "0,1")      // 0 bull, 1 pgia            
		.CHECK_OUTPUT(calculateBullAndPgia("4567","4576"), "2,2")      // 2 bull, 2 pgia    
      	.CHECK_OUTPUT(calculateBullAndPgia("4567","6547"), "1,3")      // 1 bull, 3 pgia    
      	.CHECK_OUTPUT(calculateBullAndPgia("4567","6549"), "0,3")      // 0 bull, 3 pgia  
      	.CHECK_OUTPUT(calculateBullAndPgia("123456789","987654321"), "1,9")      // 1 bull, 9 pgia    
        .CHECK_OUTPUT(calculateBullAndPgia("123456789","987694321"), "1,9")      // 0 bull, 10 pgia  
        .CHECK_OUTPUT(calculateBullAndPgia("1234567895555484488445224452145","5"), "1,9")      // 0 bull, 8 pgia  
            
           



            
            ;

		testcase.setname("Play with dummy choosers and guessers")
		.CHECK_EQUAL(play(c1234, g1234, 4, 100), 1)      // guesser wins in one turn.
		.CHECK_EQUAL(play(c1234, g9999, 4, 100), 101)    // guesser loses by running out of turns 
		.CHECK_EQUAL(play(c1234, g12345, 4, 100), 101)   // guesser loses technically by making an illegal guess (too long).
		.CHECK_EQUAL(play(c12345, g1234, 4, 100), 0)     // chooser loses technically by choosing an illegal number (too long).
            
          /*our tests*/
		.CHECK_EQUAL(play(c456789, g456789, 6, 100), 1)      // guesser wins in one turn.
		.CHECK_EQUAL(play(c456789, g111111, 6, 100), 101)      // guesser loses by running out of turns
        .CHECK_EQUAL(play(c456789, g111121, 6, 100), 101)      // guesser loses by running out of turns         
		.CHECK_EQUAL(play(c456789, g1234, 4, 100), 0)     // chooser loses technically by choosing an illegal number (too long).
        .CHECK_EQUAL(play(c456789, g1234, 3, 100), 0)     // chooser loses technically by choosing an illegal number (too long).
        .CHECK_EQUAL(play(c456789, g1234, 2, 100), 0)     // chooser loses technically by choosing an illegal number (too long).
        .CHECK_EQUAL(play(c456789, g1234, 1, 100), 0)     // chooser loses technically by choosing an illegal number (too long).
   

		;

		testcase.setname("Play with smart guesser");
		RandomChooser randy;
		SmartGuesser smarty;
		for (uint i=0; i<100; ++i) {
			testcase.CHECK_EQUAL(play(randy, smarty, 4, 100)<=10, true);  // smarty should always win in at most 10 turns!
		}

    grade = testcase.grade();
	} else {
		testcase.print_signal(signal);
		grade = 0;
	}
	cout << "Your grade is: "  << grade << endl;
	return 0;
}
