/*
 * Addition.h
 *
 *  Created on: Dec 11, 2015
 *      Author: Pavi-MAC
 */

#ifndef ADDITION_H_
#define ADDITION_H_
#include"ArithmeticExpression.h"

class Addition: public ArithmeticExpression {
public:
	string type();
	string evaluate (); //evaluate left expression and right expression
	void print();
};

#endif /* ADDITION_H_ */
