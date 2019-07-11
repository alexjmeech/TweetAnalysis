#include "String.h"
#include <cctype>
#include <cstring>
#include <limits>
using namespace std;

long String::getHash(String& of)
{
	return of.getHashCode();
}

String::String()
{
	bufferSize = 15;
	buffer = new char[bufferSize];
	length = 0;
	initialize();
}

String::String(const char cString[])
{
	length = strlen(cString);
	bufferSize = length + 15;
	buffer = new char[bufferSize];
	initialize();
    
	for (unsigned int i = 0; i < length; i++)
	{
		buffer[i] = cString[i];
	}
}

String::String(const String& copyFrom)
{
	length = copyFrom.length;
	bufferSize = copyFrom.bufferSize;
	buffer = new char[bufferSize];
	initialize();
    
	for (unsigned int i = 0; i < length; i++)
	{
		buffer[i] = copyFrom.buffer[i];
	}
}

String::String(unsigned int bufferSize)
{
	length = 0;
	this->bufferSize = bufferSize;
	buffer = new char[bufferSize];
	initialize();
}

String::~String()
{
	delete[] buffer;
}

void String::initialize(int start)
{
	for (unsigned int i = start; i < bufferSize; i++)
	{
		buffer[i] = '\0';
	}
}

String& String::operator=(const String& copy)
{
	if (this != &copy)
	{
		delete[] buffer;
		length = copy.length;
		bufferSize = copy.bufferSize;
		buffer = new char[bufferSize];
		initialize();
        
		for (unsigned int i = 0; i < length; i++)
		{
			buffer[i] = copy.buffer[i];
		}
	}
    
	return *this;
}

String& String::operator=(const char copy[])
{
	length = strlen(copy);
	bufferSize = length + 15;
	buffer = new char[bufferSize];
    
	for (unsigned int i = 0; i < length; i++)
	{
		buffer[i] = copy[i];
	}

	return *this;
}

bool operator==(const String& base, const String& other)
{
	if (base.length != other.length)
	{
		return false;
	}
    
	for (unsigned int i = 0; i < base.length; i++)
	{
		if (base.buffer[i] != other.buffer[i])
		{
			return false;
		}
	}

	return true;
}

bool operator!=(const String& base, const String& other)
{
	return !(base == other);
}

String& String::operator+=(const String& add)
{
	if (length + add.length >= bufferSize)
	{
		char* oldBuffer = buffer;
		bufferSize = length + add.length + 15;
		buffer = new char[bufferSize];
		initialize();
        
		for (unsigned int i = 0; i < length; i++)
		{
			buffer[i] = oldBuffer[i];
		}
        
		delete[] oldBuffer;
	}
    
	unsigned int index = length;
    
	for (unsigned int i = 0; i < add.length; i++)
	{
		buffer[index++] = add.buffer[i];
	}
    
	length += add.length;

	return *this;
}

String& String::operator+=(const char add[])
{
	if (length + strlen(add) >= bufferSize)
	{
		char* oldBuffer = buffer;
		bufferSize = length + strlen(add) + 15;
		buffer = new char[bufferSize];
		initialize();
        
		for (unsigned int i = 0; i < length; i++)
		{
			buffer[i] = oldBuffer[i];
		}
        
		delete[] oldBuffer;
	}
    
	unsigned int index = length;
    
	for (unsigned int i = 0; i < strlen(add); i++)
	{
		buffer[index++] = add[i];
	}
    
	length += strlen(add);

	return *this;
}

String& String::operator+=(const char add)
{
	if (length + 1 >= bufferSize)
	{
		char* oldBuffer = buffer;
		bufferSize = length + 16;
		buffer = new char[bufferSize];
		initialize();
        
		for (unsigned int i = 0; i < length; i++)
		{
			buffer[i] = oldBuffer[i];
		}
        
		delete[] oldBuffer;
	}
    
	buffer[length++] = add;

	return *this;
}

char& String::operator[](const unsigned int index)
{
	if (index >= length)
	{
		throw InvalidArgumentSizeException();
	}

	return buffer[index];
}

String operator+(const String& base, const String& add)
{
	String newString(base.length + add.length + 15);
	unsigned int index = 0;
    
	for (unsigned int i = 0; i < base.length; i++)
	{
		newString.buffer[index++] = base.buffer[i];
	}
    
	for (unsigned int i = 0; i < add.length; i++)
	{
		newString.buffer[index++] = add.buffer[i];
	}
    
	newString.length = base.length + add.length;

	return newString;
}

