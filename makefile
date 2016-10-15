
output: Addition.o ArithmeticExpression.o Calc.o Division.o Expression.o Multiplication.o Subtraction.o
	g++ Addition.o ArithmeticExpression.o Calc.o Division.o Expression.o Multiplication.o Subtraction.o -o Calculator

Addition.o: Addition.cpp Addition.h
	g++ -c Addition.cpp

ArithmeticExpression.o: ArithmeticExpression.cpp ArithmeticExpression.h
	g++ -c ArithmeticExpression.cpp

Calc.o: Calc.cpp
	g++ -c Calc.cpp

Division.o: Division.cpp
	g++ -c Division.cpp

Expression.o: Expression.cpp
	g++ -c Expression.cpp

Multiplication.o: Multiplication.cpp
	g++ -c Multiplication.cpp

Subtraction.o: Subtraction.cpp
	g++ -c Subtraction.cpp

clean: 
	rm *.o Calculator