#pragma once

#include <iostream>

template <class T>
class Vector
{
private:
	T * data;
	size_t size;

public:
	Vector();
	Vector(const Vector<T>& vect);
	void push_back(const T& x);
	void push_front(const T& x);
	void pop_back();
	void pop_front();
	void removeFromIndex(int x);
	bool containsElement(const T& x) const;
	Vector<T>& operator+= (const T& x);
	Vector<T> operator+ (const T& x) const;
	Vector<T>& operator+= (const Vector<T>& other);
	Vector<T> operator+ (const Vector<T>& other) const;
	T& operator[] (size_t i);
	T operator[] (size_t i) const;
	Vector<T>& operator= (const Vector<T>& vect);
	size_t length() const;
	bool operator== (const Vector<T>& other);
	bool operator!= (const Vector<T>& other);
	bool isEmpty();
	~Vector();
};

template <class T>
std::ostream& operator<< (std::ostream& stream, const Vector<T>& vect);