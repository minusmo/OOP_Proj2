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
	char buffer[100];

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
		buffer[i] = n % 10 + '0';
		n /= 10;
		i++;
	}

	if (i == 0) {
		new (this) inf_int();
	}
	else {
		buffer[i] = '\0';

		this->digits = string();
		this->length = i;

		int j;
		for (j = 0; j < i + 1; j++) {
			if (buffer[j] == '\0') break;
			this->digits.push_back(buffer[j]);
		}
	}
}

inf_int::inf_int(const char* str) {
	if (str[0] == '-') {
		this->thesign = false;
	}
	else {
		this->thesign = true;
	}

	size_t strLen = strlen(str);
	int i = 0;
	this->digits = string();
	for (; i < strLen; i++) {
		this->digits.push_back(str[strLen - 1 - i]);
	}

	this->length = (unsigned int)strLen;
}

inf_int::inf_int(const inf_int& ex_inf_int) {
	this->digits = string();
	unsigned int i;
	for (auto digit : ex_inf_int.digits) {
		this->digits.push_back(digit);
	}

	this->length = ex_inf_int.length;
	this->thesign = ex_inf_int.thesign;
}

inf_int::~inf_int() {

}

inf_int& inf_int::operator=(const inf_int& ex_inf_int)
{
	this->digits = string();
	unsigned int i;
	for (auto digit : ex_inf_int.digits) {
		this->digits.push_back(digit);
	}

	this->length = ex_inf_int.length;
	this->thesign = ex_inf_int.thesign;

	return *this;
}

bool operator==(const inf_int& a, const inf_int& b)
{
	// we assume 0 is always positive.
	if ((a.digits == b.digits) && a.thesign == b.thesign)	// 부호가 같고, 절댓값이 일치해야함.
		return true;
	return false;
}

bool operator!=(const inf_int& a, const inf_int& b)
{
	return !operator==(a, b);
}

bool operator>(const inf_int& a, const inf_int& b)
{
	// to be filled
	// 절대값 비교
	// 둘 다 양수일 경우 절댓값 비교한 것을 그대로 return
	// 둘 다 음수일 경우 절댓값 비교의 것을 반전하여 return
	// 부호가 다를 경우, a가 양수일 경우 b는 음수, a가 음수일 경우 b는 양수이기에 a의 부호진리값을 반환하면 됨
	if (a == b) {
		return false;
	}
	
	if (a.thesign && b.thesign) {
		return absLess(a, b);
	}
	else if (!a.thesign && !b.thesign) {
		return !absLess(a, b);
	}
	else {
		return a.thesign;
	}
}

bool operator<(const inf_int& a, const inf_int& b)
{
	if (operator>(a, b) || operator==(a, b)) {
		return false;
	}
	else {
		return true;
	}
}

inf_int operator+(const inf_int& a, const inf_int& b)
{
	inf_int c;
	unsigned int i;

	if (a.thesign == b.thesign) {	// 이항의 부호가 같을 경우 + 연산자로 연산
		c.digits = string();
		if (a.length < b.length) {
			int carry = 0;
			for (int i = 0; i < (int)a.length; i++)
			{
				int sum = ((a.digits[i] - '0') + (b.digits[i] - '0') + carry);
				c.digits.push_back(sum % 10 + '0');

				carry = sum / 10;
			}

			for (int i = a.length; i < (int)b.length; i++)
			{
				int sum = ((b.digits[i] - '0') + carry);
				c.digits.push_back(sum % 10 + '0');
				carry = sum / 10;
			}

			if (carry)
				c.digits.push_back(carry + '0');
		}
		else {
			int carry = 0;
			for (int i = 0; i < (int)b.length; i++)
			{
				int sum = ((a.digits[i] - '0') + (b.digits[i] - '0') + carry);
				c.digits.push_back(sum % 10 + '0');

				carry = sum / 10;
			}

			for (int i = b.length; i < (int)a.length; i++)
			{
				int sum = ((a.digits[i] - '0') + carry);
				c.digits.push_back(sum % 10 + '0');
				carry = sum / 10;
			}

			if (carry)
				c.digits.push_back(carry + '0');
		}
		

		c.length = (unsigned int)c.digits.length();
		c.thesign = a.thesign;
		
		return c;
	}
	else {	// 이항의 부호가 다를 경우 - 연산자로 연산
		c = b;
		c.thesign = a.thesign;

		return a - c;
	}
}

