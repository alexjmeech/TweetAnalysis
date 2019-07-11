#ifndef TWEETRATING_H_
#define TWEETRATING_H_

class TweetRating
{
private:
	const bool positive;
public:
	TweetRating(bool positive) : positive(positive) {}

	bool isPositive();
};

#endif /* TWEETRATING_H_ */
