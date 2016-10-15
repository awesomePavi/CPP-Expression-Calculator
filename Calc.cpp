/*
 * Name: Kabir Kenth, Tarun Jain, Pavithran Pathmarajah
 * MacID: kenthks, jaint, pathmap
 * Student Number: 001429801, 001419931, 001410729
 * Description: The main function, system shall take as input a string of integer arithmetic expression, checks if the input is valid,  parse the input into expression tree, and  evaluate the expression.
 */

#include <iostream>
#include <iomanip>
#include <string>
#include <cstdlib>
#include "Expression.h"
#include "ArithmeticExpression.h"
#include "Addition.h"
#include "Subtraction.h"
#include "Multiplication.h"
#include "Division.h"

using namespace std;

// checks to see if the character is a digit (0-9)
bool isDigit(char c) {
	switch (c) {
	case '0':
		return true;
	case '1':
		return true;
	case '2':
		return true;
	case '3':
		return true;
	case '4':
		return true;
	case '5':
		return true;
	case '6':
		return true;
	case '7':
		return true;
	case '8':
		return true;
	case '9':
		return true;
	}
	return false;
}
// checks to see if the character is an operator (+,-,*,/)
bool isOperator(char c) {
	switch (c) {
	case '+':
		return true;
	case '-':
		return true;
	case '*':
		return true;
	case '/':
		return true;
	}
	return false;
}
// if other symbols have been use (ie. @, &, etc.)
bool notSymbol(string expression) {
	for (int i = 0; i < expression.length(); i++) {
		// returns true if it is not a digit, operator, and bracket
		if ((expression[i] != '(') && (expression[i] != ')')
				&& !(isDigit(expression[i])) && !(isOperator(expression[i])))return true;
	}

	return false;
}
// determines if the expression is to short (less than 3 characters)
bool tooShort(string expression) {
	if (expression.length() < 3)
		return true;
	return false;
}
// checks to see if the # open brackets != # closed brackets
bool extraBracket(string expression) {
	int count = 0;
	// Iterates through the string and accesses each character value
	for (int i = 0; i < expression.length(); i++) {
		if (expression[i] == '(')
			count++;
		if (expression[i] == ')')
			count--;
		// returns true if hanging closed bracket appears
		if (count < 0)
			return true;
	}
	// returns true if count is not equal to zero
	if (count != 0)
		return true;

	return false;
}
// checks to see if there is no operator in between two integers
bool noOp(string expression) {
	// only performs this check if the strings length is greater than 2
	if (expression.length() > 2) {
		// iterates through the string and checks to see if case exists
		for (int i = 0; i < expression.length() - 2; i++) {
			if ((isDigit(expression[i])) &&(expression[i + 1] == ' ')
					&& (isDigit(expression[i + 2])))
				return true;
		}
	}

	return false;
}
// checks to see if two operators are after each other
bool twoOp(string expression) {
	if (expression.length() > 1) {
		// iterates through the string and checks to see if case exists
		for (int i = 0; i < expression.length() - 1; i++) {
			if ((isOperator(expression[i])) && (isOperator(expression[i+1])))return true;
		}
	}
	return false;
}
// checks to see if any brackets are properly formated
bool bracketCheck(string expression) {
	// adds brackets to beginning and end of string
	string temp = "(" + expression + ")";
	if (temp.length() > 1) {
		// iterates through the string and checks to see if case exists
		for (int i = 0; i < temp.length() - 1; i++) {
			// empty brackets -- ()
			if (temp[i] == '(' && temp[i + 1] == ')')
				return true;
			// multiplication of brackets -- )(
			if (temp[i] == ')' && temp[i + 1] == '(')
				return true;
			// multiplication of numbers and brackets -- )2 or 2(
			if ((isDigit(temp[i])) && (temp[i+1] == '('))return true;
			if ((temp[i] == ')') && (isDigit(temp[i + 1])))
				return true;
			// operators at the end of bracket -- *)
			if (isOperator((temp[i])) && (temp[i + 1] == ')'))
				return true;
			// checks to make sure it is a negative integer
			if ((temp[i] == '(') && (temp[i + 1] == '-')) {
				int j = i + 2;
				while (temp[j] != ')') {
					if (!(isDigit(temp[j])))
						return true;
					j++;
				}
			}
			// operators at front bracket excluding '-' -- (*
			if ((temp[i] == '(')
					&& (temp[i + 1] == '+' || temp[i + 1] == '*'
							|| temp[i + 1] == '/'))
				return true;
		}
	}
	return false;
}
// function ensures that expression is valid input
bool checkExpression(string expression) {
	// checks if space is between two digits
	if (noOp(expression))
		return false;
	// removes whitespace
	expression.erase(remove_if(expression.begin(), expression.end(), ::isspace),
			expression.end());
	// checks if expression length is at least 3 characters (without white space)
	if (tooShort(expression))
		return false;
	// checks if only appropriate symbols are used
	if (notSymbol(expression))
		return false;
	// checks if two operators are next to each other
	if (twoOp(expression))
		return false;
	// ensures brackets are implemented properly
	if (extraBracket(expression))
		return false;
	if (bracketCheck(expression))
		return false;
	return true;
}

