#define CATCH_CONFIG_RUNNER
#include "catch.hpp"
#include <ctime>
#include <iostream>
#include <fstream>
#include "String.h"
#include "Tweet.h"
#include "SentimentAnalyzer.h"
using namespace std;

int main(int argc, char* argv[])
{
	if (argc < 5)
	{
		Catch::Session().run(argc, argv);
		return 0;
	}
    
	std::time_t start = time(NULL);
	SentimentAnalyzer* cp = new SentimentAnalyzer();
	ifstream data(argv[1]);
	ifstream target(argv[2]);
	(*cp).train(data, target);
	data.close();
	target.close();
	ifstream testing(argv[3]);
	ofstream output(argv[4]);
	(*cp).analyze(testing, output);
	testing.close();
	output.close();
	delete cp;
	std::time_t end = time(NULL);
	cout << "TIME ELAPSED: " << end - start << " seconds" << endl;

	return 0;
}
