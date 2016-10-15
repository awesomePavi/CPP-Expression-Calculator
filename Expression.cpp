/*
 * Name: Kabir Kenth, Tarun Jain, Pavithran Pathmarajah
 * MacID: kenthks, jaint, pathmap
 * Student Number: 001429801, 001419931, 001410729
 * Description: Parent to the ArithmaticExpr Class
 */

#include "Expression.h"

//the other type that can be recursed through so the addition knows the next item is not special so it may show its addition operator per usual
string Expression::type(){
	return "Expression";
}

//returns the value stored in the expression type, to evaluate the whole expression. this type is the base leaves of the tree
string Expression::evaluate(){
	return val;
}
//prints the value stored in the expression type. this type is the base leaves of the tree
void Expression::print(){
	if (val=="("||val==")")
		cout<<val;
	else
		cout<<stoi(val)+(int)incr;// prints expression
}