String operator+(const String& base, const char add[])
{
	String newString(base.length + strlen(add) + 15);
	unsigned int index = 0;
    
	for (unsigned int i = 0; i < base.length; i++)
	{
		newString.buffer[index++] = base.buffer[i];
	}
    
	for (unsigned int i = 0; i < strlen(add); i++)
	{
		newString.buffer[index++] = add[i];
	}
    
	newString.length = base.length + strlen(add);

	return newString;
}

String operator+(const String& base, const char add)
{
	String newString(base.length + 16);
	unsigned int index = 0;
    
	for (unsigned int i = 0; i < base.length; i++)
	{
		newString.buffer[index++] = base.buffer[i];
	}
    
	newString.buffer[index++] = add;
	newString.length = base.length + 1;

	return newString;
}

String operator+(const char add[], const String& base)
{
	String newString(base.length + strlen(add) + 15);
	unsigned int index = 0;
    
	for (unsigned int i = 0; i < strlen(add); i++)
	{
		newString.buffer[index++] = add[i];
	}
    
	for (unsigned int i = 0; i < base.length; i++)
	{
		newString.buffer[index++] = base.buffer[i];
	}
    
	newString.length = base.length + strlen(add);

	return newString;
}

String operator+(const char add, const String& base)
{
	String newString(base.length + 16);
	unsigned int index = 0;
	newString.buffer[index++] = add;
    
	for (unsigned int i = 0; i < base.length; i++)
	{
		newString.buffer[index++] = base.buffer[i];
	}
    
	newString.length = base.length + 1;

	return newString;
}

ostream& operator<<(ostream& stream, const String& string)
{
	if (string.length > 0)
	{
		for (unsigned int i = 0; i < string.length; i++)
		{
			stream << string.buffer[i];
		}
	}

	return stream;
}

istream& operator>>(istream& stream, String& string)
{
	delete[] string.buffer;
	string.length = 0;
	string.bufferSize = 15;
	string.buffer = new char[string.bufferSize];
	string.initialize();

	char c;
    
	while (stream.get(c) && !isspace(c))
	{
		string += c;
	}

	return stream;
}

istream& getline(istream& stream, String& string)
{
	return getline(stream, string, '\n');
}

istream& getline(istream& stream, String& string, char stop)
{
	delete[] string.buffer;
	string.length = 0;
	string.bufferSize = 15;
	string.buffer = new char[string.bufferSize];
	string.initialize();

	char c;
    
	while (stream.get(c) && c != stop)
	{
		string += c;
	}

	return stream;
}

unsigned int String::getLength()
{
	return length;
}

String String::substring(unsigned int start, unsigned int end)
{
	if (start >= this->length || end > this->length || end < start)
	{
		throw InvalidArgumentSizeException();
	}
    
	String newString((end - start) + 15);

	newString.length = (end - start);
    
	for (unsigned int i = 0; i < newString.length; i++)
	{
		newString.buffer[i] = buffer[start + i];
	}

	return newString;
}

String String::substringLength(unsigned int start, unsigned int length)
{
	if (start >= this->length || start + length > this->length)
	{
		throw InvalidArgumentSizeException();
	}
    
	String newString(length + 15);

	newString.length = length;
    
	for (unsigned int i = 0; i < length; i++)
	{
		newString.buffer[i] = buffer[start + i];
	}

	return newString;
}

ArrayWrapper<String> String::split(String& text, bool usesCase)
{
	if (text.length > length)
	{
		String* array = new String[1];
		array[0] = *this;
		return ArrayWrapper<String>(array, 1, true);
	}
    
	int count = 0;
	String* array = new String[length];

	unsigned int lastInstance = 0;
    
	for (unsigned int i = 0; i < length; i++)
	{
		bool found = true;
        
		for (unsigned int ii = 0; ii < text.length; ii++)
		{
			if (usesCase)
			{
				if (buffer[i + ii] != text.buffer[ii])
				{
					found = false;
					break;
				}
			}
			else
			{
				if (tolower(buffer[i + ii]) != tolower(text.buffer[ii]))
				{
					found = false;
					break;
				}
			}
		}

		if (found)
		{
			count++;
			array[count - 1] = substringLength(lastInstance, i - lastInstance);
			lastInstance = i + text.length;
		}
	}

	if (count == 0)
	{
		count = 1;
		array[0] = *this;
	}
	else if (lastInstance < length)
	{
		array[count++] = substringLength(lastInstance, length - lastInstance);
	}

	return ArrayWrapper<String>(array, count, true);
}

ArrayWrapper<String> String::split(const char text[], bool usesCase)
{
	String t = String(text);
	return split(t, usesCase);
}

ArrayWrapper<String> String::split(const char text, bool usesCase)
{
	String t = String();
	t += text;
	return split(t, usesCase);
}

