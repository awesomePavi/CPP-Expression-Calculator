/*
 * Name: Kabir Kenth, Tarun Jain, Pavithran Pathmarajah
 * MacID: kenthks, jaint, pathmap
 * Student Number: 001429801, 001419931, 001410729
 * Description: Super-class that all expressions (Addition,
 * Subtraction, Multiplication, Division) are based from
 */

#include "ArithmeticExpression.h"

//too create the leaves/branches when a new expression is made +,-,*,/, arithmetic
ArithmeticExpression::ArithmeticExpression() {
   left = new Expression();
   right = new Expression();
}

ArithmeticExpression::~ArithmeticExpression() {
}

//returns the type, this is only required to identify subtraction so it returns the linked type, since subtraction is linked by an
//operator it will appear after the second recursion
string ArithmeticExpression::type(){
	return this->left->type();
}

//depending on what type of pass through the ArithmeticExpression is being used for the evaluate function ensures it returns a value
string ArithmeticExpression::evaluate(){

	if (this->left->evaluate()=="(")
		return right->evaluate();

	if (this->right->evaluate()=="(")
			return left->evaluate();

	if (this->left->evaluate()==")")
			return right->evaluate();

	if (this->right->evaluate()==")")
				return left->evaluate();

	return "";
}

//print the left followed by right branches/leaves
void ArithmeticExpression::print(){
	this->left->print();
	this->right->print();
}

//used by the sub-classes to convert the strings to floats to do arithmetic
float ArithmeticExpression::convert(string s){
	//standard library function
	return stof(s);
}
