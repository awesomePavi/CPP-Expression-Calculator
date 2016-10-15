/*
 * Multiplication.h
 *
 *  Created on: Dec 11, 2015
 *      Author: Pavi-MAC
 */

#ifndef MULTIPLICATION_H_
#define MULTIPLICATION_H_
#include"ArithmeticExpression.h"
class Multiplication : public ArithmeticExpression {
public:
	string type();
	string evaluate (); //evaluate left expression and right expression
	void print();
};

#endif /* MULTIPLICATION_H_ */
