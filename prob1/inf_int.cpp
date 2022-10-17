#include "inf_int.h"

// 
// to be filled by students
//
// example :
//
// bool operator==(const inf_int& a , const inf_int& b)
// {
//     // we assume 0 is always positive.
//     if ( (strcmp(a.digits , b.digits)==0) && a.thesign==b.thesign )
//         return true;
//     return false;
// }
//

inf_int::inf_int() {
	this->length = 1;
	this->thesign = true;
	this->digits = string();
	this->digits.push_back('0');
}

inf_int::inf_int(int n) {
	if (n < 0) {
		this->thesign = false;
		n = -n;
	}
	else {
		this->thesign = true;
	}

	int i = 0;
	while (n > 0)
	{
		this->digits.push_back(n % 10 + '0');
		n /= 10;
		i++;
	}

	if (i == 0) {
		(this); new inf_int();
	}
	else {
		this->length = i;
	}
}

inf_int::inf_int(const char* str) {
	if (str[0] == '-') {
		this->thesign = false;
	}
	else {
		this->thesign = true;
	}

	if (this->thesign == false) {
		int i = 1;
		for (; i < sizeof(str) / sizeof(char); i++) {
			this->digits.push_back(str[i]);
		}
		this->length = i - 1;
	}
	else {
		int i = 0;
		for (; i < sizeof(str) / sizeof(char); i++) {
			this->digits.push_back(str[i]);
		}
		this->length = i;
	}
}

inf_int::inf_int(const inf_int& ex_inf_int) {
	this->length = ex_inf_int.length;
	this->digits = ex_inf_int.digits;
	this->thesign = ex_inf_int.thesign;
}

inf_int::~inf_int() {

}