#include "SentimentAnalyzer.h"
using namespace std;

bool isPunctuation(char c)
{
	return ispunct(c) && c != '@' && c != '\'';
}

int countCapitals(String& word)
{
	int caps = 0;
	for (unsigned int i = 0; i < word.getLength(); i++)
	{
		if (isupper(word[i]))
		{
			caps++;
		}
	}

	return caps;
}

bool isNeutral(String& word)
{
	if (word == "the"
			|| word == "a"
			|| word == "i"
			|| word == "he"
			|| word == "she"
			|| word == "they"
			|| word == "lol"
			|| word == "it"
			|| word == "is"
			|| word == "was"
			|| word == "be"
			|| word == "are"
			|| word == "were"
			|| word == "to"
			|| word == "do"
			|| word == "had"
			|| word == "yet"
			|| word == "for"
			|| word == "me"
			|| word == "you"
			|| word == "because"
			|| word == "bc"
			|| word == "cuz"
			|| word == "cos"
			|| word == "of"
			|| word == "my"
			|| word == "today"
			|| word == "yesterday"
			|| word == "and"
			|| word == "at"
			|| word == "when"
			|| word == "that"
			|| word == "i'm"
			|| word == "days"
			|| word == "this"
			|| word == "now"
			|| word == "them"
			|| word == "in"
			|| word == "week"
			|| word == "go"
			|| word == "another"
			|| word == "getting"
			|| word == "too"
			|| word == "has"
			|| word == "have"
			|| word == "got"
			|| word == "where"
			|| word == "it's"
			|| word == "really"
			|| word == "up"
			|| word == "either"
			|| word == "him"
			|| word == "her"
			|| word == "im"
			|| word == "am"
			|| word == "this"
			|| word == "that"
			|| word == "you'll"
			|| word == "let's"
			|| word == "www"
			|| word == "org"
			|| word == "com"
			|| word == "we're"
			|| word == "tinyurl"
			|| word == "who"
			|| word == "us"
			|| word == "went"
			|| word == "any"
			|| word == "as"
			|| word == "or"
			|| word == "twitpic"
			|| word == "i've"
			|| word == "could"
			|| word == "yes"
			|| word == "you're"
			|| word == "someone"
			|| word == "we"
			|| word == "going"
			|| word == "so"
			|| word == "here"
			|| word == "will"
			|| word == "http"
			|| word == "its"
			|| word == "with"
			|| word == "u"
			|| word == "if"
	)
	{
		return true;
	}

	if (word.getLength() > 0 && word[0] == '@')
	{
		return true;
	}
    
	char* c_string = word.c_string();
    
	if (atoi(c_string) != 0)
	{
		delete[] c_string;
		return true;
	}
    
	delete[] c_string;

	return false;
}

bool doesNegate(String& word)
{
	if (word == "no" || word == "not" || word == "doesnt" || word == "hasnt" || word == "wasnt" || word == "isnt" || word == "dont" || word == "cant" || word == "but" || word == "never" || word == "didnt")
	{
		return true;
	}
    
	if (word.getLength() > 3 && word.substring(word.getLength() - 3, word.getLength()) == "n't")
	{
		return true;
	}

	return false;
}

ArrayWrapper<WordExtraWeight> simplifySentence(String& sentence, bool multipliers)
{
	ArrayWrapper<String> words = sentence.split(' ', true);
	WordExtraWeight* weights = new WordExtraWeight[words.arrayLength()];
	int recorded = 0;
	bool negated = false;
    
	for (unsigned int i = 0; i < words.arrayLength(); i++)
	{
		String word = words[i].clone().toLower().trim();
        
		if (word.getLength() == 0)
		{
			continue;
		}
        
		if (isNeutral(word))
		{
			continue;
		}
        
		if (doesNegate(word))
		{
			if (multipliers)
			{
				negated = !negated;
			}
            
			continue;
		}
        
		int weight = 1;
		if (multipliers)
		{
			if (countCapitals(words[i]) > (0.5 * word.getLength()))
			{
				weight *= 2;
			}

			if (negated)
			{
				negated = false;
				weight *= -1;
			}
		}
        
		weights[recorded++] = WordExtraWeight(word, weight);
	}

	return ArrayWrapper<WordExtraWeight>(weights, recorded, true);
}

