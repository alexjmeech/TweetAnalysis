#ifndef WORDEXTRAWEIGHT_H_
#define WORDEXTRAWEIGHT_H_

#include "String.h"

class WordExtraWeight
{
private:
	String word;
	int weight;
public:
	WordExtraWeight();

	WordExtraWeight(String& word, int weight);

	String& getWord();

	int getWeight();
};

#endif /* WORDEXTRAWEIGHT_H_ */
