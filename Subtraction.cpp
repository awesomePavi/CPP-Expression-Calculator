/*
 * Name: Kabir Kenth, Tarun Jain, Pavithran Pathmarajah
 * MacID: kenthks, jaint, Pathmap
 * Student Number: 001429801, 001419931, 001410729
 * Description: Subrtacts two expressions
 */

#include "Subtraction.h"

//so the addition node knows when not to show its sign for subtraction statements, since this object acts as a negative number
string Subtraction::type(){
	return "Subtraction";
}

//returns a string of the subtraction of the converted right and left string evaluations, right being 0. to make a negative number
string Subtraction::evaluate(){
	return to_string(convert(this->left->evaluate())-(convert(this->right->evaluate())+Expression::incr));// evaluate expression and return string representation of the result.

}

//prints the negative number
void Subtraction::print(){
	cout << " - ";
	this->right->print();
}


