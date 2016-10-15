/*
 * Name: Kabir Kenth, Tarun Jain, Pavithran Pathmarajah
 * MacID: kenthks, jaint, pathmap
 * Student Number: 001429801, 001419931, 001410729
 * Description: Multiplies two expressions
 */

#include "Multiplication.h"

//returns the type, this is only required to identify subtraction so it returns the linked type, since subtraction is linked by an
//operator it will appear after the second recursion
string Multiplication::type(){
	return this->left->type();
}

//returns a string of the multiplication of the converted right and left string evaluations
string Multiplication::evaluate(){
	return to_string((convert(this->left->evaluate())+Expression::incr)*(convert(this->right->evaluate())+Expression::incr));// evaluate expression and return string representation of the result.

}

//prints the left branch operator and right branch
void Multiplication::print(){
	this->left->print();
	cout<<" * ";// prints expression
	this->right->print();
}
