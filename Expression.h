/*
 * Expression.h
 *
 *  Created on: Dec 11, 2015
 *      Author: Pavi-MAC
 */

//shielding, to ensure it is only declared once
#ifndef EXPRESSION_H_
#define EXPRESSION_H_
//standard libraries all sub-classes will use
#include <iostream>
#include <string>
using namespace std;

class Expression {
public:
	static float incr;
	string val; //the value stored in the leaves of the tree
	virtual string type(); //returns the type of the element, expression or subtraction are the only
						   //results so addition print function knows, what to display
	virtual string evaluate(); // evaluate expression and return string representation of the result.
	virtual void print(); // prints expression
};

#endif /* EXPRESSION_H_ */
