#pragma once
#include <iostream>
#ifndef DSTACK
#define DSTACK

typedef char StackElement; // change type depending on application

class Stack
{
public:
	Stack(int size = 128);
	bool Empty() const; // means this function can't change any member variables
	bool Full() const;
	void Push(const StackElement& value);
	void Display() const;
	StackElement Top() const;
	void Pop();
	Stack(const Stack& originalStk); // copy function
	const Stack& operator = (const Stack& rightHandSide);
	~Stack();

private:
	int myTop, stkCapacity;
	StackElement* mArray;
};

#endif