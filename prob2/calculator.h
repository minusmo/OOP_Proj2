#pragma once

#include "inf_int.h"
#include "string"
using namespace std;
class calculator
{
public:
	void examineExpression(string, string[3]);
	inf_int add(inf_int a, inf_int b);
	inf_int subtract(inf_int a, inf_int b);
	inf_int multiply(inf_int a, inf_int b);
};

