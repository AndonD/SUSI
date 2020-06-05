#pragma once

#include "stdafx.h"
#include "Vector.h"
#include <iostream>


template <class T>
Vector<T>::Vector()
{
	data = nullptr;
	size = 0;
}

template <class T>
Vector<T>::Vector(const Vector<T> &vect)
{
	this->size = vect.size;
	this->data = new T[vect.size];
	for (size_t i = 0; i < size; ++i)
	{
		this->data[i] = vect.data[i];
	}
}

template <class T>
void Vector<T>::push_back(const T &x)
{
	T* biggerBuffer = new T[this->size + 1];
	for (size_t i = 0; i < this->size; ++i)
	{
		biggerBuffer[i] = this->data[i];
	}
	biggerBuffer[this->size] = x;

	delete[] this->data;
	this->size++;
	this->data = new T[this->size];
	for (size_t i = 0; i < this->size; i++)
	{
		this->data[i] = biggerBuffer[i];
	}
	delete[] biggerBuffer;
}

template <class T>
void Vector<T>::push_front(const T &x)
{
	T* biggerBuffer = new T[this->size + 1];
	for (size_t i = 0; i < this->size; ++i)
	{
		biggerBuffer[i + 1] = this->data[i];
	}
	biggerBuffer[0] = x;

	delete[] this->data;
	this->size++;
	this->data = new T[this->size];
	for (size_t i = 0; i < this->size; i++)
	{
		this->data[i] = biggerBuffer[i];
	}
	delete[] biggerBuffer;
}

template <class T>
void Vector<T>::remove_last()
{
	if (this->size > 0)
	{
		removeFromIndex(this->size - 1);
	}
	else
	{
		return;
	}
}

template <class T>
void Vector<T>::remove_first()
{
	if (this->size > 0)
	{
		removeFromIndex(0);
	}
	else
	{
		return;
	}
}

template <class T>
void Vector<T>::removeFromIndex(size_t x)
{
	if (x <= this->size - 1)
	{
		T* smallerBuffer = new T[this->size - 1];
		for (size_t i = 0; i < x; i++)
		{
			smallerBuffer[i] = this->data[i];
		}
		for (size_t i = x; i < this->size - 1; i++)
		{
			smallerBuffer[i] = this->data[i + 1];
		}

		delete[] this->data;
		this->size--;
		this->data = new T[this->size];
		for (size_t i = 0; i < this->size; i++)
		{
			this->data[i] = smallerBuffer[i];
		}
		delete[] smallerBuffer;
	}
	else
	{
		return;
	}
}

template<class T>
bool Vector<T>::containsElement(const T &x) const
{
	for (size_t i = 0; i < this->size; i++)
	{
		if (this->data[i] == x)
		{
			return true;
		}
	}
	return false;
}

template <class T>
Vector<T>& Vector<T>::operator+= (const T &x)
{
	this->push_back(x);
	return *this;
}

template <class T>
Vector<T> Vector<T>::operator+ (const T &x) const
{
	Vector<T> result(*this);
	result += x;
	return result;
}

template <class T>
Vector<T>& Vector<T>::operator+= (const Vector<T> &other)
{
	T* newBuffer = new T[this->size + other.size];
	for (size_t i = 0; i < this->size; ++i)
	{
		newBuffer[i] = this->data[i];
	}
	for (size_t i = 0; i < other.size; ++i)
	{
		newBuffer[this->size + i] = other.data[i];
	}

	delete[] this->data;
	this->data = newBuffer;
	this->size = this->size + other.size;

	return *this;
}

template <class T>
Vector<T> Vector<T>::operator+ (const Vector<T> &other) const
{
	Vector<T> result;

	result.data = new T[this->size + other.size];
	for (size_t i = 0; i < this->size; ++i)
	{
		result.data[i] = this->data[i];
	}
	for (size_t i = 0; i < other.size; ++i)
	{
		result.data[this->size + i] = other.data[i];
	}

	result.size = this->size + other.size;
	return result;
}

template <class T>
T& Vector<T>::operator[] (size_t i)
{
	return data[i];
}

template <class T>
T Vector<T>::operator[] (size_t i) const
{
	return data[i];
}

template <class T>
Vector<T>& Vector<T>::operator= (const Vector<T> &vect)
{
	if (this != &vect)
	{
		delete[] this->data;

		this->size = vect.size;
		this->data = new T[vect.size];
		for (size_t i = 0; i < size; ++i)
		{
			this->data[i] = vect.data[i];
		}
	}
	return *this;
}

template <class T>
size_t Vector<T>::length() const
{
	return size;
}

template <class T>
bool Vector<T>::operator== (const Vector<T> &other) const
{
	if (this->size == other.size)
	{
		for (size_t i = 0; i < this->size; i++)
		{
			if (this->data[i] != other.data[i])
			{
				return false;
			}
		}
		return true;
	}
	return false;
}

template <class T>
bool Vector<T>::operator!= (const Vector<T> &other) const
{
	return !(this == other);
}

template <class T>
bool Vector<T>::isEmpty() const
{
	return (this->size == 0);
}

template <class T>
Vector<T>::~Vector()
{
	delete[] data;
}


template <class T>
std::ostream& operator<< (std::ostream &out, const Vector<T> &vect)
{
	//out << "[";
	for (size_t i = 0; i < vect.length(); ++i)
	{
		if (i == vect.length() - 1)
		{
			out << vect[i];
			continue;
		}
		out << vect[i] << ", ";
	}
	//out << "]";

	return out;
}