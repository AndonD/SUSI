#pragma once

#include <iostream>

class String
{
public:
	char *content;

	String();
	String(char c);
	String(const char *otherStr);
	String(const String &other);
	size_t length() const;
	void initialize(const char *otherStr);
	void clear();
	void print();
	String operator+ (char c);
	String& operator+= (char c);
	String operator+ (const String &other);
	String& operator+= (const String &other);
	bool operator== (const String &other);
	bool operator!= (const String &other);
	char& operator[] (size_t i);
	String& operator= (char c);
	String& operator= (const char* otherStr);
	String& operator= (const String &other);
	~String();
};

String operator+ (char c, const String &str);
std::ostream& operator<< (std::ostream& out, String s);
std::istream& operator>> (std::istream& in, String& s);