ArrayWrapper<String> String::split(function<bool(char)> shouldSplit)
{
	if (length < 1)
	{
		String* array = new String[1];
		array[0] = *this;
		return ArrayWrapper<String>(array, 1, true);
	}
    
	int count = 0;
	String* array = new String[length];

	unsigned int lastInstance = 0;
	for (unsigned int i = 0; i < length; i++)
	{
		if (shouldSplit(buffer[i]))
		{
			count++;
			array[count - 1] = substringLength(lastInstance, i - lastInstance);
			lastInstance = i + 1;
		}
	}

	if (count == 0)
	{
		count = 1;
		array[0] = *this;
	}
	else if (lastInstance < length)
	{
		array[count++] = substringLength(lastInstance, length - lastInstance);
	}

	return ArrayWrapper<String>(array, count, true);
}

unsigned int String::find(String& text, bool usesCase, unsigned int start)
{
	if (start + text.length > length)
	{
		throw TextNotFoundException();
	}
	for (unsigned int i = start; i < length; i++)
	{
		bool found = true;
        
		for (unsigned int ii = 0; ii < text.length; ii++)
		{
			if (usesCase)
			{
				if (buffer[i + ii] != text.buffer[ii])
				{
					found = false;
					break;
				}
			}
			else
			{
				if (tolower(buffer[i + ii]) != tolower(text.buffer[ii]))
				{
					found = false;
					break;
				}
			}
		}

		if (found)
		{
			return i;
		}
	}

	throw TextNotFoundException();
}

unsigned int String::find(const char text[], bool usesCase, unsigned int start)
{
	String t = String(text);
	return find(t, usesCase, start);
}

unsigned int String::find(const char text, bool usesCase, unsigned int start)
{
	String t = String();
	t += text;
	return find(t, usesCase, start);
}

long String::getHashCode() const
{
	long hash = 0;
    
	for (unsigned int i = 0; i < length; i++)
	{
		hash = 31 * hash + buffer[i]; // Hashing equation from Java
	}

	return hash;
}

String String::trim()
{
	if (length == 0)
	{
		return String();
	}
    
	char* arr = new char[length + 1];
	int count = 0;
	int spaces = 0;
    
	for (unsigned int i = 0; i < length; i++)
	{
		if (isspace(buffer[i]))
		{
			if (count > 0)
			{
				spaces++;
			}
			continue;
		}
		else
		{
			for (unsigned int ii = i - spaces; ii < i; ii++)
			{
				arr[count++] = buffer[ii];
			}
			spaces = 0;
			arr[count++] = buffer[i];
		}
	}
    
	if (count > 0)
	{
		arr[count] = '\0';
	}
	else
	{
		arr[0] = '\0';
	}

	String out =  String(arr);
	delete[] arr;
	return out;
}

String String::trimStart()
{
	if (length == 0)
	{
		return String();
	}
    
	char* arr = new char[length + 1];
	int count = 0;
	bool foundChar = false;
    
	for (unsigned int i = 0; i < length; i++)
	{
		if (!isspace(buffer[i]) || foundChar)
		{
			foundChar = true;
			arr[count++] = buffer[i];
		}
	}
    
	arr[count] = '\0';

	String out =  String(arr);
	delete[] arr;
	return out;
}

String String::trimEnd()
{
	if (length == 0)
	{
		return String();
	}
    
	char* arr = new char[length + 1];
	int count = 0;
	int spaces = 0;
    
	for (unsigned int i = 0; i < length; i++)
	{
		if (isspace(buffer[i]))
		{
			spaces++;
			continue;
		}
		else
		{
			for (unsigned int ii = i - spaces; ii < i; ii++)
			{
				arr[count++] = buffer[ii];
			}
			spaces = 0;
			arr[count++] = buffer[i];
		}
	}
    
	if (count > 0)
	{
		arr[count] = '\0';
	}
	else
	{
		arr[0] = '\0';
	}

	String out =  String(arr);
	delete[] arr;
	return out;
}

String String::toLower()
{
	String str(bufferSize);
	str.length = length;
    
	for (unsigned int i = 0; i < str.length; i++)
	{
		str.buffer[i] = tolower(buffer[i]);
	}

	return str;
}

String String::toUpper()
{
	String str(bufferSize);
	str.length = length;
    
	for (unsigned int i = 0; i < str.length; i++)
	{
		str.buffer[i] = toupper(buffer[i]);
	}

	return str;
}

String String::clone()
{
	String s(bufferSize);
	s.length = length;
    
	for (unsigned int i = 0; i < length; i++)
	{
		s.buffer[i] = buffer[i];
	}

	return s;
}

char* String::c_string()
{
	char* arr = new char[length + 1];

	for (unsigned int i = 0; i < length; i++)
	{
		arr[i] = buffer[i];
	}
	arr[length] = '\0';

	return arr;
}
