/*
 * Division.h
 *
 *  Created on: Dec 11, 2015
 *      Author: Pavi-MAC
 */

#ifndef DIVISION_H_
#define DIVISION_H_
#include"ArithmeticExpression.h"
class Division : public ArithmeticExpression {
public:
	string type();
	string evaluate (); //evaluate left expression and right expression
	void print();
};

#endif /* DIVISION_H_ */
