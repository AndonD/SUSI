#include "stdafx.h"
#include "String.h"
#include <iostream>
#include <cstring>
//#include <fstream>


String::String()
{
	initialize("");
}

String::String(char c)
{
	this->content = new char[2];
	this->content[0] = c;
	this->content[1] = '\0';
}

String::String(const char* otherStr)
{
	initialize(otherStr);
}

String::String(const String &other)
{
	this->content = new char[other.length() + 1];
	for (size_t i = 0; i < other.length(); i++)
	{
		this->content[i] = other.content[i];
	}
	this->content[other.length()] = '\0';
}

char* String::c_str() const
{
	return this->content;
}

size_t String::length() const
{
	return strlen(this->content);
}

void String::initialize(const char* otherStr)
{
	size_t otherLength = strlen(otherStr);
	this->content = new char[otherLength + 1];
	for (size_t i = 0; i < otherLength; i++)
	{
		this->content[i] = otherStr[i];
	}
	this->content[otherLength] = '\0';
}

void String::clear()
{
	this->initialize("");
}

void String::print() const
{
	std::cout << this->content << std::endl;
}

String String::operator+ (char c)
{
	String result;
	result.content = new char[this->length() + 1 + 1];
	for (size_t i = 0; i < this->length(); i++)
	{
		result.content[i] = this->content[i];
	}
	result.content[this->length()] = c;
	result.content[this->length() + 1] = '\0';

	return result;
}

String& String::operator+= (char c)
{
	String buffer = new char[this->length() + 1 + 1];
	for (size_t i = 0; i < this->length(); i++)
	{
		buffer.content[i] = this->content[i];
	}
	buffer.content[this->length()] = c;
	buffer.content[this->length() + 1] = '\0';

	delete[]this->content;
	this->initialize(buffer.content);
	return *this;
}

String String::operator+ (const String &other)
{
	String result;
	result.content = new char[this->length() + other.length() + 1];
	for (size_t i = 0; i < this->length(); i++)
	{
		result.content[i] = this->content[i];
	}
	for (size_t i = 0; i < other.length(); i++)
	{
		result.content[this->length() + i] = other.content[i];
	}
	result.content[this->length() + other.length()] = '\0';

	return result;
}

String& String::operator+= (const String &other)
{
	String buffer = new char[this->length() + other.length() + 1];
	for (size_t i = 0; i < this->length(); i++)
	{
		buffer.content[i] = this->content[i];
	}
	for (size_t i = 0; i < other.length(); i++)
	{
		buffer.content[this->length() + i] = other.content[i];
	}
	buffer.content[this->length() + other.length()] = '\0';

	delete[] this->content;
	this->initialize(buffer.content);

	return *this;
}

bool String::operator== (const String &other)
{
	return (strcmp(this->content, other.content) == 0);
}

bool String::operator!= (const String &other)
{
	return (strcmp(this->content, other.content) != 0);
}

char& String::operator[] (size_t i)
{
	return this->content[i];
}

String& String::operator= (char c)
{
	this->content = new char[2];
	this->content[0] = c;
	this->content[1] = '\0';
	return *this;
}

String& String::operator= (const char* otherStr)
{
	delete[] this->content;
	this->initialize(otherStr);
	return *this;
}

String& String::operator= (const String &other)
{
	delete[] this->content;
	this->initialize(other.content);
	return *this;
}

String::~String()
{
	delete[] content;
}

String operator+ (char c, const String &str)
{
	String result;
	result = c;
	result += str;

	return result;
}

std::ostream& operator<< (std::ostream &out, const String &str)
{
	out << str.c_str();
	return out;
}

std::istream& operator>> (std::istream &in, String &str)
{
	char c;
	do
	{
		c = in.get();
		if (c != '\n')
		{
			str += c;
		}
	} while (c != '\n');

	return in;
}
