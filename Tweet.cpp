#include "Tweet.h"

Tweet::Tweet(long id, String& author, String& message)
{
	this->id = id;
	this->author = author;
	this->message = message;
}

Tweet::Tweet(const Tweet& copy)
{
	this->id = copy.id;
	this->author = copy.author;
	this->message = copy.message;
    
	if (copy.rating != nullptr)
	{
		this->rating = new TweetRating(copy.rating->isPositive());
	}
}

Tweet::~Tweet()
{
	delete rating;
}

Tweet& Tweet::operator=(const Tweet& copy)
{
	if (this != &copy)
	{
		this->id = copy.id;
		this->author = copy.author;
		this->message = copy.message;
        
		if (this->rating != nullptr)
		{
			delete this->rating;
		}
        
		if (copy.rating != nullptr)
		{
			this->rating = new TweetRating(copy.rating->isPositive());
		}
		else
		{
			this->rating = nullptr;
		}
	}
    
	return *this;
}

long Tweet::getId()
{
	return id;
}

String Tweet::getAuthor()
{
	return author;
}

String Tweet::getMessage()
{
	return message;
}

bool Tweet::isRated()
{
	return rating != nullptr;
}

TweetRating*& Tweet::getRating()
{
	return rating;
}
