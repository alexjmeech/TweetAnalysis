#include "catch.hpp"
#include "String.h"
#include <cstring>

TEST_CASE("String class", "[string]")
{
	String testBase = "testing";
	char testCS[] = "testingCS";

	SECTION("COPY CONSTRUCTOR")
	{
		String s = testBase;
		String t = s;
		REQUIRE(s == testBase);
		REQUIRE(t == s);
		REQUIRE(t == testBase);
	}

	SECTION("COPY CSTRING CONSTRUCTOR")
	{
		String s = testCS;
		String t = testCS;
		REQUIRE(s == testCS);
		REQUIRE(t == testCS);
		REQUIRE(t == s);
	}

	SECTION("ASSIGNMENT OPERATOR")
	{
		String s;
		String t;
		s = testBase;
		t = s;
		REQUIRE(s == testBase);
		REQUIRE(t == s);
		REQUIRE(t == testBase);
	}

	SECTION("CSTRING ASSIGNMENT OPERATOR")
	{
		String s;
		String t;
		s = testCS;
		t = testCS;
		REQUIRE(s == testCS);
		REQUIRE(t == testCS);
		REQUIRE(t == s);
	}

	SECTION("EQUALITY OPERATOR")
	{
		String testCompare = "testing";
		String testCSCompare = String(testCS);
		REQUIRE(testBase == testCompare);
		REQUIRE(testCS == testCSCompare);
		REQUIRE(String("a") == String("a"));
	}

	SECTION("INEQUALITY OPERATOR")
	{
		String testCompare = "testing";
		String testCSCompare = String(testCS);
		REQUIRE(testBase != testCSCompare);
		REQUIRE(testCS != testCompare);
		REQUIRE(String("a") != String("b"));
	}

	SECTION("STRING APPEND OPERATOR")
	{
		String base = "base";
		String a = "a";
		String b = "b";
		String c = "c";
		REQUIRE((base += a) == String("basea"));
		REQUIRE((base += b) == String("baseab"));
		REQUIRE((base += c) == String("baseabc"));
	}

	SECTION("CSTRING APPEND OPERATOR")
	{
		String base = "base";
		char a[] = "a";
		char b[] = "b";
		char c[] = "c";
		REQUIRE((base += a) == String("basea"));
		REQUIRE((base += b) == String("baseab"));
		REQUIRE((base += c) == String("baseabc"));
	}

	SECTION("CHAR APPEND OPERATOR")
	{
		String base = "base";
		char a = 'a';
		char b = 'b';
		char c = 'c';
		REQUIRE((base += a) == String("basea"));
		REQUIRE((base += b) == String("baseab"));
		REQUIRE((base += c) == String("baseabc"));
	}

	SECTION("CHAR AT INDEX OPERATOR")
	{
		REQUIRE(testBase[0] == 't');
		REQUIRE(testBase[1] == 'e');
		REQUIRE(testBase[2] == 's');
	}

	SECTION("STRING STRING ADDITION OPERATOR")
	{
		String left = "left";
		String right = "right";

		REQUIRE((left + right) == String("leftright"));
		REQUIRE((right + left) == String("rightleft"));
		REQUIRE((left + right + left) == String("leftrightleft"));
	}

	SECTION("STRING CSTRING ADDITION OPERATOR")
	{
		String left = "left";
		char right[] = "right";
		char mid[] = "mid";

		REQUIRE((left + right) == String("leftright"));
		REQUIRE((left + right + right) == String("leftrightright"));
		REQUIRE((left + mid) == String("leftmid"));
	}

	SECTION("STRING CHAR ADDITION OPERATOR")
	{
		String left = "left";
		char r = 'r';
		char s = 's';

		REQUIRE((left + r) == String("leftr"));
		REQUIRE((left + r + r) == String("leftrr"));
		REQUIRE((left + s) == String("lefts"));
	}

	SECTION("CSTRING STRING ADDITION OPERATOR")
	{
		char left[] = "left";
		String right = "right";
		String mid = "mid";

		REQUIRE((left + right) == String("leftright"));
		REQUIRE((left + (left + right)) == String("leftleftright"));
		REQUIRE((left + mid) == String("leftmid"));

	}

	SECTION("CHAR STRING ADDITION OPERATOR")
	{
		String left = "left";
		String right = "right";
		char s = 's';

		REQUIRE((s + left) == String("sleft"));
		REQUIRE((s + right) == String("sright"));
		REQUIRE((s + (s + right)) == String("ssright"));
	}

	SECTION("GETLENGTH")
	{
		REQUIRE(testBase.getLength() == 7);
		REQUIRE(String("left").getLength() == 4);
		REQUIRE(String().getLength() == 0);
	}

	SECTION("SUBSTRING")
	{
		REQUIRE(testBase.substring(1, 3) == String("es"));
		REQUIRE(testBase.substring(0, 1) == String("t"));
		REQUIRE(testBase.substring(1, testBase.getLength()) == String("esting"));
	}

	SECTION("SUBSTRINGLENGTH")
	{
		REQUIRE(testBase.substringLength(1, 3) == String("est"));
		REQUIRE(testBase.substringLength(1, 1) == String("e"));
		REQUIRE(testBase.substringLength(1, 2) == String("es"));
	}

	SECTION("STRING SPLIT")
	{
		String toSplit = "atestingatestingatestinga";
		REQUIRE(toSplit.split(testBase).arrayLength() == 4);
		REQUIRE(toSplit.split(testBase)[0] == String("a"));
		REQUIRE(toSplit.split(testBase)[1] == String("a"));
	}

	SECTION("CSTRING SPLIT")
	{
		String toSplit = "atestingCSatestingCSatestingCSa";

		REQUIRE(toSplit.split(testCS).arrayLength() == 4);
		REQUIRE(toSplit.split(testCS)[0] == String("a"));
		REQUIRE(toSplit.split(testCS)[1] == String("a"));
	}

	SECTION("CHAR SPLIT")
	{
		String toSplit = "atatata";

		REQUIRE(toSplit.split('t').arrayLength() == 4);
		REQUIRE(toSplit.split('t')[0] == String("a"));
		REQUIRE(toSplit.split('t')[1] == String("a"));
	}

	SECTION("PREDICATE SPLIT")
	{
		String toSplit = "a.a.a.a";
		std::function<bool(char)> p = [](char c) -> bool { return ispunct(c); };
		REQUIRE(toSplit.split(p).arrayLength() == 4);
		REQUIRE(toSplit.split(p)[0] == String("a"));
		REQUIRE(toSplit.split(p)[1] == String("a"));
	}

	SECTION("STRING FIND")
	{
		String toSearch = "hiTESTINGhilo";
		REQUIRE(toSearch.find(testBase, false) == 2);
		bool foundFirst;
		bool foundSecond;
        
		try
		{
			toSearch.find(testBase, true);
			foundFirst = true;
		}
		catch (TextNotFoundException& e)
		{
			foundFirst = false;
		}
        
		try
		{
			toSearch.find(testBase, false, 4);
			foundFirst = true;
		}
		catch (TextNotFoundException& e)
		{
			foundSecond = false;
		}
        
		REQUIRE(foundFirst == false);
		REQUIRE(foundSecond == false);
	}

	SECTION("CSTRING FIND")
	{
		String toSearch = "hiTESTINGCShilo";
		REQUIRE(toSearch.find(testCS, false) == 2);
		bool foundFirst;
		bool foundSecond;
        
		try
		{
			toSearch.find(testBase, true);
			foundFirst = true;
		}
		catch (TextNotFoundException& e)
		{
			foundFirst = false;
		}
        
		try
		{
			toSearch.find(testBase, false, 4);
			foundFirst = true;
		}
		catch (TextNotFoundException& e)
		{
			foundSecond = false;
		}
        
		REQUIRE(foundFirst == false);
		REQUIRE(foundSecond == false);
	}

	SECTION("CHAR FIND")
	{
		String toSearch = "hiThilo";
		REQUIRE(toSearch.find('t', false) == 2);
		bool foundFirst;
		bool foundSecond;
		try
		{
			toSearch.find('t', true);
			foundFirst = true;
		}
		catch (TextNotFoundException& e)
		{
			foundFirst = false;
		}
        
		try
		{
			toSearch.find('t', false, 4);
			foundFirst = true;
		}
		catch (TextNotFoundException& e)
		{
			foundSecond = false;
		}
        
		REQUIRE(foundFirst == false);
		REQUIRE(foundSecond == false);
	}

	SECTION("GETHASHCODE")
	{
		REQUIRE(String().getHashCode() == 0);
		REQUIRE(String("a").getHashCode() == 97);
		REQUIRE(testBase.getHashCode() == 105951736336);
	}

	SECTION("TRIM")
	{
		String spaced = "   ha   ";
		String spaceOut = "  t t  ";
		REQUIRE(spaced.trim() == String("ha"));
		REQUIRE((' ' + testBase + ' ').trim() == testBase);
		REQUIRE(spaceOut.trim() == String("t t"));
	}

	SECTION("TRIMSTART")
	{
		String spaced = "   ha   ";
		String spaceOut = "  t t  ";
		REQUIRE(spaced.trimStart() == String("ha   "));
		REQUIRE((' ' + testBase).trimStart() == testBase);
		REQUIRE(spaceOut.trimStart() == String("t t  "));
	}

	SECTION("TRIMEND")
	{
		String spaced = "   ha   ";
		String spaceOut = "  t t  ";
		REQUIRE(spaced.trimEnd() == String("   ha"));
		REQUIRE((testBase + ' ').trimEnd() == testBase);
		REQUIRE(spaceOut.trimEnd() == String("  t t"));
	}

	SECTION("TOLOWER")
	{
		REQUIRE(String("A").toLower() == String("a"));
		REQUIRE(String("TESTING").toLower() == testBase);
		REQUIRE(String("B").toLower() != String("B"));
	}

	SECTION("TOUPPER")
	{
		REQUIRE(testBase.toUpper() == String("TESTING"));
		REQUIRE(testBase != testBase.toUpper());
		REQUIRE(String("a").toUpper() == String("A"));
	}

	SECTION("CLONE")
	{
		String testClone = testBase.clone();
		REQUIRE(testClone == testBase);
		REQUIRE(testClone.getLength() == testBase.getLength());
		REQUIRE((testClone + 'a') == (testBase + 'a'));
	}

	SECTION("C_STRING")
	{
		char testCmp[] = "testing";
		String csTestCmp = "testingCS";

		String a = "a";
		char csA[] = "a";

		REQUIRE(strcmp(testBase.c_string(), testCmp) == 0);
		REQUIRE(strcmp(csTestCmp.c_string(), testCS) == 0);
		REQUIRE(strcmp(a.c_string(), csA) == 0);
	}
}
