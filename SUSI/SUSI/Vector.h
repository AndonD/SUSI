#pragma once

#include <iostream>

template <class T>
class Vector
{
private:
	T* data;
	size_t size;

public:
	Vector();
	Vector(const Vector<T> &vect);
	void push_back(const T &x);
	void push_front(const T &x);
	void remove_last();
	void remove_first();
	void removeFromIndex(size_t x);
	bool containsElement(const T &x) const;
	Vector<T>& operator+= (const T &x);
	Vector<T> operator+ (const T &x) const;
	Vector<T>& operator+= (const Vector<T> &other);
	Vector<T> operator+ (const Vector<T> &other) const;
	T& operator[] (size_t i);
	T operator[] (size_t i) const;
	Vector<T>& operator= (const Vector<T> &vect);
	size_t length() const;
	bool operator== (const Vector<T> &other) const;
	bool operator!= (const Vector<T> &other) const;
	bool isEmpty() const;
	~Vector();
};

template <class T>
std::ostream& operator<< (std::ostream &stream, const Vector<T> &vect);