#include "inf_int.h"

// the default constructor
inf_int::inf_int() {
	this->length = 1;
	this->thesign = true;
	this->digits = string();
	this->digits.push_back('0');
}

// constructor using integer parameter
inf_int::inf_int(int n) {
	string buff;
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
		buff.push_back(n % 10 + '0');
		n /= 10;
		i++;
	}

	if (i == 0) {
		new (this) inf_int();
	}
	else {
		this->digits = buff;
		this->length = i;
	}
}

// constructor using const char* parameter
inf_int::inf_int(const char* str) {
	if (str[0] == '-') {
		this->thesign = false;
	}
	else {
		this->thesign = true;
	}

	size_t strLen = strlen(str);

	this->digits = string();
	if (this->thesign) {
		for (int i = 0; i < (int)strLen; i++) {
			this->digits.push_back(str[strLen - 1 - i]);
		}
		this->length = (unsigned int)strLen;
	}
	else {
		for (int i = 0; i < (int)strLen - 1; i++) {
			this->digits.push_back(str[strLen - 1 - i]);
		}
		this->length = (unsigned int)strLen - 1;
	}
}

// a copy constructor
inf_int::inf_int(const inf_int& ex_inf_int) {
	this->digits = string();
	for (auto digit : ex_inf_int.digits) {
		this->digits.push_back(digit);
	}

	this->length = ex_inf_int.length;
	this->thesign = ex_inf_int.thesign;
}

// a destructor but do nothing, because we don't have any dynamically allocated member variable
inf_int::~inf_int() {
	// do nothing because we don't use dynamically allocated member variables
}

// operator= overloaded to use as copy constructor
inf_int& inf_int::operator=(const inf_int& ex_inf_int)
{
	this->digits = string();
	for (auto digit : ex_inf_int.digits) {
		this->digits.push_back(digit);
	}

	this->length = ex_inf_int.length;
	this->thesign = ex_inf_int.thesign;

	return *this;
}

// operator== overloaded to check if two inf_int are the same
bool operator==(const inf_int& a, const inf_int& b)
{
	// we assume 0 is always positive.
	// absolute value should be the same and two signs should be the same,
	if ((a.digits == b.digits) && a.thesign == b.thesign)
		return true;
	return false;
}

// operator!= overloaded to check if two inf_int are different
bool operator!=(const inf_int& a, const inf_int& b)
{
	return !operator==(a, b);
}

// operator> overloaded to check if the first parameter is bigger than the second one
bool operator>(const inf_int& a, const inf_int& b)
{
	// compare absolute value
	// when both signs are positive, return the absolutely compared result
	// when both signs are negative, return inversed the absolutely compared result
	// when two signs are different, return thesign of a. because there are two cases + - => true, - + => false
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

// operator< overloaded to check if the first parameter is less than the second one
bool operator<(const inf_int& a, const inf_int& b)
{
	if (operator>(a, b) || operator==(a, b)) {
		return false;
	}
	else {
		return true;
	}
}

// operator+ overloaded to operate + with inf_int instances
inf_int operator+(const inf_int& a, const inf_int& b)
{
	inf_int c;
	// when two signs are the same, use addition operation
	if (a.thesign == b.thesign) {
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

			if (carry) c.digits.push_back(carry + '0');
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

			if (carry) c.digits.push_back(carry + '0');
		}


		c.length = (unsigned int)c.digits.length();
		c.thesign = a.thesign;

		return c;
	}
	else {
		// when two signs are different, use subtract
		c = b;
		c.thesign = a.thesign;

		return a - c;
	}
}

// operator- overloaded to operate - with inf_int instances
inf_int operator-(const inf_int& a, const inf_int& b)
{
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
			unsigned int zeros = 0;
			for (unsigned int i = (unsigned int)c.digits.length() - 1; i > 0; i--) {
				if (c.digits[i] == '0') {
					zeros++;
				}
				else {
					break;
				}
			}
			c.digits = c.digits.substr(0, (unsigned int)c.digits.length() - zeros);

			c.length = (unsigned int)c.digits.length();
			if (a.thesign) {
				c.thesign = false;
			}
			else {
				c.thesign = true;
			}
			return c;
		}
		else {
			inf_int d = b;
			d.thesign = a.thesign;
			c = a + d;
			return c;
		}
	}
	else if (a.digits == b.digits) {
		// when two numbers are the same
		if (a.thesign == b.thesign) {
			c = inf_int(0);
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

			unsigned int zeros = 0;
			for (unsigned int i = (unsigned int)c.digits.length() - 1; i > 0; i--) {
				if (c.digits[i] == '0') {
					zeros++;
				}
				else {
					break;
				}
			}
			c.digits = c.digits.substr(0, (unsigned int)c.digits.length() - zeros);

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

// operator* overloaded to operatr * with inf_int instances
inf_int operator*(const inf_int& a, const inf_int& b)
{
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

	c.digits = string(a.length + b.length, 0);

	for (int i = 0; i < (int)a.length; i++) {
		for (int j = 0; j < (int)b.length; j++) {
			int n = c.digits[i + j] + (a.digits[i] - '0') * (b.digits[j] - '0');
			c.digits[i + j] = n % 10;
			c.digits[i + j + 1] += n / 10;
		}
	}

	for (int k = 0; k < c.digits.length(); k++) {
		c.digits[k] += '0';
	}

	unsigned int zeros = 0;
	for (unsigned int i = (unsigned int)c.digits.length() - 1; i > 0; i--) {
		if (c.digits[i] == '0') {
			zeros++;
		}
		else {
			break;
		}
	}
	c.digits = c.digits.substr(0, (unsigned int)c.digits.length() - zeros);

	c.length = (unsigned int)c.digits.length();
	return c;
}

// operator<< overloaded to operate << with inf_int instance
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

// returns true if the inf_int is 0 else returns false
bool isZero(const inf_int& a) {
	if (a.length != 1) return false;
	if (a.thesign != true) return false;
	if (a.digits[a.length - 1] != '0') return false;
	return true;
}

// returns true if the first inf_int is absolutely less than the second one else return false
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