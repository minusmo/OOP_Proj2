#include "inf_int.h"
#include "calculator.h"
#include "string"
#include "iostream"

using namespace std;
int main() {
	calculator calc = calculator();
	string input = "run";
	while (1) {
		cout << "Input: ";
		getline(cin, input);
		if (input == "0") {
			break;
		}
		else {
			string expressions[3];
			inf_int operand1, operand2, result;
			calc.examineExpression(input, expressions);
			operand1 = inf_int(expressions[0].c_str());
			operand2 = inf_int(expressions[1].c_str());
			//cout << "operation with: " << expressions[0] << expressions[1] << expressions[2] << endl;
			if (expressions[2] == "+") {
				result = calc.add(operand1, operand2);
			}
			else if (expressions[2] == "-") {
				result = calc.subtract(operand1, operand2);
			}
			else if (expressions[2] == "*") {
				result = calc.multiply(operand1, operand2);
			}
			cout << "Output: " << result << endl;
		}
	}
	return 0;
}