void SentimentAnalyzer::learnTweet(Tweet& tweet)
{
	if (!tweet.isRated())
	{
		return;
	}
    
	bool positive = tweet.getRating()->isPositive();
	ArrayWrapper<String> sentences = tweet.getMessage().split(isPunctuation);
    
	for (unsigned int i = 0; i < sentences.arrayLength(); i++)
	{
		if (sentences[i].getLength() < 1)
		{
			continue;
		}
        
		ArrayWrapper<WordExtraWeight> simplified = simplifySentence(sentences[i], false);
        
		for (unsigned int ii = 0; ii < simplified.arrayLength(); ii++)
		{
			WordExtraWeight weighted = simplified[ii];
			int weight = positive ? 1 : -1;
            
			if (wordWeights.find(weighted.getWord()) != wordWeights.end())
			{
				wordWeights[weighted.getWord()] += weight;
			}
			else
			{
				wordWeights[weighted.getWord()] = weight;
			}
		}
	}
}

int SentimentAnalyzer::rateTweet(Tweet& tweet)
{
	int weight = 0;
	int wordsCounted = 0;
	ArrayWrapper<String> sentences = tweet.getMessage().split('.', true);
    
	for (unsigned int i = 0; i < sentences.arrayLength(); i++)
	{
		if (sentences[i].getLength() < 1)
		{
			continue;
		}
        
		ArrayWrapper<WordExtraWeight> simplified = simplifySentence(sentences[i], true);
        
		for (unsigned int ii = 0; ii < simplified.arrayLength(); ii++)
		{
			WordExtraWeight weighted = simplified[ii];
            
			if (wordWeights.find(weighted.getWord()) != wordWeights.end())
			{
				wordsCounted++;
				weight += weighted.getWeight() * wordWeights[weighted.getWord()];
			}
		}
	}

	weight += (wordsCounted / 2);

	tweet.getRating() = new TweetRating(weight >= 0);

	return weight;
}

SentimentAnalyzer::SentimentAnalyzer()
{
	this->wordWeights.reserve(1500000);
}

void SentimentAnalyzer::train(ifstream& tweets, ifstream& ratings)
{
	String line;
	cout << "Loading Data" << endl;
    
	if (tweets.good())
	{
		getline(tweets, line);
	}
	else
	{
		return;
	}
    
	if (ratings.good())
	{
		getline(ratings, line);
	}
	else
	{
		return;
	}
    
	char* c_string;
    
	while (tweets.good() && ratings.good())
	{
		getline(tweets, line, ',');
        
		if (line == "")
		{
			continue;
		}
        
		c_string = line.c_string();
		int num = std::atoi(c_string);
		delete[] c_string;
		getline(tweets, line, ',');
		c_string = line.c_string();
		long id = std::atol(c_string);
		delete[] c_string;
		getline(tweets, line, ',');
		String author = line.clone();
		getline(tweets, line);
		String message = line.clone();
		Tweet tweet(id, author, message);

		getline(ratings, line, ',');
		c_string = line.c_string();
		int rnum = atoi(c_string);
		delete[] c_string;
		getline(ratings, line, ',');
		c_string = line.c_string();
		int rating = atoi(c_string);
		delete[] c_string;
		getline(ratings, line);
		c_string = line.c_string();
		long rid = atol(c_string);
		delete[] c_string;
        
		if (rnum == num && rid == id)
		{
			tweet.getRating() = new TweetRating(rating == 4);
		}
        
		learnTweet(tweet);
	}
    
	cout << "Data Loaded" << endl;

	cout << "Trained!" << endl;
}

void SentimentAnalyzer::analyze(ifstream& tweets, ofstream& ratings)
{
	cout << "Analyzing" << endl;
	String line;
    
	if (tweets.good())
	{
		getline(tweets, line);
	}
	else
	{
		return;
	}
    
	if (!ratings.good())
	{
		return;
	}
    
	char* c_string;
    
	while (tweets.good())
	{
		getline(tweets, line, ',');
        
		if (line == "")
		{
			continue;
		}
        
		c_string = line.c_string();
		int num = std::atoi(c_string);
		delete[] c_string;
		getline(tweets, line, ',');
		c_string = line.c_string();
		long id = std::atol(c_string);
		delete[] c_string;
		getline(tweets, line, ',');
		String author = line.clone();
		getline(tweets, line);
		String message = line.clone();
		Tweet tweet(id, author, message);
		rateTweet(tweet);

		ratings << '\"' << tweet.getId() << '\"' << ',' << '\"' << (tweet.getRating()->isPositive() ? '4' : '0') << '\"' << endl;
	}
    
	cout << "Analysis Complete" << endl;
}
