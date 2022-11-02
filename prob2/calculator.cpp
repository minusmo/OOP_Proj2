#include "Calculator.h"

void Calculator::examineExpression(string input, string expressions[3]) {
	string operand1, operand2, oper;
	size_t ws1= input.find(" ");
	operand1 = input.substr(0, (int)ws1);
	size_t ws2 = input.find(" ", (int)ws1+1);
	oper = input.substr(ws1+1, 1);

	operand2 = input.substr(ws2+1, (int)input.length() - (int)ws2 - 1);
	expressions[0] = operand1;
	expressions[1] = operand2;
	expressions[2] = oper;
}

inf_int Calculator::add(inf_int a, inf_int b) {
	return a + b;
}

inf_int Calculator::subtract(inf_int a, inf_int b) {
	return a - b;
}

inf_int Calculator::multiply(inf_int a, inf_int b) {
	return a * b;
}