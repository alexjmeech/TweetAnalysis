#include "WordExtraWeight.h"

WordExtraWeight::WordExtraWeight()
{
	word = String();
	weight = 0;
}

WordExtraWeight::WordExtraWeight(String& word, int weight)
{
	this->word = word;
	this->weight = weight;
}

String& WordExtraWeight::getWord()
{
	return word;
}

int WordExtraWeight::getWeight()
{
	return weight;
}
