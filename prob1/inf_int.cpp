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
	this->digits = new char[2];
	this->digits[0] = '0';
	this->digits[1] = '\0';
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

		this->digits = new char[i + 1];
		this->length = i;
		strcpy(this->digits, buffer);
	}
}

inf_int::inf_int(const char* str) {
	if (str[0] == '-') {
		this->thesign = false;
	}
	else {
		this->thesign = true;
	}

	int strLen = sizeof(str) / sizeof(char);
	int i = 0;
	if (this->thesign == false) {
		for (; i < strLen-1; i++) {
			this->digits[i] = str[strLen - 1 - i];
		}
	}
	else {
		for (; i < strLen; i++) {
			this->digits[i] = str[strLen - 1 - i];
		}
	}
	this->length = i + 1;
}

inf_int::inf_int(const inf_int& ex_inf_int) {
	this->digits = new char[ex_inf_int.length + 1];

	strcpy(this->digits, ex_inf_int.digits);
	this->length = ex_inf_int.length;
	this->thesign = ex_inf_int.thesign;
}

inf_int::~inf_int() {
	delete digits;
}

inf_int& inf_int::operator=(const inf_int& ex_inf_int)
{
	if (this->digits) {
		delete this->digits;		// 이미 문자열이 있을 경우 제거.
	}
	this->digits = new char[ex_inf_int.length + 1];

	strcpy(this->digits, ex_inf_int.digits);
	this->length = ex_inf_int.length;
	this->thesign = ex_inf_int.thesign;

	return *this;
}

bool operator==(const inf_int& a, const inf_int& b)
{
	// we assume 0 is always positive.
	if ((strcmp(a.digits, b.digits) == 0) && a.thesign == b.thesign)	// 부호가 같고, 절댓값이 일치해야함.
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
		for (i = 0; i < a.length; i++) {
			c.Add(a.digits[i], i + 1);
		}
		for (i = 0; i < b.length; i++) {
			c.Add(b.digits[i], i + 1);
		}

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
	inf_int c,d;
	unsigned int i;

	if (a.thesign != b.thesign) {	// if thesign is different, unify thesign and +
		d = b;
		d.thesign = a.thesign;
		c = a + d;
		return c;
	}
	else {	// if thesign is same, substitute absolute value and decide thesign. always substitute from bigger to smaller number
		if (absLess(a, b)) {
			if (a.thesign) {
				c.thesign = false;
			}
			else {
				c.thesign = true;
			}
			for (i = 0; i < b.length; i++) {
				c.Add(b.digits[i], i + 1);
			}
			for (i = 0; i < a.length; i++) {
				c.Sub(a.digits[i], i + 1);
			}
		}
		else if (strcmp(a.digits, b.digits)) {
			c = inf_int();
		}
		else {
			if (a.thesign) {
				c.thesign = true;
			}
			else {
				c.thesign = false;
			}
			for (i = 0; i < a.length; i++) {
				c.Add(a.digits[i], i + 1);
			}
			for (i = 0; i < b.length; i++) {
				c.Sub(b.digits[i], i + 1);
			}
		}

		return c;
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
	c.length = a.length + b.length;
	c.digits = new char[c.length + 1];
	
	for (unsigned int i = 0; i < a.length; i++) {
		for (unsigned int j = 0; j < b.length; j++) {
			if (c.digits[i + j] != '0') c.digits[i + j] = '0';
			int n = (a.digits[i] - '0') * (b.digits[j] - '0') + c.digits[i + j];
			c.digits[i + j] = n % 10;
			c.digits[i + j + 1] += n / 10;
		}
	}
	for (unsigned int i = 0; i < c.length; i++) {
		c.digits[i] += '0';
	}
	if (c.digits[c.length-1] == '0') {
		c.digits = (char*)realloc(c.digits, c.length);
		c.digits[c.length - 1] = '\0';
		c.length -= 1;
	}
	else {
		c.digits[c.length] = '\0';
	}
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
		this->digits = (char*)realloc(this->digits, index + 1);

		if (this->digits == NULL) {		// 할당 실패 예외처리
			cout << "Memory reallocation failed, the program will terminate." << endl;

			exit(0);
		}

		this->length = index;					// 길이 지정
		this->digits[this->length] = '\0';	// 널문자 삽입
	}

	if (this->digits[index - 1] < '0') {	// 연산 전에 '0'보다 작은 아스키값인 경우 0으로 채움. 쓰여지지 않았던 새로운 자리수일 경우 발생
		this->digits[index - 1] = '0';
	}

	this->digits[index - 1] += num - '0';	// 값 연산


	if (this->digits[index - 1] > '9') {	// 자리올림이 발생할 경우
		this->digits[index - 1] -= 10;	// 현재 자릿수에서 (아스키값) 10을 빼고
		Add('1', index + 1);			// 윗자리에 1을 더한다
	}
}

void inf_int::Sub(const char num, const unsigned int index) {// substitute num at index of a
	// 항상 절대값이 더 큰 것에서 작은 것을 빼므로 피연산자(RHS)의 인덱스가 길이를 넘어갈 일이 없다.

	if (this->digits[index - 1] < '0') {	// 연산 전에 '0'보다 작은 아스키값인 경우 0으로 채움. 쓰여지지 않았던 새로운 자리수일 경우 발생
		this->digits[index - 1] = '0';
	}

	this->digits[index - 1] -= num + '0';	// 값 연산. 0-9의 값의 차를 구하고 베이스 값 '0'을 더한다.


	if (this->digits[index - 1] < '0') {	// 자리내림이 발생할 경우
		this->digits[index - 1] += 10;	// 현재 자릿수에서 (아스키값) 10을 더하고
		Sub('1', index + 1);			// 윗자리에 1을 뺀다
	}

	if (this->digits[index - 1] == '0' && index == this->length) {
		// 가장 큰 자리수의 숫자가 같은 상황에서 뺀 경우
		this->digits = (char*)realloc(this->digits, index);
		if (this->digits == NULL) {		// 할당 실패 예외처리
			cout << "Memory reallocation failed, the program will terminate." << endl;

			exit(0);
		}
		this->length -= 1;
		this->digits[this->length] = '\0';
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
		for (int i = 0; i < a.length; i++)
		{
			if (a.digits[i] > b.digits[i]) {
				return false;
			}
			else {
				continue;
			}
		}
		if (strcmp(a.digits, b.digits)) return false;
		return true;
	}
}