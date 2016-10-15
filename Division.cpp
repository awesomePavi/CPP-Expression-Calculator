/*
 * Name: Kabir Kenth, Tarun Jain, Pavithran Pathmarajah
 * MacID: kenthks, jaint, Pathmap
 * Student Number: 001429801, 001419931, 001410729
 * Description: Divides two expressions
 */
#include "Division.h"

//returns the type, this is only required to identify subtraction so it returns the linked type, since subtraction is linked by an
//operator it will appear after the second recursion
string Division::type(){
	return this->left->type();
}

//returns a string of the division of the converted right and left string evaluations
string Division::evaluate(){
	return to_string((convert(this->left->evaluate())+Expression::incr)/(convert(this->right->evaluate())+Expression::incr));// evaluate expression and return string representation of the result.

}

//prints the left branch operator and right branch
void Division::print(){
	this->left->print();
	cout<<" / ";// prints expression
	this->right->print();

}
