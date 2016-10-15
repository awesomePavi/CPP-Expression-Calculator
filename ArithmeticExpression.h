/*
 * ArithmeticExpression.h
 *
 *  Created on: Dec 11, 2015
 *      Author: Pavi-MAC
 */

#ifndef ARITHMETICEXPRESSION_H_
#define ARITHMETICEXPRESSION_H_
//the super-class all expressions are based from
#include "Expression.h"
//so that when dynamic casting is done all ArithmeticExpression and subclasses are associated with Expression
class ArithmeticExpression: public Expression {
public:
	ArithmeticExpression();			//constructor to create fresh branches for this class objects and sub-classes
	virtual~ArithmeticExpression(); //destructor to properly dispose of the object
	Expression *left;				//left branch/leaf
	Expression *right;				//right branch/leaf
	string evaluate (); 			//from superclass
	string type();					//from superclass
	void print();				    //from superclass
	float convert (string s);		//to convert form string to integer for evaluations
};
#endif /* ARITHMETICEXPRESSION_H_ */
