#include "Stack.h"

#include <iostream>
using namespace std;

Stack::Stack(int size)
{
	if (size <= 0) {
		cerr << "Invalid size for stack, terminating execution" << endl;
		exit(1);
	}

	stkCapacity = size; // set the size of the stack
	mArray = new(nothrow) StackElement[stkCapacity]; // returns a null pointer if allocation fails

	if (mArray != 0)
		myTop = -1;
	else
	{
		cerr << "Inadequate memory to allocate stack, terminating execution\n";
		exit(1);
	}
}

bool Stack::Empty() const
{
	// if the stack is empty (myTop == -1) return true, otherwise return false
	return (myTop == -1);
}

bool Stack::Full() const
{
	return (myTop == (stkCapacity - 1));
}

void Stack::Push(const StackElement& value)
{
	if (!Full()) // if there is space in the stack
	{
		myTop++;
		mArray[myTop] = value;
	}
	else
	{
		cerr << "*** Stack full -- can't add new value ***\n"
			<< "Must increase the value of STACK_CAPACITY in Stack.h\n";
		exit(1); // terminate the program
	}
}

void Stack::Display() const
{
	for (int i = myTop; i >= 0; i--)
	{
		cout << mArray[i] << endl;
	}
}

StackElement Stack::Top() const
{
	if (!Empty())
		return (mArray[myTop]);
	else
	{
		cerr << "*** Stack is empty -- returning incorrect value ***\n";
		StackElement incorrectVal = 1024;
		return incorrectVal;
	}
}

void Stack::Pop()
{
	if (!Empty())
		myTop--;
	else
		cerr << "*** Stack is empty -- can't remove a value ***\n";
}

Stack::Stack(const Stack& originalStk)
	: stkCapacity(originalStk.stkCapacity), myTop(originalStk.myTop)
{
	// get new array for copy
	mArray = new(nothrow) StackElement[stkCapacity];

	if (mArray != 0)
	{
		// copy the members of the original array
		for (int pos = 0; pos <= myTop; pos++)
			mArray[pos] = originalStk.mArray[pos];
	}
	else
	{
		cerr << "*** Inadequate memory to allocate stack ***\n";
		exit(1);
	}
}

const Stack& Stack::operator = (const Stack& rightHandSide)
{
	if (this != &rightHandSide) // check that the stacks do not point to the same addresses
	{
		// Allocate a new array if necessary
		if (stkCapacity != rightHandSide.stkCapacity)
		{
			delete[] mArray; // delete the previous array

			stkCapacity = rightHandSide.stkCapacity; // copy the size of the stack
			mArray = new StackElement[stkCapacity];

			if (mArray == 0) // if the stack was not allocated
			{
				cerr << "*** Inadequate memory ***\n";
				exit(1);
			}
		}

		myTop = rightHandSide.myTop; // copy the top of the stack
		for (int pos = 0; pos <= myTop; pos++)
		{
			mArray[pos] = rightHandSide.mArray[pos]; // copy stack elements
		}
	}

	return *this;
}

Stack::~Stack()
{
	delete[] mArray;
}