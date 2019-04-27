#pragma once

#include <string>


namespace bullpgia {
	class Guesser {
		public:
			uint length;
			virtual std::string guess()=0;
			virtual void startNewGame(uint theLength) {length = theLength;}
			virtual void learn(std::string) {;}
 	};
}
