/********************************************************************
          Convert infix notation to postfix notation
********************************************************************/

#include <iostream>
#include <string>    // string, == find, npos
#include <cassert>   // using assert function
#include <cctype>    // using alnum function to see if alphabetic number is entered

#include "Stack.h"

using namespace std;

string InfixToPostfix(string exp);

int main()
{
	string infixExp; // infix expression
	cout << "NOTE: Enter # for infix expression to stop.\n";

	while (true)
	{
		cout << "\nInfix Expression: ";
		getline(cin, infixExp);

		if (infixExp == "#") // exit condition
			break;

		cout << "Postfix expression is " << InfixToPostfix(infixExp) << endl;
	}

	system("pause");
	return 0;
}

// Converts an infix expression to postfix (gives error message for invalid expression
string InfixToPostfix(string exp)
{
	char token; // character in a given expression
	char topToken; // top character of the stack

	Stack opStack;  // stack of operators
	string pFixExp; // postfix expression

	for (int i = 0; i < exp.length(); i++)
	{
		token = exp[i];

		switch (token)
		{
		case ' ':  // do nothing
			break; 
		case '(':
			opStack.Push(token);
			break;
		case ')':
			while (true) // pop the contents until open brace appears
			{
				assert(!opStack.Empty()); // make sure the stack is not empty
				topToken = opStack.Top();
				opStack.Pop();
				// pop until the opening brace occurs
				if (topToken == '(')
					break;
				// otherwise append the contents of the stack to the postfix expression
				pFixExp = pFixExp + " " + topToken;
			}
			break;
		case '+':
		case '-':
		case '*':
		case '/':
		case '%':
			while (true)
			{
				if (opStack.Empty() || opStack.Top() == '(' || (token == '*' || token == '/' || token == '%')
					&& (opStack.Top() == '+' || opStack.Top() == '-'))
				{
					opStack.Push(token);
					break;
				}
				else
				{
					topToken = opStack.Top();
					opStack.Pop();
					pFixExp = pFixExp + " " + token;
				}
			}
			break;
		default: // if the token is an operand
			pFixExp = pFixExp + " " + token;
			while (true)
			{
				if (!isalnum(exp[i + 1])) // # sign detected (not a alphabetic number)
					break;
				i++;
				token = exp[i];
				pFixExp += token;
			}
		}
	}

	// pop remaining items in the stack
	while (true)
	{
		if (opStack.Empty())
			break;
		topToken = opStack.Top();
		opStack.Pop();
		if (topToken != '(')
			pFixExp = pFixExp + " " + topToken;
		else
		{
			cout << "*** Error in infix expression ***\n";
			break;
		}
	}

	return pFixExp;
}