/*-------------------------------------------------------------------------------
 *                     PARSING INPUT STRING TO TREE
 *-------------------------------------------------------------------------------
 */

//special parsing case for subtraction or negative number is branched off the next operator as 0 - the number
Expression* expressionParseSub(string in, Expression* subVal);

//takes in input string and out puts the equated expression pointer (recursive tree builder)
Expression* expressionParse(string in) {
	//to keep track of what level into the equation we are each set of -> () represents a level
	int braces = 0;
	//found is to keep track of when an operator is found
	bool found = false;
	//operators are searched for 1 at a time in reverse DMAS, so that when the evaluate is called the Division and Multiplication occur first
	string check[4] = { "-", "+", "*", "/" };
	//look for operators
	for (int a = 0; a < 4; a++) {
		//check string from back to front so that there is always a left and right on an operator ex. -1+7, if from front will not have a left side
		for (int x = in.length() - 1; x > -1; x--) {
			//if there is a closing brace increment the level by 1 until a matching close brace is found
			if (in.substr(x, 1) == ")")
				braces++;
			else if (in.substr(x, 1) == "(")
				braces--;
			//if a matching operator is found and the parser is on the highest level
			else if (braces == 0 && in.substr(x, 1) == check[a]) {
				//so that the operator type loop above this loop also haults
				found = true;
				//braces also doubles as a position variable fort he operator
				braces = x;
				//end the loop
				x = -5;
			}
		}
		//an oeprator has been found end the search
		if (found)
			a = 7;
	}
	//Expression to be returned
	Expression *node = new Expression();
	//If the operator found is subtraction
	if (in.substr(braces, 1) == "-") {
		//subtraction is an addition of a negative number and the other number
		node = new Addition();
		//create the expression to hold the negative number
		Expression *sub = new Subtraction();
		//the expression to hold 0
		Expression *tmp = new Expression();
		tmp->val = "0";

		//split the negative number into the left and right branch
		ArithmeticExpression *subPtr = dynamic_cast<ArithmeticExpression*>(sub);
		//put 0 into the left branch of the subtraction object
		subPtr->left = tmp;

		//to find the number of digits the number is
		int bracesTmp = 0;
		//too keep track of level
		int braceCheck = 0;
		//look for the next operator, on the same level. this is to find the number that i negative
		for (int i = braces + 1; i < in.length(); i++) {
			//incrememnt digit length
			bracesTmp++;
			if (in.substr(i, 1) == ")")
				braceCheck++;
			else if (in.substr(i, 1) == "(")
				braceCheck--;
			//if on the top level and an operator is found
			if (braceCheck == 0) {
				if (in.substr(i, 1) == "-" || in.substr(i, 1) == "+"
						|| in.substr(i, 1) == "*" || in.substr(i, 1) == "/") {
					//the digit length needs to be decremented, in order to avoid concating the operatr
					bracesTmp--;
					//leave loop
					i = in.length() + 5;
				}
			}
		}

		//check if the string is a single number, for cases such as -18
		//convert string to char array
		const char *cstr = in.c_str();
		//the string is a digit until proven otherwise
		bool digit = true;

		//go through string 1 at a time and check if it is a digit using C standard library
		for (int i = 1; i < in.length(); i++) {
			//if a character in the string is not a digit
			if (!isdigit(cstr[i])) {
				//the string is not one big number
				digit = false;
			}
		}
		//if the string is one number
		if (digit) {
			//the negative number
			Expression *tmp2 = new Expression();
			//set value
			tmp2->val = in.substr(braces + 1, bracesTmp);
			//set the number to be subtracted from 0
			subPtr->right = tmp2;
			//make the expression the negative number, since it's the remainder in the string
			node = sub;
			return node;
		}
		//if the string contains other items in it
		if (!digit) {
			//to account for the subtraction operator being before brackets
			subPtr->right = expressionParse(in.substr(braces + 1, bracesTmp)); // ex. 5-(6*7/3)
			//split the node into two parts one for the negative number the other for the rest of the expression
			ArithmeticExpression *nodePtr =
					dynamic_cast<ArithmeticExpression*>(node);
			//make left node what is on the left of the operator
			nodePtr->left = expressionParse(in.substr(0, braces));
			;
			//if there is still operators in the expression that branch after the subtraction operator
			if (braces + bracesTmp + 1 < in.length()) {
				//fill the tree after the subtraction operator, using an expression parser designed specifically
				//to link to the subtraction operator
				nodePtr->right = expressionParseSub(
						in.substr(braces + bracesTmp + 1), sub);
			} else {
				//if there is nothing branching off the subtraction operator then make it the last leaf on the branch
				nodePtr->right = sub;
			}
		}
		//return branch to the branch above
		return node;

	}
	//if the operator that is found is addition
	else if (in.substr(braces, 1) == "+") {
		//set the returned expression to be of addition type
		node = new Addition();
	}
	//if the operator that is found is multiplication
	else if (in.substr(braces, 1) == "*") {
		//set the returned expression to be of multiplication type
		node = new Multiplication();
	}
	//if the operator that is found is division
	else if (in.substr(braces, 1) == "/") {
		//set the returned expression to be of division type
		node = new Division();
	}
	/*if an opening brace is the head of the string, and the code reached here means no
	 *operators could be found at the current level and the program must go down a level*/
	else if (in.substr(0, 1) == "(") {
		//The expression is set to a pass through for evaluation but, will add the "(" for printing
		node = new ArithmeticExpression();
		// cast the expression into a ArithmeticExpression to access the left and right pointers
		ArithmeticExpression *nodePtr =
				dynamic_cast<ArithmeticExpression*>(node);
		// a blank expression to hold the "(" to be printed
		Expression *tmp = new Expression();
		tmp->val = "(";
		//set the left pointer as the "("
		nodePtr->left = tmp;

		//the right pointer is a parsed expression from what is in the brackets
		nodePtr->right = expressionParse(in.substr(1, in.length() - 2));

		//add the closing ")" so the expression can be printed
		//splits the left branch and moves to the left until the last leaf is found then appends a branch with two leaves one the
		//the old leaf and two the closing brace ")"
		//split first branch
		ArithmeticExpression *endOfPtrOld =
				dynamic_cast<ArithmeticExpression*>(nodePtr->right);
		// if there is no branches ^ tries to split a leaf
		if (!endOfPtrOld) {
			//create a new branch for the ")"
			Expression *endBrace = new ArithmeticExpression();
			//fil lthe branch
			ArithmeticExpression *endBracePtr =
					dynamic_cast<ArithmeticExpression*>(endBrace);
			//closing brace leaf
			Expression *tmp2 = new Expression();
			tmp2->val = ")";
			endBracePtr->right = tmp2;
			//move the pre-existing leaf to the new branch
			endBracePtr->left = nodePtr->right;
			//swap out leaf with branch
			nodePtr->right = endBrace;
			//return the new branch
			return node;
			//return the parsed expression
		} else {
			//too hunt for the last branch and keep track of the old one
			ArithmeticExpression *endOfPtrNew =
					dynamic_cast<ArithmeticExpression*>(endOfPtrOld->right);
			//keep splitting until a leaf is found
			while (endOfPtrNew != 0) {
				//leaf has not been found yet so set old to current branch
				endOfPtrOld = endOfPtrNew;
				//try next branch on right -> towards the end
				ArithmeticExpression *tmp =
						dynamic_cast<ArithmeticExpression*>(endOfPtrOld->right);

				endOfPtrNew = tmp;
			}
			//same leaf to branch system as above
			Expression *endBrace = new ArithmeticExpression();
			ArithmeticExpression *endBracePtr =
					dynamic_cast<ArithmeticExpression*>(endBrace);
			Expression *tmp2 = new Expression();
			tmp2->val = ")";
			endBracePtr->right = tmp2;
			endBracePtr->left = endOfPtrOld->right;
			//Change the old branches right leaf pointer to this created branch
			endOfPtrOld->right = endBrace;
		}
		//return the parsed expression
		return node;
		//if the statement reaches here the end of the branch has been reached and a leaf will be formed
	} else {
		//set leaf value
		node->val = in;
		//return the parsed expression
		return node;
	}
	//if this code is reached the branch is an '+', '*', or '/' and the left and right branch/ leaves must be fomed
	//split into branches
	ArithmeticExpression *nodePtr = dynamic_cast<ArithmeticExpression*>(node);
	//find left and right leaf/branch
	nodePtr->left = expressionParse(in.substr(0, braces));
	nodePtr->right = expressionParse(in.substr(braces + 1));

	//return the parsed expression
	return node;
}

