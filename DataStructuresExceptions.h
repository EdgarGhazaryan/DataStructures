#pragma once

#include <exception>

class IsEmptyException : public std::exception {
public:
	IsEmptyException() : std::exception("Empty class object.") {}
};

class IndexOutOfBoundsException : public std::exception {
public:
	IndexOutOfBoundsException() : std::exception("Index is wrong.") {}
};