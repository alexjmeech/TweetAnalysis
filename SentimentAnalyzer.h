#ifndef SENTIMENTANALYZER_H_
#define SENTIMENTANALYZER_H_

#include <fstream>
#include "String.h"
#include "Tweet.h"
#include "WordExtraWeight.h"
#include <unordered_map>
using namespace std;

struct KeyHasher
{
	std::size_t operator()(const String& string) const
	{
		using std::size_t;
		using std::hash;

		long h = string.getHashCode();
		return static_cast<size_t>(h);
	}
};

class SentimentAnalyzer
{
private:
	unordered_map<String, int, KeyHasher> wordWeights;

	void learnTweet(Tweet&);
	int rateTweet(Tweet&);
public:
	SentimentAnalyzer();

	void train(ifstream&, ifstream&);

	void analyze(ifstream&, ofstream&);
};

#endif /* SENTIMENTANALYZER_H_ */