inf_int operator-(const inf_int& a, const inf_int& b)
{
	// to be filled
	inf_int c;
	
	if (absLess(a, b)) {
		// subtract a from b
		if (b.thesign == a.thesign) {
			c.digits = string();
			int carry = 0;
			unsigned int i;
			for (i = 0; i < a.length; i++) {
				int sub = ((b.digits[i] - '0') - (a.digits[i] - '0') - carry);
				if (sub < 0) {
					sub = sub + 10;
					carry = 1;
				}
				else {
					carry = 0;
				}
				c.digits.push_back(sub + '0');
			}
			for (i = a.length; i < b.length; i++) {
				int sub = ((b.digits[i] - '0') - carry);
				if (sub < 0) {
					sub = sub + 10;
					carry = 1;
				}
				else {
					carry = 0;
				}
				c.digits.push_back(sub + '0');
			}

			c.length = (unsigned int)c.digits.length();
			c.thesign = b.thesign;
			return c;
		}
		else {
			inf_int d = a;
			d.thesign = b.thesign;
			c = b + d;
			return c;
		}
	}
	else if (a.digits == b.digits) {
		// when two numbers are the same
		if (a.thesign == b.thesign) {
			c = inf_int();
		}
		else {
			c = inf_int(2) * a;
			c.thesign = a.thesign;
		}
		return c;
	}
	else {
		// subtract b from a
		if (a.thesign == b.thesign) {
			c.digits = string();
			int carry = 0;
			for (unsigned int i = 0; i < b.length; i++) {
				int sub = ((a.digits[i] - '0') - (b.digits[i] - '0') - carry);
				if (sub < 0) {
					sub = sub + 10;
					carry = 1;
				}
				else {
					carry = 0;
				}
				c.digits.push_back(sub + '0');
			}
			for (unsigned int i = b.length; i < a.length; i++) {
				int sub = ((a.digits[i] - '0') - carry);
				if (sub < 0) {
					sub = sub + 10;
					carry = 1;
				}
				else {
					carry = 0;
				}
				c.digits.push_back(sub + '0');
			}

			c.length = (unsigned int)c.digits.length();
			c.thesign = a.thesign;
			return c;
		}
		else {
			inf_int d = b;
			d.thesign = a.thesign;
			c = a + d;
			return c;
		}
	}
}

inf_int operator*(const inf_int& a, const inf_int& b)
{
	// to be filled
	inf_int c;
	if (isZero(a) || isZero(b)) {
		c = inf_int();
		return c;
	}
	if (a.thesign == b.thesign) {
		c.thesign = true;
	}
	else {
		c.thesign = false;
	}

	c.digits = string(a.length+b.length,0);

	for (int i = 0; i < (int)a.length; i++) {
		for (int j = 0; j < (int)b.length; j++) {
			int n = c.digits[i + j] + (a.digits[i] - '0') * (b.digits[j] - '0');
			c.digits[i + j] = n % 10;
			c.digits[i + j + 1] += n/10;
		}
	}
	
	for (int k = 0; k < c.digits.length();k++) {
		c.digits[k] += '0';
	}
	if (c.digits[c.digits.length() - 1] == '0') {
		c.digits = c.digits.substr(0, c.digits.length() - 1);
	}

	c.length = (unsigned int)c.digits.length();
	return c;
}


ostream& operator<<(ostream& out, const inf_int& a)
{
	int i;

	if (a.thesign == false) {
		out << '-';
	}
	for (i = a.length - 1; i >= 0; i--) {
		out << a.digits[i];
	}
	return out;
}

void inf_int::Add(const char num, const unsigned int index)	// a의 index 자리수에 n을 더한다. 0<=n<=9, ex) a가 391일때, Add(a, 2, 2)의 결과는 411
{
	if (this->length < index) {
		this->length = index;					// 길이 지정
		this->digits.push_back(num % 10 + '0');
	}
	else {
		int sum = num - '0' + this->digits[index-1] - '0';
		if (sum > 9) {
			this->digits[index - 1] = sum % 10 + '0';
			Add('1', index + 1);
		}
		else {
			this->digits[index - 1] = sum + '0';
		}
	}
}

bool isZero(const inf_int& a) {
	if (a.length != 1) return false;
	if (a.thesign != true) return false;
	if (a.digits[a.length - 1] != '0') return false;
	return true;
}

bool absLess(const inf_int& a, const inf_int& b) {
	if (a.length < b.length) {
		return true;
	}
	else if (a.length > b.length) {
		return false;
	}
	else {
		for (unsigned int i = 0; i < a.length; i++)
		{
			if (a.digits[i] > b.digits[i]) {
				return false;
			}
			else if (a.digits[i] < b.digits[i]) {
				return true;
			}
		}
		return false;
	}
}