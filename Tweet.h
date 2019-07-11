#ifndef TWEET_H_
#define TWEET_H_

#include "String.h"
#include "TweetRating.h"
using namespace std;

class Tweet
{
private:
	long id;
	String author;
	String message;
	TweetRating* rating = nullptr;
public:
	Tweet(long id, String& author, String& message);

	Tweet(const Tweet& copy);

	~Tweet();

	Tweet& operator=(const Tweet& copy);

	long getId();

	String getAuthor();

	String getMessage();

	bool isRated();

	TweetRating*& getRating();
};

#endif /* TWEET_H_ */
