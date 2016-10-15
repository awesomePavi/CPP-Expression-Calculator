/*
 * Subtraction.h
 *
 *  Created on: Dec 11, 2015
 *      Author: Pavi-MAC
 */

#ifndef SUBTRACTION_H_
#define SUBTRACTION_H_
#include"ArithmeticExpression.h"
class Subtraction : public ArithmeticExpression {
public:
	string type();
	string evaluate (); //evaluate left expression and right expression
	void print();
};

#endif /* SUBTRACTION_H_ */