//same as expressionParse but, the left leaf/branch is always subVal for this is used to find the operator
// that the formed negative number acts with
Expression* expressionParseSub(string in, Expression* subVal) {
	//to keep track of what level into the equation we are each set of -> () represents a level
	int braces = 0;
	//found is to keep track of when an operator is found
	bool found = false;
	//operators are searched for 1 at a time in reverse DMAS, so that when the evaluate is called the Division and Multiplication occur first
	string check[4] = { "-", "+", "*", "/" };
	//look for operators
	for (int a = 0; a < 4; a++) {
		//check string from back to front so that there is always a left and right on an operator ex. -1+7, if from front will not have a left side
		for (int x = 0; x < in.length(); x++) {
			//if there is a closing brace increment the level by 1 until a matching close brace is found
			if (in.substr(x, 1) == ")")
				braces++;
			else if (in.substr(x, 1) == "(")
				braces--;
			//if a matching operator is found and the parser is on the highest level
			else if (braces == 0 && in.substr(x, 1) == check[a]) {
				//so that the operator type loop above this loop also haults
				found = true;
				//braces also doubles as a position variable fort he operator
				braces = x;
				//end the loop
				x = -5;
			}
		}
		//an oeprator has been found end the search
		if (found)
			a = 7;
	}
	//Expression to be returned
	Expression *node = new Expression();
	//If the operator found is subtraction
	if (in.substr(braces, 1) == "-") {
		//subtraction is an addition of a negative number and the other number
		node = new Addition();
		//create the expression to hold the negative number
		Expression *sub = new Subtraction();
		//the expression to hold 0
		Expression *tmp = new Expression();
		tmp->val = "0";

		//split the negative number into the left and right branch
		ArithmeticExpression *subPtr = dynamic_cast<ArithmeticExpression*>(sub);
		//put 0 into the left branch of the subtraction object
		subPtr->left = tmp;

		//to find the number of digits the number is
		int bracesTmp = 0;
		//too keep track of level
		int braceCheck = 0;
		//look for the next operator, on the same level. this is to find the number that i negative
		for (int i = braces + 1; i < in.length(); i++) {
			//incrememnt digit length
			bracesTmp++;
			if (in.substr(i, 1) == ")")
				braceCheck++;
			else if (in.substr(i, 1) == "(")
				braceCheck--;
			//if on the top level and an operator is found
			if (braceCheck == 0) {
				if (in.substr(i, 1) == "-" || in.substr(i, 1) == "+"
						|| in.substr(i, 1) == "*" || in.substr(i, 1) == "/") {
					//the digit length needs to be decremented, in order to avoid concating the operatr
					bracesTmp--;
					//leave loop
					i = in.length() + 5;
				}
			}
		}

		//check if the string is a single number, for cases such as -18
		//convert string to char array
		const char *cstr = in.c_str();
		//the string is a digit until proven otherwise
		bool digit = true;

		//go through string 1 at a time and check if it is a digit using C standard library
		for (int i = 1; i < in.length(); i++) {
			//if a character in the string is not a digit
			if (!isdigit(cstr[i])) {
				//the string is not one big number
				digit = false;
			}
		}
		//if the string is one number
		if (digit) {
			//the negative number
			Expression *tmp2 = new Expression();
			//set value
			tmp2->val = in.substr(braces + 1, bracesTmp);
			//set the number to be subtracted from 0
			subPtr->right = tmp2;
			//make the expression the negative number, since it's the remainder in the string
			node = sub;
			return node;
		}
		//if the string contains other items in it
		if (!digit) {
			//to account for the subtraction operator being before brackets
			subPtr->right = expressionParse(in.substr(braces + 1, bracesTmp)); // ex. 5-(6*7/3)
			//split the node into two parts one for the negative number the other for the rest of the expression
			ArithmeticExpression *nodePtr =
					dynamic_cast<ArithmeticExpression*>(node);
			//make left node the negative number
			nodePtr->left = subVal;
			//if there is still operators in the expression that branch after the subtraction operator
			if (braces + bracesTmp + 1 < in.length())
				//fill the tree after the subtraction operator, using an expression parser designed specifically
				//to link to the subtraction operator
				nodePtr->right = expressionParseSub(
						in.substr(braces + bracesTmp + 1), sub);
			else {
				//if there is nothing branching off the subtraction operator then make it the last leaf on the branch
				nodePtr->right = sub;
			}
		}
		//return branch to the branch above
		return node;

	}
	//if the operator that is found is addition
	else if (in.substr(braces, 1) == "+") {
		//set the returned expression to be of addition type
		node = new Addition();
	}
	//if the operator that is found is multiplication
	else if (in.substr(braces, 1) == "*") {
		//set the returned expression to be of multiplication type
		node = new Multiplication();
	}
	//if the operator that is found is division
	else if (in.substr(braces, 1) == "/") {
		//set the returned expression to be of division type
		node = new Division();
	}
	/*if an opening brace is the head of the string, and the code reached here means no
	 *operators could be found at the current level and the program must go down a level*/
	else if (in.substr(0, 1) == "(") {
		//The expression is set to a pass through for evaluation but, will add the "(" for printing
		node = new ArithmeticExpression();
		// cast the expression into a ArithmeticExpression to access the left and right pointers
		ArithmeticExpression *nodePtr =
				dynamic_cast<ArithmeticExpression*>(node);
		// a blank expression to hold the "(" to be printed
		Expression *tmp = new Expression();
		tmp->val = "(";
		//set the left pointer as the "("
		nodePtr->left = tmp;

		//the right pointer is a parsed expression from what is in the brackets
		nodePtr->right = expressionParse(in.substr(1, in.length() - 2));

		//add the closing ")" so the expression can be printed
		//splits the left branch and moves to the left until the last leaf is found then appends a branch with two leaves one the
		//the old leaf and two the closing brace ")"
		//split first branch
		ArithmeticExpression *endOfPtrOld =
				dynamic_cast<ArithmeticExpression*>(nodePtr->right);
		// if there is no branches ^ tries to split a leaf
		if (!endOfPtrOld) {
			//create a new branch for the ")"
			Expression *endBrace = new ArithmeticExpression();
			//fill the branch
			ArithmeticExpression *endBracePtr =
					dynamic_cast<ArithmeticExpression*>(endBrace);
			//closing brace leaf
			Expression *tmp2 = new Expression();
			tmp2->val = ")";
			endBracePtr->right = tmp2;
			//move the pre-existing leaf to the new branch
			endBracePtr->left = nodePtr->right;
			//swap out leaf with branch
			nodePtr->right = endBrace;
			//return the new branch
			return node;
			//return the parsed expression
		} else {
			//too hunt for the last branch and keep track of the old one
			ArithmeticExpression *endOfPtrNew =
					dynamic_cast<ArithmeticExpression*>(endOfPtrOld->right);
			//keep splitting until a leaf is found
			while (endOfPtrNew != 0) {
				//leaf has not been found yet so set old to current branch
				endOfPtrOld = endOfPtrNew;
				//try next branch on right -> towards the end
				ArithmeticExpression *tmp =
						dynamic_cast<ArithmeticExpression*>(endOfPtrOld->right);

				endOfPtrNew = tmp;
			}
			//same leaf to branch system as above
			Expression *endBrace = new ArithmeticExpression();
			ArithmeticExpression *endBracePtr =
					dynamic_cast<ArithmeticExpression*>(endBrace);
			Expression *tmp2 = new Expression();
			tmp2->val = ")";
			endBracePtr->right = tmp2;
			endBracePtr->left = endOfPtrOld->right;
			//Change the old branches right leaf pointer to this created branch
			endOfPtrOld->right = endBrace;
		}
		//return the parsed expression
		return node;
		//if the statement reaches here the end of the branch has been reached and a leaf will be formed
	} else {
		//set leaf value
		node->val = in;
		//return the parsed expression
		return node;
	}
	//if this code is reached the branch is an '+', '*', or '/' and the left and right branch/ leaves must be fomed
	//split into branches
	ArithmeticExpression *nodePtr = dynamic_cast<ArithmeticExpression*>(node);
	//left node is the negative number
	nodePtr->left = subVal;
	//find the right branch/leaf
	nodePtr->right = expressionParse(in.substr(braces + 1));

	//return the parsed expression
	return node;
}
float Expression::incr = 0;
int main() {
	bool validIn = false;

	//creates the expression object
	Expression* tree = new Expression();

	// user inputs an expression
	string expression = "";
	while (!validIn) {
		// get user input
		cout << "Please enter an expression:";
		getline(cin, expression);
		// end's Program if "#" is inputed
		if (expression == "#")
			break;
		// check if expression is a valid input
		if (expression == "#") {
			validIn = true;
		} else if (expression == "@") {
			Expression::incr++;
			tree->print();
			cout << " = ";
			cout << fixed << setprecision(2) << stof(tree->evaluate()) << endl;
		} else if (checkExpression(expression)) {
			// Remove Whitespace
			expression.erase(
					remove_if(expression.begin(), expression.end(), ::isspace),
					expression.end());
			//fills tree, with the user inputted expression
			tree = expressionParse(expression);
			Expression::incr = 0;
			//print expression and value
			tree->print();
			cout << " = ";
			cout << fixed << setprecision(2) << stof(tree->evaluate()) << endl;
		} else
			cout << endl << "Expression is not well formed" << endl;
	}

	delete tree;
	return 0;
}

