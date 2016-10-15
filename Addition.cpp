/*
 * Name: Kabir Kenth, Tarun Jain, Pavithran Pathmarajah
 * MacID: kenthks, jaint, Pathmap
 * Student Number: 001429801, 001419931, 001410729
 * Description: Adds two expressions
 */


#include "Addition.h"

//returns the type, this is only required to identify subtraction so it returns the linked type, since subtraction is linked by an
//operator it will appear after the second recursion
string Addition::type(){
	return this->left->type();
}

//returns a string of the addition of the converted right and left string evaluations
string Addition::evaluate(){
	return to_string((convert(this->left->evaluate())+Expression::incr)+(convert(this->right->evaluate())+Expression::incr));// evaluate expression and return string representation of the result.
}

//prints the left branch operator and right branch unless it is for adding a negative number or subtraction
void Addition::print(){
	this->left->print();
	//if the follwoing operator is a subtraction or one down it is subtraction do not display the + operator
	if ((this->right->type()=="Subtraction"))
		cout<<"";
	else{
		cout<<" + ";// prints expression
	}
	this->right->print();
}

